#include "VideoOpenGLWidget.h"

VideoOpenGLWidget::VideoOpenGLWidget(QWidget *parent)
	: QOpenGLWidget(parent)
{
	ui.setupUi(this);
}

VideoOpenGLWidget::~VideoOpenGLWidget()
{
}
