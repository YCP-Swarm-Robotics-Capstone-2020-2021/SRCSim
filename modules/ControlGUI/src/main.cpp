#include "mainwindow.h"
#include <QApplication>
#include <QTimer>
#include <QPixmap>
#include <QSplashScreen>

using namespace std;

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  MainWindow w;
  QPixmap img("../../Images/SRCImg.jpg");
  QSplashScreen splash(img, Qt::WindowStaysOnTopHint);
  splash.showFullScreen();
  QTimer::singleShot(1500, &splash, &QWidget::close);
  QTimer::singleShot(1500, &w, &QWidget::show);

  return a.exec();
}
