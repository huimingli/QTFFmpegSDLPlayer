#pragma once

#include <QtWidgets/QWidget>
#include "ui_QTPlayer.h"

class QTPlayer : public QWidget
{
	Q_OBJECT

public:
	QTPlayer(QWidget *parent = Q_NULLPTR);

private:
	Ui::QTPlayerClass ui;
};
