#include "Media.h"



const static long long  MAX_AUDIOQ_SIZE = (5 * 16 * 1024);
const static long long   MAX_VIDEOQ_SIZE = (5 * 256 * 1024);
Media::Media()
{
	av_register_all();
	pFormatCtx = nullptr;
	audio = new Audio;
	video = new Video;
	readPacketsThread = new ReadPacketsThread;
}
Media *  Media::config() {
	// Open input file
	if (avformat_open_input(&pFormatCtx, filename, nullptr, nullptr) < 0)
		return nullptr;

	if (avformat_find_stream_info(pFormatCtx, nullptr) < 0)
		return nullptr;

	// Output the stream info to standard 
	av_dump_format(pFormatCtx, 0, filename, 0);

	for (uint32_t i = 0; i < pFormatCtx->nb_streams; i++)
	{
		if (pFormatCtx->streams[i]->codec->codec_type == AVMEDIA_TYPE_AUDIO && audio->getStreamIndex() < 0)
			audio->setStreamIndex(i);

		if (pFormatCtx->streams[i]->codec->codec_type == AVMEDIA_TYPE_VIDEO && video->getStreamIndex() < 0)
			video->setStreamIndex(i);
	}

	if (audio->getStreamIndex() < 0 || video->getStreamIndex() < 0)
		return nullptr;

	// Fill audio state
	AVCodec *pCodec = avcodec_find_decoder(pFormatCtx->streams[audio->getStreamIndex()]->codec->codec_id);
	if (!pCodec)
		return nullptr;

	audio->stream = pFormatCtx->streams[audio->getStreamIndex()];

	audio->audioContext = avcodec_alloc_context3(pCodec);
	if (avcodec_copy_context(audio->audioContext, pFormatCtx->streams[audio->getStreamIndex()]->codec) != 0)
		return nullptr;

	avcodec_open2(audio->audioContext, pCodec, nullptr);

	// Fill video state
	AVCodec *pVCodec = avcodec_find_decoder(pFormatCtx->streams[video->getStreamIndex()]->codec->codec_id);
	if (!pVCodec)
		return nullptr;

	video->stream = pFormatCtx->streams[video->getStreamIndex()];

	video->videoContext = avcodec_alloc_context3(pVCodec);
	if (avcodec_copy_context(video->videoContext, pFormatCtx->streams[video->getStreamIndex()]->codec) != 0)
		return nullptr;

	avcodec_open2(video->videoContext, pVCodec, nullptr);

	/*video->frame_timer = static_cast<double>(av_gettime()) / 1000000.0;
	video->frame_last_delay = 40e-3;//¼ÆËãÊ±¼ä£¬TODO*/

	return this;
}

Media * Media::setMediaFile(char * filename)
{
	this->filename = filename;
	return this;
}

bool Media::checkMediaSizeValid()
{
	Uint32 audioSize = this->audio->getAudioQueueSize();
	Uint32 videoSize = this->video->getVideoQueueSize();
	return (audioSize> MAX_AUDIOQ_SIZE || videoSize> MAX_VIDEOQ_SIZE);
}

int Media::getVideoStreamIndex()
{
	return video->getStreamIndex();
}

int Media::getAudioStreamIndex()
{
	return audio->getStreamIndex();
}

void Media::enqueueVideoPacket(const AVPacket packet)
{
	
	video->enqueuePacket(packet);
}

void Media::enqueueAudioPacket(const AVPacket pkt)
{
	audio->enqueuePacket(pkt);
}

void Media::startReadPackets()
{
	readPacketsThread->start();
}

void Media::startReadVideoFrame()
{
	video->start();
}

Media::~Media()
{
	if (audio != nullptr)
		delete audio;

	if (video != nullptr)
		delete video;
	if (readPacketsThread != nullptr)
		delete readPacketsThread;
}
