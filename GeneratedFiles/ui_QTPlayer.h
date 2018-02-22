/********************************************************************************
** Form generated from reading UI file 'QTPlayer.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QTPLAYER_H
#define UI_QTPLAYER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QWidget>
#include "titlebar.h"
#include "videoopenglwidget.h"

QT_BEGIN_NAMESPACE

class Ui_QTPlayerClass
{
public:
    VideoOpenGLWidget *openGLWidget;
    QWidget *bottemWidget;
    QSlider *playslider;
    QPushButton *pauseButton;
    QPushButton *playButton;
    QLabel *currentHour;
    QLabel *currentMinute;
    QLabel *currentSecond;
    QLabel *totalHour;
    QLabel *totalMinute;
    QLabel *totalSecond;
    TitleBar *titleBar;
    QPushButton *openButton;

    void setupUi(QWidget *QTPlayerClass)
    {
        if (QTPlayerClass->objectName().isEmpty())
            QTPlayerClass->setObjectName(QStringLiteral("QTPlayerClass"));
        QTPlayerClass->resize(800, 600);
        QTPlayerClass->setStyleSheet(QString::fromUtf8("QPushButton:!hover\n"
"{\n"
"    background-color: qlineargradient(spread:pad,x1:0,y1:0,x2:0,y2:1,stop:0 rgba(120, 120, 120, 255),stop:0.495      rgba(39, 39, 39, 255),stop:0.505 rgba(39, 39, 39, 255),stop:1 rgba(120, 120, 120, 255));\n"
"    border:none;\n"
"    border-radius:5px;\n"
"	color: rgb(255, 255, 255);\n"
"	font: 75 12pt \"\351\273\221\344\275\223\";\n"
"}\n"
"QPushButton:hover\n"
"{\n"
"    background-color: qlineargradient(spread:pad,x1:0,y1:0,x2:0,y2:1,stop:0 rgba(39, 39, 39, 255),stop:0.495      rgba(120, 120, 120, 255),stop:0.505 rgba(120, 120, 120, 255),stop:1 rgba(39, 39, 39, 255));\n"
"    border:none;\n"
"    border-radius:5px;\n"
"	color: rgb(255, 255, 255);\n"
"	font: 75 12pt \"\351\273\221\344\275\223\";\n"
"}\n"
"#playButton{background-color: rgba(255, 255, 255,0);}\n"
"\n"
"#playButton:hover{image: url(:/QTPlayer/Resources/PlayN.png);}\n"
"\n"
"#playButton:!hover{image: url(:/QTPlayer/Resources/PlayH.png);}\n"
"\n"
"#playButton:pressed{image: url(:/QTPlayer/Resources/PlayP.png);}\n"
"\n"
""
                        "#pauseButton{background-color: rgba(255, 255, 255,0);}\n"
"\n"
"#pauseButton:hover{image: url(:/QTPlayer/Resources/PauseN.png);}\n"
"\n"
"#pauseButton:!hover{image: url(:/QTPlayer/Resources/PauseH.png);}\n"
"\n"
"#pauseButton:pressed{image: url(:/QTPlayer/Resources/PauseP.png);}\n"
"\n"
"#bottemWidget{\n"
"background-color: rgba(0, 0, 0, 122);\n"
"}\n"
"#minimizeButton{\n"
"background-color: rgba(255, 255, 255,0);\n"
"image: url(:/QTPlayer/Resources/PauseP.png);\n"
"}\n"
"#totalHour{\n"
"    color: rgb(255, 255, 255);\n"
"	font: 75 8pt \"\351\273\221\344\275\223\";\n"
"}\n"
"#totalMinute{\n"
"    color: rgb(255, 255, 255);\n"
"	font: 75 8pt \"\351\273\221\344\275\223\";\n"
"}\n"
"#totalSecond{\n"
"    color: rgb(255, 255, 255);\n"
"	font: 75 8pt \"\351\273\221\344\275\223\";\n"
"}\n"
"#currentHour{\n"
"    color: rgb(255, 255, 255);\n"
"	font: 75 8pt \"\351\273\221\344\275\223\";\n"
"}\n"
"#currentMinute{\n"
"    color: rgb(255, 255, 255);\n"
"	font: 75 8pt \"\351\273\221\344\275\223\";\n"
"}\n"
"#currentSecon"
                        "d{\n"
"    color: rgb(255, 255, 255);\n"
"	font: 75 8pt \"\351\273\221\344\275\223\";\n"
"}"));
        openGLWidget = new VideoOpenGLWidget(QTPlayerClass);
        openGLWidget->setObjectName(QStringLiteral("openGLWidget"));
        openGLWidget->setGeometry(QRect(0, 0, 800, 600));
        bottemWidget = new QWidget(QTPlayerClass);
        bottemWidget->setObjectName(QStringLiteral("bottemWidget"));
        bottemWidget->setGeometry(QRect(0, 520, 800, 80));
        playslider = new QSlider(bottemWidget);
        playslider->setObjectName(QStringLiteral("playslider"));
        playslider->setGeometry(QRect(120, 10, 601, 22));
        playslider->setMaximum(999);
        playslider->setOrientation(Qt::Horizontal);
        pauseButton = new QPushButton(bottemWidget);
        pauseButton->setObjectName(QStringLiteral("pauseButton"));
        pauseButton->setGeometry(QRect(390, 40, 31, 28));
        playButton = new QPushButton(bottemWidget);
        playButton->setObjectName(QStringLiteral("playButton"));
        playButton->setGeometry(QRect(430, 40, 31, 28));
        currentHour = new QLabel(bottemWidget);
        currentHour->setObjectName(QStringLiteral("currentHour"));
        currentHour->setGeometry(QRect(110, 40, 16, 20));
        currentMinute = new QLabel(bottemWidget);
        currentMinute->setObjectName(QStringLiteral("currentMinute"));
        currentMinute->setGeometry(QRect(130, 40, 16, 20));
        currentSecond = new QLabel(bottemWidget);
        currentSecond->setObjectName(QStringLiteral("currentSecond"));
        currentSecond->setGeometry(QRect(150, 40, 16, 20));
        totalHour = new QLabel(bottemWidget);
        totalHour->setObjectName(QStringLiteral("totalHour"));
        totalHour->setGeometry(QRect(635, 30, 21, 20));
        totalMinute = new QLabel(bottemWidget);
        totalMinute->setObjectName(QStringLiteral("totalMinute"));
        totalMinute->setGeometry(QRect(650, 30, 16, 20));
        totalSecond = new QLabel(bottemWidget);
        totalSecond->setObjectName(QStringLiteral("totalSecond"));
        totalSecond->setGeometry(QRect(670, 30, 16, 20));
        titleBar = new TitleBar(QTPlayerClass);
        titleBar->setObjectName(QStringLiteral("titleBar"));
        titleBar->setGeometry(QRect(0, 0, 800, 60));
        openButton = new QPushButton(QTPlayerClass);
        openButton->setObjectName(QStringLiteral("openButton"));
        openButton->setGeometry(QRect(360, 260, 93, 28));
        openGLWidget->raise();
        bottemWidget->raise();
        titleBar->raise();
        openButton->raise();
        playslider->raise();

        retranslateUi(QTPlayerClass);
        QObject::connect(openButton, SIGNAL(clicked()), QTPlayerClass, SLOT(openVideoFile()));
        QObject::connect(playslider, SIGNAL(sliderPressed()), QTPlayerClass, SLOT(sliderPress()));
        QObject::connect(playslider, SIGNAL(sliderReleased()), QTPlayerClass, SLOT(sliderRelease()));

        QMetaObject::connectSlotsByName(QTPlayerClass);
    } // setupUi

    void retranslateUi(QWidget *QTPlayerClass)
    {
        QTPlayerClass->setWindowTitle(QApplication::translate("QTPlayerClass", "QTPlayer", Q_NULLPTR));
        pauseButton->setText(QString());
        playButton->setText(QString());
        currentHour->setText(QApplication::translate("QTPlayerClass", "0", Q_NULLPTR));
        currentMinute->setText(QApplication::translate("QTPlayerClass", "0", Q_NULLPTR));
        currentSecond->setText(QApplication::translate("QTPlayerClass", "0", Q_NULLPTR));
        totalHour->setText(QApplication::translate("QTPlayerClass", "0", Q_NULLPTR));
        totalMinute->setText(QApplication::translate("QTPlayerClass", "0", Q_NULLPTR));
        totalSecond->setText(QApplication::translate("QTPlayerClass", "0", Q_NULLPTR));
        openButton->setText(QApplication::translate("QTPlayerClass", "open", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class QTPlayerClass: public Ui_QTPlayerClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTPLAYER_H
