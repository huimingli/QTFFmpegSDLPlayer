#pragma once

#include <QtWidgets/QWidget>
#include "ui_QTPlayer.h"
 
class QTPlayer : public QWidget
{
	Q_OBJECT

public:
	QTPlayer(QWidget *parent = Q_NULLPTR);
public slots:
    void openVideoFile();
	void timerEvent(QTimerEvent *e);
	void sliderPress();
	void sliderRelease();
signals:
	void sendPos(float pos);
private:
	Ui::QTPlayerClass ui;
};
