
#pragma once
#include <queue>
#include <QMutex>
#include <QWaitCondition>
extern "C"{

#include <libavcodec\avcodec.h>
#include <libavformat/avformat.h>
}
 
struct FrameQueue
{
	static const int capacity = 30;

	std::queue<AVFrame*> queue;

	uint32_t nb_frames;

	QMutex mutex;
	QWaitCondition cond;

	FrameQueue();
	bool enQueue(const AVFrame* frame);
	bool deQueue(AVFrame **frame);
};

