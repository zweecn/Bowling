/********************************************************************************
** Form generated from reading UI file 'detailRule.ui'
**
** Created: Sun Jun 27 12:40:14 2010
**      by: Qt User Interface Compiler version 4.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DETAILRULE_H
#define UI_DETAILRULE_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDateTimeEdit>
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_busiDetailRule
{
public:
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *okPushButton;
    QSpacerItem *horizontalSpacer_2;
    QWidget *widget1;
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox;
    QWidget *layoutWidget;
    QGridLayout *gridLayout;
    QLabel *morningStartLabel;
    QDateTimeEdit *morningStartDateTimeEdit;
    QLabel *morningEndLabel;
    QDateTimeEdit *morningEndDateTimeEdit;
    QLabel *morningPriceLabel;
    QLineEdit *morningPriceLineEdit;
    QGroupBox *groupBox_2;
    QWidget *layoutWidget1;
    QGridLayout *gridLayout_2;
    QLabel *afternoonStartLabel;
    QDateTimeEdit *afternoonStartDateTimeEdit;
    QLabel *afternoonEndLabel;
    QDateTimeEdit *afternoonEndDateTimeEdit;
    QLabel *afternoonPriceLabel;
    QLineEdit *afternoonPriceLineEdit;
    QGroupBox *groupBox_3;
    QWidget *layoutWidget_3;
    QGridLayout *gridLayout_4;
    QLabel *eveningStartLabel;
    QDateTimeEdit *eveningStartDateTimeEdit;
    QLabel *eveningEndLabel;
    QDateTimeEdit *eveningEndDateTimeEdit;
    QLabel *eveningPriceLabel;
    QLineEdit *eveningPriceLineEdit;

    void setupUi(QDialog *busiDetailRule)
    {
        if (busiDetailRule->objectName().isEmpty())
            busiDetailRule->setObjectName(QString::fromUtf8("busiDetailRule"));
        busiDetailRule->resize(260, 413);
        widget = new QWidget(busiDetailRule);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(10, 380, 241, 25));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        okPushButton = new QPushButton(widget);
        okPushButton->setObjectName(QString::fromUtf8("okPushButton"));

        horizontalLayout->addWidget(okPushButton);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        widget1 = new QWidget(busiDetailRule);
        widget1->setObjectName(QString::fromUtf8("widget1"));
        widget1->setGeometry(QRect(10, 10, 241, 361));
        verticalLayout = new QVBoxLayout(widget1);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        groupBox = new QGroupBox(widget1);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        layoutWidget = new QWidget(groupBox);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(20, 20, 211, 81));
        gridLayout = new QGridLayout(layoutWidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        morningStartLabel = new QLabel(layoutWidget);
        morningStartLabel->setObjectName(QString::fromUtf8("morningStartLabel"));

        gridLayout->addWidget(morningStartLabel, 0, 0, 1, 1);

        morningStartDateTimeEdit = new QDateTimeEdit(layoutWidget);
        morningStartDateTimeEdit->setObjectName(QString::fromUtf8("morningStartDateTimeEdit"));

        gridLayout->addWidget(morningStartDateTimeEdit, 0, 1, 1, 1);

        morningEndLabel = new QLabel(layoutWidget);
        morningEndLabel->setObjectName(QString::fromUtf8("morningEndLabel"));

        gridLayout->addWidget(morningEndLabel, 1, 0, 1, 1);

        morningEndDateTimeEdit = new QDateTimeEdit(layoutWidget);
        morningEndDateTimeEdit->setObjectName(QString::fromUtf8("morningEndDateTimeEdit"));
        morningEndDateTimeEdit->setEnabled(true);
        morningEndDateTimeEdit->setInputMethodHints(Qt::ImhPreferNumbers);

        gridLayout->addWidget(morningEndDateTimeEdit, 1, 1, 1, 1);

        morningPriceLabel = new QLabel(layoutWidget);
        morningPriceLabel->setObjectName(QString::fromUtf8("morningPriceLabel"));

        gridLayout->addWidget(morningPriceLabel, 2, 0, 1, 1);

        morningPriceLineEdit = new QLineEdit(layoutWidget);
        morningPriceLineEdit->setObjectName(QString::fromUtf8("morningPriceLineEdit"));

        gridLayout->addWidget(morningPriceLineEdit, 2, 1, 1, 1);


        verticalLayout->addWidget(groupBox);

        groupBox_2 = new QGroupBox(widget1);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        layoutWidget1 = new QWidget(groupBox_2);
        layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(20, 20, 211, 81));
        gridLayout_2 = new QGridLayout(layoutWidget1);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        afternoonStartLabel = new QLabel(layoutWidget1);
        afternoonStartLabel->setObjectName(QString::fromUtf8("afternoonStartLabel"));

        gridLayout_2->addWidget(afternoonStartLabel, 0, 0, 1, 1);

        afternoonStartDateTimeEdit = new QDateTimeEdit(layoutWidget1);
        afternoonStartDateTimeEdit->setObjectName(QString::fromUtf8("afternoonStartDateTimeEdit"));

        gridLayout_2->addWidget(afternoonStartDateTimeEdit, 0, 1, 1, 1);

        afternoonEndLabel = new QLabel(layoutWidget1);
        afternoonEndLabel->setObjectName(QString::fromUtf8("afternoonEndLabel"));

        gridLayout_2->addWidget(afternoonEndLabel, 1, 0, 1, 1);

        afternoonEndDateTimeEdit = new QDateTimeEdit(layoutWidget1);
        afternoonEndDateTimeEdit->setObjectName(QString::fromUtf8("afternoonEndDateTimeEdit"));
        afternoonEndDateTimeEdit->setEnabled(true);
        afternoonEndDateTimeEdit->setInputMethodHints(Qt::ImhPreferNumbers);

        gridLayout_2->addWidget(afternoonEndDateTimeEdit, 1, 1, 1, 1);

        afternoonPriceLabel = new QLabel(layoutWidget1);
        afternoonPriceLabel->setObjectName(QString::fromUtf8("afternoonPriceLabel"));

        gridLayout_2->addWidget(afternoonPriceLabel, 2, 0, 1, 1);

        afternoonPriceLineEdit = new QLineEdit(layoutWidget1);
        afternoonPriceLineEdit->setObjectName(QString::fromUtf8("afternoonPriceLineEdit"));

        gridLayout_2->addWidget(afternoonPriceLineEdit, 2, 1, 1, 1);


        verticalLayout->addWidget(groupBox_2);

        groupBox_3 = new QGroupBox(widget1);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        layoutWidget_3 = new QWidget(groupBox_3);
        layoutWidget_3->setObjectName(QString::fromUtf8("layoutWidget_3"));
        layoutWidget_3->setGeometry(QRect(20, 20, 211, 81));
        gridLayout_4 = new QGridLayout(layoutWidget_3);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        gridLayout_4->setContentsMargins(0, 0, 0, 0);
        eveningStartLabel = new QLabel(layoutWidget_3);
        eveningStartLabel->setObjectName(QString::fromUtf8("eveningStartLabel"));

        gridLayout_4->addWidget(eveningStartLabel, 0, 0, 1, 1);

        eveningStartDateTimeEdit = new QDateTimeEdit(layoutWidget_3);
        eveningStartDateTimeEdit->setObjectName(QString::fromUtf8("eveningStartDateTimeEdit"));

        gridLayout_4->addWidget(eveningStartDateTimeEdit, 0, 1, 1, 1);

        eveningEndLabel = new QLabel(layoutWidget_3);
        eveningEndLabel->setObjectName(QString::fromUtf8("eveningEndLabel"));

        gridLayout_4->addWidget(eveningEndLabel, 1, 0, 1, 1);

        eveningEndDateTimeEdit = new QDateTimeEdit(layoutWidget_3);
        eveningEndDateTimeEdit->setObjectName(QString::fromUtf8("eveningEndDateTimeEdit"));
        eveningEndDateTimeEdit->setEnabled(true);
        eveningEndDateTimeEdit->setInputMethodHints(Qt::ImhPreferNumbers);

        gridLayout_4->addWidget(eveningEndDateTimeEdit, 1, 1, 1, 1);

        eveningPriceLabel = new QLabel(layoutWidget_3);
        eveningPriceLabel->setObjectName(QString::fromUtf8("eveningPriceLabel"));

        gridLayout_4->addWidget(eveningPriceLabel, 2, 0, 1, 1);

        eveningPriceLineEdit = new QLineEdit(layoutWidget_3);
        eveningPriceLineEdit->setObjectName(QString::fromUtf8("eveningPriceLineEdit"));

        gridLayout_4->addWidget(eveningPriceLineEdit, 2, 1, 1, 1);


        verticalLayout->addWidget(groupBox_3);


        retranslateUi(busiDetailRule);

        QMetaObject::connectSlotsByName(busiDetailRule);
    } // setupUi

    void retranslateUi(QDialog *busiDetailRule)
    {
        busiDetailRule->setWindowTitle(QApplication::translate("busiDetailRule", "Dialog", 0, QApplication::UnicodeUTF8));
        okPushButton->setText(QApplication::translate("busiDetailRule", "\347\241\256\345\256\232", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("busiDetailRule", "\344\270\212\345\215\210\345\234\272", 0, QApplication::UnicodeUTF8));
        morningStartLabel->setText(QApplication::translate("busiDetailRule", "\350\265\267\345\247\213\346\227\266\351\227\264\357\274\232", 0, QApplication::UnicodeUTF8));
        morningStartDateTimeEdit->setDisplayFormat(QApplication::translate("busiDetailRule", "HH:mm:ss", 0, QApplication::UnicodeUTF8));
        morningEndLabel->setText(QApplication::translate("busiDetailRule", "\347\273\223\346\235\237\346\227\266\351\227\264\357\274\232", 0, QApplication::UnicodeUTF8));
        morningEndDateTimeEdit->setDisplayFormat(QApplication::translate("busiDetailRule", "HH:mm:ss", 0, QApplication::UnicodeUTF8));
        morningPriceLabel->setText(QApplication::translate("busiDetailRule", "\345\215\225\345\261\200\346\224\266\350\264\271\357\274\232", 0, QApplication::UnicodeUTF8));
        groupBox_2->setTitle(QApplication::translate("busiDetailRule", "\344\270\213\345\215\210\345\234\272", 0, QApplication::UnicodeUTF8));
        afternoonStartLabel->setText(QApplication::translate("busiDetailRule", "\350\265\267\345\247\213\346\227\266\351\227\264\357\274\232", 0, QApplication::UnicodeUTF8));
        afternoonStartDateTimeEdit->setDisplayFormat(QApplication::translate("busiDetailRule", "HH:mm:ss", 0, QApplication::UnicodeUTF8));
        afternoonEndLabel->setText(QApplication::translate("busiDetailRule", "\347\273\223\346\235\237\346\227\266\351\227\264\357\274\232", 0, QApplication::UnicodeUTF8));
        afternoonEndDateTimeEdit->setDisplayFormat(QApplication::translate("busiDetailRule", "HH:mm:ss", 0, QApplication::UnicodeUTF8));
        afternoonPriceLabel->setText(QApplication::translate("busiDetailRule", "\345\215\225\345\261\200\346\224\266\350\264\271\357\274\232", 0, QApplication::UnicodeUTF8));
        groupBox_3->setTitle(QApplication::translate("busiDetailRule", "\346\231\232\351\227\264\345\234\272", 0, QApplication::UnicodeUTF8));
        eveningStartLabel->setText(QApplication::translate("busiDetailRule", "\350\265\267\345\247\213\346\227\266\351\227\264\357\274\232", 0, QApplication::UnicodeUTF8));
        eveningStartDateTimeEdit->setDisplayFormat(QApplication::translate("busiDetailRule", "HH:mm:ss", 0, QApplication::UnicodeUTF8));
        eveningEndLabel->setText(QApplication::translate("busiDetailRule", "\347\273\223\346\235\237\346\227\266\351\227\264\357\274\232", 0, QApplication::UnicodeUTF8));
        eveningEndDateTimeEdit->setDisplayFormat(QApplication::translate("busiDetailRule", "HH:mm:ss", 0, QApplication::UnicodeUTF8));
        eveningPriceLabel->setText(QApplication::translate("busiDetailRule", "\345\215\225\345\261\200\346\224\266\350\264\271\357\274\232", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class busiDetailRule: public Ui_busiDetailRule {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DETAILRULE_H
