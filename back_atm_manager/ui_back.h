/********************************************************************************
** Form generated from reading UI file 'back.ui'
**
** Created: Sun Jun 27 14:34:02 2010
**      by: Qt User Interface Compiler version 4.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BACK_H
#define UI_BACK_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QComboBox>
#include <QtGui/QDateEdit>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QTabWidget>
#include <QtGui/QTableView>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_backAdmin
{
public:
    QGridLayout *gridLayout_2;
    QTabWidget *backTab;
    QWidget *equipmentTab;
    QGridLayout *gridLayout_3;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer_11;
    QPushButton *fixPushButton;
    QTableView *equipTableView;
    QWidget *bookTab;
    QGridLayout *gridLayout_4;
    QTableView *bookTableView;
    QHBoxLayout *horizontalLayout;
    QPushButton *registerPushButton;
    QSpacerItem *horizontalSpacer;
    QPushButton *checkBookPushButton;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *cancelBookPushButton;
    QWidget *coachTab;
    QGridLayout *gridLayout_5;
    QVBoxLayout *verticalLayout_4;
    QTableView *coachTableView;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *horizontalSpacer_9;
    QPushButton *newCoachPushButton;
    QWidget *goodsTab;
    QGridLayout *gridLayout_9;
    QTabWidget *goodsChildTab;
    QWidget *tab;
    QGridLayout *gridLayout_7;
    QTableView *goodsTotalTableView;
    QWidget *tab_2;
    QGridLayout *gridLayout_8;
    QTableView *goodsDetailTableView;
    QHBoxLayout *horizontalLayout_2;
    QLabel *saleOrBuyTypeLabel;
    QComboBox *saleOrBuyComboBox;
    QCheckBox *goodsDateCheckBox;
    QDateEdit *goodsDateEdit;
    QSpacerItem *horizontalSpacer_3;
    QCheckBox *goodsTypeCheckBox;
    QComboBox *goodsTypeComboBox;
    QSpacerItem *horizontalSpacer_4;
    QPushButton *checkGoodsPushButton;
    QWidget *widget;
    QGridLayout *gridLayout_6;
    QHBoxLayout *horizontalLayout_9;
    QSpacerItem *horizontalSpacer_15;
    QVBoxLayout *verticalLayout_2;
    QSpacerItem *verticalSpacer_2;
    QGridLayout *gridLayout;
    QLabel *newGoodsNameLabel;
    QLineEdit *newGoodsNameLineEdit;
    QLabel *newGoodsItemNumLabel;
    QLineEdit *newGoodsItemNumLineEdit;
    QLabel *newGoodsDateLabel;
    QDateEdit *newGoodsDateDateEdit;
    QLabel *newGoodsPriceLabel;
    QLineEdit *newGoodsPriceLineEdit;
    QLabel *newGoodsCountLabel;
    QLineEdit *newGoodsCountLineEdit;
    QLabel *newGoodsEmpLabel;
    QComboBox *newGoodsEmpComboBox;
    QLabel *newGoodsSupplyLabel;
    QComboBox *newGoodsSupplyComboBox;
    QLabel *newGoodsTypeLabel;
    QComboBox *newGoodsTypeComboBox;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout_8;
    QSpacerItem *horizontalSpacer_5;
    QPushButton *newGoodsOkPushButton;
    QSpacerItem *horizontalSpacer_8;
    QSpacerItem *verticalSpacer_3;
    QSpacerItem *horizontalSpacer_16;
    QWidget *ruleTab;
    QGridLayout *gridLayout_10;
    QVBoxLayout *verticalLayout_5;
    QHBoxLayout *horizontalLayout_10;
    QPushButton *monPushButton;
    QSpacerItem *horizontalSpacer_17;
    QPushButton *tuePushButton;
    QSpacerItem *horizontalSpacer_18;
    QPushButton *wedPushButton;
    QSpacerItem *horizontalSpacer_19;
    QPushButton *thuPushButton;
    QHBoxLayout *horizontalLayout_11;
    QSpacerItem *horizontalSpacer_22;
    QPushButton *friPushButton;
    QSpacerItem *horizontalSpacer_20;
    QPushButton *satPushButton;
    QSpacerItem *horizontalSpacer_21;
    QPushButton *sunPushButton;
    QSpacerItem *horizontalSpacer_23;
    QWidget *awardTab;
    QGridLayout *gridLayout_11;
    QTableView *awardTableView;
    QHBoxLayout *horizontalLayout_5;
    QSpacerItem *horizontalSpacer_13;
    QPushButton *awardAddPushButton;
    QSpacerItem *horizontalSpacer_14;
    QPushButton *awardDeletePushButton;
    QWidget *dumpTab;
    QGridLayout *gridLayout_12;
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer_5;
    QHBoxLayout *horizontalLayout_6;
    QLabel *dumpDatabaseLabel;
    QLineEdit *dumpDatabaseEditLine;
    QPushButton *dumpBrowsePushButton;
    QSpacerItem *horizontalSpacer_6;
    QPushButton *dumpPushButton;
    QSpacerItem *verticalSpacer_4;
    QHBoxLayout *horizontalLayout_7;
    QLabel *restoreDatabaseLabel;
    QLineEdit *restoreDatabaseEditLine;
    QPushButton *restoreBrowsePushButton;
    QSpacerItem *horizontalSpacer_7;
    QPushButton *restorePushButton;
    QSpacerItem *verticalSpacer_6;

    void setupUi(QWidget *backAdmin)
    {
        if (backAdmin->objectName().isEmpty())
            backAdmin->setObjectName(QString::fromUtf8("backAdmin"));
        backAdmin->setWindowModality(Qt::ApplicationModal);
        backAdmin->resize(723, 518);
        gridLayout_2 = new QGridLayout(backAdmin);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        backTab = new QTabWidget(backAdmin);
        backTab->setObjectName(QString::fromUtf8("backTab"));
        backTab->setTabShape(QTabWidget::Rounded);
        equipmentTab = new QWidget();
        equipmentTab->setObjectName(QString::fromUtf8("equipmentTab"));
        gridLayout_3 = new QGridLayout(equipmentTab);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalSpacer_11 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_11);

        fixPushButton = new QPushButton(equipmentTab);
        fixPushButton->setObjectName(QString::fromUtf8("fixPushButton"));

        horizontalLayout_3->addWidget(fixPushButton);


        gridLayout_3->addLayout(horizontalLayout_3, 1, 0, 1, 1);

        equipTableView = new QTableView(equipmentTab);
        equipTableView->setObjectName(QString::fromUtf8("equipTableView"));

        gridLayout_3->addWidget(equipTableView, 0, 0, 1, 1);

        backTab->addTab(equipmentTab, QString());
        bookTab = new QWidget();
        bookTab->setObjectName(QString::fromUtf8("bookTab"));
        gridLayout_4 = new QGridLayout(bookTab);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        bookTableView = new QTableView(bookTab);
        bookTableView->setObjectName(QString::fromUtf8("bookTableView"));

        gridLayout_4->addWidget(bookTableView, 0, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        registerPushButton = new QPushButton(bookTab);
        registerPushButton->setObjectName(QString::fromUtf8("registerPushButton"));

        horizontalLayout->addWidget(registerPushButton);

        horizontalSpacer = new QSpacerItem(148, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        checkBookPushButton = new QPushButton(bookTab);
        checkBookPushButton->setObjectName(QString::fromUtf8("checkBookPushButton"));

        horizontalLayout->addWidget(checkBookPushButton);

        horizontalSpacer_2 = new QSpacerItem(148, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        cancelBookPushButton = new QPushButton(bookTab);
        cancelBookPushButton->setObjectName(QString::fromUtf8("cancelBookPushButton"));

        horizontalLayout->addWidget(cancelBookPushButton);


        gridLayout_4->addLayout(horizontalLayout, 1, 0, 1, 1);

        backTab->addTab(bookTab, QString());
        coachTab = new QWidget();
        coachTab->setObjectName(QString::fromUtf8("coachTab"));
        gridLayout_5 = new QGridLayout(coachTab);
        gridLayout_5->setSpacing(6);
        gridLayout_5->setContentsMargins(11, 11, 11, 11);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        coachTableView = new QTableView(coachTab);
        coachTableView->setObjectName(QString::fromUtf8("coachTableView"));

        verticalLayout_4->addWidget(coachTableView);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalSpacer_9 = new QSpacerItem(588, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_9);

        newCoachPushButton = new QPushButton(coachTab);
        newCoachPushButton->setObjectName(QString::fromUtf8("newCoachPushButton"));

        horizontalLayout_4->addWidget(newCoachPushButton);


        verticalLayout_4->addLayout(horizontalLayout_4);


        gridLayout_5->addLayout(verticalLayout_4, 0, 0, 1, 1);

        backTab->addTab(coachTab, QString());
        goodsTab = new QWidget();
        goodsTab->setObjectName(QString::fromUtf8("goodsTab"));
        gridLayout_9 = new QGridLayout(goodsTab);
        gridLayout_9->setSpacing(6);
        gridLayout_9->setContentsMargins(11, 11, 11, 11);
        gridLayout_9->setObjectName(QString::fromUtf8("gridLayout_9"));
        goodsChildTab = new QTabWidget(goodsTab);
        goodsChildTab->setObjectName(QString::fromUtf8("goodsChildTab"));
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        gridLayout_7 = new QGridLayout(tab);
        gridLayout_7->setSpacing(6);
        gridLayout_7->setContentsMargins(11, 11, 11, 11);
        gridLayout_7->setObjectName(QString::fromUtf8("gridLayout_7"));
        goodsTotalTableView = new QTableView(tab);
        goodsTotalTableView->setObjectName(QString::fromUtf8("goodsTotalTableView"));

        gridLayout_7->addWidget(goodsTotalTableView, 0, 0, 1, 1);

        goodsChildTab->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        gridLayout_8 = new QGridLayout(tab_2);
        gridLayout_8->setSpacing(6);
        gridLayout_8->setContentsMargins(11, 11, 11, 11);
        gridLayout_8->setObjectName(QString::fromUtf8("gridLayout_8"));
        goodsDetailTableView = new QTableView(tab_2);
        goodsDetailTableView->setObjectName(QString::fromUtf8("goodsDetailTableView"));

        gridLayout_8->addWidget(goodsDetailTableView, 0, 0, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        saleOrBuyTypeLabel = new QLabel(tab_2);
        saleOrBuyTypeLabel->setObjectName(QString::fromUtf8("saleOrBuyTypeLabel"));

        horizontalLayout_2->addWidget(saleOrBuyTypeLabel);

        saleOrBuyComboBox = new QComboBox(tab_2);
        saleOrBuyComboBox->setObjectName(QString::fromUtf8("saleOrBuyComboBox"));

        horizontalLayout_2->addWidget(saleOrBuyComboBox);

        goodsDateCheckBox = new QCheckBox(tab_2);
        goodsDateCheckBox->setObjectName(QString::fromUtf8("goodsDateCheckBox"));

        horizontalLayout_2->addWidget(goodsDateCheckBox);

        goodsDateEdit = new QDateEdit(tab_2);
        goodsDateEdit->setObjectName(QString::fromUtf8("goodsDateEdit"));

        horizontalLayout_2->addWidget(goodsDateEdit);

        horizontalSpacer_3 = new QSpacerItem(36, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);

        goodsTypeCheckBox = new QCheckBox(tab_2);
        goodsTypeCheckBox->setObjectName(QString::fromUtf8("goodsTypeCheckBox"));

        horizontalLayout_2->addWidget(goodsTypeCheckBox);

        goodsTypeComboBox = new QComboBox(tab_2);
        goodsTypeComboBox->setObjectName(QString::fromUtf8("goodsTypeComboBox"));

        horizontalLayout_2->addWidget(goodsTypeComboBox);

        horizontalSpacer_4 = new QSpacerItem(36, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_4);

        checkGoodsPushButton = new QPushButton(tab_2);
        checkGoodsPushButton->setObjectName(QString::fromUtf8("checkGoodsPushButton"));

        horizontalLayout_2->addWidget(checkGoodsPushButton);


        gridLayout_8->addLayout(horizontalLayout_2, 1, 0, 1, 1);

        goodsChildTab->addTab(tab_2, QString());
        widget = new QWidget();
        widget->setObjectName(QString::fromUtf8("widget"));
        gridLayout_6 = new QGridLayout(widget);
        gridLayout_6->setSpacing(6);
        gridLayout_6->setContentsMargins(11, 11, 11, 11);
        gridLayout_6->setObjectName(QString::fromUtf8("gridLayout_6"));
        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setSpacing(6);
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        horizontalSpacer_15 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_9->addItem(horizontalSpacer_15);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_2);

        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        newGoodsNameLabel = new QLabel(widget);
        newGoodsNameLabel->setObjectName(QString::fromUtf8("newGoodsNameLabel"));

        gridLayout->addWidget(newGoodsNameLabel, 0, 0, 1, 1);

        newGoodsNameLineEdit = new QLineEdit(widget);
        newGoodsNameLineEdit->setObjectName(QString::fromUtf8("newGoodsNameLineEdit"));

        gridLayout->addWidget(newGoodsNameLineEdit, 0, 1, 1, 1);

        newGoodsItemNumLabel = new QLabel(widget);
        newGoodsItemNumLabel->setObjectName(QString::fromUtf8("newGoodsItemNumLabel"));

        gridLayout->addWidget(newGoodsItemNumLabel, 1, 0, 1, 1);

        newGoodsItemNumLineEdit = new QLineEdit(widget);
        newGoodsItemNumLineEdit->setObjectName(QString::fromUtf8("newGoodsItemNumLineEdit"));

        gridLayout->addWidget(newGoodsItemNumLineEdit, 1, 1, 1, 1);

        newGoodsDateLabel = new QLabel(widget);
        newGoodsDateLabel->setObjectName(QString::fromUtf8("newGoodsDateLabel"));

        gridLayout->addWidget(newGoodsDateLabel, 2, 0, 1, 1);

        newGoodsDateDateEdit = new QDateEdit(widget);
        newGoodsDateDateEdit->setObjectName(QString::fromUtf8("newGoodsDateDateEdit"));

        gridLayout->addWidget(newGoodsDateDateEdit, 2, 1, 1, 1);

        newGoodsPriceLabel = new QLabel(widget);
        newGoodsPriceLabel->setObjectName(QString::fromUtf8("newGoodsPriceLabel"));

        gridLayout->addWidget(newGoodsPriceLabel, 3, 0, 1, 1);

        newGoodsPriceLineEdit = new QLineEdit(widget);
        newGoodsPriceLineEdit->setObjectName(QString::fromUtf8("newGoodsPriceLineEdit"));

        gridLayout->addWidget(newGoodsPriceLineEdit, 3, 1, 1, 1);

        newGoodsCountLabel = new QLabel(widget);
        newGoodsCountLabel->setObjectName(QString::fromUtf8("newGoodsCountLabel"));

        gridLayout->addWidget(newGoodsCountLabel, 4, 0, 1, 1);

        newGoodsCountLineEdit = new QLineEdit(widget);
        newGoodsCountLineEdit->setObjectName(QString::fromUtf8("newGoodsCountLineEdit"));

        gridLayout->addWidget(newGoodsCountLineEdit, 4, 1, 1, 1);

        newGoodsEmpLabel = new QLabel(widget);
        newGoodsEmpLabel->setObjectName(QString::fromUtf8("newGoodsEmpLabel"));

        gridLayout->addWidget(newGoodsEmpLabel, 5, 0, 1, 1);

        newGoodsEmpComboBox = new QComboBox(widget);
        newGoodsEmpComboBox->setObjectName(QString::fromUtf8("newGoodsEmpComboBox"));

        gridLayout->addWidget(newGoodsEmpComboBox, 5, 1, 1, 1);

        newGoodsSupplyLabel = new QLabel(widget);
        newGoodsSupplyLabel->setObjectName(QString::fromUtf8("newGoodsSupplyLabel"));

        gridLayout->addWidget(newGoodsSupplyLabel, 6, 0, 1, 1);

        newGoodsSupplyComboBox = new QComboBox(widget);
        newGoodsSupplyComboBox->setObjectName(QString::fromUtf8("newGoodsSupplyComboBox"));

        gridLayout->addWidget(newGoodsSupplyComboBox, 6, 1, 1, 1);

        newGoodsTypeLabel = new QLabel(widget);
        newGoodsTypeLabel->setObjectName(QString::fromUtf8("newGoodsTypeLabel"));

        gridLayout->addWidget(newGoodsTypeLabel, 7, 0, 1, 1);

        newGoodsTypeComboBox = new QComboBox(widget);
        newGoodsTypeComboBox->setObjectName(QString::fromUtf8("newGoodsTypeComboBox"));

        gridLayout->addWidget(newGoodsTypeComboBox, 7, 1, 1, 1);


        verticalLayout_2->addLayout(gridLayout);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setSpacing(6);
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_5);

        newGoodsOkPushButton = new QPushButton(widget);
        newGoodsOkPushButton->setObjectName(QString::fromUtf8("newGoodsOkPushButton"));

        horizontalLayout_8->addWidget(newGoodsOkPushButton);

        horizontalSpacer_8 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_8);


        verticalLayout_2->addLayout(horizontalLayout_8);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_3);


        horizontalLayout_9->addLayout(verticalLayout_2);

        horizontalSpacer_16 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_9->addItem(horizontalSpacer_16);


        gridLayout_6->addLayout(horizontalLayout_9, 0, 0, 1, 1);

        goodsChildTab->addTab(widget, QString());

        gridLayout_9->addWidget(goodsChildTab, 0, 0, 1, 1);

        backTab->addTab(goodsTab, QString());
        ruleTab = new QWidget();
        ruleTab->setObjectName(QString::fromUtf8("ruleTab"));
        gridLayout_10 = new QGridLayout(ruleTab);
        gridLayout_10->setSpacing(6);
        gridLayout_10->setContentsMargins(11, 11, 11, 11);
        gridLayout_10->setObjectName(QString::fromUtf8("gridLayout_10"));
        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setSpacing(6);
        horizontalLayout_10->setObjectName(QString::fromUtf8("horizontalLayout_10"));
        monPushButton = new QPushButton(ruleTab);
        monPushButton->setObjectName(QString::fromUtf8("monPushButton"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(monPushButton->sizePolicy().hasHeightForWidth());
        monPushButton->setSizePolicy(sizePolicy);
        monPushButton->setSizeIncrement(QSize(1, 1));

        horizontalLayout_10->addWidget(monPushButton);

        horizontalSpacer_17 = new QSpacerItem(18, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_10->addItem(horizontalSpacer_17);

        tuePushButton = new QPushButton(ruleTab);
        tuePushButton->setObjectName(QString::fromUtf8("tuePushButton"));
        sizePolicy.setHeightForWidth(tuePushButton->sizePolicy().hasHeightForWidth());
        tuePushButton->setSizePolicy(sizePolicy);
        tuePushButton->setSizeIncrement(QSize(1, 1));

        horizontalLayout_10->addWidget(tuePushButton);

        horizontalSpacer_18 = new QSpacerItem(18, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_10->addItem(horizontalSpacer_18);

        wedPushButton = new QPushButton(ruleTab);
        wedPushButton->setObjectName(QString::fromUtf8("wedPushButton"));
        sizePolicy.setHeightForWidth(wedPushButton->sizePolicy().hasHeightForWidth());
        wedPushButton->setSizePolicy(sizePolicy);
        wedPushButton->setSizeIncrement(QSize(1, 1));

        horizontalLayout_10->addWidget(wedPushButton);

        horizontalSpacer_19 = new QSpacerItem(18, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_10->addItem(horizontalSpacer_19);

        thuPushButton = new QPushButton(ruleTab);
        thuPushButton->setObjectName(QString::fromUtf8("thuPushButton"));
        sizePolicy.setHeightForWidth(thuPushButton->sizePolicy().hasHeightForWidth());
        thuPushButton->setSizePolicy(sizePolicy);
        thuPushButton->setSizeIncrement(QSize(1, 1));

        horizontalLayout_10->addWidget(thuPushButton);


        verticalLayout_5->addLayout(horizontalLayout_10);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setSpacing(6);
        horizontalLayout_11->setObjectName(QString::fromUtf8("horizontalLayout_11"));
        horizontalSpacer_22 = new QSpacerItem(78, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_11->addItem(horizontalSpacer_22);

        friPushButton = new QPushButton(ruleTab);
        friPushButton->setObjectName(QString::fromUtf8("friPushButton"));
        sizePolicy.setHeightForWidth(friPushButton->sizePolicy().hasHeightForWidth());
        friPushButton->setSizePolicy(sizePolicy);
        friPushButton->setSizeIncrement(QSize(1, 1));

        horizontalLayout_11->addWidget(friPushButton);

        horizontalSpacer_20 = new QSpacerItem(18, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_11->addItem(horizontalSpacer_20);

        satPushButton = new QPushButton(ruleTab);
        satPushButton->setObjectName(QString::fromUtf8("satPushButton"));
        sizePolicy.setHeightForWidth(satPushButton->sizePolicy().hasHeightForWidth());
        satPushButton->setSizePolicy(sizePolicy);
        satPushButton->setSizeIncrement(QSize(1, 1));

        horizontalLayout_11->addWidget(satPushButton);

        horizontalSpacer_21 = new QSpacerItem(18, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_11->addItem(horizontalSpacer_21);

        sunPushButton = new QPushButton(ruleTab);
        sunPushButton->setObjectName(QString::fromUtf8("sunPushButton"));
        sizePolicy.setHeightForWidth(sunPushButton->sizePolicy().hasHeightForWidth());
        sunPushButton->setSizePolicy(sizePolicy);
        sunPushButton->setSizeIncrement(QSize(1, 1));

        horizontalLayout_11->addWidget(sunPushButton);

        horizontalSpacer_23 = new QSpacerItem(78, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_11->addItem(horizontalSpacer_23);


        verticalLayout_5->addLayout(horizontalLayout_11);


        gridLayout_10->addLayout(verticalLayout_5, 0, 0, 1, 1);

        backTab->addTab(ruleTab, QString());
        awardTab = new QWidget();
        awardTab->setObjectName(QString::fromUtf8("awardTab"));
        gridLayout_11 = new QGridLayout(awardTab);
        gridLayout_11->setSpacing(6);
        gridLayout_11->setContentsMargins(11, 11, 11, 11);
        gridLayout_11->setObjectName(QString::fromUtf8("gridLayout_11"));
        awardTableView = new QTableView(awardTab);
        awardTableView->setObjectName(QString::fromUtf8("awardTableView"));

        gridLayout_11->addWidget(awardTableView, 0, 0, 1, 1);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        horizontalSpacer_13 = new QSpacerItem(308, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_13);

        awardAddPushButton = new QPushButton(awardTab);
        awardAddPushButton->setObjectName(QString::fromUtf8("awardAddPushButton"));

        horizontalLayout_5->addWidget(awardAddPushButton);

        horizontalSpacer_14 = new QSpacerItem(78, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_14);

        awardDeletePushButton = new QPushButton(awardTab);
        awardDeletePushButton->setObjectName(QString::fromUtf8("awardDeletePushButton"));

        horizontalLayout_5->addWidget(awardDeletePushButton);


        gridLayout_11->addLayout(horizontalLayout_5, 1, 0, 1, 1);

        backTab->addTab(awardTab, QString());
        dumpTab = new QWidget();
        dumpTab->setObjectName(QString::fromUtf8("dumpTab"));
        gridLayout_12 = new QGridLayout(dumpTab);
        gridLayout_12->setSpacing(6);
        gridLayout_12->setContentsMargins(11, 11, 11, 11);
        gridLayout_12->setObjectName(QString::fromUtf8("gridLayout_12"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalSpacer_5 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_5);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        dumpDatabaseLabel = new QLabel(dumpTab);
        dumpDatabaseLabel->setObjectName(QString::fromUtf8("dumpDatabaseLabel"));

        horizontalLayout_6->addWidget(dumpDatabaseLabel);

        dumpDatabaseEditLine = new QLineEdit(dumpTab);
        dumpDatabaseEditLine->setObjectName(QString::fromUtf8("dumpDatabaseEditLine"));

        horizontalLayout_6->addWidget(dumpDatabaseEditLine);

        dumpBrowsePushButton = new QPushButton(dumpTab);
        dumpBrowsePushButton->setObjectName(QString::fromUtf8("dumpBrowsePushButton"));

        horizontalLayout_6->addWidget(dumpBrowsePushButton);

        horizontalSpacer_6 = new QSpacerItem(58, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_6);

        dumpPushButton = new QPushButton(dumpTab);
        dumpPushButton->setObjectName(QString::fromUtf8("dumpPushButton"));

        horizontalLayout_6->addWidget(dumpPushButton);


        verticalLayout->addLayout(horizontalLayout_6);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_4);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        restoreDatabaseLabel = new QLabel(dumpTab);
        restoreDatabaseLabel->setObjectName(QString::fromUtf8("restoreDatabaseLabel"));

        horizontalLayout_7->addWidget(restoreDatabaseLabel);

        restoreDatabaseEditLine = new QLineEdit(dumpTab);
        restoreDatabaseEditLine->setObjectName(QString::fromUtf8("restoreDatabaseEditLine"));

        horizontalLayout_7->addWidget(restoreDatabaseEditLine);

        restoreBrowsePushButton = new QPushButton(dumpTab);
        restoreBrowsePushButton->setObjectName(QString::fromUtf8("restoreBrowsePushButton"));

        horizontalLayout_7->addWidget(restoreBrowsePushButton);

        horizontalSpacer_7 = new QSpacerItem(58, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_7);

        restorePushButton = new QPushButton(dumpTab);
        restorePushButton->setObjectName(QString::fromUtf8("restorePushButton"));

        horizontalLayout_7->addWidget(restorePushButton);


        verticalLayout->addLayout(horizontalLayout_7);

        verticalSpacer_6 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_6);


        gridLayout_12->addLayout(verticalLayout, 0, 0, 1, 1);

        backTab->addTab(dumpTab, QString());

        gridLayout_2->addWidget(backTab, 0, 0, 1, 1);


        retranslateUi(backAdmin);

        backTab->setCurrentIndex(0);
        goodsChildTab->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(backAdmin);
    } // setupUi

    void retranslateUi(QWidget *backAdmin)
    {
        backAdmin->setWindowTitle(QApplication::translate("backAdmin", "\345\220\216\345\217\260\347\256\241\347\220\206", 0, QApplication::UnicodeUTF8));
        fixPushButton->setText(QApplication::translate("backAdmin", "\347\273\264\344\277\256", 0, QApplication::UnicodeUTF8));
        backTab->setTabText(backTab->indexOf(equipmentTab), QApplication::translate("backAdmin", "\345\231\250\346\242\260\347\256\241\347\220\206", 0, QApplication::UnicodeUTF8));
        registerPushButton->setText(QApplication::translate("backAdmin", "\347\231\273\350\256\260\351\242\204\347\272\246", 0, QApplication::UnicodeUTF8));
        checkBookPushButton->setText(QApplication::translate("backAdmin", "\346\237\245\350\257\242\351\242\204\347\272\246", 0, QApplication::UnicodeUTF8));
        cancelBookPushButton->setText(QApplication::translate("backAdmin", "\350\247\243\351\231\244\351\242\204\347\272\246", 0, QApplication::UnicodeUTF8));
        backTab->setTabText(backTab->indexOf(bookTab), QApplication::translate("backAdmin", "\351\242\204\347\272\246\347\256\241\347\220\206", 0, QApplication::UnicodeUTF8));
        newCoachPushButton->setText(QApplication::translate("backAdmin", "\346\226\260\345\242\236\346\225\231\347\273\203", 0, QApplication::UnicodeUTF8));
        backTab->setTabText(backTab->indexOf(coachTab), QApplication::translate("backAdmin", "\346\225\231\347\273\203\347\256\241\347\220\206", 0, QApplication::UnicodeUTF8));
        goodsChildTab->setTabText(goodsChildTab->indexOf(tab), QApplication::translate("backAdmin", "\350\277\233\345\207\272\350\264\247\347\273\237\350\256\241", 0, QApplication::UnicodeUTF8));
        saleOrBuyTypeLabel->setText(QApplication::translate("backAdmin", "\350\264\255\345\205\245/\345\224\256\345\207\272\357\274\232", 0, QApplication::UnicodeUTF8));
        saleOrBuyComboBox->clear();
        saleOrBuyComboBox->insertItems(0, QStringList()
         << QApplication::translate("backAdmin", "\346\211\200\346\234\211", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("backAdmin", "\350\264\255\345\205\245", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("backAdmin", "\345\224\256\345\207\272", 0, QApplication::UnicodeUTF8)
        );
        goodsDateCheckBox->setText(QApplication::translate("backAdmin", "\346\227\245\346\234\237\357\274\232", 0, QApplication::UnicodeUTF8));
        goodsTypeCheckBox->setText(QApplication::translate("backAdmin", "\350\277\233\350\264\247\347\247\215\347\261\273\357\274\232", 0, QApplication::UnicodeUTF8));
        goodsTypeComboBox->clear();
        goodsTypeComboBox->insertItems(0, QStringList()
         << QApplication::translate("backAdmin", "\345\225\206\345\223\201", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("backAdmin", "\345\231\250\346\242\260", 0, QApplication::UnicodeUTF8)
        );
        checkGoodsPushButton->setText(QApplication::translate("backAdmin", "\346\237\245\350\257\242", 0, QApplication::UnicodeUTF8));
        goodsChildTab->setTabText(goodsChildTab->indexOf(tab_2), QApplication::translate("backAdmin", "\350\277\233\350\264\247/\345\207\272\350\264\247", 0, QApplication::UnicodeUTF8));
        newGoodsNameLabel->setText(QApplication::translate("backAdmin", "\345\225\206\345\223\201\345\220\215\347\247\260\357\274\232", 0, QApplication::UnicodeUTF8));
        newGoodsItemNumLabel->setText(QApplication::translate("backAdmin", "\350\277\233\350\264\247\351\241\271\345\217\267\357\274\232", 0, QApplication::UnicodeUTF8));
        newGoodsDateLabel->setText(QApplication::translate("backAdmin", "\350\277\233\350\264\247\346\227\245\346\234\237\357\274\232", 0, QApplication::UnicodeUTF8));
        newGoodsPriceLabel->setText(QApplication::translate("backAdmin", "\345\215\225\344\273\267\357\274\232", 0, QApplication::UnicodeUTF8));
        newGoodsCountLabel->setText(QApplication::translate("backAdmin", "\346\225\260\351\207\217\357\274\232", 0, QApplication::UnicodeUTF8));
        newGoodsEmpLabel->setText(QApplication::translate("backAdmin", "\347\273\217\346\211\213\344\272\272\357\274\232", 0, QApplication::UnicodeUTF8));
        newGoodsSupplyLabel->setText(QApplication::translate("backAdmin", "\344\276\233\350\264\247\345\225\206\357\274\232", 0, QApplication::UnicodeUTF8));
        newGoodsTypeLabel->setText(QApplication::translate("backAdmin", "\350\277\233\350\264\247\347\247\215\347\261\273\357\274\232", 0, QApplication::UnicodeUTF8));
        newGoodsTypeComboBox->clear();
        newGoodsTypeComboBox->insertItems(0, QStringList()
         << QApplication::translate("backAdmin", "\345\231\250\346\242\260", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("backAdmin", "\345\225\206\345\223\201", 0, QApplication::UnicodeUTF8)
        );
        newGoodsOkPushButton->setText(QApplication::translate("backAdmin", "\347\241\256\350\256\244", 0, QApplication::UnicodeUTF8));
        goodsChildTab->setTabText(goodsChildTab->indexOf(widget), QApplication::translate("backAdmin", "\345\275\225\345\205\245\345\225\206\345\223\201", 0, QApplication::UnicodeUTF8));
        backTab->setTabText(backTab->indexOf(goodsTab), QApplication::translate("backAdmin", "\350\277\233\345\207\272\350\264\247\347\256\241\347\220\206", 0, QApplication::UnicodeUTF8));
        monPushButton->setText(QString());
        tuePushButton->setText(QString());
        wedPushButton->setText(QString());
        thuPushButton->setText(QString());
        friPushButton->setText(QString());
        satPushButton->setText(QString());
        sunPushButton->setText(QString());
        backTab->setTabText(backTab->indexOf(ruleTab), QApplication::translate("backAdmin", "\344\270\232\345\212\241\350\247\204\345\210\231", 0, QApplication::UnicodeUTF8));
        awardAddPushButton->setText(QApplication::translate("backAdmin", "\346\267\273\345\212\240", 0, QApplication::UnicodeUTF8));
        awardDeletePushButton->setText(QApplication::translate("backAdmin", "\345\210\240\351\231\244", 0, QApplication::UnicodeUTF8));
        backTab->setTabText(backTab->indexOf(awardTab), QApplication::translate("backAdmin", "\345\245\226\345\212\261\350\247\204\345\210\231", 0, QApplication::UnicodeUTF8));
        dumpDatabaseLabel->setText(QApplication::translate("backAdmin", "\345\244\207\344\273\275\346\225\260\346\215\256\345\272\223\357\274\232", 0, QApplication::UnicodeUTF8));
        dumpBrowsePushButton->setText(QApplication::translate("backAdmin", "\346\265\217\350\247\210", 0, QApplication::UnicodeUTF8));
        dumpPushButton->setText(QApplication::translate("backAdmin", "\345\244\207\344\273\275", 0, QApplication::UnicodeUTF8));
        restoreDatabaseLabel->setText(QApplication::translate("backAdmin", "\346\201\242\345\244\215\346\225\260\346\215\256\345\272\223\357\274\232", 0, QApplication::UnicodeUTF8));
        restoreBrowsePushButton->setText(QApplication::translate("backAdmin", "\346\265\217\350\247\210", 0, QApplication::UnicodeUTF8));
        restorePushButton->setText(QApplication::translate("backAdmin", "\346\201\242\345\244\215", 0, QApplication::UnicodeUTF8));
        backTab->setTabText(backTab->indexOf(dumpTab), QApplication::translate("backAdmin", "\346\225\260\346\215\256\345\244\207\344\273\275/\346\201\242\345\244\215", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class backAdmin: public Ui_backAdmin {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BACK_H
