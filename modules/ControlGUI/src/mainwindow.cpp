#include "mainwindow.h"
#include "styles.h"
#include "ui_mainwindow.h"
#include <QMessageBox>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_currentState(EnumDefs::VehicleStates::STANDBY),
    m_maxSpeed(100)
{
    ui->setupUi(this);
    myPainter = new SwarmFormationPainter(this);
    QSizePolicy policy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    policy.setHeightForWidth(true);
    myPainter->setSizePolicy(policy);
    ui->glLayout->addWidget(myPainter);
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
    connect(ui->actionKill_All, SIGNAL(triggered()), this, SLOT(onKillAllPressed()));
    connect(this, &MainWindow::updatePaintList, myPainter, &SwarmFormationPainter::setDolphinList);
    connect(ui->shapeSelection, SIGNAL(currentIndexChanged(int)), myPainter, SLOT(setCurrentShape(int)));
    connect(ui->widthBox, SIGNAL(valueChanged(int)), myPainter, SLOT(setCurrentWidth(int)));
    connect(ui->lengthBox, SIGNAL(valueChanged(int)), myPainter, SLOT(setCurrentLength(int)));
    connect(ui->rotationBox, SIGNAL(valueChanged(int)), myPainter, SLOT(setCurrentRotation(int)));
    connect(ui->zoomSlider, SIGNAL(valueChanged(int)), this, SLOT(descretizeZoom(int)));
    connect(this, &MainWindow::zoomValue, myPainter, &SwarmFormationPainter::setFeetArenaView);
    connect(ui->submitZeta, SIGNAL(released()), myPainter, SLOT(submitZetaPressed()));
    connect(myPainter, &SwarmFormationPainter::emitZeta, this, &MainWindow::zetaSent);
    connect(ui->LOG_BOOKMARK_BUTTON, SIGNAL(pressed()), this, SIGNAL(logBookmarkReq()));

    connect(&forwardTimer, &QTimer::timeout, this, &MainWindow::onForwardButtonReleased);
    connect(&rightTimer, &QTimer::timeout, this, &MainWindow::onRightButtonReleased);
    connect(&leftTimer, &QTimer::timeout, this, &MainWindow::onLeftButtonReleased);
    connect(&backTimer, &QTimer::timeout, this, &MainWindow::onReverseButtonReleased);

    connect(ui->boundaryPushButton, SIGNAL(released()), this, SLOT(sendUpdateBoundarySizeSignal()));

    setBotList({});
    setupStateSelection();
    setupShapeList();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setBotList(QList<QString> list)
{
    QString tempBotID = ui->dolphinSelection->currentText();
    qDebug()<<"setBotList 1"<<m_currentBotID;
    ui->dolphinSelection->clear();
    for(int i = 0; i < list.size(); i++)
    {
        if(!m_robotStateMap.contains(list[i]))
            m_robotStateMap[list[i]] = RobotState();
        ui->dolphinSelection->insertItem(i, list[i]);
    }
    if(!m_robotStateMap.contains("All"))
        m_robotStateMap["All"] = RobotState();
    ui->dolphinSelection->insertItem(list.size(), "All");
    m_numBots = list.size();

    ui->dolphinSelection->model()->sort(0);
    ui->dolphinSelection->setCurrentText(tempBotID);
    qDebug()<<"setBotList 2"<<tempBotID;
    updateCurrentDisplay();
    ui->dolphinSelection->setCurrentText(tempBotID);
    m_currentBotID = tempBotID;
    emit updatePaintList(list);
    startup = false;
}

void MainWindow::onSubmitStateButtonClicked()
{
    m_robotStateMap[m_currentBotID].maxSpeed = m_maxSpeed;
    if(m_currentState==EnumDefs::VehicleStates::SWARMMODE)
        myPainter->submitZetaPressed();
    emit sendStateCMD(m_currentState, m_currentBotID, m_maxSpeed);
}

void MainWindow::onCurrentStateChanged(QString state)
{
    EnumDefs::VehicleStates tempState = EnumDefs::VehicleStates(0);
    while(tempState != EnumDefs::VehicleStates::UILAST){
        if(state.toUpper() == defs.UIStateMap[tempState]){
            if(tempState != EnumDefs::ALLSTOP && m_currentState != EnumDefs::STANDBY && tempState != EnumDefs::STANDBY && m_currentState != tempState){
                int ret = QMessageBox::warning(this, tr("State Change Not Allowed"), tr("You must pass through StandBy state when changing states. Did you mean to change to Standby?"),
                                     QMessageBox::Yes|QMessageBox::No);

                if(ret == QMessageBox::Yes){
                    m_currentState = EnumDefs::STANDBY;
                }
                ui->stateSelection->setCurrentText(defs.UIStateMap[m_currentState]);
                return;
            } else
                m_currentState = tempState;
        }
        tempState = EnumDefs::VehicleStates(int(tempState)+1);
    }
}

void MainWindow::onCurrentBotChanged(QString bot)
{
    if(bot == "")
        return;
    if(!m_robotStateMap.contains(bot)&&!startup){
        printWarning("Received Bot ID that is not yet registered: "+bot, "All");
        return;
    }
    m_currentBotID = bot;
    updateCurrentDisplay();
}

void MainWindow::onForwardButtonPressed()
{
    forwardTimer.start(BUTTON_PRESS_INTERVAL); //BUTTON_PRESS_INTERVAL ms
    forward = true;
    if(m_currentBotID == "All" && m_currentState == EnumDefs::SWARMMODE){
        myPainter->submitZetaPressed(0, -ui->speedSelection->value()/1000.0);
    } else
        emit sendSpeed(m_currentBotID, forward, reverse, left, right, ui->speedSelection->value());
}

void MainWindow::onForwardButtonReleased()
{
    forward = false;
    emit sendSpeed(m_currentBotID, forward, reverse, left, right, ui->speedSelection->value());
}
void MainWindow::onLeftButtonPressed()
{
    leftTimer.start(BUTTON_PRESS_INTERVAL); //BUTTON_PRESS_INTERVAL ms
    left = true;
    if(m_currentBotID == "All" && m_currentState == EnumDefs::SWARMMODE){
        myPainter->submitZetaPressed(ui->speedSelection->value()/1000.0);
    } else
        emit sendSpeed(m_currentBotID, forward, reverse, left, right, ui->speedSelection->value());
}

void MainWindow::onLeftButtonReleased()
{
    left = false;
    emit sendSpeed(m_currentBotID, forward, reverse, left, right, ui->speedSelection->value());
}

void MainWindow::onRightButtonPressed()
{
    rightTimer.start(BUTTON_PRESS_INTERVAL); //BUTTON_PRESS_INTERVAL ms
    right = true;
    if(m_currentBotID == "All" && m_currentState == EnumDefs::SWARMMODE){
        myPainter->submitZetaPressed(-ui->speedSelection->value()/1000.0);
    } else
        emit sendSpeed(m_currentBotID, forward, reverse, left, right, ui->speedSelection->value());
}
void MainWindow::onRightButtonReleased()
{
    right = false;
    emit sendSpeed(m_currentBotID, forward, reverse, left, right, ui->speedSelection->value());
}

void MainWindow::onBackwardButtonPressed()
{
    backTimer.start(BUTTON_PRESS_INTERVAL); //BUTTON_PRESS_INTERVAL ms
    reverse = true;
    if(m_currentBotID == "All" && m_currentState == EnumDefs::SWARMMODE){
        myPainter->submitZetaPressed(0, ui->speedSelection->value()/1000.0);
    } else
        emit sendSpeed(m_currentBotID, forward, reverse, left, right, ui->speedSelection->value());
}

void MainWindow::onReverseButtonReleased()
{
    reverse = false;
    emit sendSpeed(m_currentBotID, forward, reverse, left, right, ui->speedSelection->value());
}
void MainWindow::onSpeedUpButtonPressed()
{
    ui->speedSelection->setValue(int(ui->speedSelection->value()+SPEED_INTERVAL));
    m_robotStateMap[m_currentBotID].cmdSpeed = ui->speedSelection->value();
}

void MainWindow::onSlowDownButtonPressed()
{
    ui->speedSelection->setValue(int(ui->speedSelection->value()-SPEED_INTERVAL));
    m_robotStateMap[m_currentBotID].cmdSpeed = ui->speedSelection->value();
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
            ui->statusLabel->setStyleSheet("QLabel { color : "+QString::fromStdString(NORMAL_FONT_COLOR)+";}");
            break;
        case EnumDefs::StatusState::CAUTION:
            ui->statusLabel->setStyleSheet("QLabel { color : "+QString::fromStdString(CAUTION_FONT_COLOR)+";}");
            break;
        case EnumDefs::StatusState::WARNING:
            ui->statusLabel->setStyleSheet("QLabel { color : "+QString::fromStdString(WARNING_FONT_COLOR)+";}");
            break;
    }
}

void MainWindow::updateDolphinState(QString id, int state)
{
    EnumDefs::VehicleStates currentState = m_robotStateMap[id].state;
    if(int(currentState) == state)
        return;

    m_robotStateMap[id].state = EnumDefs::VehicleStates(state);
    currentState = EnumDefs::VehicleStates(state);
    switch(currentState){
        case EnumDefs::VehicleStates::ALLSTOP:
        case EnumDefs::VehicleStates::BOUNDARY:
            printCaution(id+" state updated to "+defs.UIStateMap[currentState], id);
            break;
        default:
            printAdvisory(id+" state updated to "+defs.UIStateMap[currentState], id);
            break;
    }
    updateCurrentDisplay();
}

void MainWindow::updateDolphinMsg(QString id, QString msg, int lvl){
    switch(lvl){
        case EnumDefs::StatusState::NORMAL:
            printAdvisory(id+": "+msg, id);
            break;
        case EnumDefs::StatusState::CAUTION:
            printCaution(id+": "+msg, id);
            break;
        case EnumDefs::StatusState::WARNING:
            printWarning(id+": "+msg, id);
            break;
        default:
            printText(id+": "+msg, id);
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
    ui->CurrentStateLabel->setText(defs.UIStateMap[m_robotStateMap[m_currentBotID].state]);
    switch(m_robotStateMap[m_currentBotID].state){
        case EnumDefs::VehicleStates::ALLSTOP:
            ui->CurrentStateLabel->setStyleSheet("QLabel { color : "+QString::fromStdString(WARNING_FONT_COLOR)+";}");
            break;
        default:
            ui->CurrentStateLabel->setStyleSheet("QLabel { color : "+QString::fromStdString(NORMAL_FONT_COLOR)+";}");
            break;
    }

    ui->dolphinSelection->setCurrentText(m_currentBotID);

    for(int j = 0; j<4; j++){
        updateMotorSpeed(m_robotStateMap[m_currentBotID].motorSpeed[j], j+1, m_currentBotID);
        updateMotorCurrent(m_robotStateMap[m_currentBotID].motorCurrent[j], j+1, m_currentBotID);
    }
    updateDolphinStatus(m_robotStateMap[m_currentBotID].status, m_currentBotID);
    updateDolphinState(m_currentBotID, m_robotStateMap[m_currentBotID].state);
    ui->maxSpeedSlider->setValue(m_robotStateMap[m_currentBotID].maxSpeed);
    ui->speedSelection->setValue(m_robotStateMap[m_currentBotID].cmdSpeed);
    ui->textBrowser->clear();
    QList<QString>::iterator iter;
    for(iter = m_robot_message_buffer[m_currentBotID].begin(); iter!=m_robot_message_buffer[m_currentBotID].end(); iter++){
        ui->textBrowser->append(*iter);
    }

    ui->uProcessWatchReport->setText(m_robotProcessMap.value(m_currentBotID, "No Process Message"));
}

void MainWindow::printCaution(QString text, QString dolphin)
{
    m_robot_message_buffer[dolphin].append("<div style=\"color:"+QString::fromStdString(CAUTION_FONT_COLOR)+";font-size:"+QString::number(TEXT_FONT_SIZE)+"px;\">Caution: "+text+"</div>");
    if(m_currentBotID == dolphin)
        updateDebugText("<div style=\"color:"+QString::fromStdString(CAUTION_FONT_COLOR)+";font-size:"+QString::number(TEXT_FONT_SIZE)+"px;\">Caution: "+text+"</div>");
}

void MainWindow::printWarning(QString text, QString dolphin)
{
    m_robot_message_buffer[dolphin].append("<b style=\"color:"+QString::fromStdString(WARNING_FONT_COLOR)+";font-size:"+QString::number(TEXT_FONT_SIZE)+"px;\">Warning: "+text+"</b>");
    if(m_currentBotID == dolphin)
        updateDebugText("<b style=\"color:"+QString::fromStdString(WARNING_FONT_COLOR)+";font-size:"+QString::number(TEXT_FONT_SIZE)+"px;\">Warning: "+text+"</b>");
    updateWarningText("<b style=\"color:"+QString::fromStdString(WARNING_FONT_COLOR)+";font-size:"+QString::number(TEXT_FONT_SIZE)+"px;\">Warning: "+text+"</b>");
}

void MainWindow::printAdvisory(QString text, QString dolphin)
{
    m_robot_message_buffer[dolphin].append("<div style=\"color:"+QString::fromStdString(ADVISORY_FONT_COLOR)+";font-size:"+QString::number(TEXT_FONT_SIZE)+"px;\">Advisory: "+text+"</div>");
    if(m_currentBotID == dolphin)
        updateDebugText("<div style=\"color:"+QString::fromStdString(ADVISORY_FONT_COLOR)+";font-size:"+QString::number(TEXT_FONT_SIZE)+"px;\">Advisory: "+text+"</div>");
}

void MainWindow::printText(QString text, QString dolphin)
{
    m_robot_message_buffer[dolphin].append("<div style=\"color:"+QString::fromStdString(NORMAL_FONT_COLOR)+";font-size:"+QString::number(TEXT_FONT_SIZE)+"px;\">Advisory: "+text+"</div>");
    if(m_currentBotID == dolphin)
        updateDebugText("<div style=\"color:"+QString::fromStdString(NORMAL_FONT_COLOR)+";font-size:"+QString::number(TEXT_FONT_SIZE)+"px;\">Advisory: "+text+"</div>");
}

void MainWindow::onKillAllPressed()
{
    int ret = QMessageBox::critical(this, tr("Kill All Dialogue"),
                                    tr("Are you sure you want to kill all MOOS related applications?"),
                                    QMessageBox::Yes | QMessageBox::No, QMessageBox::No);
    switch(ret){
        case QMessageBox::Yes:
            system("ktm");
            break;
        case QMessageBox::No:
            break;
        default:
            break;
    }
}

void MainWindow::onPreveiwPressed()
{

}

void MainWindow::setupShapeList()
{
    ui->shapeSelection->clear();
    for(int i = 0; i<SwarmFormationPainter::Shape::SHAPEENUMEND; i++)
    {
        ui->shapeSelection->addItem(myPainter->getShapeSring(SwarmFormationPainter::Shape(i)));
    }
}

void MainWindow::descretizeZoom(int zoom)
{
    if (zoom%2 != 0){
        zoom += 1;
    }
    ui->zoomSlider->setValue(zoom);
    emit zoomValue(zoom);
}

void MainWindow::updateDolphinWatch(QString id, QString msg)
{
    m_robotProcessMap[id] = msg;
    updateCurrentDisplay();
}

void MainWindow::sendUpdateBoundarySizeSignal()
{
    int boundarySize = ui->boundarySpinBox->value();
    emit updateBoundarySize(boundarySize);
}
