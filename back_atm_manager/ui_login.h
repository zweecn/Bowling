/********************************************************************************
** Form generated from reading UI file 'login.ui'
**
** Created: Mon Jun 28 21:19:33 2010
**      by: Qt User Interface Compiler version 4.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGIN_H
#define UI_LOGIN_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QSpacerItem>

QT_BEGIN_NAMESPACE

class Ui_loginUI
{
public:
    QGridLayout *gridLayout;
    QSpacerItem *verticalSpacer;
    QLabel *rowIdLabel;
    QSpacerItem *horizontalSpacer_8;
    QCheckBox *vipCheckBox;
    QSpacerItem *verticalSpacer_2;
    QRadioButton *countRadioButton;
    QLineEdit *oneTimeLineEdit;
    QLabel *label;
    QLineEdit *countLineEdit;
    QLabel *label_3;
    QSpacerItem *verticalSpacer_3;
    QRadioButton *timeRadioButton;
    QLineEdit *oneHoueLineEdit;
    QLabel *label_2;
    QLineEdit *hoursLineEdit;
    QLabel *label_4;
    QSpacerItem *verticalSpacer_4;
    QLabel *totalLabel;
    QSpacerItem *horizontalSpacer_7;
    QPushButton *okButton;
    QPushButton *cancelButton;
    QLineEdit *vipCardLineEdit;

    void setupUi(QDialog *loginUI)
    {
        if (loginUI->objectName().isEmpty())
            loginUI->setObjectName(QString::fromUtf8("loginUI"));
        loginUI->resize(341, 291);
        gridLayout = new QGridLayout(loginUI);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        verticalSpacer = new QSpacerItem(35, 28, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 0, 3, 1, 1);

        rowIdLabel = new QLabel(loginUI);
        rowIdLabel->setObjectName(QString::fromUtf8("rowIdLabel"));
        QFont font;
        font.setPointSize(12);
        rowIdLabel->setFont(font);

        gridLayout->addWidget(rowIdLabel, 1, 0, 1, 2);

        horizontalSpacer_8 = new QSpacerItem(70, 22, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_8, 1, 2, 1, 1);

        vipCheckBox = new QCheckBox(loginUI);
        vipCheckBox->setObjectName(QString::fromUtf8("vipCheckBox"));
        vipCheckBox->setFont(font);

        gridLayout->addWidget(vipCheckBox, 1, 3, 1, 1);

        verticalSpacer_2 = new QSpacerItem(35, 28, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_2, 2, 3, 1, 1);

        countRadioButton = new QRadioButton(loginUI);
        countRadioButton->setObjectName(QString::fromUtf8("countRadioButton"));
        countRadioButton->setFont(font);

        gridLayout->addWidget(countRadioButton, 3, 0, 1, 2);

        oneTimeLineEdit = new QLineEdit(loginUI);
        oneTimeLineEdit->setObjectName(QString::fromUtf8("oneTimeLineEdit"));
        oneTimeLineEdit->setFont(font);

        gridLayout->addWidget(oneTimeLineEdit, 3, 2, 1, 1);

        label = new QLabel(loginUI);
        label->setObjectName(QString::fromUtf8("label"));
        label->setFont(font);

        gridLayout->addWidget(label, 3, 3, 1, 1);

        countLineEdit = new QLineEdit(loginUI);
        countLineEdit->setObjectName(QString::fromUtf8("countLineEdit"));
        countLineEdit->setFont(font);

        gridLayout->addWidget(countLineEdit, 3, 4, 1, 1);

        label_3 = new QLabel(loginUI);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setFont(font);

        gridLayout->addWidget(label_3, 3, 6, 1, 1);

        verticalSpacer_3 = new QSpacerItem(35, 28, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_3, 4, 3, 1, 1);

        timeRadioButton = new QRadioButton(loginUI);
        timeRadioButton->setObjectName(QString::fromUtf8("timeRadioButton"));
        timeRadioButton->setFont(font);

        gridLayout->addWidget(timeRadioButton, 5, 0, 1, 2);

        oneHoueLineEdit = new QLineEdit(loginUI);
        oneHoueLineEdit->setObjectName(QString::fromUtf8("oneHoueLineEdit"));
        oneHoueLineEdit->setFont(font);

        gridLayout->addWidget(oneHoueLineEdit, 5, 2, 1, 1);

        label_2 = new QLabel(loginUI);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setFont(font);

        gridLayout->addWidget(label_2, 5, 3, 1, 1);

        hoursLineEdit = new QLineEdit(loginUI);
        hoursLineEdit->setObjectName(QString::fromUtf8("hoursLineEdit"));
        hoursLineEdit->setFont(font);

        gridLayout->addWidget(hoursLineEdit, 5, 4, 1, 1);

        label_4 = new QLabel(loginUI);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setFont(font);

        gridLayout->addWidget(label_4, 5, 6, 1, 1);

        verticalSpacer_4 = new QSpacerItem(20, 29, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_4, 6, 3, 1, 1);

        totalLabel = new QLabel(loginUI);
        totalLabel->setObjectName(QString::fromUtf8("totalLabel"));
        totalLabel->setFont(font);

        gridLayout->addWidget(totalLabel, 7, 0, 1, 1);

        horizontalSpacer_7 = new QSpacerItem(112, 24, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_7, 7, 1, 1, 2);

        okButton = new QPushButton(loginUI);
        okButton->setObjectName(QString::fromUtf8("okButton"));
        okButton->setFont(font);

        gridLayout->addWidget(okButton, 7, 3, 1, 1);

        cancelButton = new QPushButton(loginUI);
        cancelButton->setObjectName(QString::fromUtf8("cancelButton"));
        cancelButton->setFont(font);

        gridLayout->addWidget(cancelButton, 7, 4, 1, 2);

        vipCardLineEdit = new QLineEdit(loginUI);
        vipCardLineEdit->setObjectName(QString::fromUtf8("vipCardLineEdit"));
        vipCardLineEdit->setFont(font);

        gridLayout->addWidget(vipCardLineEdit, 1, 4, 1, 1);


        retranslateUi(loginUI);
        QObject::connect(okButton, SIGNAL(clicked()), loginUI, SLOT(accept()));
        QObject::connect(cancelButton, SIGNAL(clicked()), loginUI, SLOT(reject()));

        QMetaObject::connectSlotsByName(loginUI);
    } // setupUi

    void retranslateUi(QDialog *loginUI)
    {
        loginUI->setWindowTitle(QApplication::translate("loginUI", "\347\231\273\350\256\260", 0, QApplication::UnicodeUTF8));
        rowIdLabel->setText(QApplication::translate("loginUI", "\347\220\203\351\201\223\345\217\267:", 0, QApplication::UnicodeUTF8));
        vipCheckBox->setText(QApplication::translate("loginUI", "VIP\345\217\267", 0, QApplication::UnicodeUTF8));
        countRadioButton->setText(QApplication::translate("loginUI", "\350\256\260\345\261\200", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("loginUI", "\345\205\203/\345\261\200", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("loginUI", "\345\261\200", 0, QApplication::UnicodeUTF8));
        timeRadioButton->setText(QApplication::translate("loginUI", "\350\256\241\346\227\266", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("loginUI", "\345\205\203/\346\227\266", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("loginUI", "\346\227\266", 0, QApplication::UnicodeUTF8));
        totalLabel->setText(QApplication::translate("loginUI", "\345\220\210\350\256\241:", 0, QApplication::UnicodeUTF8));
        okButton->setText(QApplication::translate("loginUI", "\347\241\256\345\256\232", 0, QApplication::UnicodeUTF8));
        cancelButton->setText(QApplication::translate("loginUI", "\345\217\226\346\266\210", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class loginUI: public Ui_loginUI {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGIN_H
