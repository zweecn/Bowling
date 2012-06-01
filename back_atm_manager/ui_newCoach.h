/********************************************************************************
** Form generated from reading UI file 'newCoach.ui'
**
** Created: Sun Jun 27 12:40:14 2010
**      by: Qt User Interface Compiler version 4.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NEWCOACH_H
#define UI_NEWCOACH_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
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

class Ui_newCoachUI
{
public:
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayout;
    QLabel *coachNameLabel;
    QLineEdit *coachNameLineEdit;
    QLabel *coachGenderLabel;
    QComboBox *coachGenderComboBox;
    QLabel *coachContactLabel;
    QLineEdit *coachContactLineEdit;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *okPushButton;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QWidget *newCoachUI)
    {
        if (newCoachUI->objectName().isEmpty())
            newCoachUI->setObjectName(QString::fromUtf8("newCoachUI"));
        newCoachUI->resize(400, 300);
        layoutWidget = new QWidget(newCoachUI);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(40, 50, 321, 191));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        coachNameLabel = new QLabel(layoutWidget);
        coachNameLabel->setObjectName(QString::fromUtf8("coachNameLabel"));

        gridLayout->addWidget(coachNameLabel, 0, 0, 1, 1);

        coachNameLineEdit = new QLineEdit(layoutWidget);
        coachNameLineEdit->setObjectName(QString::fromUtf8("coachNameLineEdit"));

        gridLayout->addWidget(coachNameLineEdit, 0, 1, 1, 1);

        coachGenderLabel = new QLabel(layoutWidget);
        coachGenderLabel->setObjectName(QString::fromUtf8("coachGenderLabel"));

        gridLayout->addWidget(coachGenderLabel, 1, 0, 1, 1);

        coachGenderComboBox = new QComboBox(layoutWidget);
        coachGenderComboBox->setObjectName(QString::fromUtf8("coachGenderComboBox"));

        gridLayout->addWidget(coachGenderComboBox, 1, 1, 1, 1);

        coachContactLabel = new QLabel(layoutWidget);
        coachContactLabel->setObjectName(QString::fromUtf8("coachContactLabel"));

        gridLayout->addWidget(coachContactLabel, 2, 0, 1, 1);

        coachContactLineEdit = new QLineEdit(layoutWidget);
        coachContactLineEdit->setObjectName(QString::fromUtf8("coachContactLineEdit"));

        gridLayout->addWidget(coachContactLineEdit, 2, 1, 1, 1);


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


        retranslateUi(newCoachUI);

        QMetaObject::connectSlotsByName(newCoachUI);
    } // setupUi

    void retranslateUi(QWidget *newCoachUI)
    {
        newCoachUI->setWindowTitle(QApplication::translate("newCoachUI", "\346\267\273\345\212\240\346\225\231\347\273\203", 0, QApplication::UnicodeUTF8));
        coachNameLabel->setText(QApplication::translate("newCoachUI", "\345\247\223\345\220\215\357\274\232", 0, QApplication::UnicodeUTF8));
        coachGenderLabel->setText(QApplication::translate("newCoachUI", "\346\200\247\345\210\253\357\274\232", 0, QApplication::UnicodeUTF8));
        coachGenderComboBox->clear();
        coachGenderComboBox->insertItems(0, QStringList()
         << QApplication::translate("newCoachUI", "\347\224\267", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("newCoachUI", "\345\245\263", 0, QApplication::UnicodeUTF8)
        );
        coachContactLabel->setText(QApplication::translate("newCoachUI", "\350\201\224\347\263\273\346\226\271\345\274\217\357\274\232", 0, QApplication::UnicodeUTF8));
        okPushButton->setText(QApplication::translate("newCoachUI", "\347\241\256\350\256\244", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class newCoachUI: public Ui_newCoachUI {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NEWCOACH_H
