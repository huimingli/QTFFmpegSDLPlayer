#pragma once
#include "Audio.h"
#include "Video.h"
#include "ReadPacketsThread.h"
extern "C" {

#include <libavformat\avformat.h>

}
class Media
{
public:
	AVFormatContext *pFormatCtx;
	static Media *getInstance() {
		static Media media;
		return &media;
	}
	~Media();
	Media * config();
	Media * setMediaFile(char*filename);
	bool checkMediaSizeValid();
	int getVideoStreamIndex();
	int getAudioStreamIndex();
	void enqueueVideoPacket(const AVPacket packet);
	void enqueueAudioPacket(const AVPacket packet);
	void startReadPackets();
	void startReadVideoFrame();Video *video;
private:
	ReadPacketsThread *readPacketsThread;
    Media();
	char *filename;
	Audio *audio;
	
};

