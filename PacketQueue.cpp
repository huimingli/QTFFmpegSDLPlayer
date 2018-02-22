#include "PacketQueue.h"
#include <iostream>
static bool isExit = false;
PacketQueue::PacketQueue()
{
	size = 0;
}

PacketQueue::~PacketQueue() {
	mutex.lock();
	isExit = true;	 
	mutex.unlock();
}

bool PacketQueue::enQueue(const AVPacket packet)
{
	mutex.lock();
	queue.push(packet);
	size += packet.size;
	cond.wakeOne();
	mutex.unlock();
	return true;
}

AVPacket PacketQueue::deQueue()
{
	bool ret = false;
	AVPacket pkt;
	
	if (isExit) {
		
		return pkt;
	}
	mutex.lock();
	 
	while (true)
	{
		if (!queue.empty())
		{
			pkt = queue.front();
			queue.pop();
			size -= pkt.size;		 			
			ret = true;
			break;
		}	 
		else
		{			
			cond.wait(&mutex);
		} 
	}
	mutex.unlock();
	return pkt;
}

Uint32 PacketQueue::getPacketSize()
{
	return size;
}

void PacketQueue::queueFlush() {
	 while (!queue.empty())
	 {	
		 AVPacket pkt = deQueue();
		 av_free_packet(&pkt);		
	 }
}