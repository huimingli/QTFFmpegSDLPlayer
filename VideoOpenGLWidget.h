#pragma once

#include <QWidget>
#include <QOpenGLWidget>
#include "ui_VideoOpenGLWidget.h"

class VideoOpenGLWidget : public QOpenGLWidget
{
	Q_OBJECT

public:
	VideoOpenGLWidget(QWidget *parent = Q_NULLPTR);
	~VideoOpenGLWidget();

private:
	Ui::VideoOpenGLWidget ui;
};
