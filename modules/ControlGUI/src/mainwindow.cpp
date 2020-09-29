#include "mainwindow.h"
#include "styles.h"
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

    setupStateSelection();
    setBotList({"Dolphin0", "Dolphin1", "Dolphin2", "Dolphin3"});
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
        if(!m_robotStateMap.contains(list[i]))
            m_robotStateMap[list[i]] = RobotState();
    }
    ui->dolphinSelection->insertItem(list.size(), "All");
    if(!m_robotStateMap.contains("All"))
        m_robotStateMap["All"] = RobotState();
    m_numBots = list.size();

    updateCurrentDisplay();
    startup = false;
}

void MainWindow::onSubmitStateButtonClicked()
{
    m_robotStateMap[m_currentBotID].maxSpeed = m_maxSpeed;
    emit sendStateCMD(m_currentState, m_currentBotID, m_maxSpeed);
    updateDolphinStatus(EnumDefs::StatusState::WARNING, "Dolphin3");
    updateDolphinStatus(EnumDefs::StatusState::CAUTION, "Dolphin2");
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
}

void MainWindow::onCurrentBotChanged(QString bot)
{
    if(!m_robotStateMap.contains(bot)&&!startup){
        printWarning("Received Bot ID that is not yet registered.", "All");
        return;
    }
    m_currentBotID = bot;
    updateCurrentDisplay();
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

void MainWindow::updateWarningText(QString text)
{
    ui->warningBrowser->append(text);
}

void MainWindow::updateDolphinStatus(EnumDefs::StatusState status, QString dolphin)
{
    m_robotStateMap[dolphin].status = status;
    if(dolphin != m_currentBotID)
        return;

    ui->statusLabel->setText(defs.StatusMap[m_robotStateMap[m_currentBotID].status]);
    switch(m_robotStateMap[m_currentBotID].status){
        case EnumDefs::StatusState::NORMAL:
            ui->statusLabel->setStyleSheet("QLabel { color : "+QString(NORMAL_FONT_COLOR)+";}");
            break;
        case EnumDefs::StatusState::CAUTION:
            ui->statusLabel->setStyleSheet("QLabel { color : "+QString(CAUTION_FONT_COLOR)+";}");
            break;
        case EnumDefs::StatusState::WARNING:
            ui->statusLabel->setStyleSheet("QLabel { color : "+QString(WARNING_FONT_COLOR)+";}");
            break;
    }
}

void MainWindow::updateBatteryPerc(double perc, QString dolphin)
{
    m_robotStateMap[dolphin].batteryCharge = perc;
    if(dolphin == m_currentBotID)
        ui->batteryPercentage->setText(QString::number(perc)+"%");
}

void MainWindow::updateMotorSpeed(double speed, int motor, QString dolphin)
{
    m_robotStateMap[dolphin].motorSpeed[motor] = speed;
    if(dolphin != m_currentBotID)
        return;

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
            printCaution("Receieved Speed update for a motor that is not 1-4: "+QString::number(motor), m_currentBotID);
            break;
    }
}


void MainWindow::updateMotorCurrent(double current, int motor, QString dolphin)
{
    m_robotStateMap[dolphin].motorCurrent[motor] = current;
    if(dolphin != m_currentBotID)
        return;

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
            printCaution("Receieved Current update for a motor that is not 1-4: "+QString::number(motor), m_currentBotID);
            break;
    }
}

void MainWindow::setupStateSelection()
{
    ui->stateSelection->clear();
    EnumDefs::VehicleStates state = EnumDefs::VehicleStates(0);
    while(state != EnumDefs::VehicleStates::UILAST){
        ui->stateSelection->addItem(defs.UIStateMap[state]);
        state = EnumDefs::VehicleStates(int(state) + 1);
    }
}

void MainWindow::updateCurrentDisplay()
{
    ui->stateSelection->setCurrentText(defs.UIStateMap[m_robotStateMap[m_currentBotID].state]);
    ui->dolphinSelection->setCurrentText(m_currentBotID);

    for(int j = 0; j<4; j++){
        updateMotorSpeed(m_robotStateMap[m_currentBotID].motorSpeed[j], j+1, m_currentBotID);
        updateMotorCurrent(m_robotStateMap[m_currentBotID].motorCurrent[j], j+1, m_currentBotID);
    }
    updateDolphinStatus(m_robotStateMap[m_currentBotID].status, m_currentBotID);
    ui->maxSpeedSlider->setValue(m_robotStateMap[m_currentBotID].maxSpeed);
    ui->textBrowser->clear();
    QList<QString>::iterator iter;
    for(iter = m_robot_message_buffer[m_currentBotID].begin(); iter!=m_robot_message_buffer[m_currentBotID].end(); iter++){
        ui->textBrowser->append(*iter);
    }
}

void MainWindow::printCaution(QString text, QString dolphin)
{
    m_robot_message_buffer[dolphin].append("<div style=\"color:"+QString(CAUTION_FONT_COLOR)+";font-size:"+QString::number(TEXT_FONT_SIZE)+"px;\">Caution: "+text+"</div>");
    if(m_currentBotID == dolphin)
        updateDebugText("<div style=\"color:"+QString(CAUTION_FONT_COLOR)+";font-size:"+QString::number(TEXT_FONT_SIZE)+"px;\">Caution: "+text+"</div>");
}

void MainWindow::printWarning(QString text, QString dolphin)
{
    m_robot_message_buffer[dolphin].append("<b style=\"color:"+QString(WARNING_FONT_COLOR)+";font-size:"+QString::number(TEXT_FONT_SIZE)+"px;\">Warning: "+text+"</b>");
    if(m_currentBotID == dolphin)
        updateDebugText("<b style=\"color:"+QString(WARNING_FONT_COLOR)+";font-size:"+QString::number(TEXT_FONT_SIZE)+"px;\">Warning: "+text+"</b>");
    updateWarningText("<b style=\"color:"+QString(WARNING_FONT_COLOR)+";font-size:"+QString::number(TEXT_FONT_SIZE)+"px;\">Warning: "+text+"</b>");
}

void MainWindow::printAdvisory(QString text, QString dolphin)
{
    m_robot_message_buffer[dolphin].append("<div style=\"color:"+QString(ADVISORY_FONT_COLOR)+";font-size:"+QString::number(TEXT_FONT_SIZE)+"px;\">Advisory: "+text+"</div>");
    if(m_currentBotID == dolphin)
        updateDebugText("<div style=\"color:"+QString(ADVISORY_FONT_COLOR)+";font-size:"+QString::number(TEXT_FONT_SIZE)+"px;\">Advisory: "+text+"</div>");
}

void MainWindow::printText(QString text, QString dolphin)
{
    m_robot_message_buffer[dolphin].append("<div style=\"color:"+QString(NORMAL_FONT_COLOR)+";font-size:"+QString::number(TEXT_FONT_SIZE)+"px;\">Advisory: "+text+"</div>");
    if(m_currentBotID == dolphin)
        updateDebugText("<div style=\"color:"+QString(NORMAL_FONT_COLOR)+";font-size:"+QString::number(TEXT_FONT_SIZE)+"px;\">Advisory: "+text+"</div>");
}
