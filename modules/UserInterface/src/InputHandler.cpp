#include "InputHandler.h"
#include <QApplication>
#include "ui_mainwindow.h"
#include <iostream>



InputHandler::InputHandler(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    metaState = QMetaEnum::fromType<EnumDefs::VehicleStates>();

    EnumDefs::VehicleStates modeEnum = EnumDefs::VehicleStates::ENUMLAST;
    for(int i = 0; i<modeEnum; i++){
        ui->RunModeBox->insertItem(0, defs.StateMap.value((EnumDefs::VehicleStates)i));
    }
    connect(ui->RunModeBox, SIGNAL(currentTextChanged(QString)), this, SLOT(AlgChangedBox_valueChanged(QString)));
    connect(ui->BotSelectionBox, SIGNAL(currentIndexChanged(int)), this, SLOT(BotChangedBox_valueChanged(int)));
    connect(ui->updateButton, SIGNAL(released()), this, SLOT(submitButton_hitButton()));
}

void InputHandler::getMaxBots(int num){
    ui->BotSelectionBox->clear();
    for(int i = 0; i<num; i++){
        ui->BotSelectionBox->insertItem(i, "Dolphin"+ QString::number(i));
    }
    ui->BotSelectionBox->insertItem(num, "All");
}
