/************************************************************/
/*    NAME: Kyle                                              */
/*    ORGN: YCP                                             */
/*    FILE: main.cpp                                        */
/*    DATE: 06/22/2020                                         */
/************************************************************/

#include <string>
#include "ivp/MBUtils.h"
#include "ivp/ColorParse.h"
#include <QApplication>
#include "UserInterface.h"
#include "UserInterface_Info.h"
#include "InputHandler.h"

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
  cout << "-iUserInterface launching as " << run_command << endl;
  cout << termColor() << endl;

  UserInterface UserInterface;
  InputHandler inputHandler;
  a.connect(&inputHandler, SIGNAL(updateRunAlg(int)), &UserInterface, SLOT(updateState(int)), Qt::QueuedConnection);
  a.connect(&inputHandler, SIGNAL(updateRobot(int)), &UserInterface, SLOT(updateBot(int)), Qt::QueuedConnection);
  a.connect(&UserInterface, SIGNAL(informMaxBots(int)), &inputHandler, SLOT(getMaxBots(int)),  Qt::QueuedConnection);
  a.connect(&inputHandler, SIGNAL(submitMessage()) , &UserInterface, SLOT(sendMessage()),  Qt::QueuedConnection);

  UserInterface.startProcess(run_command.c_str(), mission_file.c_str(), argc, argv);
  inputHandler.show();
  return a.exec();
}

