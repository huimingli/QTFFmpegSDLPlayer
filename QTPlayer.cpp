#include "QTPlayer.h"
#include "DisplayMediaTimer.h"
#include "TitleBar.h"
#include <QVBoxLayout>
#include<QFileDialog>
#include "menus.h"
#include<QMessageBox>
#include "ImageFilter.h"
#include "Media.h"
#include "ReadPacketsThread.h"
#include <QContextMenuEvent>
static bool isPressSlider = false;
static bool isPlay = false;
QTPlayer::QTPlayer(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
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
	popMenu = new QMenu(this);
	leftRightMirrorAction = new QAction(this);
	upDownMirrorAction = new QAction(this);
	rgbAction = new QAction(this);
	grayAction = new QAction(this);
	leftRightMirrorAction->setText(QString::fromLocal8Bit("左右镜像"));
	upDownMirrorAction->setText(QString::fromLocal8Bit("上下镜像"));
	rgbAction->setText(QString::fromLocal8Bit("彩色"));
	grayAction->setText(QString::fromLocal8Bit("黑白"));
	
	connect(leftRightMirrorAction, &QAction::triggered, this, &QTPlayer::mirrorLeftAndRight);
	connect(upDownMirrorAction, &QAction::triggered, this, &QTPlayer::mirrorUpAndDown);
	connect(rgbAction, &QAction::triggered, this, &QTPlayer::gray2Rgb);
	connect(grayAction, &QAction::triggered, this, &QTPlayer::rgb2Gray);
	 
	startTimer(40);
	ReadPacketsThread *readPacketsThread = ReadPacketsThread::getInstance();
	readPacketsThread->start();

	Media::getInstance()->video->start();
	play();
}

void QTPlayer::contextMenuEvent(QContextMenuEvent *event) {
	popMenu->clear();
	popMenu->addAction(leftRightMirrorAction);
	popMenu->addAction(upDownMirrorAction);
	popMenu->addAction(rgbAction);
	popMenu->addAction(grayAction);

	//菜单出现的位置为当前鼠标的位置
	popMenu->exec(QCursor::pos());
	event->accept();
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
	isPlay = false;
	play();
	float pos = 0;
	pos = (float)ui.volumeSlider->value() / (float)(ui.volumeSlider->maximum() + 1);
	if (Media::getInstance()->getAVFormatContext())
		Media::getInstance()->audio->setVolume(pos*SDL_MIX_MAXVOLUME);
}

void QTPlayer::setVolume(int volume) {
	float pos = 0;
	pos = (float)ui.volumeSlider->value() / (float)(ui.volumeSlider->maximum() + 1);
	if (Media::getInstance()->getAVFormatContext())
	    Media::getInstance()->audio->setVolume(pos*SDL_MIX_MAXVOLUME);
}

void QTPlayer::timerEvent(QTimerEvent * e)
{
	if (Media::getInstance()->totalMs > 0)
	{
		double pts = (double)Media::getInstance()->pts * 1000;
		double total = (double)Media::getInstance()->totalMs;
		double rate = pts / total;
		if (!isPressSlider&&isPlay) {
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

void QTPlayer::play() {
	const QString PAUSE = "QPushButton#playButton{border-image:url(:/QTPlayer/Resources/PauseP.png);}";

	const QString PLAY = "QPushButton#playButton{border-image:url(:/QTPlayer/Resources/PlayP.png);}";
	isPlay = !isPlay;
	DisplayMediaTimer::getInstance()->setPlay(isPlay);
	if (isPlay)
	{
		ui.bottemWidget->setStyleSheet(PAUSE);
		if(Media::getInstance()->getAVFormatContext())
		    Media::getInstance()->audio->audioPlay();
	}
	else
	{
		ui.bottemWidget->setStyleSheet(PLAY);
		if (Media::getInstance()->getAVFormatContext())
		    SDL_CloseAudio();
	}
}

void QTPlayer::mirrorUpAndDown() {
	if (Media::getInstance()->getAVFormatContext() && isPlay)
	    ImageFilter::getInstance()->addTask(XTask{ XTASK_MIRRORUPANDDOWN });
	//ImageFilter::getInstance()->addColorTask(ColorTask{ COLRTASK_GRAY_RGBA });
}

void QTPlayer::mirrorLeftAndRight() {
	if (Media::getInstance()->getAVFormatContext() && isPlay)
	    ImageFilter::getInstance()->addTask(XTask{ XTASK_MIRRORLEFTANDRIGHT });
}

void QTPlayer::gray2Rgb()
{
	if (Media::getInstance()->getAVFormatContext() && isPlay)
	    ImageFilter::getInstance()->addColorTask(ColorTask{ COLRTASK_GRAY_TO_RGBA });
}

void QTPlayer::rgb2Gray()
{
	if (Media::getInstance()->getAVFormatContext()&&isPlay)
	    ImageFilter::getInstance()->addColorTask(ColorTask{ COLRTASK_RGBA_TO_GRAY });
}

void QTPlayer::resizeEvent(QResizeEvent *e) {
	ui.openGLWidget->resize(size());
	ui.bottemWidget->resize(this->width(), ui.bottemWidget->height());
	ui.bottemWidget->move(0,this->height() - ui.bottemWidget->height());

	ui.playButton->move((ui.bottemWidget->width()- ui.playButton->width())/2, (ui.bottemWidget->height() - ui.playButton->height()) / 2);
	ui.openButton->move(ui.playButton->x()+ ui.playButton->width()+30, ui.playButton->y());

	//ui.leftRightButton->move(ui.playButton->x() - ui.leftRightButton->width() - 30, ui.playButton->y());
	//ui.upDownButton->move(ui.leftRightButton->x() - ui.upDownButton->width() - 30, ui.playButton->y());
	ui.volumeSlider->move(this->width()-ui.volumeSlider->width()-25, ui.bottemWidget->height() - ui.volumeSlider->height()-20);
	ui.playslider->move(25, ui.playButton->y()-20);
	ui.playslider->resize(ui.bottemWidget->width() - 50, ui.playslider->height());

	ui.totalLayout->setSpacing(0);
	ui.totalContainer->setLayout(ui.totalLayout);
	ui.totalContainer->move(ui.playslider->x() + ui.playslider->width() - ui.totalContainer->width()-10, ui.playslider->y()+10);

	ui.currentLayout->setSpacing(0);
	ui.currentContainer->setLayout(ui.currentLayout);
	ui.currentContainer->resize(ui.totalContainer->size());
	ui.currentContainer->move(ui.playslider->x()+10, ui.playslider->y() + 10);
	DisplayMediaTimer::getInstance()->resetImage(width(), height());
}