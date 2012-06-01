/********************************************************************************
** Form generated from reading UI file 'changerow1.ui'
**
** Created: Fri Jul 2 23:00:03 2010
**      by: Qt User Interface Compiler version 4.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHANGEROW1_H
#define UI_CHANGEROW1_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>

QT_BEGIN_NAMESPACE

class Ui_changeRowUI
{
public:
    QGridLayout *gridLayout;
    QSpacerItem *verticalSpacer_2;
    QSpacerItem *horizontalSpacer;
    QComboBox *comboBoxPrev;
    QLabel *label_2;
    QComboBox *comboBoxAfter;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *hboxLayout;
    QSpacerItem *spacerItem;
    QPushButton *pushButtonChange;
    QPushButton *cancelButton;

    void setupUi(QDialog *changeRowUI)
    {
        if (changeRowUI->objectName().isEmpty())
            changeRowUI->setObjectName(QString::fromUtf8("changeRowUI"));
        changeRowUI->resize(400, 300);
        QFont font;
        font.setPointSize(12);
        changeRowUI->setFont(font);
        gridLayout = new QGridLayout(changeRowUI);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        verticalSpacer_2 = new QSpacerItem(20, 100, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_2, 0, 3, 1, 1);

        horizontalSpacer = new QSpacerItem(69, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 1, 0, 1, 1);

        comboBoxPrev = new QComboBox(changeRowUI);
        comboBoxPrev->setObjectName(QString::fromUtf8("comboBoxPrev"));
        comboBoxPrev->setFont(font);

        gridLayout->addWidget(comboBoxPrev, 1, 1, 1, 1);

        label_2 = new QLabel(changeRowUI);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setFont(font);
        label_2->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_2, 1, 2, 1, 2);

        comboBoxAfter = new QComboBox(changeRowUI);
        comboBoxAfter->setObjectName(QString::fromUtf8("comboBoxAfter"));
        comboBoxAfter->setFont(font);

        gridLayout->addWidget(comboBoxAfter, 1, 4, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(69, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 1, 5, 1, 1);

        verticalSpacer = new QSpacerItem(20, 100, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 2, 3, 1, 1);

        hboxLayout = new QHBoxLayout();
#ifndef Q_OS_MAC
        hboxLayout->setSpacing(6);
#endif
        hboxLayout->setContentsMargins(0, 0, 0, 0);
        hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
        spacerItem = new QSpacerItem(131, 31, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout->addItem(spacerItem);

        pushButtonChange = new QPushButton(changeRowUI);
        pushButtonChange->setObjectName(QString::fromUtf8("pushButtonChange"));
        pushButtonChange->setFont(font);

        hboxLayout->addWidget(pushButtonChange);

        cancelButton = new QPushButton(changeRowUI);
        cancelButton->setObjectName(QString::fromUtf8("cancelButton"));
        cancelButton->setFont(font);

        hboxLayout->addWidget(cancelButton);


        gridLayout->addLayout(hboxLayout, 3, 0, 1, 6);


        retranslateUi(changeRowUI);
        QObject::connect(pushButtonChange, SIGNAL(clicked()), changeRowUI, SLOT(accept()));
        QObject::connect(cancelButton, SIGNAL(clicked()), changeRowUI, SLOT(reject()));

        QMetaObject::connectSlotsByName(changeRowUI);
    } // setupUi

    void retranslateUi(QDialog *changeRowUI)
    {
        changeRowUI->setWindowTitle(QApplication::translate("changeRowUI", "\346\233\264\346\215\242\347\220\203\351\201\223", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("changeRowUI", "\346\233\264\346\215\242\344\270\272", 0, QApplication::UnicodeUTF8));
        pushButtonChange->setText(QApplication::translate("changeRowUI", "\347\241\256\345\256\232", 0, QApplication::UnicodeUTF8));
        cancelButton->setText(QApplication::translate("changeRowUI", "\345\217\226\346\266\210", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class changeRowUI: public Ui_changeRowUI {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHANGEROW1_H
