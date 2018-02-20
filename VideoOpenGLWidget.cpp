#include "VideoOpenGLWidget.h"
#include "Media.h"
#include <QPainter>
VideoOpenGLWidget::VideoOpenGLWidget(QWidget *parent)
	: QOpenGLWidget(parent)
{
	ui.setupUi(this);
}

VideoOpenGLWidget::~VideoOpenGLWidget()
{
}
void VideoOpenGLWidget::setVideoImage() {
	this->update();
}
void VideoOpenGLWidget::paintEvent(QPaintEvent *e)
{
	 
	static QImage *image = NULL;
	static int w = 0;
	static int h = 0;
	if (w != width() || h != height())
	{
		if (image)
		{
			delete image->bits();
			delete image;
			image = NULL;
		}
	}

	if (image == NULL)
	{
		uchar *buf = new uchar[width()*height() * 4];
		image = new QImage(buf, width(), height(), QImage::Format_ARGB32);
	}

	Media::getInstance()->video->toRGB((char*)image->bits(), width(), height());
	QPainter painter;
	painter.begin(this);
	painter.drawImage(QPoint(0, 0), *image);
	painter.end();
	 
}
