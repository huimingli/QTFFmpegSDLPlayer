#pragma once

#include <QtWidgets/QWidget>
#include "ui_QTPlayer.h"
#include <QMenu>
#include <QAction>
#include <QPropertyAnimation>
class QTPlayer : public QWidget
{
	Q_OBJECT

public:
	QTPlayer(QWidget *parent = Q_NULLPTR);
	void resizeEvent(QResizeEvent *e);
	void contextMenuEvent(QContextMenuEvent *event);
	void mirrorLeftAndRight();
	void mirrorUpAndDown();
	void gray2Rgb();
	void rgb2Gray();
	void netAddressInput();
	void openNetAddressVideo(QString address);
	void mouseDoubleClickEvent(QMouseEvent * event);
	void mouseMoveEvent(QMouseEvent *event);
public slots:
    void openVideoFile();
	void timerEvent(QTimerEvent *e);
	void sliderPress();
	void sliderRelease();
	void play();
	void setVolume(int volume);
	
signals:
	void sendPos(float pos);
private:
	QPropertyAnimation *bottomAnimation;
	bool isFullScreen = false;
	void showBottomInAnimation();
	void hideBottomInAnimation();
	QMenu *popMenu;
	QAction *leftRightMirrorAction;
	QAction *upDownMirrorAction;
	QAction *rgbAction;
	QAction *grayAction;
	QAction *netAddressAction;
	Ui::QTPlayerClass ui;
};
