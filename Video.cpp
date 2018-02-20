#include "Video.h"



Video::Video()
{
}


Video::~Video()
{
}

int Video::getStreamIndex()
{
	return streamIndex;
}

void Video::setStreamIndex(const int streamIndex)
{
	this->streamIndex = streamIndex;
}