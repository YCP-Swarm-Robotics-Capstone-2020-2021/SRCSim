/************************************************************/
/*    NAME: Josiah Sam                                              */
/*    ORGN: YCP                                             */
/*    FILE: CameraInterface.cpp                                        */
/*    DATE: 03/23/2021                                         */
/************************************************************/
#include <iterator>
#include "ivp/MBUtils.h"
#include "ivp/ACTable.h"
#include "CameraInterface.h"
#include <QJsonDocument>
#include <QJsonArray>
using namespace std;

//---------------------------------------------------------
// Constructor

CameraInterface::CameraInterface(std::string sName, std::string sMissionFile)
{    
    m_moosAppName = sName;
    m_moosMissionFile = sMissionFile;
    connect(&m_read_data_timer, &QTimer::timeout,this,&CameraInterface::readData);
    m_read_data_timer.start(READ_DATA_PERIOD);
}

//---------------------------------------------------------
// Destructor

CameraInterface::~CameraInterface()
{
}

//---------------------------------------------------------
// Procedure: OnNewMail

bool CameraInterface::OnNewMail(MOOSMSG_LIST &NewMail)
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

  if(key == "FOO")
    cout << "great!";

  else if(key != "APPCAST_REQ") // handled by AppCastingMOOSApp
    reportRunWarning("Unhandled Mail: " + key);
}

return(true);
}

//---------------------------------------------------------
// Procedure: OnConnectToServer

bool CameraInterface::OnConnectToServer()
{
registerVariables();
return(true);
}

//---------------------------------------------------------
// Procedure: Iterate()
//            happens AppTick times per second

bool CameraInterface::Iterate()
{
AppCastingMOOSApp::Iterate();
// Do your thing here!
AppCastingMOOSApp::PostReport();
return(true);
}

//---------------------------------------------------------
// Procedure: OnStartUp()
//            happens before connection is open

bool CameraInterface::OnStartUp()
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
 if(param == "foo") {
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

void CameraInterface::registerVariables()
{
AppCastingMOOSApp::RegisterVariables();
// Register("FOOBAR", 0);
}


//------------------------------------------------------------
// Procedure: buildReport()

bool CameraInterface::buildReport()
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

void CameraInterface::startProcess(const std::string &sname,const std::string &moosfile, int argc, char **argv)
{
    SetCommandLineParameters(argc, argv);

    m_moosAppName = sname;
    m_moosMissionFile = moosfile;
}

void CameraInterface::run()
{
    RunInQtEventLoop(m_moosAppName, m_moosMissionFile);
}

bool CameraInterface::RunInQtEventLoop(const std::string &sName, const std::string &sMissionFile)
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
    connect(&iterateTimer, &QTimer::timeout, this, &CameraInterface::doMOOSWork);
    iterateTimer.start(1000.0/m_dfFreq);
    currentFrequency = m_dfFreq;
    return true;
}

bool CameraInterface::doMOOSWork()
{
    /****************************  THE MAIN MOOS APP LOOP **********************************/
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

void CameraInterface::readData()
{
#if debug == 1
    static int counter = 0;
    QString data = debug_string[counter];
    counter = (counter+1)%debug_string.size();
    processData(data);
#else

#endif
}


void CameraInterface::processData(QString data)
{

    std::cout<<"In processData: "<<data.toStdString()<<std::endl;
    QJsonDocument datagram = QJsonDocument::fromJson(data.toUtf8());
    QJsonObject datagram_object = datagram.object();
    QJsonObject data_field = datagram_object["data"].toObject();
    QJsonArray robots_array = data_field["robots"].toArray();
    for(QJsonValue dolphin : robots_array){
        QString id = dolphin.toObject().value("id").toString();
        double ort = dolphin.toObject().value("ort").toDouble();
        QJsonArray pos = dolphin.toObject().value("pos").toArray();
        double x = pos[0].toDouble();
        double y = pos[1].toDouble();
        int num_dolphin = QString(id.at(7)).toInt();
        id = "Dolphin"+QString::number(num_dolphin);
        std::cout<<"ID: "<<id.toStdString()<<". Ort: "<<ort<<". X,Y="<<x<<","<<y<<std::endl;
        //xPos=-5,yPos=6,id=Dolphin0, attitude=270
        QString data = "xPos="+QString::number(x)+",yPos="+QString::number(y)+",attitude="+QString::number(ort)+",id="+id;
        Notify(QString(id+"_Update_Pos").toStdString(), data.toStdString());
    }
}
