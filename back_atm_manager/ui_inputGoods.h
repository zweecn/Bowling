/********************************************************************************
** Form generated from reading UI file 'inputGoods.ui'
**
** Created: Sun Jun 27 12:40:14 2010
**      by: Qt User Interface Compiler version 4.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INPUTGOODS_H
#define UI_INPUTGOODS_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
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

class Ui_Form
{
public:
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayout;
    QLabel *label_7;
    QLineEdit *lineEdit;
    QLabel *label_6;
    QLineEdit *lineEdit_4;
    QLabel *label;
    QDateEdit *dateEdit;
    QLabel *label_2;
    QLineEdit *lineEdit_2;
    QLabel *label_3;
    QLineEdit *lineEdit_3;
    QLabel *label_4;
    QComboBox *comboBox;
    QLabel *label_5;
    QComboBox *comboBox_2;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QWidget *Form)
    {
        if (Form->objectName().isEmpty())
            Form->setObjectName(QString::fromUtf8("Form"));
        Form->resize(400, 300);
        widget = new QWidget(Form);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(80, 40, 198, 211));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label_7 = new QLabel(widget);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        gridLayout->addWidget(label_7, 0, 0, 1, 1);

        lineEdit = new QLineEdit(widget);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));

        gridLayout->addWidget(lineEdit, 0, 1, 1, 1);

        label_6 = new QLabel(widget);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        gridLayout->addWidget(label_6, 1, 0, 1, 1);

        lineEdit_4 = new QLineEdit(widget);
        lineEdit_4->setObjectName(QString::fromUtf8("lineEdit_4"));

        gridLayout->addWidget(lineEdit_4, 1, 1, 1, 1);

        label = new QLabel(widget);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 2, 0, 1, 1);

        dateEdit = new QDateEdit(widget);
        dateEdit->setObjectName(QString::fromUtf8("dateEdit"));

        gridLayout->addWidget(dateEdit, 2, 1, 1, 1);

        label_2 = new QLabel(widget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 3, 0, 1, 1);

        lineEdit_2 = new QLineEdit(widget);
        lineEdit_2->setObjectName(QString::fromUtf8("lineEdit_2"));

        gridLayout->addWidget(lineEdit_2, 3, 1, 1, 1);

        label_3 = new QLabel(widget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 4, 0, 1, 1);

        lineEdit_3 = new QLineEdit(widget);
        lineEdit_3->setObjectName(QString::fromUtf8("lineEdit_3"));

        gridLayout->addWidget(lineEdit_3, 4, 1, 1, 1);

        label_4 = new QLabel(widget);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout->addWidget(label_4, 5, 0, 1, 1);

        comboBox = new QComboBox(widget);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));

        gridLayout->addWidget(comboBox, 5, 1, 1, 1);

        label_5 = new QLabel(widget);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout->addWidget(label_5, 6, 0, 1, 1);

        comboBox_2 = new QComboBox(widget);
        comboBox_2->setObjectName(QString::fromUtf8("comboBox_2"));

        gridLayout->addWidget(comboBox_2, 6, 1, 1, 1);


        verticalLayout->addLayout(gridLayout);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        pushButton = new QPushButton(widget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        horizontalLayout->addWidget(pushButton);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(Form);

        QMetaObject::connectSlotsByName(Form);
    } // setupUi

    void retranslateUi(QWidget *Form)
    {
        Form->setWindowTitle(QApplication::translate("Form", "Form", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("Form", "\345\225\206\345\223\201\345\220\215\347\247\260\357\274\232", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("Form", "\350\277\233\350\264\247\351\241\271\345\217\267\357\274\232", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("Form", "\350\277\233\350\264\247\346\227\245\346\234\237\357\274\232", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("Form", "\345\215\225\344\273\267\357\274\232", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("Form", "\346\225\260\351\207\217\357\274\232", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("Form", "\347\273\217\346\211\213\344\272\272\357\274\232", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("Form", "\344\276\233\350\264\247\345\225\206\357\274\232", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("Form", "\347\241\256\350\256\244", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Form: public Ui_Form {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INPUTGOODS_H
