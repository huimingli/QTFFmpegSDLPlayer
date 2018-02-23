#include "DisplayMediaTimer.h"
#include "Media.h"
#include <QMutexLocker>
#include "ImageFilter.h"
static const double SYNC_THRESHOLD = 0.01;//同步临界值
static const double NOSYNC_THRESHOLD = 10.0;//非同步临界值

//************************************
// Method:    synchronizeAudioAndVideo
// FullName:  DisplayMediaTimer::synchronizeAudioAndVideo
// Access:    public 
// Returns:   void
// Qualifier:音视频同步设置
//************************************
void DisplayMediaTimer::synchronizeAudioAndVideo()
{		 
 	if (!isPlay) {
		timer->setInterval(20);//还没播放就设置下次检查
		return;
	}
	if (Media::getInstance()->video->getVideoFrameSiez() == 0) {
		timer->setInterval(20);//视频队列没帧就设置下次检查
		return;
	}
	static int lastWidth = imageWidth;
	static int lastHeight = imageHeight;
	static QImage::Format format = img->format();
	if (lastHeight != imageHeight || lastWidth != imageWidth) {//视频宽高发生变化要重置图片
		if (img) {
			delete img;
			img = NULL;
		}
		lastHeight = imageHeight;
		lastWidth = imageWidth;
	}
	
	if (img == NULL)
	{
		if (buf != nullptr) {
			delete buf;
			buf = nullptr;
		}
		if (format == QImage::Format_ARGB32) {			
            buf = new uchar[imageWidth*imageHeight * 4];//彩色视频设置
		    img = new QImage(buf, imageWidth , imageHeight, QImage::Format_ARGB32);
		}
		else {
			buf = new uchar[imageWidth*imageHeight];
			img = new QImage(buf, imageWidth, imageHeight, QImage::Format_Grayscale8);//黑白视频设置
		}
		
	}
	AVFrame * frame;
	frame = Media::getInstance()->video->dequeueFrame();
	
	// 将视频同步到音频上，计算下一帧的延迟时间
	double current_pts = *(double*)frame->opaque;
	double delay = current_pts - Media::getInstance()->video->getFrameLastPts();
	if (delay <= 0 || delay >= 1.0)
		delay = Media::getInstance()->video->getFrameLastDelay();
	Media::getInstance()->video->setFrameLastDelay(delay);
	Media::getInstance()->video->setFrameLastPts(current_pts);
	// 当前显示帧的PTS来计算显示下一帧的延迟
	double ref_clock = Media::getInstance()->audio->getAudioClock();
	double diff = current_pts - ref_clock;// diff < 0 => video slow,diff > 0 => video quick
	double threshold = (delay > SYNC_THRESHOLD) ? delay : SYNC_THRESHOLD;
	if (fabs(diff) < NOSYNC_THRESHOLD) // 不同步
	{
		if (diff <= -threshold) // 慢了，delay设为0
			delay = 0;
		else if (diff >= threshold) // 快了，加倍delay
			delay *= 2;
	}	 
	Media::getInstance()->video->setFrameTimer(Media::getInstance()->video->getFrameTimer() + delay) ;
 
	double actual_delay = Media::getInstance()->video->getFrameTimer() - static_cast<double>(av_gettime()) / 1000000.0;
	if (actual_delay <= 0.010)
		actual_delay = 0.010;
	timer->setInterval(static_cast<int>(actual_delay * 1000 + 0.5));
	AVCodecContext *videoCtx = Media::getInstance()->video->getVideoStream()->codec;
	img = ImageFilter::getInstance()->filterColor(img);//色彩过滤
	uint8_t *data[AV_NUM_DATA_POINTERS] = { 0 };
	data[0] = (uint8_t *)img->bits();
	int linesize[AV_NUM_DATA_POINTERS] = { 0 };
	
	if (img->format() == QImage::Format_Grayscale8) {//灰度视频
		Media::getInstance()->video->swsContext = sws_getCachedContext(Media::getInstance()->video->swsContext, videoCtx->width,
			videoCtx->height,
			videoCtx->pix_fmt,
			imageWidth, imageHeight,
			AV_PIX_FMT_GRAY8,
			SWS_BICUBIC,
			NULL, NULL, NULL
		);
		
		linesize[0] = imageWidth;
	}
	else {//彩色视频
		Media::getInstance()->video->swsContext = sws_getCachedContext(Media::getInstance()->video->swsContext, videoCtx->width,
			videoCtx->height,
			videoCtx->pix_fmt,
			imageWidth, imageHeight,
			AV_PIX_FMT_BGRA,
			SWS_BICUBIC,
			NULL, NULL, NULL
		);

		linesize[0] = imageWidth * 4;
	}
	
	int h = sws_scale(Media::getInstance()->video->swsContext, frame->data, frame->linesize, 0, videoCtx->height,
		data,
		linesize
	);//缩放图片
	img->setColorCount(1);
	img = ImageFilter::getInstance()->filter(img);//视频操作过滤器
	emit updateFrame(img);//发送信号到ui线程播放视频
	av_frame_unref(frame);
	av_frame_free(&frame);
	//mutex.unlock();
}

//************************************
// Method:    DisplayMediaTimer
// FullName:  DisplayMediaTimer::DisplayMediaTimer
// Access:    private 
// Returns:   
// Qualifier:启动视频定时器
//************************************
DisplayMediaTimer::DisplayMediaTimer()
{
	buf = new uchar[imageWidth*imageHeight * 4];
	img = new QImage(buf, imageWidth, imageHeight, QImage::Format_ARGB32);
	timer = new QTimer;
	connect(timer, SIGNAL(timeout()), this, SLOT(synchronizeAudioAndVideo()));
	timer->start(20);
}

//************************************
// Method:    resetImage
// FullName:  DisplayMediaTimer::resetImage
// Access:    public 
// Returns:   void
// Qualifier:重置视频大小，窗体最大化最小化时使用
// Parameter: int width 宽
// Parameter: int height 高
//************************************
void DisplayMediaTimer::resetImage(int width, int height) {	 
	imageWidth = width;
	imageHeight = height;
}


DisplayMediaTimer::~DisplayMediaTimer()
{
	if(img)
	    delete img;
	if(buf)
	    delete buf;
	if(timer)
	    delete timer;
}

//************************************
// Method:    setPlay
// FullName:  DisplayMediaTimer::setPlay
// Access:    public 
// Returns:   void
// Qualifier: 设置播放状态
// Parameter: bool isPlaying
//************************************
void DisplayMediaTimer::setPlay(bool isPlaying)
{
	this->isPlay = isPlaying;
}

//************************************
// Method:    isPlaying
// FullName:  DisplayMediaTimer::isPlaying
// Access:    public 
// Returns:   bool
// Qualifier: 获取播放状态
//************************************
bool DisplayMediaTimer::isPlaying()
{
	return isPlay;
}
