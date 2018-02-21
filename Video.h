#pragma once
#include "PacketQueue.h"
#include "FrameQueue.h"
#include <QThread>
extern "C" {

#include <libavformat/avformat.h>
#include<libswscale/swscale.h>
#include <libswresample/swresample.h>
}
//extern "C"
//{
//#include<libavformat/avformat.h>
//
//#include <libavutil/time.h>
//}
class Video:public QThread
{
public:
	Video();
	~Video();
	AVStream *stream;
	int getStreamIndex();
	void setStreamIndex(const int streamIndex);
	AVCodecContext *videoContext;
	int getVideoQueueSize();
	void enqueuePacket(const AVPacket pkt);
	void run();
	double synchronize(AVFrame *srcFrame, double pts);

	AVFrame *frame;
	AVFrame *displayFrame;

	double frame_timer;         // Sync fields
	double frame_last_pts;
	double frame_last_delay;
	double video_clock;
	PacketQueue *videoPackets;	
	FrameQueue frameQueue;
	
private:
	SwsContext *cCtx = NULL;
	int streamIndex;
	

};

