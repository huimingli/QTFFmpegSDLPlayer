
#include "FrameQueue.h"
#include <QMutexLocker>
FrameQueue::FrameQueue()
{	 
}

bool FrameQueue::enQueue(const AVFrame* frame)
{
	AVFrame* p = av_frame_alloc();

	int ret = av_frame_ref(p, frame);
	if (ret < 0)
		return false;
	p->opaque = (void *)new double(*(double*)p->opaque); //上一个指向的是一个局部的变量，这里重新分配pts空间
	QMutexLocker locker(&mutex);
	queue.push(p);	
	cond.wakeOne();	
	return true;
}

AVFrame * FrameQueue::deQueue()
{
	bool ret = true;
	AVFrame *tmp;
	QMutexLocker locker(&mutex);
	while (true)
	{
		if (!queue.empty())
		{
			tmp = queue.front();
			queue.pop();		
			ret = true;
			break;
		}
		else
		{
			cond.wait(&mutex);		
		}
	}
	
	return tmp;
}

int FrameQueue::getQueueSize()
{
	return queue.size();	
}

void FrameQueue::queueFlush() {
	while (!queue.empty())
	{		
		AVFrame *frame = deQueue();
		av_frame_unref(frame);
	}
}