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
    void AlgChangedBox_valueChanged(QString string){emit updateRunAlg(defs.StateMap.key(string));}
    void submitButton_hitButton(){emit submitMessage();}
    void killButton_hitButton(){system("pkill pAntler");}
    void getMaxBots(int num);
};

#endif // INPUTHANDLER_H
