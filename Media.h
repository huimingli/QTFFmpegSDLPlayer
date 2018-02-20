#pragma once
#include "Audio.h"
#include "Video.h"
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
private:
    Media();
	char *filename;
	Audio *audio;
	Video *video;
};

