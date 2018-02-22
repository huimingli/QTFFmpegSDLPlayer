#pragma once

#include <QWidget>
#include <QOpenGLWidget>
#include "ui_VideoOpenGLWidget.h"
#include <QImage>
class VideoOpenGLWidget : public QOpenGLWidget
{
	Q_OBJECT

public:
	VideoOpenGLWidget(QWidget *parent = Q_NULLPTR);
	~VideoOpenGLWidget();
	void paintEvent(QPaintEvent *e);
public slots:
	void setVideoImage(QImage* img);
private:
	Ui::VideoOpenGLWidget ui;
};
