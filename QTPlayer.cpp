#include "QTPlayer.h"
#include "DisplayMediaTimer.h"
#include "TitleBar.h"
#include <QVBoxLayout>
#include<QFileDialog>
#include<QMessageBox>
#include "Media.h"
#include "ReadPacketsThread.h"
static bool isPressSlider = false;
QTPlayer::QTPlayer(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	//this->setWindowFlags(Qt::FramelessWindowHint |
	//	Qt::WindowSystemMenuHint |
	//	Qt::WindowMinMaxButtonsHint);
	this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowMinimizeButtonHint);
	QObject::connect(DisplayMediaTimer::getInstance(),//信号发出的对象
		SIGNAL(updateFrame(QImage*)),//信号
		ui.openGLWidget,//槽接收的对象
		SLOT(setVideoImage(QImage*))//槽
	);
	QObject::connect(this,//信号发出的对象
		SIGNAL(sendPos(float)),//信号
		ReadPacketsThread::getInstance(),//槽接收的对象
		SLOT(receivePos(float))//槽
	);

	 
	installEventFilter(ui.titleBar);
	
	setWindowTitle("Custom Window");
	setWindowIcon(QIcon(":/QTPlayer/Resources/bb.jpg"));
	 
	QVBoxLayout *pLayout = new QVBoxLayout();
	pLayout->addWidget(ui.titleBar);
	pLayout->addStretch();
	pLayout->setSpacing(0);
	pLayout->setContentsMargins(0, 0, 0, 0);
	setLayout(pLayout);
	startTimer(40);
	ReadPacketsThread *readPacketsThread = ReadPacketsThread::getInstance();
	readPacketsThread->start();

	Media::getInstance()->video->start();
}

void QTPlayer::openVideoFile() {
	QString fileName = QFileDialog::getOpenFileName(this, "please select your video file!");
	if (fileName.isEmpty()) {
		return;
	}

	std::string file = fileName.toLocal8Bit().data();//防止有中文
	Media *media = Media::getInstance()
		->setMediaFile(file.c_str())
		->config();
	QStringList titles = fileName.split("/");
	setWindowTitle(titles.constLast());
	int total =Media::getInstance()->totalMs;
	ui.totalHour->setText(QString::number((int)(Media::getInstance()->totalMs / 1000 / 60 / 60)) + ":");
	ui.totalMinute->setText(QString::number((int)(Media::getInstance()->totalMs / 1000 / 60) % 60) + ":");
	ui.totalSecond->setText(QString::number((int)(Media::getInstance()->totalMs / 1000) % 60 % 60));
}

void QTPlayer::timerEvent(QTimerEvent * e)
{
	if (Media::getInstance()->totalMs > 0)
	{
		double pts = (double)Media::getInstance()->pts * 1000;
		double total = (double)Media::getInstance()->totalMs;
		double rate = pts / total;
		if (!isPressSlider) {
            ui.playslider->setValue(rate);
		    ui.currentHour->setText(QString::number((int)(pts / 1000000 / 60 / 60))+":");
		    ui.currentMinute->setText(QString::number((int)(pts / 1000000 / 60) % 60) + ":");
	     	ui.currentSecond->setText(QString::number((int)(pts / 1000000) % 60 % 60));
		}
			
	}
}

void QTPlayer::sliderPress()
{
	isPressSlider = true;
}

void QTPlayer::sliderRelease()
{
	isPressSlider = false;
	float pos = 0;
	pos = (float)ui.playslider->value() / (float)(ui.playslider->maximum() + 1);
	sendPos(pos);
}

