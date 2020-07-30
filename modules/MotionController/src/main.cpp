/************************************************************/
/*    NAME: Kyle Leatherman                                              */
/*    ORGN: YCP                                             */
/*    FILE: main.cpp                                        */
/*    DATE: 06/08/2020                                         */
/************************************************************/

#include <string>
#include "ivp/MBUtils.h"
#include "ivp/ColorParse.h"
#include <QApplication>
#include "MotionController.h"
#include "MotionController_Info.h"
#include "KeyboardHandler.h"
#include "main_testing.cpp"

using namespace std;

int main(int argc, char *argv[])
{
  mainTest();
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
  cout << "aMotionController launching as " << run_command << endl;
  cout << termColor() << endl;

  MotionController MotionController;
  KeyboardHandler keyboardHandler;
  a.connect( &keyboardHandler, SIGNAL(updateSpeed(double)), &MotionController, SLOT(setSpeed(double)) , Qt::QueuedConnection);
  a.connect( &keyboardHandler, SIGNAL(updateCurv(double)), &MotionController, SLOT(setCurv(double)), Qt::QueuedConnection);

  MotionController.startProcess(run_command.c_str(),mission_file.c_str(), argc, argv);
  keyboardHandler.show();
  return a.exec();
}

