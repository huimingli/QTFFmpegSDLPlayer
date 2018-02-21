#include "Video.h"
 

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
	return videoPackets->getPacketSize();
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
		if (frameQueue.getQueueSize() >= FrameQueue::capacity) {
            msleep(100);
			continue;
		}
			
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

		frameQueue.enQueue(frame);

		av_frame_unref(frame);
		 
		//updateFrame();
	}
	av_frame_free(&frame);
}
