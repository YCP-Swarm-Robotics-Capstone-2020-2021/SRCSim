/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QCommandLinkButton>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
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
    QAction *actionKill_All;
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout_6;
    QTabWidget *uProcessWatchLabel;
    QWidget *overviewTap;
    QWidget *controlTab;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_9;
    QLabel *label;
    QComboBox *dolphinSelection;
    QSpacerItem *horizontalSpacer_3;
    QLabel *label_2;
    QComboBox *stateSelection;
    QSpacerItem *horizontalSpacer_6;
    QGridLayout *gridLayout_9;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_9;
    QLabel *statusLabel;
    QLabel *label_11;
    QLabel *CurrentStateLabel;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_22;
    QLabel *versionLabel;
    QSpacerItem *horizontalSpacer_4;
    QCommandLinkButton *submitState;
    QSpacerItem *verticalSpacer_5;
    QHBoxLayout *horizontalLayout_13;
    QLabel *label_23;
    QLabel *uProcessWatchReport;
    QHBoxLayout *horizontalLayout_14;
    QLabel *label_24;
    QLabel *commitMessageLabel;
    QSpacerItem *verticalSpacer_2;
    QHBoxLayout *horizontalLayout_5;
    QHBoxLayout *horizontalLayout;
    QGridLayout *gridLayout_6;
    QPushButton *fasterButton;
    QPushButton *brakeButton;
    QGridLayout *gridLayout;
    QSpacerItem *horizontalSpacer_12;
    QPushButton *forwardButton;
    QSpacerItem *horizontalSpacer_11;
    QPushButton *leftButton;
    QPushButton *rightButton;
    QSpacerItem *horizontalSpacer_9;
    QPushButton *reverseButton;
    QSpacerItem *horizontalSpacer_10;
    QPushButton *slowerButton;
    QSpacerItem *horizontalSpacer_18;
    QSpacerItem *horizontalSpacer;
    QVBoxLayout *verticalLayout;
    QSpinBox *cmdSpeedSpinBox;
    QHBoxLayout *horizontalLayout_8;
    QSpacerItem *horizontalSpacer_13;
    QSlider *speedSelection;
    QSpacerItem *horizontalSpacer_14;
    QLabel *label_7;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_3;
    QSpacerItem *horizontalSpacer_5;
    QLabel *batteryPercentage;
    QHBoxLayout *maxSpeedSlider_2;
    QLabel *label_4;
    QSlider *maxSpeedSlider;
    QLabel *maxSpeedPercentage;
    QSpacerItem *horizontalSpacer_2;
    QTabWidget *motorTabWidget;
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
    QLabel *m2Current;
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
    QSpacerItem *verticalSpacer;
    QLabel *label_5;
    QTextBrowser *textBrowser;
    QWidget *swarmTab;
    QVBoxLayout *verticalLayout_8;
    QHBoxLayout *horizontalLayout_11;
    QHBoxLayout *horizontalLayout_10;
    QLabel *label_13;
    QComboBox *shapeSelection;
    QGridLayout *gridLayout_7;
    QLabel *label_14;
    QSlider *horizontalSlider_3;
    QSpinBox *widthBox;
    QSpinBox *lengthBox;
    QLabel *label_15;
    QSlider *horizontalSlider_2;
    QLabel *label_16;
    QSlider *horizontalSlider;
    QSpinBox *rotationBox;
    QVBoxLayout *verticalLayout_6;
    QSpacerItem *verticalSpacer_3;
    QCommandLinkButton *submitZeta;
    QSpacerItem *verticalSpacer_4;
    QGridLayout *gridLayout_8;
    QLabel *label_18;
    QLabel *label_19;
    QLabel *label_17;
    QVBoxLayout *verticalLayout_7;
    QGridLayout *glLayout;
    QHBoxLayout *horizontalLayout_12;
    QSlider *zoomSlider;
    QTextBrowser *textBrowser_2;
    QWidget *mapTab;
    QWidget *interfaceTab;
    QVBoxLayout *verticalLayout_5;
    QLabel *label_6;
    QTextBrowser *warningBrowser;
    QPushButton *LOG_BOOKMARK_BUTTON;
    QPushButton *runPushButton;
    QHBoxLayout *horizontalLayout_4;
    QLabel *HeightLabel;
    QSpinBox *HeightSpinBox;
    QLabel *WidthLabel;
    QSpinBox *WidthSpinBox;
    QPushButton *boundaryPushButton;
    QMenuBar *menuBar;
    QMenu *menuCommands;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1312, 708);
        actionKill_All = new QAction(MainWindow);
        actionKill_All->setObjectName(QString::fromUtf8("actionKill_All"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        horizontalLayout_6 = new QHBoxLayout(centralWidget);
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        uProcessWatchLabel = new QTabWidget(centralWidget);
        uProcessWatchLabel->setObjectName(QString::fromUtf8("uProcessWatchLabel"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(2);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(uProcessWatchLabel->sizePolicy().hasHeightForWidth());
        uProcessWatchLabel->setSizePolicy(sizePolicy);
        overviewTap = new QWidget();
        overviewTap->setObjectName(QString::fromUtf8("overviewTap"));
        uProcessWatchLabel->addTab(overviewTap, QString());
        controlTab = new QWidget();
        controlTab->setObjectName(QString::fromUtf8("controlTab"));
        verticalLayout_3 = new QVBoxLayout(controlTab);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setSpacing(6);
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        label = new QLabel(controlTab);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout_9->addWidget(label);

        dolphinSelection = new QComboBox(controlTab);
        dolphinSelection->addItem(QString());
        dolphinSelection->setObjectName(QString::fromUtf8("dolphinSelection"));

        horizontalLayout_9->addWidget(dolphinSelection);

        horizontalSpacer_3 = new QSpacerItem(58, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_9->addItem(horizontalSpacer_3);

        label_2 = new QLabel(controlTab);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_9->addWidget(label_2);

        stateSelection = new QComboBox(controlTab);
        stateSelection->addItem(QString());
        stateSelection->addItem(QString());
        stateSelection->addItem(QString());
        stateSelection->addItem(QString());
        stateSelection->addItem(QString());
        stateSelection->setObjectName(QString::fromUtf8("stateSelection"));

        horizontalLayout_9->addWidget(stateSelection);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_9->addItem(horizontalSpacer_6);

        gridLayout_9 = new QGridLayout();
        gridLayout_9->setSpacing(6);
        gridLayout_9->setObjectName(QString::fromUtf8("gridLayout_9"));
        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        label_9 = new QLabel(controlTab);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        horizontalLayout_7->addWidget(label_9);

        statusLabel = new QLabel(controlTab);
        statusLabel->setObjectName(QString::fromUtf8("statusLabel"));
        statusLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_7->addWidget(statusLabel);


        gridLayout_9->addLayout(horizontalLayout_7, 0, 0, 1, 2);

        label_11 = new QLabel(controlTab);
        label_11->setObjectName(QString::fromUtf8("label_11"));

        gridLayout_9->addWidget(label_11, 1, 0, 1, 1);

        CurrentStateLabel = new QLabel(controlTab);
        CurrentStateLabel->setObjectName(QString::fromUtf8("CurrentStateLabel"));
        CurrentStateLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_9->addWidget(CurrentStateLabel, 1, 1, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_22 = new QLabel(controlTab);
        label_22->setObjectName(QString::fromUtf8("label_22"));

        horizontalLayout_2->addWidget(label_22);

        versionLabel = new QLabel(controlTab);
        versionLabel->setObjectName(QString::fromUtf8("versionLabel"));
        versionLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_2->addWidget(versionLabel);


        gridLayout_9->addLayout(horizontalLayout_2, 2, 0, 1, 2);


        horizontalLayout_9->addLayout(gridLayout_9);

        horizontalSpacer_4 = new QSpacerItem(58, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_9->addItem(horizontalSpacer_4);

        submitState = new QCommandLinkButton(controlTab);
        submitState->setObjectName(QString::fromUtf8("submitState"));

        horizontalLayout_9->addWidget(submitState);


        verticalLayout_3->addLayout(horizontalLayout_9);

        verticalSpacer_5 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Minimum);

        verticalLayout_3->addItem(verticalSpacer_5);

        horizontalLayout_13 = new QHBoxLayout();
        horizontalLayout_13->setSpacing(6);
        horizontalLayout_13->setObjectName(QString::fromUtf8("horizontalLayout_13"));
        label_23 = new QLabel(controlTab);
        label_23->setObjectName(QString::fromUtf8("label_23"));
        label_23->setAlignment(Qt::AlignCenter);

        horizontalLayout_13->addWidget(label_23);

        uProcessWatchReport = new QLabel(controlTab);
        uProcessWatchReport->setObjectName(QString::fromUtf8("uProcessWatchReport"));
        uProcessWatchReport->setAlignment(Qt::AlignCenter);

        horizontalLayout_13->addWidget(uProcessWatchReport);


        verticalLayout_3->addLayout(horizontalLayout_13);

        horizontalLayout_14 = new QHBoxLayout();
        horizontalLayout_14->setSpacing(6);
        horizontalLayout_14->setObjectName(QString::fromUtf8("horizontalLayout_14"));
        label_24 = new QLabel(controlTab);
        label_24->setObjectName(QString::fromUtf8("label_24"));
        label_24->setAlignment(Qt::AlignCenter);

        horizontalLayout_14->addWidget(label_24);

        commitMessageLabel = new QLabel(controlTab);
        commitMessageLabel->setObjectName(QString::fromUtf8("commitMessageLabel"));
        commitMessageLabel->setAlignment(Qt::AlignCenter);

        horizontalLayout_14->addWidget(commitMessageLabel);


        verticalLayout_3->addLayout(horizontalLayout_14);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Minimum);

        verticalLayout_3->addItem(verticalSpacer_2);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        gridLayout_6 = new QGridLayout();
        gridLayout_6->setSpacing(6);
        gridLayout_6->setObjectName(QString::fromUtf8("gridLayout_6"));
        fasterButton = new QPushButton(controlTab);
        fasterButton->setObjectName(QString::fromUtf8("fasterButton"));

        gridLayout_6->addWidget(fasterButton, 0, 1, 1, 1);

        brakeButton = new QPushButton(controlTab);
        brakeButton->setObjectName(QString::fromUtf8("brakeButton"));

        gridLayout_6->addWidget(brakeButton, 1, 1, 1, 1);

        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        horizontalSpacer_12 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_12, 0, 0, 1, 1);

        forwardButton = new QPushButton(controlTab);
        forwardButton->setObjectName(QString::fromUtf8("forwardButton"));
        forwardButton->setAutoRepeat(true);
        forwardButton->setAutoRepeatDelay(50);
        forwardButton->setAutoRepeatInterval(50);

        gridLayout->addWidget(forwardButton, 0, 1, 1, 2);

        horizontalSpacer_11 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_11, 0, 3, 1, 1);

        leftButton = new QPushButton(controlTab);
        leftButton->setObjectName(QString::fromUtf8("leftButton"));
        leftButton->setAutoRepeat(true);
        leftButton->setAutoRepeatDelay(50);
        leftButton->setAutoRepeatInterval(50);

        gridLayout->addWidget(leftButton, 1, 0, 1, 2);

        rightButton = new QPushButton(controlTab);
        rightButton->setObjectName(QString::fromUtf8("rightButton"));
        rightButton->setAutoRepeat(true);
        rightButton->setAutoRepeatDelay(50);
        rightButton->setAutoRepeatInterval(50);

        gridLayout->addWidget(rightButton, 1, 2, 1, 2);

        horizontalSpacer_9 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_9, 2, 0, 1, 1);

        reverseButton = new QPushButton(controlTab);
        reverseButton->setObjectName(QString::fromUtf8("reverseButton"));
        reverseButton->setAutoRepeat(true);
        reverseButton->setAutoRepeatDelay(50);
        reverseButton->setAutoRepeatInterval(50);

        gridLayout->addWidget(reverseButton, 2, 1, 1, 2);

        horizontalSpacer_10 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_10, 2, 3, 1, 1);


        gridLayout_6->addLayout(gridLayout, 0, 0, 3, 1);

        slowerButton = new QPushButton(controlTab);
        slowerButton->setObjectName(QString::fromUtf8("slowerButton"));

        gridLayout_6->addWidget(slowerButton, 2, 1, 1, 1);

        horizontalSpacer_18 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_6->addItem(horizontalSpacer_18, 1, 2, 1, 1);


        horizontalLayout->addLayout(gridLayout_6);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Minimum, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        cmdSpeedSpinBox = new QSpinBox(controlTab);
        cmdSpeedSpinBox->setObjectName(QString::fromUtf8("cmdSpeedSpinBox"));
        cmdSpeedSpinBox->setAlignment(Qt::AlignCenter);
        cmdSpeedSpinBox->setMinimum(-100);
        cmdSpeedSpinBox->setMaximum(100);
        cmdSpeedSpinBox->setValue(50);

        verticalLayout->addWidget(cmdSpeedSpinBox);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setSpacing(6);
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        horizontalSpacer_13 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_13);

        speedSelection = new QSlider(controlTab);
        speedSelection->setObjectName(QString::fromUtf8("speedSelection"));
        speedSelection->setLayoutDirection(Qt::LeftToRight);
        speedSelection->setMinimum(-100);
        speedSelection->setMaximum(100);
        speedSelection->setSingleStep(5);
        speedSelection->setValue(50);
        speedSelection->setOrientation(Qt::Vertical);
        speedSelection->setInvertedAppearance(true);
        speedSelection->setTickPosition(QSlider::TicksBothSides);
        speedSelection->setTickInterval(25);

        horizontalLayout_8->addWidget(speedSelection);

        horizontalSpacer_14 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_14);


        verticalLayout->addLayout(horizontalLayout_8);

        label_7 = new QLabel(controlTab);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label_7);


        horizontalLayout->addLayout(verticalLayout);


        horizontalLayout_5->addLayout(horizontalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_3 = new QLabel(controlTab);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout_3->addWidget(label_3);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_5);

        batteryPercentage = new QLabel(controlTab);
        batteryPercentage->setObjectName(QString::fromUtf8("batteryPercentage"));

        horizontalLayout_3->addWidget(batteryPercentage);


        verticalLayout_2->addLayout(horizontalLayout_3);

        maxSpeedSlider_2 = new QHBoxLayout();
        maxSpeedSlider_2->setSpacing(6);
        maxSpeedSlider_2->setObjectName(QString::fromUtf8("maxSpeedSlider_2"));
        label_4 = new QLabel(controlTab);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        maxSpeedSlider_2->addWidget(label_4);

        maxSpeedSlider = new QSlider(controlTab);
        maxSpeedSlider->setObjectName(QString::fromUtf8("maxSpeedSlider"));
        maxSpeedSlider->setMinimumSize(QSize(100, 0));
        maxSpeedSlider->setMaximum(100);
        maxSpeedSlider->setValue(100);
        maxSpeedSlider->setOrientation(Qt::Horizontal);

        maxSpeedSlider_2->addWidget(maxSpeedSlider);

        maxSpeedPercentage = new QLabel(controlTab);
        maxSpeedPercentage->setObjectName(QString::fromUtf8("maxSpeedPercentage"));

        maxSpeedSlider_2->addWidget(maxSpeedPercentage);


        verticalLayout_2->addLayout(maxSpeedSlider_2);


        horizontalLayout_5->addLayout(verticalLayout_2);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Minimum, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_2);

        motorTabWidget = new QTabWidget(controlTab);
        motorTabWidget->setObjectName(QString::fromUtf8("motorTabWidget"));
        motor1tab = new QWidget();
        motor1tab->setObjectName(QString::fromUtf8("motor1tab"));
        gridLayout_2 = new QGridLayout(motor1tab);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        label_32 = new QLabel(motor1tab);
        label_32->setObjectName(QString::fromUtf8("label_32"));

        gridLayout_2->addWidget(label_32, 0, 0, 1, 1);

        m1Temp = new QLabel(motor1tab);
        m1Temp->setObjectName(QString::fromUtf8("m1Temp"));

        gridLayout_2->addWidget(m1Temp, 0, 1, 1, 1);

        label_33 = new QLabel(motor1tab);
        label_33->setObjectName(QString::fromUtf8("label_33"));

        gridLayout_2->addWidget(label_33, 1, 0, 1, 1);

        m1Current = new QLabel(motor1tab);
        m1Current->setObjectName(QString::fromUtf8("m1Current"));

        gridLayout_2->addWidget(m1Current, 1, 1, 1, 1);

        label_37 = new QLabel(motor1tab);
        label_37->setObjectName(QString::fromUtf8("label_37"));

        gridLayout_2->addWidget(label_37, 2, 0, 1, 1);

        m1Speed = new QLabel(motor1tab);
        m1Speed->setObjectName(QString::fromUtf8("m1Speed"));

        gridLayout_2->addWidget(m1Speed, 2, 1, 1, 1);

        motorTabWidget->addTab(motor1tab, QString());
        motor2tab = new QWidget();
        motor2tab->setObjectName(QString::fromUtf8("motor2tab"));
        gridLayout_3 = new QGridLayout(motor2tab);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        label_20 = new QLabel(motor2tab);
        label_20->setObjectName(QString::fromUtf8("label_20"));

        gridLayout_3->addWidget(label_20, 0, 0, 1, 1);

        m2Temp = new QLabel(motor2tab);
        m2Temp->setObjectName(QString::fromUtf8("m2Temp"));

        gridLayout_3->addWidget(m2Temp, 0, 1, 1, 1);

        label_21 = new QLabel(motor2tab);
        label_21->setObjectName(QString::fromUtf8("label_21"));

        gridLayout_3->addWidget(label_21, 1, 0, 1, 1);

        m2Current = new QLabel(motor2tab);
        m2Current->setObjectName(QString::fromUtf8("m2Current"));

        gridLayout_3->addWidget(m2Current, 1, 1, 1, 1);

        label_25 = new QLabel(motor2tab);
        label_25->setObjectName(QString::fromUtf8("label_25"));

        gridLayout_3->addWidget(label_25, 2, 0, 1, 1);

        m2Speed = new QLabel(motor2tab);
        m2Speed->setObjectName(QString::fromUtf8("m2Speed"));

        gridLayout_3->addWidget(m2Speed, 2, 1, 1, 1);

        motorTabWidget->addTab(motor2tab, QString());
        motor3tab = new QWidget();
        motor3tab->setObjectName(QString::fromUtf8("motor3tab"));
        gridLayout_4 = new QGridLayout(motor3tab);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        label_26 = new QLabel(motor3tab);
        label_26->setObjectName(QString::fromUtf8("label_26"));

        gridLayout_4->addWidget(label_26, 0, 0, 1, 1);

        m3Temp = new QLabel(motor3tab);
        m3Temp->setObjectName(QString::fromUtf8("m3Temp"));

        gridLayout_4->addWidget(m3Temp, 0, 1, 1, 1);

        label_27 = new QLabel(motor3tab);
        label_27->setObjectName(QString::fromUtf8("label_27"));

        gridLayout_4->addWidget(label_27, 1, 0, 1, 1);

        m3Current = new QLabel(motor3tab);
        m3Current->setObjectName(QString::fromUtf8("m3Current"));

        gridLayout_4->addWidget(m3Current, 1, 1, 1, 1);

        label_31 = new QLabel(motor3tab);
        label_31->setObjectName(QString::fromUtf8("label_31"));

        gridLayout_4->addWidget(label_31, 2, 0, 1, 1);

        m3Speed = new QLabel(motor3tab);
        m3Speed->setObjectName(QString::fromUtf8("m3Speed"));

        gridLayout_4->addWidget(m3Speed, 2, 1, 1, 1);

        motorTabWidget->addTab(motor3tab, QString());
        motor4tab = new QWidget();
        motor4tab->setObjectName(QString::fromUtf8("motor4tab"));
        gridLayout_5 = new QGridLayout(motor4tab);
        gridLayout_5->setSpacing(6);
        gridLayout_5->setContentsMargins(11, 11, 11, 11);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        label_8 = new QLabel(motor4tab);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        gridLayout_5->addWidget(label_8, 0, 0, 1, 1);

        m4Temp = new QLabel(motor4tab);
        m4Temp->setObjectName(QString::fromUtf8("m4Temp"));

        gridLayout_5->addWidget(m4Temp, 0, 1, 1, 1);

        label_10 = new QLabel(motor4tab);
        label_10->setObjectName(QString::fromUtf8("label_10"));

        gridLayout_5->addWidget(label_10, 1, 0, 1, 1);

        m4Current = new QLabel(motor4tab);
        m4Current->setObjectName(QString::fromUtf8("m4Current"));

        gridLayout_5->addWidget(m4Current, 1, 1, 1, 1);

        label_12 = new QLabel(motor4tab);
        label_12->setObjectName(QString::fromUtf8("label_12"));

        gridLayout_5->addWidget(label_12, 2, 0, 1, 1);

        m4Speed = new QLabel(motor4tab);
        m4Speed->setObjectName(QString::fromUtf8("m4Speed"));

        gridLayout_5->addWidget(m4Speed, 2, 1, 1, 1);

        motorTabWidget->addTab(motor4tab, QString());

        horizontalLayout_5->addWidget(motorTabWidget);


        verticalLayout_3->addLayout(horizontalLayout_5);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Minimum);

        verticalLayout_3->addItem(verticalSpacer);

        label_5 = new QLabel(controlTab);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setAlignment(Qt::AlignCenter);

        verticalLayout_3->addWidget(label_5);

        textBrowser = new QTextBrowser(controlTab);
        textBrowser->setObjectName(QString::fromUtf8("textBrowser"));
        textBrowser->setAutoFillBackground(true);
        textBrowser->setStyleSheet(QString::fromUtf8("background-color:grey"));

        verticalLayout_3->addWidget(textBrowser);

        uProcessWatchLabel->addTab(controlTab, QString());
        swarmTab = new QWidget();
        swarmTab->setObjectName(QString::fromUtf8("swarmTab"));
        verticalLayout_8 = new QVBoxLayout(swarmTab);
        verticalLayout_8->setSpacing(6);
        verticalLayout_8->setContentsMargins(11, 11, 11, 11);
        verticalLayout_8->setObjectName(QString::fromUtf8("verticalLayout_8"));
        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setSpacing(6);
        horizontalLayout_11->setObjectName(QString::fromUtf8("horizontalLayout_11"));
        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setSpacing(6);
        horizontalLayout_10->setObjectName(QString::fromUtf8("horizontalLayout_10"));
        label_13 = new QLabel(swarmTab);
        label_13->setObjectName(QString::fromUtf8("label_13"));

        horizontalLayout_10->addWidget(label_13);

        shapeSelection = new QComboBox(swarmTab);
        shapeSelection->setObjectName(QString::fromUtf8("shapeSelection"));

        horizontalLayout_10->addWidget(shapeSelection);

        gridLayout_7 = new QGridLayout();
        gridLayout_7->setSpacing(6);
        gridLayout_7->setObjectName(QString::fromUtf8("gridLayout_7"));
        label_14 = new QLabel(swarmTab);
        label_14->setObjectName(QString::fromUtf8("label_14"));

        gridLayout_7->addWidget(label_14, 0, 0, 2, 1);

        horizontalSlider_3 = new QSlider(swarmTab);
        horizontalSlider_3->setObjectName(QString::fromUtf8("horizontalSlider_3"));
        horizontalSlider_3->setMinimum(1);
        horizontalSlider_3->setMaximum(6);
        horizontalSlider_3->setOrientation(Qt::Horizontal);

        gridLayout_7->addWidget(horizontalSlider_3, 0, 1, 2, 1);

        widthBox = new QSpinBox(swarmTab);
        widthBox->setObjectName(QString::fromUtf8("widthBox"));
        widthBox->setMinimum(1);
        widthBox->setMaximum(6);

        gridLayout_7->addWidget(widthBox, 0, 2, 1, 1);

        lengthBox = new QSpinBox(swarmTab);
        lengthBox->setObjectName(QString::fromUtf8("lengthBox"));
        lengthBox->setMinimum(1);
        lengthBox->setMaximum(6);

        gridLayout_7->addWidget(lengthBox, 1, 2, 2, 1);

        label_15 = new QLabel(swarmTab);
        label_15->setObjectName(QString::fromUtf8("label_15"));

        gridLayout_7->addWidget(label_15, 2, 0, 1, 1);

        horizontalSlider_2 = new QSlider(swarmTab);
        horizontalSlider_2->setObjectName(QString::fromUtf8("horizontalSlider_2"));
        horizontalSlider_2->setMinimum(1);
        horizontalSlider_2->setMaximum(6);
        horizontalSlider_2->setOrientation(Qt::Horizontal);

        gridLayout_7->addWidget(horizontalSlider_2, 2, 1, 1, 1);

        label_16 = new QLabel(swarmTab);
        label_16->setObjectName(QString::fromUtf8("label_16"));

        gridLayout_7->addWidget(label_16, 3, 0, 1, 1);

        horizontalSlider = new QSlider(swarmTab);
        horizontalSlider->setObjectName(QString::fromUtf8("horizontalSlider"));
        horizontalSlider->setMinimum(-180);
        horizontalSlider->setMaximum(180);
        horizontalSlider->setOrientation(Qt::Horizontal);

        gridLayout_7->addWidget(horizontalSlider, 3, 1, 1, 1);

        rotationBox = new QSpinBox(swarmTab);
        rotationBox->setObjectName(QString::fromUtf8("rotationBox"));
        rotationBox->setMinimum(-180);
        rotationBox->setMaximum(180);

        gridLayout_7->addWidget(rotationBox, 3, 2, 1, 1);


        horizontalLayout_10->addLayout(gridLayout_7);


        horizontalLayout_11->addLayout(horizontalLayout_10);

        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setSpacing(6);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Minimum);

        verticalLayout_6->addItem(verticalSpacer_3);

        submitZeta = new QCommandLinkButton(swarmTab);
        submitZeta->setObjectName(QString::fromUtf8("submitZeta"));

        verticalLayout_6->addWidget(submitZeta);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Minimum);

        verticalLayout_6->addItem(verticalSpacer_4);


        horizontalLayout_11->addLayout(verticalLayout_6);


        verticalLayout_8->addLayout(horizontalLayout_11);

        gridLayout_8 = new QGridLayout();
        gridLayout_8->setSpacing(6);
        gridLayout_8->setObjectName(QString::fromUtf8("gridLayout_8"));
        label_18 = new QLabel(swarmTab);
        label_18->setObjectName(QString::fromUtf8("label_18"));
        label_18->setAlignment(Qt::AlignCenter);

        gridLayout_8->addWidget(label_18, 0, 0, 1, 1);

        label_19 = new QLabel(swarmTab);
        label_19->setObjectName(QString::fromUtf8("label_19"));
        label_19->setAlignment(Qt::AlignCenter);

        gridLayout_8->addWidget(label_19, 0, 1, 1, 1);

        label_17 = new QLabel(swarmTab);
        label_17->setObjectName(QString::fromUtf8("label_17"));
        label_17->setAlignment(Qt::AlignCenter);

        gridLayout_8->addWidget(label_17, 0, 2, 1, 1);

        verticalLayout_7 = new QVBoxLayout();
        verticalLayout_7->setSpacing(6);
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        glLayout = new QGridLayout();
        glLayout->setSpacing(6);
        glLayout->setObjectName(QString::fromUtf8("glLayout"));

        verticalLayout_7->addLayout(glLayout);


        gridLayout_8->addLayout(verticalLayout_7, 1, 0, 1, 1);

        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setSpacing(6);
        horizontalLayout_12->setObjectName(QString::fromUtf8("horizontalLayout_12"));
        zoomSlider = new QSlider(swarmTab);
        zoomSlider->setObjectName(QString::fromUtf8("zoomSlider"));
        zoomSlider->setStyleSheet(QString::fromUtf8("QSlider::groove:horizontal {\n"
"border: 1px solid #bbb;\n"
"background: white;\n"
"height: 10px;\n"
"border-radius: 4px;\n"
"}\n"
"\n"
"QSlider::sub-page:horizontal {\n"
"background: qlineargradient(x1: 0, y1: 0,    x2: 0, y2: 1,\n"
"    stop: 0 #66e, stop: 1 #bbf);\n"
"background: qlineargradient(x1: 0, y1: 0.2, x2: 1, y2: 1,\n"
"    stop: 0 #bbf, stop: 1 #55f);\n"
"border: 1px solid #777;\n"
"height: 10px;\n"
"border-radius: 4px;\n"
"}\n"
"\n"
"QSlider::add-page:horizontal {\n"
"background: #fff;\n"
"border: 1px solid #777;\n"
"height: 10px;\n"
"border-radius: 4px;\n"
"}\n"
"\n"
"QSlider::handle:horizontal {\n"
"background: qlineargradient(x1:0, y1:0, x2:1, y2:1,\n"
"    stop:0 #eee, stop:1 #ccc);\n"
"border: 1px solid #777;\n"
"width: 13px;\n"
"margin-top: -2px;\n"
"margin-bottom: -2px;\n"
"border-radius: 4px;\n"
"}\n"
"\n"
"QSlider::handle:horizontal:hover {\n"
"background: qlineargradient(x1:0, y1:0, x2:1, y2:1,\n"
"    stop:0 #fff, stop:1 #ddd);\n"
"border: 1px solid #444;\n"
"border-radius: 4px;\n"
"}\n"
""
                        "\n"
"QSlider::sub-page:horizontal:disabled {\n"
"background: #bbb;\n"
"border-color: #999;\n"
"}\n"
"\n"
"QSlider::add-page:horizontal:disabled {\n"
"background: #eee;\n"
"border-color: #999;\n"
"}\n"
"\n"
"QSlider::handle:horizontal:disabled {\n"
"background: #eee;\n"
"border: 1px solid #aaa;\n"
"border-radius: 4px;\n"
"}"));
        zoomSlider->setMinimum(1);
        zoomSlider->setMaximum(30);
        zoomSlider->setSingleStep(2);
        zoomSlider->setValue(6);
        zoomSlider->setOrientation(Qt::Vertical);

        horizontalLayout_12->addWidget(zoomSlider);


        gridLayout_8->addLayout(horizontalLayout_12, 1, 1, 1, 1);

        textBrowser_2 = new QTextBrowser(swarmTab);
        textBrowser_2->setObjectName(QString::fromUtf8("textBrowser_2"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(textBrowser_2->sizePolicy().hasHeightForWidth());
        textBrowser_2->setSizePolicy(sizePolicy1);
        textBrowser_2->setStyleSheet(QString::fromUtf8("background-color:rgb(102, 102, 102)"));

        gridLayout_8->addWidget(textBrowser_2, 1, 2, 1, 1);


        verticalLayout_8->addLayout(gridLayout_8);

        uProcessWatchLabel->addTab(swarmTab, QString());
        mapTab = new QWidget();
        mapTab->setObjectName(QString::fromUtf8("mapTab"));
        uProcessWatchLabel->addTab(mapTab, QString());
        interfaceTab = new QWidget();
        interfaceTab->setObjectName(QString::fromUtf8("interfaceTab"));
        uProcessWatchLabel->addTab(interfaceTab, QString());

        horizontalLayout_6->addWidget(uProcessWatchLabel);

        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        label_6 = new QLabel(centralWidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(1);
        sizePolicy2.setHeightForWidth(label_6->sizePolicy().hasHeightForWidth());
        label_6->setSizePolicy(sizePolicy2);
        label_6->setAlignment(Qt::AlignCenter);

        verticalLayout_5->addWidget(label_6);

        warningBrowser = new QTextBrowser(centralWidget);
        warningBrowser->setObjectName(QString::fromUtf8("warningBrowser"));
        QSizePolicy sizePolicy3(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(40);
        sizePolicy3.setHeightForWidth(warningBrowser->sizePolicy().hasHeightForWidth());
        warningBrowser->setSizePolicy(sizePolicy3);
        warningBrowser->setMinimumSize(QSize(400, 0));
        warningBrowser->setStyleSheet(QString::fromUtf8("background-color:black"));

        verticalLayout_5->addWidget(warningBrowser);

        LOG_BOOKMARK_BUTTON = new QPushButton(centralWidget);
        LOG_BOOKMARK_BUTTON->setObjectName(QString::fromUtf8("LOG_BOOKMARK_BUTTON"));

        verticalLayout_5->addWidget(LOG_BOOKMARK_BUTTON);

        runPushButton = new QPushButton(centralWidget);
        runPushButton->setObjectName(QString::fromUtf8("runPushButton"));

        verticalLayout_5->addWidget(runPushButton);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        HeightLabel = new QLabel(centralWidget);
        HeightLabel->setObjectName(QString::fromUtf8("HeightLabel"));

        horizontalLayout_4->addWidget(HeightLabel);

        HeightSpinBox = new QSpinBox(centralWidget);
        HeightSpinBox->setObjectName(QString::fromUtf8("HeightSpinBox"));
        HeightSpinBox->setValue(6);

        horizontalLayout_4->addWidget(HeightSpinBox);

        WidthLabel = new QLabel(centralWidget);
        WidthLabel->setObjectName(QString::fromUtf8("WidthLabel"));

        horizontalLayout_4->addWidget(WidthLabel);

        WidthSpinBox = new QSpinBox(centralWidget);
        WidthSpinBox->setObjectName(QString::fromUtf8("WidthSpinBox"));
        WidthSpinBox->setMaximum(20);
        WidthSpinBox->setValue(6);

        horizontalLayout_4->addWidget(WidthSpinBox);

        boundaryPushButton = new QPushButton(centralWidget);
        boundaryPushButton->setObjectName(QString::fromUtf8("boundaryPushButton"));

        horizontalLayout_4->addWidget(boundaryPushButton);


        verticalLayout_5->addLayout(horizontalLayout_4);


        horizontalLayout_6->addLayout(verticalLayout_5);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1312, 22));
        menuCommands = new QMenu(menuBar);
        menuCommands->setObjectName(QString::fromUtf8("menuCommands"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuCommands->menuAction());
        menuCommands->addAction(actionKill_All);

        retranslateUi(MainWindow);
        QObject::connect(cmdSpeedSpinBox, SIGNAL(valueChanged(int)), speedSelection, SLOT(setValue(int)));
        QObject::connect(maxSpeedSlider, SIGNAL(valueChanged(int)), maxSpeedPercentage, SLOT(setNum(int)));
        QObject::connect(speedSelection, SIGNAL(valueChanged(int)), cmdSpeedSpinBox, SLOT(setValue(int)));
        QObject::connect(horizontalSlider_3, SIGNAL(valueChanged(int)), widthBox, SLOT(setValue(int)));
        QObject::connect(lengthBox, SIGNAL(valueChanged(int)), horizontalSlider_2, SLOT(setValue(int)));
        QObject::connect(rotationBox, SIGNAL(valueChanged(int)), horizontalSlider, SLOT(setValue(int)));
        QObject::connect(horizontalSlider_2, SIGNAL(valueChanged(int)), lengthBox, SLOT(setValue(int)));
        QObject::connect(horizontalSlider, SIGNAL(valueChanged(int)), rotationBox, SLOT(setValue(int)));

        uProcessWatchLabel->setCurrentIndex(1);
        motorTabWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "SRC Control GUI", nullptr));
        actionKill_All->setText(QCoreApplication::translate("MainWindow", "Kill All", nullptr));
        uProcessWatchLabel->setTabText(uProcessWatchLabel->indexOf(overviewTap), QCoreApplication::translate("MainWindow", "Overview", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Robot :", nullptr));
        dolphinSelection->setItemText(0, QCoreApplication::translate("MainWindow", "All", nullptr));

        label_2->setText(QCoreApplication::translate("MainWindow", "Cmd State:", nullptr));
        stateSelection->setItemText(0, QCoreApplication::translate("MainWindow", "Standby", nullptr));
        stateSelection->setItemText(1, QCoreApplication::translate("MainWindow", "AllStop", nullptr));
        stateSelection->setItemText(2, QCoreApplication::translate("MainWindow", "Teleop", nullptr));
        stateSelection->setItemText(3, QCoreApplication::translate("MainWindow", "SwarmMode", nullptr));
        stateSelection->setItemText(4, QCoreApplication::translate("MainWindow", "DemoMode", nullptr));

        label_9->setText(QCoreApplication::translate("MainWindow", "Status:", nullptr));
        statusLabel->setText(QCoreApplication::translate("MainWindow", "Normal", nullptr));
        label_11->setText(QCoreApplication::translate("MainWindow", "Current State:", nullptr));
        CurrentStateLabel->setText(QCoreApplication::translate("MainWindow", "STANDBY", nullptr));
        label_22->setText(QCoreApplication::translate("MainWindow", "Version:", nullptr));
        versionLabel->setText(QCoreApplication::translate("MainWindow", "N/A", nullptr));
        submitState->setText(QCoreApplication::translate("MainWindow", "Update ", nullptr));
        label_23->setText(QCoreApplication::translate("MainWindow", "uProcessWatch Report:", nullptr));
        uProcessWatchReport->setText(QCoreApplication::translate("MainWindow", "N/A", nullptr));
        label_24->setText(QCoreApplication::translate("MainWindow", "Commit Message: ", nullptr));
        commitMessageLabel->setText(QCoreApplication::translate("MainWindow", "N/A", nullptr));
        fasterButton->setText(QCoreApplication::translate("MainWindow", "Faster (Q)", nullptr));
#if QT_CONFIG(shortcut)
        fasterButton->setShortcut(QCoreApplication::translate("MainWindow", "Q", nullptr));
#endif // QT_CONFIG(shortcut)
        brakeButton->setText(QCoreApplication::translate("MainWindow", "Brake (Space)", nullptr));
#if QT_CONFIG(shortcut)
        brakeButton->setShortcut(QCoreApplication::translate("MainWindow", "Space", nullptr));
#endif // QT_CONFIG(shortcut)
        forwardButton->setText(QCoreApplication::translate("MainWindow", "Forward (W)", nullptr));
#if QT_CONFIG(shortcut)
        forwardButton->setShortcut(QCoreApplication::translate("MainWindow", "W", nullptr));
#endif // QT_CONFIG(shortcut)
        leftButton->setText(QCoreApplication::translate("MainWindow", "Left (A)", nullptr));
#if QT_CONFIG(shortcut)
        leftButton->setShortcut(QCoreApplication::translate("MainWindow", "A", nullptr));
#endif // QT_CONFIG(shortcut)
        rightButton->setText(QCoreApplication::translate("MainWindow", "Right (D)", nullptr));
#if QT_CONFIG(shortcut)
        rightButton->setShortcut(QCoreApplication::translate("MainWindow", "D", nullptr));
#endif // QT_CONFIG(shortcut)
        reverseButton->setText(QCoreApplication::translate("MainWindow", "Reverse (S)", nullptr));
#if QT_CONFIG(shortcut)
        reverseButton->setShortcut(QCoreApplication::translate("MainWindow", "S", nullptr));
#endif // QT_CONFIG(shortcut)
        slowerButton->setText(QCoreApplication::translate("MainWindow", "Slower (E)", nullptr));
#if QT_CONFIG(shortcut)
        slowerButton->setShortcut(QCoreApplication::translate("MainWindow", "E", nullptr));
#endif // QT_CONFIG(shortcut)
        label_7->setText(QCoreApplication::translate("MainWindow", "Speed", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "Battery:", nullptr));
        batteryPercentage->setText(QCoreApplication::translate("MainWindow", "100%", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "Max Speed:", nullptr));
        maxSpeedPercentage->setText(QCoreApplication::translate("MainWindow", "100", nullptr));
        label_32->setText(QCoreApplication::translate("MainWindow", "Motor Temp:", nullptr));
        m1Temp->setText(QCoreApplication::translate("MainWindow", "30*", nullptr));
        label_33->setText(QCoreApplication::translate("MainWindow", "Motor Current:", nullptr));
        m1Current->setText(QCoreApplication::translate("MainWindow", ".675 A", nullptr));
        label_37->setText(QCoreApplication::translate("MainWindow", "Motor Speed:", nullptr));
        m1Speed->setText(QCoreApplication::translate("MainWindow", "75 MPH", nullptr));
        motorTabWidget->setTabText(motorTabWidget->indexOf(motor1tab), QCoreApplication::translate("MainWindow", "Motor 1", nullptr));
        label_20->setText(QCoreApplication::translate("MainWindow", "Motor Temp:", nullptr));
        m2Temp->setText(QCoreApplication::translate("MainWindow", "30*", nullptr));
        label_21->setText(QCoreApplication::translate("MainWindow", "Motor Current:", nullptr));
        m2Current->setText(QCoreApplication::translate("MainWindow", ".675 A", nullptr));
        label_25->setText(QCoreApplication::translate("MainWindow", "Motor Speed:", nullptr));
        m2Speed->setText(QCoreApplication::translate("MainWindow", "75 MPH", nullptr));
        motorTabWidget->setTabText(motorTabWidget->indexOf(motor2tab), QCoreApplication::translate("MainWindow", "Motor 2", nullptr));
        label_26->setText(QCoreApplication::translate("MainWindow", "Motor Temp:", nullptr));
        m3Temp->setText(QCoreApplication::translate("MainWindow", "30*", nullptr));
        label_27->setText(QCoreApplication::translate("MainWindow", "Motor Current:", nullptr));
        m3Current->setText(QCoreApplication::translate("MainWindow", ".675 A", nullptr));
        label_31->setText(QCoreApplication::translate("MainWindow", "Motor Speed:", nullptr));
        m3Speed->setText(QCoreApplication::translate("MainWindow", "75 MPH", nullptr));
        motorTabWidget->setTabText(motorTabWidget->indexOf(motor3tab), QCoreApplication::translate("MainWindow", "Motor 3", nullptr));
        label_8->setText(QCoreApplication::translate("MainWindow", "Motor Temp:", nullptr));
        m4Temp->setText(QCoreApplication::translate("MainWindow", "30*", nullptr));
        label_10->setText(QCoreApplication::translate("MainWindow", "Motor Current:", nullptr));
        m4Current->setText(QCoreApplication::translate("MainWindow", ".675 A", nullptr));
        label_12->setText(QCoreApplication::translate("MainWindow", "Motor Speed:", nullptr));
        m4Speed->setText(QCoreApplication::translate("MainWindow", "75 MPH", nullptr));
        motorTabWidget->setTabText(motorTabWidget->indexOf(motor4tab), QCoreApplication::translate("MainWindow", "Motor 4", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "Debug Console", nullptr));
        uProcessWatchLabel->setTabText(uProcessWatchLabel->indexOf(controlTab), QCoreApplication::translate("MainWindow", "Control", nullptr));
        label_13->setText(QCoreApplication::translate("MainWindow", "Formation Shape:", nullptr));
        label_14->setText(QCoreApplication::translate("MainWindow", "Width:", nullptr));
        label_15->setText(QCoreApplication::translate("MainWindow", "Length:", nullptr));
        label_16->setText(QCoreApplication::translate("MainWindow", "Rotation:", nullptr));
        submitZeta->setText(QCoreApplication::translate("MainWindow", "Submit", nullptr));
        label_18->setText(QCoreApplication::translate("MainWindow", "Formation Preveiw", nullptr));
        label_19->setText(QCoreApplication::translate("MainWindow", "Zoom View", nullptr));
        label_17->setText(QCoreApplication::translate("MainWindow", "Debug Output", nullptr));
        uProcessWatchLabel->setTabText(uProcessWatchLabel->indexOf(swarmTab), QCoreApplication::translate("MainWindow", "Swarm", nullptr));
        uProcessWatchLabel->setTabText(uProcessWatchLabel->indexOf(mapTab), QCoreApplication::translate("MainWindow", "Map", nullptr));
        uProcessWatchLabel->setTabText(uProcessWatchLabel->indexOf(interfaceTab), QCoreApplication::translate("MainWindow", "Interface", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "Warnings", nullptr));
        LOG_BOOKMARK_BUTTON->setText(QCoreApplication::translate("MainWindow", "BOOKMARK LOG", nullptr));
        runPushButton->setText(QCoreApplication::translate("MainWindow", "Start Run", nullptr));
        HeightLabel->setText(QCoreApplication::translate("MainWindow", "Height(ft)", nullptr));
        WidthLabel->setText(QCoreApplication::translate("MainWindow", "Width (Ft)", nullptr));
        boundaryPushButton->setText(QCoreApplication::translate("MainWindow", "Update Boundary", nullptr));
        menuCommands->setTitle(QCoreApplication::translate("MainWindow", "Commands", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
