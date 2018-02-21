
#include "PacketQueue.h"
#include <iostream>

 

PacketQueue::PacketQueue()
{
	nb_packets = 0;
	size       = 0;

 
}

bool PacketQueue::enQueue(const AVPacket packet)
{
	mutex.lock();
	queue.push(packet);

	size += packet.size;
	nb_packets++;

	cond.wakeOne();
	mutex.unlock();
	return true;
}

AVPacket PacketQueue::deQueue()
{
	bool ret = false;
	AVPacket pkt;
	mutex.lock();
	 
	while (true)
	{
		/*if (quit)
		{
			ret = false;
			break;
		}*/

		if (!queue.empty())
		{
			pkt = queue.front();

			queue.pop();
			size -= pkt.size;
		 
			nb_packets--;
			

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
