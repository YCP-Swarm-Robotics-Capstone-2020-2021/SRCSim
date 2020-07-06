#ifndef KEYBOARDHANDLER_H
#define KEYBOARDHANDLER_H

#include <QMainWindow>
#include <QKeyEvent>
#include <iostream>
#include <QLabel>
#include <QVBoxLayout>
#include <QThread>
namespace Ui {
class MainWindow;
}

class KeyboardHandler :public QMainWindow
{
    Q_OBJECT
public:
    explicit KeyboardHandler(QWidget *parent = 0);

protected:
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);

signals:
    void updateSpeed(double speed);
    void updateCurv(double curv);
private:
    Ui::MainWindow *ui;


};

#endif // KEYBOARDHANDLER_H
