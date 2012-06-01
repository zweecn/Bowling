/********************************************************************************
** Form generated from reading UI file 'ATM.ui'
**
** Created: Sun Jun 27 12:40:15 2010
**      by: Qt User Interface Compiler version 4.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ATM_H
#define UI_ATM_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
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

class Ui_atm
{
public:
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayout;
    QLabel *atmAvgScoreLabel;
    QLabel *atmAvgScore;
    QLabel *atmHitAllLabel;
    QLabel *atmHitAllCount;
    QLabel *atmCompleteLabel;
    QLabel *atmCompleteCount;
    QHBoxLayout *horizontalLayout;
    QLabel *vipLabel;
    QLineEdit *vipLineEdit;
    QSpacerItem *horizontalSpacer;
    QPushButton *okPushButton;

    void setupUi(QWidget *atm)
    {
        if (atm->objectName().isEmpty())
            atm->setObjectName(QString::fromUtf8("atm"));
        atm->resize(400, 300);
        layoutWidget = new QWidget(atm);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(50, 70, 308, 201));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        atmAvgScoreLabel = new QLabel(layoutWidget);
        atmAvgScoreLabel->setObjectName(QString::fromUtf8("atmAvgScoreLabel"));

        gridLayout->addWidget(atmAvgScoreLabel, 0, 0, 1, 1);

        atmAvgScore = new QLabel(layoutWidget);
        atmAvgScore->setObjectName(QString::fromUtf8("atmAvgScore"));

        gridLayout->addWidget(atmAvgScore, 0, 1, 1, 1);

        atmHitAllLabel = new QLabel(layoutWidget);
        atmHitAllLabel->setObjectName(QString::fromUtf8("atmHitAllLabel"));

        gridLayout->addWidget(atmHitAllLabel, 1, 0, 1, 1);

        atmHitAllCount = new QLabel(layoutWidget);
        atmHitAllCount->setObjectName(QString::fromUtf8("atmHitAllCount"));

        gridLayout->addWidget(atmHitAllCount, 1, 1, 1, 1);

        atmCompleteLabel = new QLabel(layoutWidget);
        atmCompleteLabel->setObjectName(QString::fromUtf8("atmCompleteLabel"));

        gridLayout->addWidget(atmCompleteLabel, 2, 0, 1, 1);

        atmCompleteCount = new QLabel(layoutWidget);
        atmCompleteCount->setObjectName(QString::fromUtf8("atmCompleteCount"));

        gridLayout->addWidget(atmCompleteCount, 2, 1, 1, 1);


        verticalLayout->addLayout(gridLayout);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        vipLabel = new QLabel(layoutWidget);
        vipLabel->setObjectName(QString::fromUtf8("vipLabel"));

        horizontalLayout->addWidget(vipLabel);

        vipLineEdit = new QLineEdit(layoutWidget);
        vipLineEdit->setObjectName(QString::fromUtf8("vipLineEdit"));

        horizontalLayout->addWidget(vipLineEdit);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        okPushButton = new QPushButton(layoutWidget);
        okPushButton->setObjectName(QString::fromUtf8("okPushButton"));

        horizontalLayout->addWidget(okPushButton);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(atm);

        QMetaObject::connectSlotsByName(atm);
    } // setupUi

    void retranslateUi(QWidget *atm)
    {
        atm->setWindowTitle(QApplication::translate("atm", "\345\216\206\345\217\262\350\256\260\345\275\225\350\207\252\345\212\251\346\237\245\350\257\242", 0, QApplication::UnicodeUTF8));
        atmAvgScoreLabel->setText(QApplication::translate("atm", "\346\200\273\345\276\227\345\210\206\357\274\232", 0, QApplication::UnicodeUTF8));
        atmAvgScore->setText(QString());
        atmHitAllLabel->setText(QApplication::translate("atm", "\345\205\250\344\270\255\346\254\241\346\225\260\357\274\232", 0, QApplication::UnicodeUTF8));
        atmHitAllCount->setText(QString());
        atmCompleteLabel->setText(QApplication::translate("atm", "\350\241\245\344\270\255\346\254\241\346\225\260\357\274\232", 0, QApplication::UnicodeUTF8));
        atmCompleteCount->setText(QString());
        vipLabel->setText(QApplication::translate("atm", "VIP\345\217\267\357\274\232", 0, QApplication::UnicodeUTF8));
        okPushButton->setText(QApplication::translate("atm", "\346\237\245\350\257\242", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class atm: public Ui_atm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ATM_H
