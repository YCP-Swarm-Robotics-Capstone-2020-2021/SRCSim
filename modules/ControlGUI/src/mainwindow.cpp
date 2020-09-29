#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_currentState(EnumDefs::VehicleStates::STANDBY),
    m_maxSpeed(100)
{
    ui->setupUi(this);
    connect(ui->submitState,SIGNAL(released()), this, SLOT(onSubmitStateButtonClicked()));
    connect(ui->dolphinSelection,SIGNAL(currentTextChanged(QString)),this,SLOT(onCurrentBotChanged(QString)));
    connect(ui->stateSelection,SIGNAL(currentTextChanged(QString)),this,SLOT(onCurrentStateChanged(QString)));
    connect(ui->maxSpeedSlider,SIGNAL(valueChanged(int)),this,SLOT(onMaxSpeedChanged(int)));
    connect(ui->forwardButton, SIGNAL(pressed()), this, SLOT(onForwardButtonPressed()));
    connect(ui->reverseButton, SIGNAL(pressed()), this, SLOT(onBackwardButtonPressed()));
    connect(ui->leftButton, SIGNAL(pressed()), this, SLOT(onLeftButtonPressed()));
    connect(ui->rightButton, SIGNAL(pressed()), this, SLOT(onRightButtonPressed()));
    connect(ui->fasterButton, SIGNAL(pressed()), this, SLOT(onSpeedUpButtonPressed()));
    connect(ui->slowerButton, SIGNAL(pressed()), this, SLOT(onSlowDownButtonPressed()));
    connect(ui->brakeButton, SIGNAL(pressed()), this, SLOT(onBrakeButtonPressed()));

    updateMotorSpeed(20, 1);
    updateMotorSpeed(45, 4);
    updateMotorSpeed(67, 6);

    updateMotorCurrent(20, 2);
    updateMotorCurrent(57, 3);
    updateMotorCurrent(88, 0);

    updateBatteryPerc(50);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setBotList(QList<QString> list)
{
    ui->dolphinSelection->clear();
    for(int i = 0; i < list.size(); i++)
    {
        ui->dolphinSelection->insertItem(i, list[i]);
    }
    ui->dolphinSelection->insertItem(list.size(), "All");
    m_numBots = list.size();
}

void MainWindow::onSubmitStateButtonClicked()
{
    emit sendStateCMD(m_currentState, m_currentBotID, m_maxSpeed);
    qDebug()<<" "<<m_currentBotID<<" "<<m_currentState<<" "<<m_maxSpeed;
}

void MainWindow::onCurrentStateChanged(QString state)
{
    EnumDefs::VehicleStates tempState = EnumDefs::VehicleStates(0);
    while(tempState != EnumDefs::VehicleStates::UILAST){
        if(state.toUpper() == defs.UIStateMap[tempState]){
            m_currentState = tempState;
        }
        tempState = EnumDefs::VehicleStates(int(tempState)+1);
    }
    qDebug()<<defs.UIStateMap[m_currentState];
}

void MainWindow::onCurrentBotChanged(QString bot)
{
    m_currentBotID = bot;
    qDebug()<<m_currentBotID;
}

void MainWindow::onForwardButtonPressed()
{

}

void MainWindow::onLeftButtonPressed()
{

}

void MainWindow::onRightButtonPressed()
{

}

void MainWindow::onBackwardButtonPressed()
{

}

void MainWindow::onSpeedUpButtonPressed()
{
    ui->speedSelection->setValue(int(ui->speedSelection->value()+SPEED_INTERVAL));
}

void MainWindow::onSlowDownButtonPressed()
{
    ui->speedSelection->setValue(int(ui->speedSelection->value()-SPEED_INTERVAL));
}

void MainWindow::onBrakeButtonPressed()
{
    ui->speedSelection->setValue(0);
}

void MainWindow::updateDebugText(QString msg)
{
    ui->textBrowser->append(msg);
}

void MainWindow::updateBatteryPerc(double perc)
{
    ui->batteryPercentage->setText(QString::number(perc)+"%");
}

void MainWindow::updateMotorSpeed(double speed, int motor)
{
    switch(motor){
        case 1:
            ui->m1Speed->setText(QString::number(speed));
            break;
        case 2:
            ui->m2Speed->setText(QString::number(speed));
            break;
        case 3:
            ui->m3Speed->setText(QString::number(speed));
            break;
        case 4:
            ui->m4Speed->setText(QString::number(speed));
            break;
        default :
            updateDebugText("Warning: Received Speed update for a motor that is not 1-4: "+QString::number(motor));
            break;
    }
}


void MainWindow::updateMotorCurrent(double current, int motor)
{
    switch(motor){
        case 1:
            ui->m1Current->setText(QString::number(current)+" mA");
            break;
        case 2:
            ui->m2Current->setText(QString::number(current)+" mA");
            break;
        case 3:
            ui->m3Current->setText(QString::number(current)+" mA");
            break;
        case 4:
            ui->m4Current->setText(QString::number(current)+" mA");
            break;
        default :
            updateDebugText("Warning: Received Current update for a motor that is not 1-4: "+QString::number(motor));
            break;
    }
}
