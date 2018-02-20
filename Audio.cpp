#include "Audio.h"



Audio::Audio()
{
}


Audio::~Audio()
{
}

int Audio::getStreamIndex()
{
	return streamIndex;
}

void Audio::setStreamIndex(const int streamIndex)
{
	this->streamIndex = streamIndex;
}

int Audio::getAudioQueueSize()
{
	return audiaPackets.size;
}

void Audio::enqueuePacket(const AVPacket pkt)
{
	audiaPackets.enQueue(pkt);
}
