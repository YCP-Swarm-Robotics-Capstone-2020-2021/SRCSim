#include "uimoosinterface.h"

using namespace std;

UIMoosInterface::UIMoosInterface(std::string sName, std::string sMissionFile)
{
    m_moosAppName = sName;
    m_moosMissionFile = sMissionFile;
    connect(&pingTimer, &QTimer::timeout, this, &UIMoosInterface::send_ping);
}

UIMoosInterface::~UIMoosInterface()
{

}

bool UIMoosInterface::OnNewMail(MOOSMSG_LIST &NewMail)
{
    AppCastingMOOSApp::OnNewMail(NewMail);
    cout << "i've got mail "<< endl;
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

        if(key == "Reg_In")
        {
            std::string id;
            MOOSValFromString(id, msg.GetString(), "id");
            if(!m_idList.contains(QString::fromStdString(id))){
                m_idList.append(QString::fromStdString(id));
                emit regIn(m_idList);
            }
        }
        else if(key == "Current_State")
        {
            Notify("Received_Current_State", "TRUE");
            std::string id;
            int state;
            MOOSValFromString(id, msg.GetString(), "id");
            MOOSValFromString(state, msg.GetString(), "State");
            QPair<double , bool> toinsert = QPair<double , bool>(MOOSTime(), false);
            m_updatemap.insert(QString::fromStdString(id), toinsert);
            emit updateState(QString::fromStdString(id), state);
        }
        else if(key == "Registered_Bots")
        {
            std::string list;
            MOOSValFromString(list, msg.GetString(), "Bot_Ids");
            auto dolphinList = QString::fromStdString(list).split('|');
            QList<QString>::iterator it = dolphinList.begin();
            QList<QString> updateList;
            while((it+1) != dolphinList.end()){ //stop 1 short to account for trailing '|'
                updateList.append((*it).split(':')[0]);
                it++;
            }
            if(updateList != m_idList){
                m_idList = updateList;
                emit regIn(m_idList);
            }
        }
        else if(key == "PROC_WATCH_DOLPHIN")
        {
            QString id = QString::fromStdString(msg.GetCommunity());
            QString processMsg = QString::fromStdString(msg.GetAsString());
            emit updateProcessWatch(id, processMsg);
        }
        else if(key == "PROC_WATCH_SUMMARY")
        {
            QString id = "All";
            QString processMsg = "GCS Proc Watch Report: "+QString::fromStdString(msg.GetAsString());
            emit updateProcessWatch(id, processMsg);
        }
        else if(key == "WCA_MESSAGE"){
            std::string id;
            std::string errormsg;
            int priority;
            MOOSValFromString(id, msg.GetString(), "ID");
            MOOSValFromString(errormsg, msg.GetString(), "Message");
            MOOSValFromString(priority, msg.GetString(), "Level");
            emit updateWarning(QString::fromStdString(id), QString::fromStdString(errormsg), priority);
        }
        else if(key == "VERSION_NUMBER")
        {
            QString id = QString::fromStdString(msg.GetCommunity());
            std::string version;
            std::string message;
            MOOSValFromString(version, msg.GetString(), "version");
            MOOSValFromString(message, msg.GetString(), "message");

            emit updateDolphinVersion(id, QString::fromStdString(toupper(version)), QString::fromStdString(message));

            Notify(id.toStdString()+"_VERSION_ACK", "TRUE");
        }
        else if(key != "APPCAST_REQ") // handled by AppCastingMOOSApp
        {
            reportRunWarning("Unhandled Mail: " + key);
        }

    }
    cout << "What the hell is he doing "<< endl;
    return(true);
}

bool UIMoosInterface::OnConnectToServer()
{
    registerVariables();
    return(true);
}


bool UIMoosInterface::Iterate()
{
    AppCastingMOOSApp::Iterate();
    cout << "trying to do"<< endl;
    m_publishBoundarySizeCounter++;
    if(m_publishBoundarySizeCounter > currentFrequency*BOUNDARY_SIZE_UPDATE_INTERVAL){
        QString size = "Width="+ QString::number(m_boundary_width) + ", Height="+ QString::number(m_boundary_height);
        Notify("BOUNDARY_SIZE", size.toStdString());
        m_publishBoundarySizeCounter = 0;
    }
    cout << "did"<< endl;
    return(true);
}

bool UIMoosInterface::OnStartUp()
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
     if(param == "numofbots") {
     }
     else if(param == "timeout") {
       handled = true;
       m_timeout = QString::fromStdString(value).toDouble();

     }
     else if(param == "bar") {
       handled = true;
     }

     if(!handled)
       reportUnhandledConfigWarning(orig);

    }
    registerVariables();
    pingTimer.start(m_timeout/double(pingTimerSetting));
    return(true);
}

void UIMoosInterface::registerVariables()
{
    AppCastingMOOSApp::RegisterVariables();
    Register("Reg_In");
    Register("Current_State");
    Register("Registered_Bots");
    Register("PROC_WATCH_DOLPHIN");
    Register("PROC_WATCH_SUMMARY");
    Register("WCA_MESSAGE");
    Register("VERSION_NUMBER");
}

bool UIMoosInterface::buildReport()
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


void UIMoosInterface::startProcess(const std::string &sname, const std::string &moosfile, int argc, char **argv){

    SetCommandLineParameters(argc, argv);

    m_moosAppName = sname;
    m_moosMissionFile = moosfile;
 //   start();
}

void UIMoosInterface::run()
{
    RunInQtEventLoop(m_moosAppName, m_moosMissionFile);
}

bool UIMoosInterface::RunInQtEventLoop(const std::string &sName, const std::string &sMissionFile)
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
    connect(&iterateTimer, &QTimer::timeout, this, &UIMoosInterface::doMOOSWork);
    connect(&callcheckactive, &QTimer::timeout, this, &UIMoosInterface::checkActive);
    iterateTimer.start(1000.0/m_dfFreq);
    callcheckactive.start(1000);
    currentFrequency = m_dfFreq;
    return true;
}

bool UIMoosInterface::doMOOSWork()
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

void UIMoosInterface::receiveZeta(QString zeta)
{
    Notify("Zeta_Cmd", zeta.toStdString());
}

void UIMoosInterface::receiveStateCMD(EnumDefs::VehicleStates state, QString id, int maxSpeed)
{
    if(state != EnumDefs::VehicleStates::SWARMMODE && id != QString("All"))
        Notify(id.toStdString()+"_Change_State", "State="+QString::number(int(state)).toStdString()+", id="+id.toStdString());
    else
        Notify("Change_State", "State="+QString::number(int(state)).toStdString());
}

void UIMoosInterface::receiveSpeed(QString id, bool forward, bool reverse, bool left, bool right, int speed)
{
    int speedSign = 1;
    int curv = 0;
    //Forward
    if(forward and ((not left and not right) or (left and right))){
        speedSign = 1;
    }
    //Back
    else if(reverse and ((not left and not right) or (left and right))){
        speedSign = -1;
    }
    //Right
    else if(right and not forward and not reverse and not left){
        curv = -90;
    }
    //Left
    else if(left and not forward and not reverse and not right){
        curv = 90;
    }
    //Forward Left
    else if(forward and left and not right){
        speedSign = 1;
        curv = 45;
    }
    //Forward Right
    else if(forward and right and not left){
        speedSign = 1;
        curv = -45;
    }
    //Back Left
    else if(reverse and left and not right){
        speedSign = -1;
        curv = -45;
    }
    //Back Right
    else if(reverse and right and not left){
        speedSign = -1;
        curv = 45;
    }
    //stop
    else{
        curv = 0;
        speedSign = 0;
    }
    Notify("Received_BOOLS", "FWD: "+QString::number(forward).toStdString()+". REV: "+QString::number(reverse).toStdString()+". RIGHT: "+QString::number(right).toStdString()+". Left: "+QString::number(left).toStdString());
    Notify(id.toStdString()+"_"+SPEED_CMD, "id="+id.toStdString()+",Speed="+QString::number(speed*speedSign).toStdString()+",Curv="+QString::number(curv).toStdString());
}

void UIMoosInterface::sendLogBookmark()
{
    Notify("LOG_BOOKMARK", GetAppName()+" "+std::to_string(++m_logBookmarkCounter));
}

void UIMoosInterface::updateBoundarySize(int width, int height)
{
    m_boundary_width = width;
    m_boundary_height = height;
    QString size = "Width="+ QString::number(m_boundary_width) + ", Height="+ QString::number(m_boundary_height);
    Notify("BOUNDARY_SIZE", size.toStdString());
}

void UIMoosInterface::onRunEnded(std::string msg)
{
    Notify(RUN_ENDED, msg);
}

void UIMoosInterface::onRunStarted(std::string msg)
{
    Notify(RUN_STARTED, msg);
}
void UIMoosInterface::checkActive()
{
    if(!m_updatemap.isEmpty()){
        for(QMap<QString , QPair<double , bool> >::iterator it = m_updatemap.begin(), end = m_updatemap.end(); it != end; ++it){
            if((MOOSTime() - it.value().first) >= m_timeout && !it.value().second){
                it.value().second = true;
                Notify("DOLPHIN_DISCONNECTED", "id="+ it.key().toStdString());
                emit updateWarning(it.key(), "Dolphin has been disconnected", EnumDefs::WARNING);
            }
        }
    }
}

void UIMoosInterface::send_ping()
{
    Notify(PING, "true");
}
