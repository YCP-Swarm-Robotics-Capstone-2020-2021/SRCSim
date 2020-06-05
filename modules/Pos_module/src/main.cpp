/************************************************************/
/*    NAME: Kyle Leatherman                                              */
/*    ORGN: YCP                                             */
/*    FILE: main.cpp                                        */
/*    DATE: 06/05/2020                                         */
/************************************************************/

#include <string>
#include "ivp/MBUtils.h"
#include "ivp/ColorParse.h"
#include <QCoreApplication>
#include "Pos_module.h"
#include "Pos_module_Info.h"

using namespace std;

int main(int argc, char *argv[])
{
  QCoreApplication a(argc, argv);
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
  cout << "iPos_module launching as " << run_command << endl;
  cout << termColor() << endl;

  Pos_module Pos_module;

  Pos_module.Run(run_command.c_str(), mission_file.c_str());
  
  return a.exec();
}

