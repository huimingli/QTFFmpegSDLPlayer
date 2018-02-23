#pragma once
#include <QTimer>
#include <QMutex>
 
extern "C" {

#include <libswscale\swscale.h>
#include <libavutil\time.h>
#include <libavformat/avformat.h>
#include <libswresample/swresample.h>
}
class QImage;
class DisplayMediaTimer:public QObject
{
	Q_OBJECT
public:	 
	static DisplayMediaTimer *getInstance() {
		static DisplayMediaTimer displayMediaThread;
		return &displayMediaThread;
	}
	bool isPlaying();//获取播放状态
	void setPlay(bool isPlaying);//设置播放状态
	~DisplayMediaTimer();
	void resetImage(int width,int height);
public slots:
    void synchronizeAudioAndVideo();
private:
	DisplayMediaTimer();
	bool isPlay = false;
	QTimer *timer;//视频定时刷新器
	uchar *buf;
	QImage *img;
	int imageWidth = 800;
	int imageHeight = 600;
	QMutex mutex;
signals:
	void updateFrame(QImage *image);//发送到opengl

};

