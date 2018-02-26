#include "Media.h"
#include "ReadPacketsThread.h"
#include "DisplayMediaTimer.h"
extern "C" {
#include <libavutil/time.h>
}

const static long long  MAX_AUDIOQ_SIZE = (5 * 16 * 1024);//最大音频包大小（队列中所有加起来的大小）
const static long long   MAX_VIDEOQ_SIZE = (5 * 256 * 1024);//最大视频包大小（队列中所有视频包加起来的大小）

//************************************
// Method:    r2d
// FullName:  r2d
// Access:    public static 
// Returns:   double
// Qualifier: 时间基准计算
// Parameter: AVRational r
//************************************
static double r2d(AVRational r)
{
	return r.num == 0 || r.den == 0 ? 0. : (double)r.num / (double)r.den;
}

Media::Media()
{
	av_register_all();//注册ffmpeg所有组件
	avformat_network_init();//注册网络组件
	pFormatCtx = nullptr;
	audio = new Audio;
	video = new Video;
}

//************************************
// Method:    config
// FullName:  Media::config
// Access:    public 
// Returns:   Media::Media *
// Qualifier:配置视频
//************************************
Media *  Media::config() {
	close();
	QMutexLocker locker(&mutex);
	char errorbuf[1024] = { 0 };
	int ret = avformat_open_input(&pFormatCtx, filename, 0, 0);
	if (ret < 0) {
		av_strerror(ret, errorbuf, sizeof(errorbuf));
		printf("open %s failed: %s\n", filename, errorbuf);
		return nullptr;
	}

	if (avformat_find_stream_info(pFormatCtx, nullptr) < 0) {
		return nullptr;
	}
	//av_dump_format(pFormatCtx, 0, filename, 0);
	totalMs = ((pFormatCtx->duration / AV_TIME_BASE) * 1000);//计算视频总时长
	video->setStreamIndex(-1);//设置音视频流下标为-1，因为需要多次打开不同音视频
	audio->setStreamIndex(-1);
	for (uint32_t i = 0; i < pFormatCtx->nb_streams; i++)
	{
		if (pFormatCtx->streams[i]->codec->codec_type == AVMEDIA_TYPE_AUDIO && audio->getStreamIndex() < 0)
			audio->setStreamIndex(i);

		if (pFormatCtx->streams[i]->codec->codec_type == AVMEDIA_TYPE_VIDEO && video->getStreamIndex() < 0)
			video->setStreamIndex(i);
	}

	if (audio->getStreamIndex() < 0 || video->getStreamIndex() < 0) {
		return nullptr;
	}

	// 设置音频状态
	AVCodec *pCodec = avcodec_find_decoder(pFormatCtx->streams[audio->getStreamIndex()]->codec->codec_id);
	if (!pCodec) {
		return nullptr;
	}
 
	audio->setStream(pFormatCtx->streams[audio->getStreamIndex()]);

	audio->setAVCodecContext(avcodec_alloc_context3(pCodec));
	
	if (avcodec_copy_context(audio->getAVCodecContext(), pFormatCtx->streams[audio->getStreamIndex()]->codec) != 0) {
		return nullptr;
	}

	avcodec_open2(audio->getAVCodecContext(), pCodec, nullptr);

	// 设置视频状态
	AVCodec *pVCodec = avcodec_find_decoder(pFormatCtx->streams[video->getStreamIndex()]->codec->codec_id);
	if (!pVCodec) {
		return nullptr;
	}

	video->setVideoStream(pFormatCtx->streams[video->getStreamIndex()]);
	 
	video->setAVCodecCotext(avcodec_alloc_context3(pVCodec));
	if (avcodec_copy_context(video->getAVCodecCotext(), pFormatCtx->streams[video->getStreamIndex()]->codec) != 0) {
		return nullptr;
	}
	
	avcodec_open2(video->getAVCodecCotext(), pVCodec, nullptr);

	video->setFrameTimer(static_cast<double>(av_gettime()) / 1000000.0);//设置初始视频帧时间用于音视同步
	video->setFrameLastDelay(40e-3) ;//计算时间，TODO*/
	audio->audioPlay();
	ReadPacketsThread::getInstance()->setPlaying(true);
	DisplayMediaTimer::getInstance()->setPlay(true);
	return this;
}

//************************************
// Method:    setMediaFile
// FullName:  Media::setMediaFile
// Access:    public 
// Returns:   Media::Media *
// Qualifier: 设置视频文件
// Parameter: const char * filename 视频文件名字
//************************************
Media * Media::setMediaFile(const char * filename)
{
	this->filename = filename;
	return this;
}

//************************************
// Method:    checkMediaSizeValid
// FullName:  Media::checkMediaSizeValid
// Access:    public 
// Returns:   bool
// Qualifier: 检查视频大小是否合法
//************************************
bool Media::checkMediaSizeValid()
{
	if (this->audio == nullptr || this->video == nullptr) {
		return true;
	}
	Uint32 audioSize = this->audio->getAudioQueueSize();
	Uint32 videoSize = this->video->getVideoQueueSize();
	return (audioSize> MAX_AUDIOQ_SIZE || videoSize> MAX_VIDEOQ_SIZE);
}

//************************************
// Method:    getVideoStreamIndex
// FullName:  Media::getVideoStreamIndex
// Access:    public 
// Returns:   int
// Qualifier: 获取视频流信息
//************************************
int Media::getVideoStreamIndex()
{
	return video->getStreamIndex();
}

//************************************
// Method:    getAudioStreamIndex
// FullName:  Media::getAudioStreamIndex
// Access:    public 
// Returns:   int
// Qualifier:获取音频流下标
//************************************
int Media::getAudioStreamIndex()
{
	return audio->getStreamIndex();
}

//************************************
// Method:    enqueueVideoPacket
// FullName:  Media::enqueueVideoPacket
// Access:    public 
// Returns:   void
// Qualifier:视频包入队
// Parameter: const AVPacket & packet
//************************************
void Media::enqueueVideoPacket(const AVPacket &packet)
{	
	video->enqueuePacket(packet);
}

//************************************
// Method:    enqueueAudioPacket
// FullName:  Media::enqueueAudioPacket
// Access:    public 
// Returns:   void
// Qualifier:音频包入队
// Parameter: const AVPacket & packet
//************************************
void Media::enqueueAudioPacket(const AVPacket &packet)
{
	audio->enqueuePacket(packet);
}

//************************************
// Method:    startAudioPlay
// FullName:  Media::startAudioPlay
// Access:    public 
// Returns:   void
// Qualifier: 音频开始播放
//************************************
void Media::startAudioPlay()
{
	audio->audioPlay();
}

//************************************
// Method:    getAVFormatContext
// FullName:  Media::getAVFormatContext
// Access:    public 
// Returns:   AVFormatContext *
// Qualifier:获取音视频文件格式上下文
//************************************
AVFormatContext * Media::getAVFormatContext()
{
	QMutexLocker locker(&mutex);
	AVFormatContext * p = pFormatCtx;	
	return p;
}

//************************************
// Method:    close
// FullName:  Media::close
// Access:    public 
// Returns:   void
// Qualifier:关闭，回收资源
//************************************
void Media::close()
{
	QMutexLocker locker(&mutex);
	audio->audioClose();	
	audio->clearPacket();
	video->clearFrames(); 
	video->clearPackets();

	if (pFormatCtx) {
		avformat_close_input(&pFormatCtx);
		pFormatCtx = nullptr;
	}
	 

	if (video->swsContext)
	{
		sws_freeContext(video->swsContext);
		video->swsContext = NULL;
	}
	ReadPacketsThread::getInstance()->setPlaying(false);
	DisplayMediaTimer::getInstance()->setPlay(false);
 
}

Media::~Media()
{
	QMutexLocker locker(&mutex);
	if (audio != nullptr){
		delete audio;
		audio = nullptr;
	}
		
	if (video != nullptr) {
        delete video;	
		//video = nullptr;
	}
		 
}
