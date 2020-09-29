/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QCommandLinkButton>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
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
    QGridLayout *gridLayout_7;
    QTextBrowser *textBrowser_2;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *horizontalSpacer;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QComboBox *dolphinSelection;
    QSpacerItem *horizontalSpacer_3;
    QLabel *label_2;
    QComboBox *stateSelection;
    QSpacerItem *horizontalSpacer_4;
    QCommandLinkButton *submitState;
    QHBoxLayout *horizontalLayout_5;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_3;
    QSpacerItem *horizontalSpacer_5;
    QLabel *batteryPercentage;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_4;
    QSpacerItem *horizontalSpacer_6;
    QSlider *horizontalSlider;
    QSpacerItem *horizontalSpacer_8;
    QLabel *maxSpeedPercentage;
    QSpacerItem *horizontalSpacer_7;
    QTabWidget *tabWidget;
    QWidget *motor1tab;
    QGridLayout *gridLayout_2;
    QLabel *label_32;
    QLabel *m1Temp;
    QLabel *label_33;
    QLabel *m1Current;
    QLabel *label_37;
    QLabel *m1Speed;
    QWidget *motor2tab;
    QGridLayout *gridLayout_3;
    QLabel *label_20;
    QLabel *m2Temp;
    QLabel *label_21;
    QLabel *label_24;
    QLabel *label_25;
    QLabel *m2Speed;
    QWidget *motor3tab;
    QGridLayout *gridLayout_4;
    QLabel *label_26;
    QLabel *m3Temp;
    QLabel *label_27;
    QLabel *m3Current;
    QLabel *label_31;
    QLabel *m3Speed;
    QWidget *motor4tab;
    QGridLayout *gridLayout_5;
    QLabel *label_8;
    QLabel *m4Temp;
    QLabel *label_10;
    QLabel *m4Current;
    QLabel *label_12;
    QLabel *m4Speed;
    QSpacerItem *verticalSpacer_3;
    QVBoxLayout *verticalLayout;
    QSpinBox *cmdSpeedSpinBox;
    QHBoxLayout *horizontalLayout_8;
    QSpacerItem *horizontalSpacer_13;
    QSlider *speedSelection;
    QSpacerItem *horizontalSpacer_14;
    QLabel *label_7;
    QGridLayout *gridLayout_6;
    QHBoxLayout *horizontalLayout_7;
    QSpacerItem *horizontalSpacer_12;
    QPushButton *pushButton;
    QSpacerItem *horizontalSpacer_11;
    QVBoxLayout *verticalLayout_3;
    QPushButton *pushButton_5;
    QSpacerItem *verticalSpacer;
    QPushButton *pushButton_6;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton_3;
    QPushButton *pushButton_2;
    QHBoxLayout *horizontalLayout_6;
    QSpacerItem *horizontalSpacer_9;
    QPushButton *pushButton_4;
    QSpacerItem *horizontalSpacer_10;
    QSpacerItem *verticalSpacer_2;
    QWidget *swarmTab;
    QWidget *mapTab;
    QWidget *interfaceTab;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(891, 605);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        mainGridLayout = new QGridLayout(centralWidget);
        mainGridLayout->setSpacing(0);
        mainGridLayout->setContentsMargins(11, 11, 11, 11);
        mainGridLayout->setObjectName(QStringLiteral("mainGridLayout"));
        mainGridLayout->setContentsMargins(0, 0, 0, 0);
        controlTab = new QTabWidget(centralWidget);
        controlTab->setObjectName(QStringLiteral("controlTab"));
        overviewTap = new QWidget();
        overviewTap->setObjectName(QStringLiteral("overviewTap"));
        controlTab->addTab(overviewTap, QString());
        controlTab1 = new QWidget();
        controlTab1->setObjectName(QStringLiteral("controlTab1"));
        gridLayout_7 = new QGridLayout(controlTab1);
        gridLayout_7->setSpacing(6);
        gridLayout_7->setContentsMargins(11, 11, 11, 11);
        gridLayout_7->setObjectName(QStringLiteral("gridLayout_7"));
        textBrowser_2 = new QTextBrowser(controlTab1);
        textBrowser_2->setObjectName(QStringLiteral("textBrowser_2"));

        gridLayout_7->addWidget(textBrowser_2, 4, 4, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(148, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_7->addItem(horizontalSpacer_2, 4, 3, 1, 1);

        horizontalSpacer = new QSpacerItem(148, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_7->addItem(horizontalSpacer, 4, 1, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label = new QLabel(controlTab1);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout_2->addWidget(label);

        dolphinSelection = new QComboBox(controlTab1);
        dolphinSelection->setObjectName(QStringLiteral("dolphinSelection"));

        horizontalLayout_2->addWidget(dolphinSelection);

        horizontalSpacer_3 = new QSpacerItem(58, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);

        label_2 = new QLabel(controlTab1);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout_2->addWidget(label_2);

        stateSelection = new QComboBox(controlTab1);
        stateSelection->setObjectName(QStringLiteral("stateSelection"));

        horizontalLayout_2->addWidget(stateSelection);

        horizontalSpacer_4 = new QSpacerItem(58, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_4);

        submitState = new QCommandLinkButton(controlTab1);
        submitState->setObjectName(QStringLiteral("submitState"));

        horizontalLayout_2->addWidget(submitState);


        gridLayout_7->addLayout(horizontalLayout_2, 0, 0, 1, 5);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label_3 = new QLabel(controlTab1);
        label_3->setObjectName(QStringLiteral("label_3"));

        horizontalLayout_3->addWidget(label_3);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_5);

        batteryPercentage = new QLabel(controlTab1);
        batteryPercentage->setObjectName(QStringLiteral("batteryPercentage"));

        horizontalLayout_3->addWidget(batteryPercentage);


        verticalLayout_2->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        label_4 = new QLabel(controlTab1);
        label_4->setObjectName(QStringLiteral("label_4"));

        horizontalLayout_4->addWidget(label_4);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_6);

        horizontalSlider = new QSlider(controlTab1);
        horizontalSlider->setObjectName(QStringLiteral("horizontalSlider"));
        horizontalSlider->setMaximum(100);
        horizontalSlider->setValue(100);
        horizontalSlider->setOrientation(Qt::Horizontal);

        horizontalLayout_4->addWidget(horizontalSlider);

        horizontalSpacer_8 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_8);

        maxSpeedPercentage = new QLabel(controlTab1);
        maxSpeedPercentage->setObjectName(QStringLiteral("maxSpeedPercentage"));

        horizontalLayout_4->addWidget(maxSpeedPercentage);


        verticalLayout_2->addLayout(horizontalLayout_4);


        horizontalLayout_5->addLayout(verticalLayout_2);

        horizontalSpacer_7 = new QSpacerItem(208, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_7);

        tabWidget = new QTabWidget(controlTab1);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        motor1tab = new QWidget();
        motor1tab->setObjectName(QStringLiteral("motor1tab"));
        gridLayout_2 = new QGridLayout(motor1tab);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        label_32 = new QLabel(motor1tab);
        label_32->setObjectName(QStringLiteral("label_32"));

        gridLayout_2->addWidget(label_32, 0, 0, 1, 1);

        m1Temp = new QLabel(motor1tab);
        m1Temp->setObjectName(QStringLiteral("m1Temp"));

        gridLayout_2->addWidget(m1Temp, 0, 1, 1, 1);

        label_33 = new QLabel(motor1tab);
        label_33->setObjectName(QStringLiteral("label_33"));

        gridLayout_2->addWidget(label_33, 1, 0, 1, 1);

        m1Current = new QLabel(motor1tab);
        m1Current->setObjectName(QStringLiteral("m1Current"));

        gridLayout_2->addWidget(m1Current, 1, 1, 1, 1);

        label_37 = new QLabel(motor1tab);
        label_37->setObjectName(QStringLiteral("label_37"));

        gridLayout_2->addWidget(label_37, 2, 0, 1, 1);

        m1Speed = new QLabel(motor1tab);
        m1Speed->setObjectName(QStringLiteral("m1Speed"));

        gridLayout_2->addWidget(m1Speed, 2, 1, 1, 1);

        tabWidget->addTab(motor1tab, QString());
        motor2tab = new QWidget();
        motor2tab->setObjectName(QStringLiteral("motor2tab"));
        gridLayout_3 = new QGridLayout(motor2tab);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        label_20 = new QLabel(motor2tab);
        label_20->setObjectName(QStringLiteral("label_20"));

        gridLayout_3->addWidget(label_20, 0, 0, 1, 1);

        m2Temp = new QLabel(motor2tab);
        m2Temp->setObjectName(QStringLiteral("m2Temp"));

        gridLayout_3->addWidget(m2Temp, 0, 1, 1, 1);

        label_21 = new QLabel(motor2tab);
        label_21->setObjectName(QStringLiteral("label_21"));

        gridLayout_3->addWidget(label_21, 1, 0, 1, 1);

        label_24 = new QLabel(motor2tab);
        label_24->setObjectName(QStringLiteral("label_24"));

        gridLayout_3->addWidget(label_24, 1, 1, 1, 1);

        label_25 = new QLabel(motor2tab);
        label_25->setObjectName(QStringLiteral("label_25"));

        gridLayout_3->addWidget(label_25, 2, 0, 1, 1);

        m2Speed = new QLabel(motor2tab);
        m2Speed->setObjectName(QStringLiteral("m2Speed"));

        gridLayout_3->addWidget(m2Speed, 2, 1, 1, 1);

        tabWidget->addTab(motor2tab, QString());
        motor3tab = new QWidget();
        motor3tab->setObjectName(QStringLiteral("motor3tab"));
        gridLayout_4 = new QGridLayout(motor3tab);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        label_26 = new QLabel(motor3tab);
        label_26->setObjectName(QStringLiteral("label_26"));

        gridLayout_4->addWidget(label_26, 0, 0, 1, 1);

        m3Temp = new QLabel(motor3tab);
        m3Temp->setObjectName(QStringLiteral("m3Temp"));

        gridLayout_4->addWidget(m3Temp, 0, 1, 1, 1);

        label_27 = new QLabel(motor3tab);
        label_27->setObjectName(QStringLiteral("label_27"));

        gridLayout_4->addWidget(label_27, 1, 0, 1, 1);

        m3Current = new QLabel(motor3tab);
        m3Current->setObjectName(QStringLiteral("m3Current"));

        gridLayout_4->addWidget(m3Current, 1, 1, 1, 1);

        label_31 = new QLabel(motor3tab);
        label_31->setObjectName(QStringLiteral("label_31"));

        gridLayout_4->addWidget(label_31, 2, 0, 1, 1);

        m3Speed = new QLabel(motor3tab);
        m3Speed->setObjectName(QStringLiteral("m3Speed"));

        gridLayout_4->addWidget(m3Speed, 2, 1, 1, 1);

        tabWidget->addTab(motor3tab, QString());
        motor4tab = new QWidget();
        motor4tab->setObjectName(QStringLiteral("motor4tab"));
        gridLayout_5 = new QGridLayout(motor4tab);
        gridLayout_5->setSpacing(6);
        gridLayout_5->setContentsMargins(11, 11, 11, 11);
        gridLayout_5->setObjectName(QStringLiteral("gridLayout_5"));
        label_8 = new QLabel(motor4tab);
        label_8->setObjectName(QStringLiteral("label_8"));

        gridLayout_5->addWidget(label_8, 0, 0, 1, 1);

        m4Temp = new QLabel(motor4tab);
        m4Temp->setObjectName(QStringLiteral("m4Temp"));

        gridLayout_5->addWidget(m4Temp, 0, 1, 1, 1);

        label_10 = new QLabel(motor4tab);
        label_10->setObjectName(QStringLiteral("label_10"));

        gridLayout_5->addWidget(label_10, 1, 0, 1, 1);

        m4Current = new QLabel(motor4tab);
        m4Current->setObjectName(QStringLiteral("m4Current"));

        gridLayout_5->addWidget(m4Current, 1, 1, 1, 1);

        label_12 = new QLabel(motor4tab);
        label_12->setObjectName(QStringLiteral("label_12"));

        gridLayout_5->addWidget(label_12, 2, 0, 1, 1);

        m4Speed = new QLabel(motor4tab);
        m4Speed->setObjectName(QStringLiteral("m4Speed"));

        gridLayout_5->addWidget(m4Speed, 2, 1, 1, 1);

        tabWidget->addTab(motor4tab, QString());

        horizontalLayout_5->addWidget(tabWidget);


        gridLayout_7->addLayout(horizontalLayout_5, 2, 0, 1, 5);

        verticalSpacer_3 = new QSpacerItem(20, 177, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_7->addItem(verticalSpacer_3, 3, 0, 1, 5);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        cmdSpeedSpinBox = new QSpinBox(controlTab1);
        cmdSpeedSpinBox->setObjectName(QStringLiteral("cmdSpeedSpinBox"));
        cmdSpeedSpinBox->setAlignment(Qt::AlignCenter);
        cmdSpeedSpinBox->setMinimum(-100);
        cmdSpeedSpinBox->setMaximum(100);

        verticalLayout->addWidget(cmdSpeedSpinBox);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setSpacing(6);
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        horizontalSpacer_13 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_13);

        speedSelection = new QSlider(controlTab1);
        speedSelection->setObjectName(QStringLiteral("speedSelection"));
        speedSelection->setLayoutDirection(Qt::LeftToRight);
        speedSelection->setMinimum(-100);
        speedSelection->setMaximum(100);
        speedSelection->setSingleStep(5);
        speedSelection->setOrientation(Qt::Vertical);
        speedSelection->setTickPosition(QSlider::TicksBothSides);
        speedSelection->setTickInterval(25);

        horizontalLayout_8->addWidget(speedSelection);

        horizontalSpacer_14 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_14);


        verticalLayout->addLayout(horizontalLayout_8);

        label_7 = new QLabel(controlTab1);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label_7);


        gridLayout_7->addLayout(verticalLayout, 4, 2, 1, 1);

        gridLayout_6 = new QGridLayout();
        gridLayout_6->setSpacing(6);
        gridLayout_6->setObjectName(QStringLiteral("gridLayout_6"));
        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        horizontalSpacer_12 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_12);

        pushButton = new QPushButton(controlTab1);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        horizontalLayout_7->addWidget(pushButton);

        horizontalSpacer_11 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_11);


        gridLayout_6->addLayout(horizontalLayout_7, 0, 0, 1, 1);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        pushButton_5 = new QPushButton(controlTab1);
        pushButton_5->setObjectName(QStringLiteral("pushButton_5"));

        verticalLayout_3->addWidget(pushButton_5);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer);

        pushButton_6 = new QPushButton(controlTab1);
        pushButton_6->setObjectName(QStringLiteral("pushButton_6"));

        verticalLayout_3->addWidget(pushButton_6);


        gridLayout_6->addLayout(verticalLayout_3, 0, 1, 3, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        pushButton_3 = new QPushButton(controlTab1);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));

        horizontalLayout->addWidget(pushButton_3);

        pushButton_2 = new QPushButton(controlTab1);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));

        horizontalLayout->addWidget(pushButton_2);


        gridLayout_6->addLayout(horizontalLayout, 1, 0, 1, 1);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        horizontalSpacer_9 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_9);

        pushButton_4 = new QPushButton(controlTab1);
        pushButton_4->setObjectName(QStringLiteral("pushButton_4"));

        horizontalLayout_6->addWidget(pushButton_4);

        horizontalSpacer_10 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_10);


        gridLayout_6->addLayout(horizontalLayout_6, 2, 0, 1, 1);


        gridLayout_7->addLayout(gridLayout_6, 4, 0, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 177, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_7->addItem(verticalSpacer_2, 1, 0, 1, 5);

        controlTab->addTab(controlTab1, QString());
        swarmTab = new QWidget();
        swarmTab->setObjectName(QStringLiteral("swarmTab"));
        controlTab->addTab(swarmTab, QString());
        mapTab = new QWidget();
        mapTab->setObjectName(QStringLiteral("mapTab"));
        controlTab->addTab(mapTab, QString());
        interfaceTab = new QWidget();
        interfaceTab->setObjectName(QStringLiteral("interfaceTab"));
        controlTab->addTab(interfaceTab, QString());

        mainGridLayout->addWidget(controlTab, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 891, 22));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);
        QObject::connect(horizontalSlider, SIGNAL(valueChanged(int)), maxSpeedPercentage, SLOT(setNum(int)));
        QObject::connect(cmdSpeedSpinBox, SIGNAL(valueChanged(int)), speedSelection, SLOT(setValue(int)));
        QObject::connect(speedSelection, SIGNAL(valueChanged(int)), cmdSpeedSpinBox, SLOT(setValue(int)));

        controlTab->setCurrentIndex(1);
        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        controlTab->setTabText(controlTab->indexOf(overviewTap), QApplication::translate("MainWindow", "Overview", Q_NULLPTR));
        label->setText(QApplication::translate("MainWindow", "Robot :", Q_NULLPTR));
        dolphinSelection->clear();
        dolphinSelection->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "Dolphin1", Q_NULLPTR)
         << QApplication::translate("MainWindow", "Dolphin2", Q_NULLPTR)
         << QApplication::translate("MainWindow", "Dolphin3", Q_NULLPTR)
        );
        label_2->setText(QApplication::translate("MainWindow", "State", Q_NULLPTR));
        stateSelection->clear();
        stateSelection->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "Standby", Q_NULLPTR)
         << QApplication::translate("MainWindow", "AllStop", Q_NULLPTR)
         << QApplication::translate("MainWindow", "Teleop", Q_NULLPTR)
         << QApplication::translate("MainWindow", "Swarm Mode", Q_NULLPTR)
         << QApplication::translate("MainWindow", "Demo Mode", Q_NULLPTR)
        );
        submitState->setText(QApplication::translate("MainWindow", "Update ", Q_NULLPTR));
        label_3->setText(QApplication::translate("MainWindow", "Battery:", Q_NULLPTR));
        batteryPercentage->setText(QApplication::translate("MainWindow", "100%", Q_NULLPTR));
        label_4->setText(QApplication::translate("MainWindow", "Max Speed:", Q_NULLPTR));
        maxSpeedPercentage->setText(QApplication::translate("MainWindow", "100", Q_NULLPTR));
        label_32->setText(QApplication::translate("MainWindow", "Motor Temp:", Q_NULLPTR));
        m1Temp->setText(QApplication::translate("MainWindow", "30*", Q_NULLPTR));
        label_33->setText(QApplication::translate("MainWindow", "Motor Current:", Q_NULLPTR));
        m1Current->setText(QApplication::translate("MainWindow", ".675 A", Q_NULLPTR));
        label_37->setText(QApplication::translate("MainWindow", "Motor Speed:", Q_NULLPTR));
        m1Speed->setText(QApplication::translate("MainWindow", "75 MPH", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(motor1tab), QApplication::translate("MainWindow", "Motor 1", Q_NULLPTR));
        label_20->setText(QApplication::translate("MainWindow", "Motor Temp:", Q_NULLPTR));
        m2Temp->setText(QApplication::translate("MainWindow", "30*", Q_NULLPTR));
        label_21->setText(QApplication::translate("MainWindow", "Motor Current:", Q_NULLPTR));
        label_24->setText(QApplication::translate("MainWindow", ".675 A", Q_NULLPTR));
        label_25->setText(QApplication::translate("MainWindow", "Motor Speed:", Q_NULLPTR));
        m2Speed->setText(QApplication::translate("MainWindow", "75 MPH", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(motor2tab), QApplication::translate("MainWindow", "Motor 2", Q_NULLPTR));
        label_26->setText(QApplication::translate("MainWindow", "Motor Temp:", Q_NULLPTR));
        m3Temp->setText(QApplication::translate("MainWindow", "30*", Q_NULLPTR));
        label_27->setText(QApplication::translate("MainWindow", "Motor Current:", Q_NULLPTR));
        m3Current->setText(QApplication::translate("MainWindow", ".675 A", Q_NULLPTR));
        label_31->setText(QApplication::translate("MainWindow", "Motor Speed:", Q_NULLPTR));
        m3Speed->setText(QApplication::translate("MainWindow", "75 MPH", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(motor3tab), QApplication::translate("MainWindow", "Motor 3", Q_NULLPTR));
        label_8->setText(QApplication::translate("MainWindow", "Motor Temp:", Q_NULLPTR));
        m4Temp->setText(QApplication::translate("MainWindow", "30*", Q_NULLPTR));
        label_10->setText(QApplication::translate("MainWindow", "Motor Current:", Q_NULLPTR));
        m4Current->setText(QApplication::translate("MainWindow", ".675 A", Q_NULLPTR));
        label_12->setText(QApplication::translate("MainWindow", "Motor Speed:", Q_NULLPTR));
        m4Speed->setText(QApplication::translate("MainWindow", "75 MPH", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(motor4tab), QApplication::translate("MainWindow", "Motor 4", Q_NULLPTR));
        label_7->setText(QApplication::translate("MainWindow", "Speed", Q_NULLPTR));
        pushButton->setText(QApplication::translate("MainWindow", "Forward (W)", Q_NULLPTR));
#ifndef QT_NO_SHORTCUT
        pushButton->setShortcut(QApplication::translate("MainWindow", "W", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        pushButton_5->setText(QApplication::translate("MainWindow", "Faster (Q)", Q_NULLPTR));
#ifndef QT_NO_SHORTCUT
        pushButton_5->setShortcut(QApplication::translate("MainWindow", "Q", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        pushButton_6->setText(QApplication::translate("MainWindow", "Slower (E)", Q_NULLPTR));
#ifndef QT_NO_SHORTCUT
        pushButton_6->setShortcut(QApplication::translate("MainWindow", "E", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        pushButton_3->setText(QApplication::translate("MainWindow", "Left (A)", Q_NULLPTR));
#ifndef QT_NO_SHORTCUT
        pushButton_3->setShortcut(QApplication::translate("MainWindow", "A", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        pushButton_2->setText(QApplication::translate("MainWindow", "Right (D)", Q_NULLPTR));
#ifndef QT_NO_SHORTCUT
        pushButton_2->setShortcut(QApplication::translate("MainWindow", "D", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        pushButton_4->setText(QApplication::translate("MainWindow", "Reverse (S)", Q_NULLPTR));
#ifndef QT_NO_SHORTCUT
        pushButton_4->setShortcut(QApplication::translate("MainWindow", "S", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        controlTab->setTabText(controlTab->indexOf(controlTab1), QApplication::translate("MainWindow", "Control", Q_NULLPTR));
        controlTab->setTabText(controlTab->indexOf(swarmTab), QApplication::translate("MainWindow", "Swarm", Q_NULLPTR));
        controlTab->setTabText(controlTab->indexOf(mapTab), QApplication::translate("MainWindow", "Map", Q_NULLPTR));
        controlTab->setTabText(controlTab->indexOf(interfaceTab), QApplication::translate("MainWindow", "Interface", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
