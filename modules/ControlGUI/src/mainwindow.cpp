#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //connect(ui->submitState,SIGNAL(released()),this,SIGNAL(onSubmitStateButtonClicked()));
    //connect(ui->dolphinSelection,SIGNAL(currentTextChanged(QString)),this,SLOT(onCurrentBotChanged(QString)));
    //connect(ui->stateSelection,SIGNAL(currentTextChanged(QString)),this,SLOT(onCurrentStateChanged(QString)));

}

MainWindow::~MainWindow()
{
    delete ui;
}

/*void MainWindow::setBotList(QList<QString> list)
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
    //emit sendStateCMD(m_currentState, m_currentBotID);
}
*/
