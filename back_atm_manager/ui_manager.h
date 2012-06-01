/********************************************************************************
** Form generated from reading UI file 'manager.ui'
**
** Created: Sun Jun 27 13:54:27 2010
**      by: Qt User Interface Compiler version 4.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MANAGER_H
#define UI_MANAGER_H

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
#include <QtGui/QTabWidget>
#include <QtGui/QTableView>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_managerAdmin
{
public:
    QGridLayout *gridLayout_2;
    QTabWidget *managerTab;
    QWidget *tab;
    QGridLayout *gridLayout;
    QTableView *empTableView;
    QHBoxLayout *horizontalLayout;
    QLabel *empNameLabel;
    QLineEdit *empNameLineEdit;
    QPushButton *empCheckPushButton;
    QSpacerItem *horizontalSpacer;
    QPushButton *empInsPushButton;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *empDelPushButton;
    QWidget *tab_4;
    QGridLayout *gridLayout_4;
    QTableView *financeTableView;

    void setupUi(QWidget *managerAdmin)
    {
        if (managerAdmin->objectName().isEmpty())
            managerAdmin->setObjectName(QString::fromUtf8("managerAdmin"));
        managerAdmin->resize(600, 400);
        gridLayout_2 = new QGridLayout(managerAdmin);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        managerTab = new QTabWidget(managerAdmin);
        managerTab->setObjectName(QString::fromUtf8("managerTab"));
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        gridLayout = new QGridLayout(tab);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        empTableView = new QTableView(tab);
        empTableView->setObjectName(QString::fromUtf8("empTableView"));

        gridLayout->addWidget(empTableView, 0, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        empNameLabel = new QLabel(tab);
        empNameLabel->setObjectName(QString::fromUtf8("empNameLabel"));

        horizontalLayout->addWidget(empNameLabel);

        empNameLineEdit = new QLineEdit(tab);
        empNameLineEdit->setObjectName(QString::fromUtf8("empNameLineEdit"));

        horizontalLayout->addWidget(empNameLineEdit);

        empCheckPushButton = new QPushButton(tab);
        empCheckPushButton->setObjectName(QString::fromUtf8("empCheckPushButton"));

        horizontalLayout->addWidget(empCheckPushButton);

        horizontalSpacer = new QSpacerItem(48, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        empInsPushButton = new QPushButton(tab);
        empInsPushButton->setObjectName(QString::fromUtf8("empInsPushButton"));

        horizontalLayout->addWidget(empInsPushButton);

        horizontalSpacer_2 = new QSpacerItem(38, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        empDelPushButton = new QPushButton(tab);
        empDelPushButton->setObjectName(QString::fromUtf8("empDelPushButton"));

        horizontalLayout->addWidget(empDelPushButton);


        gridLayout->addLayout(horizontalLayout, 1, 0, 1, 1);

        managerTab->addTab(tab, QString());
        tab_4 = new QWidget();
        tab_4->setObjectName(QString::fromUtf8("tab_4"));
        gridLayout_4 = new QGridLayout(tab_4);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        financeTableView = new QTableView(tab_4);
        financeTableView->setObjectName(QString::fromUtf8("financeTableView"));

        gridLayout_4->addWidget(financeTableView, 0, 0, 1, 1);

        managerTab->addTab(tab_4, QString());

        gridLayout_2->addWidget(managerTab, 0, 0, 1, 1);


        retranslateUi(managerAdmin);

        managerTab->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(managerAdmin);
    } // setupUi

    void retranslateUi(QWidget *managerAdmin)
    {
        managerAdmin->setWindowTitle(QApplication::translate("managerAdmin", "Manager", 0, QApplication::UnicodeUTF8));
        empNameLabel->setText(QApplication::translate("managerAdmin", "\346\214\211\345\247\223\345\220\215\346\237\245\350\257\242:", 0, QApplication::UnicodeUTF8));
        empCheckPushButton->setText(QApplication::translate("managerAdmin", "\346\237\245\350\257\242", 0, QApplication::UnicodeUTF8));
        empInsPushButton->setText(QApplication::translate("managerAdmin", "\346\217\222\345\205\245", 0, QApplication::UnicodeUTF8));
        empDelPushButton->setText(QApplication::translate("managerAdmin", "\345\210\240\351\231\244", 0, QApplication::UnicodeUTF8));
        managerTab->setTabText(managerTab->indexOf(tab), QApplication::translate("managerAdmin", "\345\221\230\345\267\245\347\256\241\347\220\206", 0, QApplication::UnicodeUTF8));
        managerTab->setTabText(managerTab->indexOf(tab_4), QApplication::translate("managerAdmin", "\350\264\242\345\212\241\347\256\241\347\220\206", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class managerAdmin: public Ui_managerAdmin {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MANAGER_H
