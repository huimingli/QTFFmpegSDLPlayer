#pragma once
#include "PacketQueue.h"
extern "C" {

#include <libavformat/avformat.h>

}
class Video
{
public:
	Video();
	~Video();
	AVStream *stream;
	int getStreamIndex();
	void setStreamIndex(const int streamIndex);
	AVCodecContext *videoContext;
private:
	int streamIndex;
	PacketQueue videoPackets;
};

