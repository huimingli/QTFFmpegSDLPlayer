#pragma once
#include "Audio.h"
#include "Video.h"
#include <QMutex>
extern "C" {

#include <libavformat\avformat.h>

}
class Media
{
public:
	static Media *getInstance() {
		static Media media;
		return &media;
	}
	~Media();
	Media * config();
	Media * setMediaFile(const char*filename);
	bool checkMediaSizeValid();
	int getVideoStreamIndex();
	int getAudioStreamIndex();
	void enqueueVideoPacket(const AVPacket &packet);
	void enqueueAudioPacket(const AVPacket &packet);
	void startAudioPlay();
	AVFormatContext *getAVFormatContext();
	Video *video;
	Audio *audio;
	void close();
	int totalMs = 0;
	int pts = 0;
private:
	AVFormatContext *pFormatCtx;
    Media();
	const char *filename;
	QMutex mutex;
};

