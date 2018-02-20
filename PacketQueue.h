
#pragma once

#include <queue>

#include <SDL.h>
#include <QWaitCondition>
#include <QMutex>
extern "C"{

#include <libavcodec\avcodec.h>

}

struct PacketQueue
{
	std::queue<AVPacket> queue;

	Uint32    nb_packets;
	Uint32    size;
	QMutex mutex;
	QWaitCondition cond;

	PacketQueue();
	bool enQueue(const AVPacket *packet);
	bool deQueue(AVPacket *packet, bool block);
};

 