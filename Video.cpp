#include "Video.h"
#include "DisplayMediaThread.h"

static bool isExit = false;
Video::Video()
{
	frame_timer = 0.0;
	frame_last_delay = 0.0;
	frame_last_pts = 0.0;
	video_clock = 0.0;
	videoPackets = new PacketQueue;
}


Video::~Video()
{
	/*msleep(1000);*/
	delete videoPackets;
	isExit = true;
	wait();
}

int Video::getStreamIndex()
{
	return streamIndex;
}

void Video::setStreamIndex(const int streamIndex)
{
	this->streamIndex = streamIndex;
}

int Video::getVideoQueueSize()
{
	return videoPackets->size;
}

void Video::enqueuePacket(const AVPacket pkt)
{
	videoPackets->enQueue(pkt);
}

double Video::synchronize(AVFrame *srcFrame, double pts)
{
	double frame_delay;

	if (pts != 0)
		video_clock = pts; // Get pts,then set video clock to it
	else
		pts = video_clock; // Don't get pts,set it to video clock

	frame_delay = av_q2d(stream->codec->time_base);
	frame_delay += srcFrame->repeat_pict * (frame_delay * 0.5);

	video_clock += frame_delay;

	return pts;
}


void Video::run()
{
	 AVFrame * frame = av_frame_alloc();
	double pts;
	AVPacket pkt;
	while (!isExit)
	{
		pkt = videoPackets->deQueue();
		int ret = avcodec_send_packet(videoContext, &pkt);
		if (ret < 0 && ret != AVERROR(EAGAIN) && ret != AVERROR_EOF)
			continue;

		ret = avcodec_receive_frame(videoContext, frame);
		if (ret < 0 && ret != AVERROR_EOF)
			continue;

		if ((pts = av_frame_get_best_effort_timestamp(frame)) == AV_NOPTS_VALUE)
			pts = 0;

		pts *= av_q2d(stream->time_base);

		pts = synchronize(frame, pts);

		frame->opaque = &pts;

		/*if (frameQueue.nb_frames >= FrameQueue::capacity)
			msleep(500 * 2);*/

		frameQueue.enQueue(frame);

		av_frame_unref(frame);
		updateFrame();
	}
	av_frame_free(&frame);
}

bool Video::toRGB(char *out, int outwidth, int outheight)
{
 
	AVFrame * frame = frameQueue.deQueue();
 	AVCodecContext *videoCtx = stream->codec;

	cCtx = sws_getCachedContext(cCtx, videoCtx->width,
		videoCtx->height,
		videoCtx->pix_fmt,
		outwidth, outheight,
		AV_PIX_FMT_BGRA,
		SWS_BICUBIC,
		NULL, NULL, NULL
	);
 
	uint8_t *data[AV_NUM_DATA_POINTERS] = { 0 };
	data[0] = (uint8_t *)out;
	int linesize[AV_NUM_DATA_POINTERS] = { 0 };
	linesize[0] = outwidth * 4;
	int h = sws_scale(cCtx, frame->data, frame->linesize, 0, videoCtx->height,
		data,
		linesize
	);//Ëõ·ÅÍ¼Æ¬
	if (h > 0)
	{
		printf("(%d)", h);
	}
 
	return true;
}