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
#include <QtWidgets/QWidget>
#include "videoopenglwidget.h"

QT_BEGIN_NAMESPACE

class Ui_QTPlayerClass
{
public:
    VideoOpenGLWidget *openGLWidget;

    void setupUi(QWidget *QTPlayerClass)
    {
        if (QTPlayerClass->objectName().isEmpty())
            QTPlayerClass->setObjectName(QStringLiteral("QTPlayerClass"));
        QTPlayerClass->resize(600, 400);
        openGLWidget = new VideoOpenGLWidget(QTPlayerClass);
        openGLWidget->setObjectName(QStringLiteral("openGLWidget"));
        openGLWidget->setGeometry(QRect(0, 0, 800, 600));

        retranslateUi(QTPlayerClass);

        QMetaObject::connectSlotsByName(QTPlayerClass);
    } // setupUi

    void retranslateUi(QWidget *QTPlayerClass)
    {
        QTPlayerClass->setWindowTitle(QApplication::translate("QTPlayerClass", "QTPlayer", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class QTPlayerClass: public Ui_QTPlayerClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTPLAYER_H
