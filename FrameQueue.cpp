
#include "FrameQueue.h"
#include <QMutexLocker>
FrameQueue::FrameQueue()
{	 
}

//************************************
// Method:    enQueue
// FullName:  FrameQueue::enQueue
// Access:    public 
// Returns:   bool
// Qualifier: 帧队列入队
// Parameter: const AVFrame * frame
//************************************
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

//************************************
// Method:    deQueue
// FullName:  FrameQueue::deQueue
// Access:    public 
// Returns:   AVFrame *
// Qualifier:帧队列
//************************************
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

//************************************
// Method:    getQueueSize
// FullName:  FrameQueue::getQueueSize
// Access:    public 
// Returns:   int
// Qualifier:获取队列大小
//************************************
int FrameQueue::getQueueSize()
{
	return queue.size();	
}

//************************************
// Method:    queueFlush
// FullName:  FrameQueue::queueFlush
// Access:    public 
// Returns:   void
// Qualifier:清空帧队列
//************************************
void FrameQueue::queueFlush() {
	while (!queue.empty())
	{		
		AVFrame *frame = deQueue();
		av_frame_unref(frame);
	}
}