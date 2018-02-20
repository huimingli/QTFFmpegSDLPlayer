#include "QTPlayer.h"
#include "Media.h"
QTPlayer::QTPlayer(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	QObject::connect(Media::getInstance()->video,//信号发出的对象
		SIGNAL(updateFrame()),//信号
		ui.openGLWidget,//槽接收的对象
		SLOT(setVideoImage())//槽
	);
}
