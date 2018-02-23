#include "Media.h"
#include "ReadPacketsThread.h"
#include "DisplayMediaTimer.h"
extern "C" {
#include <libavutil/time.h>
}

const static long long  MAX_AUDIOQ_SIZE = (5 * 16 * 1024);
const static long long   MAX_VIDEOQ_SIZE = (5 * 256 * 1024);
static double r2d(AVRational r)
{
	return r.num == 0 || r.den == 0 ? 0. : (double)r.num / (double)r.den;
}
Media::Media()
{
	av_register_all();
	pFormatCtx = nullptr;
	audio = new Audio;
	video = new Video;
}
Media *  Media::config() {
	// Open input file
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

 
	av_dump_format(pFormatCtx, 0, filename, 0);
	totalMs = ((pFormatCtx->duration / AV_TIME_BASE) * 1000);
	video->setStreamIndex(-1);
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

	// Fill audio state
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

	// Fill video state
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

	video->setFrameTimer(static_cast<double>(av_gettime()) / 1000000.0);
	video->setFrameLastDelay(40e-3) ;//¼ÆËãÊ±¼ä£¬TODO*/
	audio->audioPlay();
	ReadPacketsThread::getInstance()->setPlaying(true);
	DisplayMediaTimer::getInstance()->setPlay(true);
	return this;
}

Media * Media::setMediaFile(const char * filename)
{
	this->filename = filename;
	return this;
}

bool Media::checkMediaSizeValid()
{
	if (this->audio == nullptr || this->video == nullptr) {
		return true;
	}
	Uint32 audioSize = this->audio->getAudioQueueSize();
	Uint32 videoSize = this->video->getVideoQueueSize();
	return (audioSize> MAX_AUDIOQ_SIZE || videoSize> MAX_VIDEOQ_SIZE);
}

int Media::getVideoStreamIndex()
{
	return video->getStreamIndex();
}

int Media::getAudioStreamIndex()
{
	return audio->getStreamIndex();
}

void Media::enqueueVideoPacket(const AVPacket &packet)
{	
	video->enqueuePacket(packet);
}

void Media::enqueueAudioPacket(const AVPacket &packet)
{
	audio->enqueuePacket(packet);
}

void Media::startAudioPlay()
{
	audio->audioPlay();
}

AVFormatContext * Media::getAVFormatContext()
{
	QMutexLocker locker(&mutex);
	AVFormatContext * p = pFormatCtx;	
	return p;
}

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
		video = nullptr;
	}
		 
}
