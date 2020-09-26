/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QCommandLinkButton>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QGridLayout *mainGridLayout;
    QTabWidget *controlTab;
    QWidget *overviewTap;
    QWidget *controlTab1;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QComboBox *comboBox;
    QSpacerItem *horizontalSpacer_3;
    QLabel *label_2;
    QComboBox *comboBox_2;
    QSpacerItem *horizontalSpacer_4;
    QCommandLinkButton *commandLinkButton;
    QSpacerItem *verticalSpacer_2;
    QHBoxLayout *horizontalLayout_5;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_3;
    QSpacerItem *horizontalSpacer_5;
    QLabel *label_5;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_4;
    QSpacerItem *horizontalSpacer_6;
    QLabel *label_6;
    QSpacerItem *horizontalSpacer_7;
    QTabWidget *tabWidget;
    QWidget *motor1tab;
    QGridLayout *gridLayout_2;
    QLabel *label_32;
    QLabel *label_35;
    QLabel *label_33;
    QLabel *label_36;
    QLabel *label_37;
    QLabel *label_34;
    QWidget *motor2tab;
    QGridLayout *gridLayout_3;
    QLabel *label_20;
    QLabel *label_23;
    QLabel *label_21;
    QLabel *label_24;
    QLabel *label_25;
    QLabel *label_22;
    QWidget *motor4tab;
    QGridLayout *gridLayout_5;
    QLabel *label_8;
    QLabel *label_9;
    QLabel *label_10;
    QLabel *label_11;
    QLabel *label_12;
    QLabel *label_13;
    QWidget *motor3tab;
    QGridLayout *gridLayout_4;
    QLabel *label_26;
    QLabel *label_29;
    QLabel *label_27;
    QLabel *label_30;
    QLabel *label_31;
    QLabel *label_28;
    QSpacerItem *verticalSpacer_3;
    QHBoxLayout *horizontalLayout;
    QTextBrowser *textBrowser;
    QSpacerItem *horizontalSpacer;
    QVBoxLayout *verticalLayout;
    QSlider *verticalSlider;
    QLabel *label_7;
    QSpacerItem *horizontalSpacer_2;
    QTextBrowser *textBrowser_2;
    QWidget *swarmTab;
    QWidget *mapTab;
    QWidget *interfaceTab;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1086, 916);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        mainGridLayout = new QGridLayout(centralWidget);
        mainGridLayout->setSpacing(0);
        mainGridLayout->setContentsMargins(11, 11, 11, 11);
        mainGridLayout->setObjectName(QString::fromUtf8("mainGridLayout"));
        mainGridLayout->setContentsMargins(0, 0, 0, 0);
        controlTab = new QTabWidget(centralWidget);
        controlTab->setObjectName(QString::fromUtf8("controlTab"));
        overviewTap = new QWidget();
        overviewTap->setObjectName(QString::fromUtf8("overviewTap"));
        controlTab->addTab(overviewTap, QString());
        controlTab1 = new QWidget();
        controlTab1->setObjectName(QString::fromUtf8("controlTab1"));
        verticalLayout_3 = new QVBoxLayout(controlTab1);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label = new QLabel(controlTab1);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout_2->addWidget(label);

        comboBox = new QComboBox(controlTab1);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName(QString::fromUtf8("comboBox"));

        horizontalLayout_2->addWidget(comboBox);

        horizontalSpacer_3 = new QSpacerItem(58, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);

        label_2 = new QLabel(controlTab1);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_2->addWidget(label_2);

        comboBox_2 = new QComboBox(controlTab1);
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->setObjectName(QString::fromUtf8("comboBox_2"));

        horizontalLayout_2->addWidget(comboBox_2);

        horizontalSpacer_4 = new QSpacerItem(58, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_4);

        commandLinkButton = new QCommandLinkButton(controlTab1);
        commandLinkButton->setObjectName(QString::fromUtf8("commandLinkButton"));

        horizontalLayout_2->addWidget(commandLinkButton);


        verticalLayout_3->addLayout(horizontalLayout_2);

        verticalSpacer_2 = new QSpacerItem(20, 177, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer_2);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_3 = new QLabel(controlTab1);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout_3->addWidget(label_3);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_5);

        label_5 = new QLabel(controlTab1);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        horizontalLayout_3->addWidget(label_5);


        verticalLayout_2->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label_4 = new QLabel(controlTab1);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        horizontalLayout_4->addWidget(label_4);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_6);

        label_6 = new QLabel(controlTab1);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        horizontalLayout_4->addWidget(label_6);


        verticalLayout_2->addLayout(horizontalLayout_4);


        horizontalLayout_5->addLayout(verticalLayout_2);

        horizontalSpacer_7 = new QSpacerItem(208, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_7);

        tabWidget = new QTabWidget(controlTab1);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        motor1tab = new QWidget();
        motor1tab->setObjectName(QString::fromUtf8("motor1tab"));
        gridLayout_2 = new QGridLayout(motor1tab);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        label_32 = new QLabel(motor1tab);
        label_32->setObjectName(QString::fromUtf8("label_32"));

        gridLayout_2->addWidget(label_32, 0, 0, 1, 1);

        label_35 = new QLabel(motor1tab);
        label_35->setObjectName(QString::fromUtf8("label_35"));

        gridLayout_2->addWidget(label_35, 0, 1, 1, 1);

        label_33 = new QLabel(motor1tab);
        label_33->setObjectName(QString::fromUtf8("label_33"));

        gridLayout_2->addWidget(label_33, 1, 0, 1, 1);

        label_36 = new QLabel(motor1tab);
        label_36->setObjectName(QString::fromUtf8("label_36"));

        gridLayout_2->addWidget(label_36, 1, 1, 1, 1);

        label_37 = new QLabel(motor1tab);
        label_37->setObjectName(QString::fromUtf8("label_37"));

        gridLayout_2->addWidget(label_37, 2, 0, 1, 1);

        label_34 = new QLabel(motor1tab);
        label_34->setObjectName(QString::fromUtf8("label_34"));

        gridLayout_2->addWidget(label_34, 2, 1, 1, 1);

        tabWidget->addTab(motor1tab, QString());
        motor2tab = new QWidget();
        motor2tab->setObjectName(QString::fromUtf8("motor2tab"));
        gridLayout_3 = new QGridLayout(motor2tab);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        label_20 = new QLabel(motor2tab);
        label_20->setObjectName(QString::fromUtf8("label_20"));

        gridLayout_3->addWidget(label_20, 0, 0, 1, 1);

        label_23 = new QLabel(motor2tab);
        label_23->setObjectName(QString::fromUtf8("label_23"));

        gridLayout_3->addWidget(label_23, 0, 1, 1, 1);

        label_21 = new QLabel(motor2tab);
        label_21->setObjectName(QString::fromUtf8("label_21"));

        gridLayout_3->addWidget(label_21, 1, 0, 1, 1);

        label_24 = new QLabel(motor2tab);
        label_24->setObjectName(QString::fromUtf8("label_24"));

        gridLayout_3->addWidget(label_24, 1, 1, 1, 1);

        label_25 = new QLabel(motor2tab);
        label_25->setObjectName(QString::fromUtf8("label_25"));

        gridLayout_3->addWidget(label_25, 2, 0, 1, 1);

        label_22 = new QLabel(motor2tab);
        label_22->setObjectName(QString::fromUtf8("label_22"));

        gridLayout_3->addWidget(label_22, 2, 1, 1, 1);

        tabWidget->addTab(motor2tab, QString());
        motor4tab = new QWidget();
        motor4tab->setObjectName(QString::fromUtf8("motor4tab"));
        gridLayout_5 = new QGridLayout(motor4tab);
        gridLayout_5->setSpacing(6);
        gridLayout_5->setContentsMargins(11, 11, 11, 11);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        label_8 = new QLabel(motor4tab);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        gridLayout_5->addWidget(label_8, 0, 0, 1, 1);

        label_9 = new QLabel(motor4tab);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        gridLayout_5->addWidget(label_9, 0, 1, 1, 1);

        label_10 = new QLabel(motor4tab);
        label_10->setObjectName(QString::fromUtf8("label_10"));

        gridLayout_5->addWidget(label_10, 1, 0, 1, 1);

        label_11 = new QLabel(motor4tab);
        label_11->setObjectName(QString::fromUtf8("label_11"));

        gridLayout_5->addWidget(label_11, 1, 1, 1, 1);

        label_12 = new QLabel(motor4tab);
        label_12->setObjectName(QString::fromUtf8("label_12"));

        gridLayout_5->addWidget(label_12, 2, 0, 1, 1);

        label_13 = new QLabel(motor4tab);
        label_13->setObjectName(QString::fromUtf8("label_13"));

        gridLayout_5->addWidget(label_13, 2, 1, 1, 1);

        tabWidget->addTab(motor4tab, QString());
        motor3tab = new QWidget();
        motor3tab->setObjectName(QString::fromUtf8("motor3tab"));
        gridLayout_4 = new QGridLayout(motor3tab);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        label_26 = new QLabel(motor3tab);
        label_26->setObjectName(QString::fromUtf8("label_26"));

        gridLayout_4->addWidget(label_26, 0, 0, 1, 1);

        label_29 = new QLabel(motor3tab);
        label_29->setObjectName(QString::fromUtf8("label_29"));

        gridLayout_4->addWidget(label_29, 0, 1, 1, 1);

        label_27 = new QLabel(motor3tab);
        label_27->setObjectName(QString::fromUtf8("label_27"));

        gridLayout_4->addWidget(label_27, 1, 0, 1, 1);

        label_30 = new QLabel(motor3tab);
        label_30->setObjectName(QString::fromUtf8("label_30"));

        gridLayout_4->addWidget(label_30, 1, 1, 1, 1);

        label_31 = new QLabel(motor3tab);
        label_31->setObjectName(QString::fromUtf8("label_31"));

        gridLayout_4->addWidget(label_31, 2, 0, 1, 1);

        label_28 = new QLabel(motor3tab);
        label_28->setObjectName(QString::fromUtf8("label_28"));

        gridLayout_4->addWidget(label_28, 2, 1, 1, 1);

        tabWidget->addTab(motor3tab, QString());

        horizontalLayout_5->addWidget(tabWidget);


        verticalLayout_3->addLayout(horizontalLayout_5);

        verticalSpacer_3 = new QSpacerItem(20, 177, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer_3);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        textBrowser = new QTextBrowser(controlTab1);
        textBrowser->setObjectName(QString::fromUtf8("textBrowser"));

        horizontalLayout->addWidget(textBrowser);

        horizontalSpacer = new QSpacerItem(148, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalSlider = new QSlider(controlTab1);
        verticalSlider->setObjectName(QString::fromUtf8("verticalSlider"));
        verticalSlider->setMinimum(-100);
        verticalSlider->setMaximum(100);
        verticalSlider->setSingleStep(5);
        verticalSlider->setOrientation(Qt::Vertical);
        verticalSlider->setTickPosition(QSlider::TicksBothSides);
        verticalSlider->setTickInterval(25);

        verticalLayout->addWidget(verticalSlider);

        label_7 = new QLabel(controlTab1);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        verticalLayout->addWidget(label_7);


        horizontalLayout->addLayout(verticalLayout);

        horizontalSpacer_2 = new QSpacerItem(148, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        textBrowser_2 = new QTextBrowser(controlTab1);
        textBrowser_2->setObjectName(QString::fromUtf8("textBrowser_2"));

        horizontalLayout->addWidget(textBrowser_2);


        verticalLayout_3->addLayout(horizontalLayout);

        controlTab->addTab(controlTab1, QString());
        swarmTab = new QWidget();
        swarmTab->setObjectName(QString::fromUtf8("swarmTab"));
        controlTab->addTab(swarmTab, QString());
        mapTab = new QWidget();
        mapTab->setObjectName(QString::fromUtf8("mapTab"));
        controlTab->addTab(mapTab, QString());
        interfaceTab = new QWidget();
        interfaceTab->setObjectName(QString::fromUtf8("interfaceTab"));
        controlTab->addTab(interfaceTab, QString());

        mainGridLayout->addWidget(controlTab, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1086, 25));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        controlTab->setCurrentIndex(1);
        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        controlTab->setTabText(controlTab->indexOf(overviewTap), QApplication::translate("MainWindow", "Overview", nullptr));
        label->setText(QApplication::translate("MainWindow", "Robot :", nullptr));
        comboBox->setItemText(0, QApplication::translate("MainWindow", "Dolphin1", nullptr));
        comboBox->setItemText(1, QApplication::translate("MainWindow", "Dolphin2", nullptr));
        comboBox->setItemText(2, QApplication::translate("MainWindow", "Dolphin3", nullptr));

        label_2->setText(QApplication::translate("MainWindow", "State", nullptr));
        comboBox_2->setItemText(0, QApplication::translate("MainWindow", "Standby", nullptr));
        comboBox_2->setItemText(1, QApplication::translate("MainWindow", "AllStop", nullptr));
        comboBox_2->setItemText(2, QApplication::translate("MainWindow", "Teleop", nullptr));
        comboBox_2->setItemText(3, QApplication::translate("MainWindow", "Swarm Mode", nullptr));
        comboBox_2->setItemText(4, QApplication::translate("MainWindow", "Demo Mode", nullptr));

        commandLinkButton->setText(QApplication::translate("MainWindow", "Update ", nullptr));
        label_3->setText(QApplication::translate("MainWindow", "Battery:", nullptr));
        label_5->setText(QApplication::translate("MainWindow", "100%", nullptr));
        label_4->setText(QApplication::translate("MainWindow", "Max Speed:", nullptr));
        label_6->setText(QApplication::translate("MainWindow", "100%", nullptr));
        label_32->setText(QApplication::translate("MainWindow", "Motor Temp:", nullptr));
        label_35->setText(QApplication::translate("MainWindow", "30*", nullptr));
        label_33->setText(QApplication::translate("MainWindow", "Motor Current:", nullptr));
        label_36->setText(QApplication::translate("MainWindow", ".675 A", nullptr));
        label_37->setText(QApplication::translate("MainWindow", "Motor Speed:", nullptr));
        label_34->setText(QApplication::translate("MainWindow", "75 MPH", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(motor1tab), QApplication::translate("MainWindow", "Motor 1", nullptr));
        label_20->setText(QApplication::translate("MainWindow", "Motor Temp:", nullptr));
        label_23->setText(QApplication::translate("MainWindow", "30*", nullptr));
        label_21->setText(QApplication::translate("MainWindow", "Motor Current:", nullptr));
        label_24->setText(QApplication::translate("MainWindow", ".675 A", nullptr));
        label_25->setText(QApplication::translate("MainWindow", "Motor Speed:", nullptr));
        label_22->setText(QApplication::translate("MainWindow", "75 MPH", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(motor2tab), QApplication::translate("MainWindow", "Motor 2", nullptr));
        label_8->setText(QApplication::translate("MainWindow", "Motor Temp:", nullptr));
        label_9->setText(QApplication::translate("MainWindow", "30*", nullptr));
        label_10->setText(QApplication::translate("MainWindow", "Motor Current:", nullptr));
        label_11->setText(QApplication::translate("MainWindow", ".675 A", nullptr));
        label_12->setText(QApplication::translate("MainWindow", "Motor Speed:", nullptr));
        label_13->setText(QApplication::translate("MainWindow", "75 MPH", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(motor4tab), QApplication::translate("MainWindow", "Motor 4", nullptr));
        label_26->setText(QApplication::translate("MainWindow", "Motor Temp:", nullptr));
        label_29->setText(QApplication::translate("MainWindow", "30*", nullptr));
        label_27->setText(QApplication::translate("MainWindow", "Motor Current:", nullptr));
        label_30->setText(QApplication::translate("MainWindow", ".675 A", nullptr));
        label_31->setText(QApplication::translate("MainWindow", "Motor Speed:", nullptr));
        label_28->setText(QApplication::translate("MainWindow", "75 MPH", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(motor3tab), QApplication::translate("MainWindow", "Motor 3", nullptr));
        label_7->setText(QApplication::translate("MainWindow", "Speed", nullptr));
        controlTab->setTabText(controlTab->indexOf(controlTab1), QApplication::translate("MainWindow", "Control", nullptr));
        controlTab->setTabText(controlTab->indexOf(swarmTab), QApplication::translate("MainWindow", "Swarm", nullptr));
        controlTab->setTabText(controlTab->indexOf(mapTab), QApplication::translate("MainWindow", "Map", nullptr));
        controlTab->setTabText(controlTab->indexOf(interfaceTab), QApplication::translate("MainWindow", "Interface", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
