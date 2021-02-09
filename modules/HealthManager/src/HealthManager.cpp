/************************************************************/
/*    NAME: Kyle Leatherman                                              */
/*    ORGN: YCP                                             */
/*    FILE: HealthManager.cpp                                        */
/*    DATE: 11/07/2020                                         */
/************************************************************/
#include <iterator>
#include "HealthManager.h"
#include <QDebug>

using namespace std;

//---------------------------------------------------------
// Constructor

HealthManager::HealthManager(std::string sName, std::string sMissionFile)
{
    m_moosAppName = sName;
    m_moosMissionFile = sMissionFile;
    qDebug()<<system("touch ~/Documents/duh.txt");
}

//---------------------------------------------------------
// Destructor

HealthManager::~HealthManager()
{
}

//---------------------------------------------------------
// Procedure: OnNewMail

bool HealthManager::OnNewMail(MOOSMSG_LIST &NewMail)
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

  if(key == "PROC_WATCH_SUMMARY"){
      id = msg.GetCommunity();
      std::string val = msg.GetAsString();
    if("All Present" != msg.GetAsString()){
        m_substring = msg.GetAsString().substr(6, msg.GetAsString().size()-1);
        Notify("WCA_MESSAGE", "ID="+ msg.GetCommunity() + ",Message=Module " + m_substring +" has crashed,Level=" + QString::number(EnumDefs::StatusState::WARNING).toStdString());
        Notify("Change_State", "State="+QString::number(EnumDefs::VehicleStates::ALLSTOP).toStdString());
        m_launchmode = true;
    }
    else{
        m_launchmode = false;
    }
  }
  else if(key == "BLACK_LINE_DETECTED"){
      m_black_line_detected = (toupper(msg.GetAsString())=="TRUE");
      if(m_black_line_detected && m_currentState != EnumDefs::TELEOP and id != "NotSet"){
          if(!m_lineWCAPublished){
            Notify("WCA_MESSAGE", "ID="+ id + ",Message=The dolphin has hit the black line,Level=" + QString::number(EnumDefs::StatusState::WARNING).toStdString());
            m_lineWCAPublished = true;
          }
          Notify("Change_State", "State="+QString::number(EnumDefs::VehicleStates::ALLSTOP).toStdString());
      } else {
          m_lineWCAPublished = false;
      }
  }
  else if(key == "Current_State"){
      int x;
      MOOSValFromString(x , msg.GetString(), "State");
      m_currentState = EnumDefs::VehicleStates(x);
  }
  else if(key == "VERSION_ACK")
  {
      m_versionRecv = true;
  }
  else if(key != "APPCAST_REQ"){ // handled by AppCastingMOOSApp
    reportRunWarning("Unhandled Mail: " + key);
  }
}

return(true);
}

//---------------------------------------------------------
// Procedure: OnConnectToServer

bool HealthManager::OnConnectToServer()
{
registerVariables();
return(true);
}

//---------------------------------------------------------
// Procedure: Iterate()
//            happens AppTick times per second

bool HealthManager::Iterate()
{
AppCastingMOOSApp::Iterate();
if(m_launchmode){
    restartProcess(QString::fromStdString(m_substring).split(','));
}
if(!m_versionRecv){
    Notify("VERSION_NUMBER", "version="+m_versionNum+",message="+m_commitMessage);
}
AppCastingMOOSApp::PostReport();
return(true);
}

//---------------------------------------------------------
// Procedure: OnStartUp()
//            happens before connection is open

bool HealthManager::OnStartUp()
{
AppCastingMOOSApp::OnStartUp();

STRING_LIST sParams;
m_MissionReader.EnableVerbatimQuoting(true);
if(!m_MissionReader.GetConfigurationAndPreserveSpace(GetAppName(), sParams))
 reportConfigWarning("No config block found for " + GetAppName());

STRING_LIST::iterator p;
for(p=sParams.begin(); p!=sParams.end(); p++) {
 string orig  = *p;
 string line  = *p;
 string param = tolower(biteStringX(line, '='));
 string value = line;

 bool handled = false;
 if(param == "binarypath") {
   handled = true;
   m_binarypath = QString::fromStdString(value);
 }
 else if(param == "runsim") {
   handled = true;
   m_runSim = value == "true";
 }
 else if(param == "versionnum")
 {
     handled = true;
     m_versionNum = value;
 }
 else if(param == "commitmessage")
 {
    handled = true;
    m_commitMessage = value;
 }
 if(!handled)
   reportUnhandledConfigWarning(orig);

}
m_launchtime = MOOSTime();
registerVariables();
return(true);
}

//---------------------------------------------------------
// Procedure: registerVariables

void HealthManager::registerVariables()
{
AppCastingMOOSApp::RegisterVariables();
  Register("PROC_WATCH_SUMMARY");
  Register("BLACK_LINE_DETECTED");
  Register("VERSION_ACK");
  Register("Current_State");
}


//------------------------------------------------------------
// Procedure: buildReport()

bool HealthManager::buildReport()
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

void HealthManager::run()
{
    RunInQtEventLoop(m_moosAppName, m_moosMissionFile);
}

bool HealthManager::RunInQtEventLoop(const std::string &sName, const std::string &sMissionFile)
{
    //straight away do we want colour in this application?
    if(m_CommandLineParser.GetFlag("--moos_no_colour"))
    {
        std::cerr<<"turning off colour\n";
        MOOS::ConsoleColours::Enable(false);
    }


    //save absolutely crucial info...
    m_sAppName      = sName; //default
    m_CommandLineParser.GetOption("--moos_app_name",m_sAppName);//overload

    //but things might be overloaded
    m_sMissionFile  = sMissionFile; //default
    m_CommandLineParser.GetVariable("--moos_file",m_sMissionFile); //overload

    m_MissionReader.SetAppName(m_sAppName);

    //by default we will register with our application name
    if(m_sMOOSName.empty()) //default
        m_sMOOSName=m_sAppName;

    m_CommandLineParser.GetVariable("--moos_name",m_sMOOSName); //overload


    if(m_CommandLineParser.GetFlag("--moos_help"))
    {
        PrintDefaultCommandLineSwitches();
        exit(0);
    }

    if(m_CommandLineParser.GetFlag("--help"))
    {
        PrintDefaultCommandLineSwitches();
        std::cout<<"\ncustom help:\n";
        OnPrintHelpAndExit();
        exit(0);
    }

    if(m_CommandLineParser.GetFlag("--moos_print_example"))
        OnPrintExampleAndExit();

    if(m_CommandLineParser.GetFlag("--moos_print_interface"))
        OnPrintInterfaceAndExit();

    if(m_CommandLineParser.GetFlag("--moos_print_version"))
        OnPrintVersionAndExit();




    //look at mission file etc
    if(!Configure())
    {
        std::cerr<<"configure returned false. Quitting\n";
        return false;
    }

    //here we give users a chance to alter configurations
    //or do more work in configuring
    if(m_CommandLineParser.IsAvailable())
        OnProcessCommandLine();

    //what time did we start?
    m_dfAppStartTime = MOOSTime();

    //can we start the communications ?
    if(m_bUseMOOSComms)
    {

        if(!ConfigureComms())
        {
            return false;
        }

        ///////////////////////////////////////////////////////////////
        //OK we are going to wait for a conenction to be established
        // this is a little harsh but it saves derived classes having to
        // hold off connecting to the server until ready
        // but we will only hang around for 1 second...
        // so it is possible that notifies will fail...but very unlikely
        // note this is not a hack! just being helpful. Ths success of an
        // application is NOT dependent on this
        int t = 0;
        int dT = 50;
        while(!m_Comms.IsConnected())
        {
            MOOSPause(dT);
            t+=dT;
            if(t>5000)
                break;
        }
        //give iostream time to write comms start details up to screen..this is not really necessary
        //as the code is thread safe...it is aesthetic only
        MOOSPause(500);
    }


    /** let derivatives do stuff before execution*/
    if(!OnStartUpPrepare())
    {
        MOOSTrace("Derived OnStartUpPrepare() returned false... Quitting\n");
        return false;
    }

    if(!OnStartUp())
    {
        MOOSTrace("Derived OnStartUp() returned false... Quitting\n");
        return false;
    }


    if(!OnStartUpComplete())
    {
        MOOSTrace("Derived OnStartUpComplete() returned false... Quitting\n");
        return false;
    }

    if(m_CommandLineParser.GetFlag("--moos_configuration_audit"))
    {
        PrintSearchedConfigurationFileParameters();
        return true;
    }


    DoBanner();
    connect(&iterateTimer, &QTimer::timeout, this, &HealthManager::doMOOSWork);
    iterateTimer.start(1000.0/m_dfFreq);
    currentFrequency = m_dfFreq;
    return true;
}

bool HealthManager::doMOOSWork()
{    /****************************  THE MAIN MOOS APP LOOP **********************************/
    m_dfFreq = -1; //Set this to -1 in order to override the MOOS Sleep function
    bool bOK = DoRunWork();
    if(m_bQuitOnIterateFail && !bOK){
        m_Comms.Close();
        emit workFinished();
        return MOOSFail("MOOSApp Exiting as requested");
    }
    /***************************   END OF MOOS APP LOOP ***************************************/
    return true;
}

void HealthManager::restartProcess(QList<QString> appName){
    int error;
    for(QString str : appName){
            QString command;
            QString pathStr;
            if(str.at(0) == "p"){
                command = str + " --alias=" + str + " " + QString::fromStdString(m_moosMissionFile) +" &";
                error = system(command.toLocal8Bit().data());
                qDebug()<<error;
            }
            else{
                if(m_runSim){
                    pathStr = "./" + m_binarypath + "/" + str + "/bin/" + str;
                }
                else{
                    pathStr = "./" + m_binarypath + "/" + str;
                }
                command =  pathStr + " --alias=" + str + " " + QString::fromStdString(m_moosMissionFile)+" &";
                error = system(command.toLocal8Bit().data());
                qDebug()<<error;
            }
            error = system("ls");
        }
        error = system("echo \"hello world\" >> ~/Documents/duh.txt");
        qDebug()<<error;

}
