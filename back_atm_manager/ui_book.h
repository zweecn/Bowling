/********************************************************************************
** Form generated from reading UI file 'book.ui'
**
** Created: Sun Jun 27 12:40:14 2010
**      by: Qt User Interface Compiler version 4.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BOOK_H
#define UI_BOOK_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDateTimeEdit>
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

class Ui_bookUI
{
public:
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayout;
    QLabel *vipLabel;
    QLineEdit *vipLineEdit;
    QLabel *bookTimeLabel;
    QDateTimeEdit *bookTimeDateTimeEdit;
    QLabel *rowLabel;
    QComboBox *rowComboBox;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *okPushButton;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QWidget *bookUI)
    {
        if (bookUI->objectName().isEmpty())
            bookUI->setObjectName(QString::fromUtf8("bookUI"));
        bookUI->resize(400, 300);
        layoutWidget = new QWidget(bookUI);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(40, 40, 331, 191));
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

        bookTimeDateTimeEdit = new QDateTimeEdit(layoutWidget);
        bookTimeDateTimeEdit->setObjectName(QString::fromUtf8("bookTimeDateTimeEdit"));

        gridLayout->addWidget(bookTimeDateTimeEdit, 1, 1, 1, 1);

        rowLabel = new QLabel(layoutWidget);
        rowLabel->setObjectName(QString::fromUtf8("rowLabel"));

        gridLayout->addWidget(rowLabel, 2, 0, 1, 1);

        rowComboBox = new QComboBox(layoutWidget);
        rowComboBox->setObjectName(QString::fromUtf8("rowComboBox"));

        gridLayout->addWidget(rowComboBox, 2, 1, 1, 1);


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


        retranslateUi(bookUI);

        QMetaObject::connectSlotsByName(bookUI);
    } // setupUi

    void retranslateUi(QWidget *bookUI)
    {
        bookUI->setWindowTitle(QApplication::translate("bookUI", "\351\242\204\347\272\246\347\231\273\350\256\260", 0, QApplication::UnicodeUTF8));
        vipLabel->setText(QApplication::translate("bookUI", "VIP\345\217\267:", 0, QApplication::UnicodeUTF8));
        bookTimeLabel->setText(QApplication::translate("bookUI", "\351\242\204\347\272\246\346\227\266\351\227\264\357\274\232", 0, QApplication::UnicodeUTF8));
        rowLabel->setText(QApplication::translate("bookUI", "\347\220\203\351\201\223\357\274\232", 0, QApplication::UnicodeUTF8));
        okPushButton->setText(QApplication::translate("bookUI", "\347\231\273\350\256\260", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class bookUI: public Ui_bookUI {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BOOK_H
