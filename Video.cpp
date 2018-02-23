#include "Video.h"
#include <QMutexLocker>
static bool isExit = false;
Video::Video()
{
	frameTimer = 0.0;
	frameLastDelay = 0.0;
	frameLastPts = 0.0;
	videoClock = 0.0;
	videoPackets = new PacketQueue;
}


Video::~Video()
{
	QMutexLocker locker(&mutex);
	delete videoPackets;
	isExit = true;
	locker.unlock();
	wait();
	
}

//************************************
// Method:    getStreamIndex
// FullName:  Video::getStreamIndex
// Access:    public 
// Returns:   int
// Qualifier: 获取流下标
//************************************
int Video::getStreamIndex()
{
	return streamIndex;
}

//************************************
// Method:    setStreamIndex
// FullName:  Video::setStreamIndex
// Access:    public 
// Returns:   void
// Qualifier:设置流下标
// Parameter: const int & streamIndex
//************************************
void Video::setStreamIndex(const int &streamIndex)
{
	this->streamIndex = streamIndex;
}

//************************************
// Method:    getVideoQueueSize
// FullName:  Video::getVideoQueueSize
// Access:    public 
// Returns:   int
// Qualifier:获取视频队列大小
//************************************
int Video::getVideoQueueSize()
{
	return videoPackets->getPacketSize();
}

//************************************
// Method:    enqueuePacket
// FullName:  Video::enqueuePacket
// Access:    public 
// Returns:   void
// Qualifier: 包入队
// Parameter: const AVPacket & pkt
//************************************
void Video::enqueuePacket(const AVPacket &pkt)
{
	videoPackets->enQueue(pkt);
}

//************************************
// Method:    dequeueFrame
// FullName:  Video::dequeueFrame
// Access:    public 
// Returns:   AVFrame *
// Qualifier: 帧队列出队
//************************************
AVFrame * Video::dequeueFrame()
{
	return frameQueue.deQueue();
}

//************************************
// Method:    synchronizeVideo
// FullName:  Video::synchronizeVideo
// Access:    public 
// Returns:   double
// Qualifier: 计算同步视频的播放时间
// Parameter: AVFrame * & srcFrame
// Parameter: double & pts
//************************************
double Video::synchronizeVideo(AVFrame *&srcFrame, double &pts)
{
	double frameDelay;
	if (pts != 0)
		videoClock = pts; // Get pts,then set video clock to it
	else
		pts = videoClock; // Don't get pts,set it to video clock
	frameDelay = av_q2d(stream->codec->time_base);
	frameDelay += srcFrame->repeat_pict * (frameDelay * 0.5);
	videoClock += frameDelay;
	return pts;
}

//************************************
// Method:    getVideoStream
// FullName:  Video::getVideoStream
// Access:    public 
// Returns:   AVStream *
// Qualifier: 获取视频流
//************************************
AVStream * Video::getVideoStream()
{
	return stream;
}

//************************************
// Method:    setVideoStream
// FullName:  Video::setVideoStream
// Access:    public 
// Returns:   void
// Qualifier:设置视频流
// Parameter: AVStream * & videoStream
//************************************
void Video::setVideoStream(AVStream *& videoStream)
{
	this->stream = videoStream;
}

//************************************
// Method:    getAVCodecCotext
// FullName:  Video::getAVCodecCotext
// Access:    public 
// Returns:   AVCodecContext *
// Qualifier:获取视频解码器上下文
//************************************
AVCodecContext * Video::getAVCodecCotext()
{
	return this->videoContext;
}

//************************************
// Method:    setAVCodecCotext
// FullName:  Video::setAVCodecCotext
// Access:    public 
// Returns:   void
// Qualifier:设置视频解码器上下文
// Parameter: AVCodecContext * avCodecContext
//************************************
void Video::setAVCodecCotext(AVCodecContext * avCodecContext)
{
	this->videoContext = avCodecContext;
}

//************************************
// Method:    setFrameTimer
// FullName:  Video::setFrameTimer
// Access:    public 
// Returns:   void
// Qualifier:设置帧时间
// Parameter: const double & frameTimer
//************************************
void Video::setFrameTimer(const double & frameTimer)
{
	this->frameTimer = frameTimer;
}


//************************************
// Method:    run
// FullName:  Video::run
// Access:    public 
// Returns:   void
// Qualifier:视频读帧线程处理函数
//************************************
void Video::run()
{
	 AVFrame * frame = av_frame_alloc();
	double pts;
	AVPacket pkt;
	while (!isExit)
	{
		QMutexLocker locker(&mutex);
		if (frameQueue.getQueueSize() >= FrameQueue::capacity) {//视频帧多于30帧就等待消费
			locker.unlock();
            msleep(100);
			continue;
		}			
		if (videoPackets->getPacketSize() == 0) {//没帧等待帧入队
			locker.unlock();
			msleep(100);
			continue;
		}
		pkt = videoPackets->deQueue();//出队
		int ret = avcodec_send_packet(videoContext, &pkt);
		if (ret < 0 && ret != AVERROR(EAGAIN) && ret != AVERROR_EOF) {
			continue;
		}
			
		ret = avcodec_receive_frame(videoContext, frame);
		if (ret < 0 && ret != AVERROR_EOF) {
			continue;
		}
			
		if ((pts = av_frame_get_best_effort_timestamp(frame)) == AV_NOPTS_VALUE)
			pts = 0;
		pts *= av_q2d(stream->time_base);
		pts = synchronizeVideo(frame, pts);//同步视频播放时间
		frame->opaque = &pts;	
		frameQueue.enQueue(frame);//帧入队
		av_frame_unref(frame);
	}
	av_frame_free(&frame);
}

//************************************
// Method:    getFrameTimer
// FullName:  Video::getFrameTimer
// Access:    public 
// Returns:   double
// Qualifier:获取帧时间
//************************************
double Video::getFrameTimer()
{
	return frameTimer;
}

//************************************
// Method:    setFrameLastPts
// FullName:  Video::setFrameLastPts
// Access:    public 
// Returns:   void
// Qualifier:获取上一帧的播放时间
// Parameter: const double & frameLastPts
//************************************
void Video::setFrameLastPts(const double & frameLastPts)
{
	this->frameLastPts = frameLastPts;
}

//************************************
// Method:    getFrameLastPts
// FullName:  Video::getFrameLastPts
// Access:    public 
// Returns:   double
// Qualifier:获取上一帧的播放时间
//************************************
double Video::getFrameLastPts()
{
	return frameLastPts;
}

//************************************
// Method:    setFrameLastDelay
// FullName:  Video::setFrameLastDelay
// Access:    public 
// Returns:   void
// Qualifier:设置上一帧的延时
// Parameter: const double & frameLastDelay
//************************************
void Video::setFrameLastDelay(const double & frameLastDelay)
{
	this->frameLastDelay = frameLastDelay;
}

//************************************
// Method:    getFrameLastDelay
// FullName:  Video::getFrameLastDelay
// Access:    public 
// Returns:   double
// Qualifier:获取上一帧延时
//************************************
double Video::getFrameLastDelay()
{
	return frameLastDelay;
}

//************************************
// Method:    setVideoClock
// FullName:  Video::setVideoClock
// Access:    public 
// Returns:   void
// Qualifier:设置视频时钟
// Parameter: const double & videoClock
//************************************
void Video::setVideoClock(const double & videoClock)
{
	this->videoClock = videoClock;
}

//************************************
// Method:    getVideoClock
// FullName:  Video::getVideoClock
// Access:    public 
// Returns:   double
// Qualifier:获取视频时钟
//************************************
double Video::getVideoClock()
{
	return videoClock;
}

//************************************
// Method:    getVideoFrameSiez
// FullName:  Video::getVideoFrameSiez
// Access:    public 
// Returns:   int
// Qualifier:获取帧大小
//************************************
int Video::getVideoFrameSiez()
{
	return frameQueue.getQueueSize();
}

//************************************
// Method:    clearFrames
// FullName:  Video::clearFrames
// Access:    public 
// Returns:   void
// Qualifier:清空帧队列
//************************************
void Video::clearFrames()
{
	frameQueue.queueFlush();
}

//************************************
// Method:    clearPackets
// FullName:  Video::clearPackets
// Access:    public 
// Returns:   void
// Qualifier:清空包队列
//************************************
void Video::clearPackets()
{
	videoPackets->queueFlush();
}
