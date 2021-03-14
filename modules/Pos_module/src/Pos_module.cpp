/************************************************************/
/*    NAME: Kyle Leatherman                                              */
/*    ORGN: YCP                                             */
/*    FILE: Pos_module.cpp                                        */
/*    DATE: 06/05/2020                                         */
/************************************************************/
#include <iterator>
#include "ivp/MBUtils.h"
#include "ivp/ACTable.h"
#include "Pos_module.h"

using namespace std;

//---------------------------------------------------------
// Constructor

Pos_module::Pos_module()
{
}

//---------------------------------------------------------
// Destructor

Pos_module::~Pos_module()
{
}

//---------------------------------------------------------
// Procedure: OnNewMail

bool Pos_module::OnNewMail(MOOSMSG_LIST &NewMail)
{
AppCastingMOOSApp::OnNewMail(NewMail);

MOOSMSG_LIST::iterator p;
for(p=NewMail.begin(); p!=NewMail.end(); p++) {
 CMOOSMsg &msg = *p;
 string key    = msg.GetKey();

#if 0 // Keep these around just for template
 string comm  = msg.GetCommunity();
 double dval  = msg.GetDouble();
 string sval  = msg.GetString();
 string msrc  = msg.GetSource();
 double mtime = msg.GetTime();
 bool   mdbl  = msg.IsDouble();
 bool   mstr  = msg.IsString();
#endif

  if(key == "Update_Pos"){
    handleUpdatePos(msg);
  }
  else if(key == "BOUNDARY_SIZE"){
      MOOSValFromString(m_boundaryWidth , msg.GetString(), "Width");
      MOOSValFromString(m_boundaryHeight , msg.GetString(), "Height");
  }
  else if(key != "APPCAST_REQ") // handled by AppCastingMOOSApp
    reportRunWarning("Unhandled Mail: " + key);
}

return(true);
}

//---------------------------------------------------------
// Procedure: OnConnectToServer

bool Pos_module::OnConnectToServer()
{
registerVariables();
return(true);
}

//---------------------------------------------------------
// Procedure: Iterate()
//            happens AppTick times per second

bool Pos_module::Iterate()
{
AppCastingMOOSApp::Iterate();
// Do your thing here!
//AppCastingMOOSApp::PostReport();
return(true);
}

//---------------------------------------------------------
// Procedure: OnStartUp()
//            happens before connection is open

bool Pos_module::OnStartUp()
{
AppCastingMOOSApp::OnStartUp();

STRING_LIST sParams;
m_MissionReader.EnableVerbatimQuoting(false);
if(!m_MissionReader.GetConfiguration(GetAppName(), sParams))
 reportConfigWarning("No config block found for " + GetAppName());

STRING_LIST::iterator p;
for(p=sParams.begin(); p!=sParams.end(); p++) {
 string orig  = *p;
 string line  = *p;
 string param = tolower(biteStringX(line, '='));
 string value = line;

 bool handled = false;
 if(param == "id") {
   id = QString::fromStdString(value);
   handled = true;
 }
 else if(param == "bar") {
   handled = true;
 }

 if(!handled)
   reportUnhandledConfigWarning(orig);

}

registerVariables();
return(true);
}

//---------------------------------------------------------
// Procedure: registerVariables

void Pos_module::registerVariables()
{
AppCastingMOOSApp::RegisterVariables();
 Register("Update_Pos");
 Register("BOUNDARY_SIZE");
}


//------------------------------------------------------------
// Procedure: buildReport()

bool Pos_module::buildReport()
{
m_msgs << "============================================" << endl;
m_msgs << "File:                                       " << endl;
m_msgs << "============================================" << endl;

ACTable actab(4);
actab << "Alpha | Bravo | Charlie | Delta";
actab.addHeaderLines();
actab << "one" << "two" << "three" << "four";
m_msgs << actab.getFormattedString();

return(true);
}

bool Pos_module::handleUpdatePos(CMOOSMsg &msg){
     if(!msg.IsString()){
        return MOOSFail("You did not input a string you ninny");
     }
     MOOSValFromString(x , msg.GetString(), "xPos");
     MOOSValFromString(y , msg.GetString(), "yPos");
     MOOSValFromString(attitude , msg.GetString(), "attitude");
     QString coords = "xPos="+ QString::number(x) + ", yPos="+ QString::number(y)+ ", attitude="+ QString::number(attitude) + ", id="+id;
     Notify("Current_Pos", coords.toStdString(), MOOSTime());
     detectBoundary();
     return true;
}

void Pos_module::detectBoundary()
{
    if(abs(x) > m_boundaryWidth/2.0){
        m_boundary_detected = true;
    }
    else if(abs(y) > m_boundaryHeight/2.0){
        m_boundary_detected = true;
    }
    else{
        m_boundary_detected = false;
    }
    Notify("BOUND_DETECT", (m_boundary_detected) ? "TRUE" : "FALSE");
}
