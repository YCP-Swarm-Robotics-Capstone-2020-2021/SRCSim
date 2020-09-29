#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "VehicleStateDefines.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    EnumDefs::VehicleStates m_currentState;
    //QStirng m_currentBotID;
    int m_numBots;

public slots:
    //void setBotList(QList<QString> list);
    //void onSubmitStateButtonClicked();
    //void onCurrentBotChanged(QString bot){m_currentBotID = bot};
    //void onCurrentStateChanged(QString state);

signals:
   // sendStateCMD(EnumDefs::VehicleStates, QString);
};

#endif // MAINWINDOW_H
