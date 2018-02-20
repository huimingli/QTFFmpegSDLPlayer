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
