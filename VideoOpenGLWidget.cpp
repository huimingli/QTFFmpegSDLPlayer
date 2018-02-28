#include "VideoOpenGLWidget.h"
#include "Media.h"
#include <QPainter>
#include "ReadPacketsThread.h"
#include <QMatrix>

static QImage* image;
VideoOpenGLWidget::VideoOpenGLWidget(QWidget *parent)
	: QOpenGLWidget(parent)
{
	ui.setupUi(this);

}

VideoOpenGLWidget::~VideoOpenGLWidget()
{
}

//************************************
// Method:    setVideoImage
// FullName:  VideoOpenGLWidget::setVideoImage
// Access:    public 
// Returns:   void
// Qualifier: 槽，调用更新函数
// Parameter: QImage * img
//************************************
void VideoOpenGLWidget::setVideoImage(QImage* img) {
	if (ReadPacketsThread::getInstance()->getIsPlaying()) {
		image = img;	 
		this->update();
	}
}

//************************************
// Method:    paintEvent
// FullName:  VideoOpenGLWidget::paintEvent
// Access:    public 
// Returns:   void
// Qualifier: 更新画面
// Parameter: QPaintEvent * e
//************************************
void VideoOpenGLWidget::paintEvent(QPaintEvent *e)
{
	if (image == nullptr)
		return;

	QPainter painter;
	painter.begin(this);
	painter.drawImage(QPoint(0, 0), *image);
	painter.end(); 
}
