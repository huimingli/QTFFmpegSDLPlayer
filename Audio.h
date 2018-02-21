#pragma once
#include "PacketQueue.h"
extern "C" {

#include <libavformat/avformat.h>

}
class Audio
{
public:
	Audio();
	~Audio();
	const uint32_t BUFFERSIZE = 192000;// 缓冲区的大小
	double audioClock; // audio clock
	uint8_t *audioBuff;       // 解码后数据的缓冲空间
	uint32_t audioBuffSize;  // buffer中的字节数
	uint32_t audioBuffIndex; // buffer中未发送数据的index
							   /**
							   * audio play
							   */
	bool audioPlay();

	// get audio clock
	double get_audio_clock();

	int getStreamIndex();
	void setStreamIndex(const int streamIndex);
	AVCodecContext *audioContext;
	AVStream *stream;
	int getAudioQueueSize();
	void enqueuePacket(const AVPacket pkt);
	PacketQueue audiaPackets;
private:
	int streamIndex;

};
/**
* 向设备发送audio数据的回调函数
*/
void audioCallback(void* userdata, Uint8 *stream, int len);

/**
* 解码Avpacket中的数据填充到缓冲空间
*/
int audioDecodeFrame(Audio*audio, uint8_t *audioBuffer, int bufferSize);
