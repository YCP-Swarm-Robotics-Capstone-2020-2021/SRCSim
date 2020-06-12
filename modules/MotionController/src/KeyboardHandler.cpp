#include "KeyboardHandler.h"
#include <QApplication>
#include "ui_mainwindow.h"

KeyboardHandler::KeyboardHandler(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    myLabelText = new QLabel ("You Didn't Pressed / Released any Key");


}

void KeyboardHandler::keyPressEvent(QKeyEvent *event){
    switch(event->key()){
        case Qt::Key_W:{
            emit updateSpeed(75.0);
            break;
        }
        case Qt::Key_A:{
            emit updateCurv(45.0);
            break;
        }
        case Qt::Key_S:{
            emit updateSpeed(-75.0);
            break;
        }
        case Qt::Key_D:{
            emit updateCurv(-45.0);
            break;
        }
        default:
            //QWidget::keyPressEvent(event);
            break;
    }
}

void KeyboardHandler::keyReleaseEvent(QKeyEvent *event){
    switch(event->key()){
        case Qt::Key_W:{
            emit updateSpeed(0.0);
            break;
        }
        case Qt::Key_A:{
            emit updateCurv(0.0);
            break;
        }
        case Qt::Key_S:{
            emit updateSpeed(0.0);
            break;
        }
        case Qt::Key_D:{
            emit updateCurv(0.0);
            break;
        }
        default:
            //QWidget::keyPressEvent(event);
            break;
    }
}

