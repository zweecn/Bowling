/********************************************************************************
** Form generated from reading UI file 'bowling_front.ui'
**
** Created: Fri Jul 2 23:00:03 2010
**      by: Qt User Interface Compiler version 4.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BOWLING_FRONT_H
#define UI_BOWLING_FRONT_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_bowling_frontClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *bowling_frontClass)
    {
        if (bowling_frontClass->objectName().isEmpty())
            bowling_frontClass->setObjectName(QString::fromUtf8("bowling_frontClass"));
        bowling_frontClass->resize(600, 400);
        menuBar = new QMenuBar(bowling_frontClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        bowling_frontClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(bowling_frontClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        bowling_frontClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(bowling_frontClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        bowling_frontClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(bowling_frontClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        bowling_frontClass->setStatusBar(statusBar);

        retranslateUi(bowling_frontClass);

        QMetaObject::connectSlotsByName(bowling_frontClass);
    } // setupUi

    void retranslateUi(QMainWindow *bowling_frontClass)
    {
        bowling_frontClass->setWindowTitle(QApplication::translate("bowling_frontClass", "bowling_front", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class bowling_frontClass: public Ui_bowling_frontClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BOWLING_FRONT_H
