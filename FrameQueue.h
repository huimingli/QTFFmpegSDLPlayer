
#pragma once
#include <queue>
#include <QMutex>
#include <QWaitCondition>
extern "C"{

#include <libavcodec\avcodec.h>
#include <libavformat/avformat.h>
}
 
class FrameQueue
{
public:
	static const int capacity = 30;
	FrameQueue();
	bool enQueue(const AVFrame* frame);
	AVFrame * deQueue();	
	int getQueueSize();
	void queueFlush();
private:
    std::queue<AVFrame*> queue;	 
	QMutex mutex;
	QWaitCondition cond;


};

