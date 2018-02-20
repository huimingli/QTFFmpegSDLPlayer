
#include "PacketQueue.h"
#include <iostream>

 

PacketQueue::PacketQueue()
{
	nb_packets = 0;
	size       = 0;

 
}

bool PacketQueue::enQueue(const AVPacket *packet)
{
	AVPacket *pkt = av_packet_alloc();
	if (av_packet_ref(pkt, packet) < 0)
		return false;

	mutex.lock();
	queue.push(*pkt);

	size += pkt->size;
	nb_packets++;

	cond.wakeOne();
	mutex.unlock();
	return true;
}

bool PacketQueue::deQueue(AVPacket *packet, bool block)
{
	bool ret = false;

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
			if (av_packet_ref(packet, &queue.front()) < 0)
			{
				ret = false;
				break;
			}
			AVPacket pkt = queue.front();

			queue.pop();
			av_packet_unref(&pkt);
			nb_packets--;
			size -= packet->size;

			ret = true;
			break;
		}
		else if (!block)
		{
			ret = false;
			break;
		}
		else
		{
			cond.wait(&mutex);
		}
	}
	mutex.unlock();
	return ret;
}