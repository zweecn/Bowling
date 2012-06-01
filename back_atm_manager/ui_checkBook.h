/********************************************************************************
** Form generated from reading UI file 'checkBook.ui'
**
** Created: Sun Jun 27 12:40:14 2010
**      by: Qt User Interface Compiler version 4.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHECKBOOK_H
#define UI_CHECKBOOK_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDateEdit>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_checkBook
{
public:
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayout;
    QLabel *vipLabel;
    QLineEdit *vipLineEdit;
    QLabel *bookTimeLabel;
    QDateEdit *bookTimeDateEdit;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *okPushButton;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QWidget *checkBook)
    {
        if (checkBook->objectName().isEmpty())
            checkBook->setObjectName(QString::fromUtf8("checkBook"));
        checkBook->resize(400, 300);
        layoutWidget = new QWidget(checkBook);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(50, 50, 301, 171));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        vipLabel = new QLabel(layoutWidget);
        vipLabel->setObjectName(QString::fromUtf8("vipLabel"));

        gridLayout->addWidget(vipLabel, 0, 0, 1, 1);

        vipLineEdit = new QLineEdit(layoutWidget);
        vipLineEdit->setObjectName(QString::fromUtf8("vipLineEdit"));

        gridLayout->addWidget(vipLineEdit, 0, 1, 1, 1);

        bookTimeLabel = new QLabel(layoutWidget);
        bookTimeLabel->setObjectName(QString::fromUtf8("bookTimeLabel"));

        gridLayout->addWidget(bookTimeLabel, 1, 0, 1, 1);

        bookTimeDateEdit = new QDateEdit(layoutWidget);
        bookTimeDateEdit->setObjectName(QString::fromUtf8("bookTimeDateEdit"));

        gridLayout->addWidget(bookTimeDateEdit, 1, 1, 1, 1);


        verticalLayout->addLayout(gridLayout);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        okPushButton = new QPushButton(layoutWidget);
        okPushButton->setObjectName(QString::fromUtf8("okPushButton"));

        horizontalLayout->addWidget(okPushButton);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(checkBook);

        QMetaObject::connectSlotsByName(checkBook);
    } // setupUi

    void retranslateUi(QWidget *checkBook)
    {
        checkBook->setWindowTitle(QApplication::translate("checkBook", "\346\237\245\350\257\242\351\242\204\347\272\246", 0, QApplication::UnicodeUTF8));
        vipLabel->setText(QApplication::translate("checkBook", "VIP\345\217\267\357\274\232", 0, QApplication::UnicodeUTF8));
        bookTimeLabel->setText(QApplication::translate("checkBook", "\351\242\204\347\272\246\346\227\266\351\227\264\357\274\232", 0, QApplication::UnicodeUTF8));
        okPushButton->setText(QApplication::translate("checkBook", "\346\237\245\350\257\242", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class checkBook: public Ui_checkBook {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHECKBOOK_H
