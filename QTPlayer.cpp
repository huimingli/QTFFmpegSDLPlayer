#include "QTPlayer.h"
#include "DisplayMediaThread.h"
QTPlayer::QTPlayer(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	QObject::connect(DisplayMediaThread::getInstance(),//信号发出的对象
		SIGNAL(updateFrame(QImage)),//信号
		ui.openGLWidget,//槽接收的对象
		SLOT(setVideoImage(QImage))//槽
	);
}
