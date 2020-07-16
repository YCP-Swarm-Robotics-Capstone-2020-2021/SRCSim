#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H

#include <QMainWindow>
#include <VehicleStateDefines.h>
#include <stdlib.h>

namespace Ui {
class MainWindow;
}

class InputHandler: public QMainWindow
{
    Q_OBJECT
public:
    explicit InputHandler(QWidget *parent = 0);
    QMetaEnum metaState;

signals:
    void updateRunAlg(int alg);
    void updateRobot(int num);
    void submitMessage();

private:
    Ui::MainWindow *ui;
    QString modelist(int idx);
    EnumDefs defs;

private slots :
    void BotChangedBox_valueChanged(int num){emit updateRobot(num);};
    void AlgChangedBox_valueChanged(QString string){emit updateRunAlg(defs.UIStateMap.key(string));}
    void submitButton_hitButton(){emit submitMessage();}
    int killButton_hitButton(){int x = system("pkill pAntler"); return x;}
    void getMaxBots(int num);
};

#endif // INPUTHANDLER_H
