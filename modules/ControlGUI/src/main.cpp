#include "mainwindow.h"
#include "uimoosinterface.h"
#include "uimoosinterface_info.h"
#include "ivp/MBUtils.h"
#include "ivp/ColorParse.h"
#include <QApplication>
#include <QTimer>
#include <QThread>
#include <QPixmap>
#include <QSplashScreen>
#include <string>

using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    string mission_file;
    string run_command = argv[0];

    for(int i=1; i<argc; i++) {
      string argi = argv[i];
      if((argi=="-v") || (argi=="--version") || (argi=="-version"))
        showReleaseInfoAndExit();
      else if((argi=="-e") || (argi=="--example") || (argi=="-example"))
        showExampleConfigAndExit();
      else if((argi == "-h") || (argi == "--help") || (argi=="-help"))
        showHelpAndExit();
      else if((argi == "-i") || (argi == "--interface"))
        showInterfaceAndExit();
      else if(strEnds(argi, ".moos") || strEnds(argi, ".moos++"))
        mission_file = argv[i];
      else if(strBegins(argi, "--alias="))
        run_command = argi.substr(8);
      else if(i==2)
        run_command = argi;
    }

    if(mission_file == "")
      showHelpAndExit();

    cout << termColor("green");
    cout << "-UIMoosInterface launching as " << run_command << endl;
    cout << termColor() << endl;

    //Setup and start the MOOS App
    UIMoosInterface mapp(run_command, mission_file);
    MainWindow w;
    //Do connections here
    a.connect(&mapp, &UIMoosInterface::regIn, &w, &MainWindow::setBotList);
    a.connect(&mapp, &UIMoosInterface::updateState, &w, &MainWindow::updateDolphinState);
    mapp.run();
    QPixmap img("../../Images/SRCImg.jpg");
    QSplashScreen splash(img, Qt::WindowStaysOnTopHint);
    splash.showFullScreen();
    QTimer::singleShot(1500, &splash, &QWidget::close);
    QTimer::singleShot(1500, &w, &QWidget::show);

    return a.exec();
}
