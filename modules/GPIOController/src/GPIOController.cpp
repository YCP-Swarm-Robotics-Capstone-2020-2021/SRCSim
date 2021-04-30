/************************************************************/
/*    NAME: Josiah Sam                                              */
/*    ORGN: YCP                                             */
/*    FILE: GPIOController.cpp                                        */
/*    DATE: 02/10/2021                                         */
/************************************************************/
#include <iterator>
#include "ivp/MBUtils.h"
#include "ivp/ACTable.h"
#include "GPIOController.h"

using namespace std;

//---------------------------------------------------------
// Constructor

GPIOController::GPIOController(std::string sName, std::string sMissionFile)
{    
    m_moosAppName = sName;
    m_moosMissionFile = sMissionFile;
    connect(&motorcontroller, &MotorController::notifyMOOSMsg, this, &GPIOController::notifyMOOSMsg);
    connect(&lircontoller, &LIRController::notifyMOOSMsg, this, &GPIOController::notifyMOOSMsg);
    connect(&distanceRangeTimer, &QTimer::timeout, &lircontoller, &LIRController::getRanges);
}

//---------------------------------------------------------
// Destructor

GPIOController::~GPIOController()
{
}

//---------------------------------------------------------
// Procedure: OnNewMail

bool GPIOController::OnNewMail(MOOSMSG_LIST &NewMail)
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
  else if(key == "Speed_Curv"){
    double speed = 0;
    double curv = 0;
    MOOSValFromString(speed,msg.GetString(),"Speed");
    MOOSValFromString(curv,msg.GetString(),"Curv");
    motorcontroller.onSpeedCurv(speed, curv);
  }
  else if(key == "Speed_Curv_Override"){
    double speed = 0;
    double curv = 0;
    MOOSValFromString(speed,msg.GetString(),"Speed");
    MOOSValFromString(curv,msg.GetString(),"Curv");
    if(state == EnumDefs::VehicleStates::TELEOP){
        motorcontroller.onSpeedCurvOverride(speed, curv);
    }
  }
  else if(key == "OVERRIDE_ON"){
    bool on = (msg.GetAsString()=="true");
    motorcontroller.setOverride(on);
  }
  else if(key == "Current_State"){
      if(!msg.IsString()){
         return MOOSFail("MotionController::handleCurrentState - You did not input a string you ninny");
      }
      int x;
      MOOSValFromString(x , msg.GetString(), "State");
      state = EnumDefs::VehicleStates(x);
  }
  else if(key == "CONNECTION_STATUS"){
      int x;
      MOOSValFromString(x, msg.GetString(), "Status");
      connectionStatus = EnumDefs::ConnectionState(x);
  }
  else if(key != "APPCAST_REQ") // handled by AppCastingMOOSApp
    reportRunWarning("Unhandled Mail: " + key);
}

return(true);
}

//---------------------------------------------------------
// Procedure: OnConnectToServer

bool GPIOController::OnConnectToServer()
{
registerVariables();
return(true);
}

//---------------------------------------------------------
// Procedure: Iterate()
//            happens AppTick times per second

bool GPIOController::Iterate()
{
AppCastingMOOSApp::Iterate();
// Do your thing here!
//AppCastingMOOSApp::PostReport();
if(!onStartupComplete){
    if(!m_motorStartupComplete){
        cout<<"Trying to connect motors."<<endl;
        m_motorStartupComplete = motorcontroller.start();
    }
    if(!m_ledStartupComplete){
        cout<<"Trying to connect LEDs"<<endl;
        m_ledStartupComplete = ledcontoller.start();
    }
    if(!m_lirStartupComplete){
        cout<<"Trying to connect LIRSeonsors"<<endl;
        m_lirStartupComplete = lircontoller.start();

	if(m_lirStartupComplete){
	  distanceRangeTimer.start(rangingTimerPeriod);
	}

    }
    onStartupComplete = m_motorStartupComplete && m_ledStartupComplete && m_lirStartupComplete;
}
if(m_ledStartupComplete){
    ledcontoller.updateLEDStatus(state, connectionStatus);
}
return(true);
}

//---------------------------------------------------------
// Procedure: OnStartUp()
//            happens before connection is open

bool GPIOController::OnStartUp()
{
AppCastingMOOSApp::OnStartUp();

STRING_LIST sParams;
m_MissionReader.EnableVerbatimQuoting(false);
if(!m_MissionReader.GetConfiguration(GetAppName(), sParams))
 reportConfigWarning("No config block found for " + GetAppName());
int ccwl = 0, cwl = 0;
STRING_LIST::iterator p;
for(p=sParams.begin(); p!=sParams.end(); p++) {
 string orig  = *p;
 string line  = *p;
 string param = tolower(biteStringX(line, '='));
 string value = line;
 bool handled = false;
 if(param == "wheelradius") {
   for(int i= 0; i<2; i++){
       QList<Motor*> temp = motorcontroller.motorMap.value(SIDE(i));
       temp[0]->wheelrad = QString::fromStdString(value).toDouble();
       temp[1]->wheelrad = QString::fromStdString(value).toDouble();
       motorcontroller.motorMap.insert(SIDE(i), temp);
   }

     handled = true;
 }
 else if (param == "p"){
     for(int i= 0; i<2; i++){
         QList<Motor*> temp = motorcontroller.motorMap.value(SIDE(i));
         temp[0]->p = QString::fromStdString(value).toDouble();
         temp[1]->p = QString::fromStdString(value).toDouble();
         motorcontroller.motorMap.insert(SIDE(i), temp);
     }

       handled = true;
 }
 else if (param == "i"){
     for(int i= 0; i<2; i++){
         QList<Motor*> temp = motorcontroller.motorMap.value(SIDE(i));
         temp[0]->i = QString::fromStdString(value).toDouble();
         temp[1]->i = QString::fromStdString(value).toDouble();
         motorcontroller.motorMap.insert(SIDE(i), temp);
     }

       handled = true;
 }
 else if (param == "d"){
     for(int i= 0; i<2; i++){
         QList<Motor*> temp = motorcontroller.motorMap.value(SIDE(i));
         temp[0]->d = QString::fromStdString(value).toDouble();
         temp[1]->d = QString::fromStdString(value).toDouble();
         motorcontroller.motorMap.insert(SIDE(i), temp);
     }

       handled = true;
 }
 else if (param == "cwbandl"){
     cwl = QString::fromStdString(value).toDouble();
     for(int i= 0; i<2; i++){
         QList<Motor*> temp = motorcontroller.motorMap.value(SIDE(i));
         temp[0]->cwlow = QString::fromStdString(value).toDouble();
         temp[1]->cwlow = QString::fromStdString(value).toDouble();
         motorcontroller.motorMap.insert(SIDE(i), temp);
     }

       handled = true;
 }
 else if (param == "cwbandh"){
     for(int i= 0; i<2; i++){
         QList<Motor*> temp = motorcontroller.motorMap.value(SIDE(i));
         temp[0]->cwhigh = QString::fromStdString(value).toDouble();
         temp[1]->cwhigh = QString::fromStdString(value).toDouble();
         motorcontroller.motorMap.insert(SIDE(i), temp);
     }

       handled = true;
 }
 else if (param == "ccwbandl"){
     ccwl = QString::fromStdString(value).toDouble();
     for(int i= 0; i<2; i++){
         QList<Motor*> temp = motorcontroller.motorMap.value(SIDE(i));
         temp[0]->ccwlow = QString::fromStdString(value).toDouble();
         temp[1]->ccwlow = QString::fromStdString(value).toDouble();
         motorcontroller.motorMap.insert(SIDE(i), temp);
     }

       handled = true;
 }
 else if (param == "ccwbandl"){
     for(int i= 0; i<2; i++){
         QList<Motor*> temp = motorcontroller.motorMap.value(SIDE(i));
         temp[0]->ccwlow = QString::fromStdString(value).toDouble();
         temp[1]->ccwlow = QString::fromStdString(value).toDouble();
         motorcontroller.motorMap.insert(SIDE(i), temp);
     }

       handled = true;
 }
 else if (param == "ccwbandh"){
     for(int i= 0; i<2; i++){
         QList<Motor*> temp = motorcontroller.motorMap.value(SIDE(i));
         temp[0]->ccwhigh = QString::fromStdString(value).toDouble();
         temp[1]->ccwhigh = QString::fromStdString(value).toDouble();
         motorcontroller.motorMap.insert(SIDE(i), temp);
     }

       handled = true;
 }
 else if (param == "readbandl"){
     for(int i= 0; i<2; i++){
         QList<Motor*> temp = motorcontroller.motorMap.value(SIDE(i));
         temp[0]->rdlow = QString::fromStdString(value).toDouble();
         temp[1]->rdlow = QString::fromStdString(value).toDouble();
         motorcontroller.motorMap.insert(SIDE(i), temp);
     }

       handled = true;
 }
 else if (param == "readbandh"){
     for(int i= 0; i<2; i++){
         QList<Motor*> temp = motorcontroller.motorMap.value(SIDE(i));
         temp[0]->rdhigh = QString::fromStdString(value).toDouble();
         temp[1]->rdhigh = QString::fromStdString(value).toDouble();
         motorcontroller.motorMap.insert(SIDE(i), temp);
     }

       handled = true;
 }
 else if (param == "maxrpm"){
     for(int i= 0; i<2; i++){
         QList<Motor*> temp = motorcontroller.motorMap.value(SIDE(i));
         temp[0]->maxRPM = QString::fromStdString(value).toDouble();
         temp[1]->maxRPM = QString::fromStdString(value).toDouble();
         motorcontroller.motorMap.insert(SIDE(i), temp);
     }
       handled = true;
 }
 else if (param == "motor"){
     QList<QString> temp = QString::fromStdString(value).split(',');
     int id = 0;
     int cGPIO = 0;
     int rGPIO = 0;
     int side = 0;
     bool reversed = false;
     for(QString value : temp){
         QList<QString> temp2 = value.split(':');
         if(temp2[0] == "id"){
             id = temp2[1].toDouble();
         }
         else if(temp2[0] == "CTRLGPIO"){
             cGPIO = temp2[1].toDouble();
         }
         else if(temp2[0] == "READGPIO"){
             rGPIO = temp2[1].toDouble();
         }
         else if(temp2[0] == "SIDE"){
              side = temp2[1] == "R" ? 1 : 0;
         }
         else if(temp2[0] == "REVERSED"){
              reversed = (temp2[1] == "true");
         }
     }
     QList<Motor*> temp3 = motorcontroller.motorMap.value(SIDE(side));
     temp3[((id-1)%2)]->id = id;
     temp3[((id-1)%2)]->writeGPIO = cGPIO;
     temp3[((id-1)%2)]->readGPIO = rGPIO;
     temp3[((id-1)%2)]->reversed = reversed;
     temp3[((id-1)%2)]->side = SIDE(side);
     motorcontroller.motorMap.insert(SIDE(side), temp3);
     handled = true;
 }
 else if (param == "led"){
     QList<QString> temp = QString::fromStdString(value).split(',');
     int id = -1;
     int pin = -1;
     for(QString value : temp){
         QList<QString> temp2 = value.split(':');
         if(toupper(temp2[0].toStdString()) == "ID"){
            id = temp2[1].toInt();
         }
         else if (toupper(temp2[0].toStdString()) == "PIN"){
            pin = temp2[1].toInt();
         }
     }
     if(pin < 0 || id < 0){
         return -1;
     }
     LED led;
     led.id = id;
     led.pin = pin;
     ledcontoller.led_list.insert(id, led);
     handled = true;
 }
 else if (param == "currentspeednotifyrates"){
     motorcontroller.notifyCurrentSpeedInterval = QString::fromStdString(value).toDouble();
     handled = true;
 }
 else if(param == "maxspeed") {
   double max_speed = QString::fromStdString(value).toDouble();
   motorcontroller.maxSpeed = max_speed;
   handled = true;
 }
 else if(param == "debug") {
   bool debug = (toupper(value)=="TRUE");
   ledcontoller.debug = debug;
   handled = true;
 }
 else if(param == "lirsensor"){
     QList<QString> temp = QString::fromStdString(value).split(',');
     QString id = "";
     int pin = -1;
     double freq = -1;
     double distance = -1;
     LIRSensor sensor;
     for(QString value : temp){
         QList<QString> temp2 = value.split(':');
         if(toupper(temp2[0].toStdString()) == "ID"){
            id = temp2[1];
            if(toupper(id.toStdString()) == "LEFT"){
                sensor.side = LEFT;
            }else {
                sensor.side = RIGHT;
            }
         }
         else if (toupper(temp2[0].toStdString()) == "INTGPIO"){
            pin = temp2[1].toInt();
            sensor.intGpio = pin;
         }
         else if (toupper(temp2[0].toStdString()) == "FREQ"){
            freq = temp2[1].toDouble();
            sensor.frequency = freq;

	    rangingTimerPeriod = 1000.0/freq;
         }
         else if (toupper(temp2[0].toStdString()) == "DIST"){
            distance = temp2[1].toDouble();
            sensor.distance = distance;

	    lircontoller.minRangeMM = distance;	    

         }
         else if(toupper(temp2[0].toStdString()) == "BUS"){
             sensor.bus = temp2[1].toInt();
         }
     }
     if(pin < 0 || id < 0){
         return -1;
     }
     lircontoller.sensor_list[sensor.side] = sensor;
     handled = true;
 }
 else if(param == "lirsensoraddress"){
    QString addr = QString::fromStdString(value);
    lircontoller.address = addr.toUInt(NULL, 16);
 }

 if(!handled)
   reportUnhandledConfigWarning(orig);

}
motorcontroller.setupDeadbandRange(ccwl, cwl);
for(auto list : motorcontroller.motorMap){
    cout<<"Key: "<<motorcontroller.motorMap.key(list);
    for(auto element : list){
        QString reversed = (element->reversed)?"y":"n";
        cout<<"\nMotor: "<<element->id
            <<"\tP: "<<element->p<<"\n"
            <<"\tI:"<<element->i<<"\n"
            <<"\tD:"<<element->d<<"\n"
            <<"\tSide:"<<element->side<<"\n"
            <<"\tCWL:"<<element->cwlow<<"\n"
            <<"\tCWH:"<<element->cwhigh<<"\n"
            <<"\tCCWL:"<<element->ccwlow<<"\n"
            <<"\tCCWH:"<<element->ccwhigh<<"\n"
            <<"\tRDL:"<<element->rdlow<<"\n"
            <<"\tRDH:"<<element->rdhigh<<"\n"
            <<"\tDBH:"<<element->dblow<<"\n"
            <<"\tDBL:"<<element->dbhigh<<"\n"
            <<"\tMaxRPM:"<<element->maxRPM<<"\n"
            <<"\tMaxRPM:"<<element->wheelrad<<"\n"
            <<"\tReversed:"<<reversed.toStdString()<<"\n"
            <<"\tReadGPIO:"<<element->readGPIO<<"\n"
            <<"\tWriteGPIO:"<<element->writeGPIO<<"\n"<<endl;
    }
}
for(auto led : ledcontoller.led_list.values()){
    cout<<"\n\tPin: "<<led.pin<<"\n"
        <<"\tID: " <<led.id <<"\n"
        <<"\tStatus:"<<led.status<<"\n";
}

for(auto IR : lircontoller.sensor_list.values()){
    cout<<"\n\tSide: "<<((IR.side) ? "RIGHT" : "LEFT")<<"\n"
        <<"\tPin: "<<IR.intGpio<<"\n"
        <<"\tDistance "<<IR.distance<<"\n"
        <<"\tAddress "<<lircontoller.address<<"\n"
        <<"\tBus "<<IR.bus<<"\n"
        <<"\tFrequency "<<IR.frequency<<"\n"<<endl;
}
registerVariables();
return(true);
}

//---------------------------------------------------------
// Procedure: registerVariables

void GPIOController::registerVariables()
{
    AppCastingMOOSApp::RegisterVariables();
    Register("Speed_Curv");
    Register("OVERRIDE_ON");
    Register("Speed_Curv_Override");
    Register("CONNECTION_STATUS");
    Register("Current_State");
}


//------------------------------------------------------------
// Procedure: buildReport()

bool GPIOController::buildReport()
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

void GPIOController::startProcess(const std::string &sname, const std::string &moosfile, int argc, char **argv)
{
    SetCommandLineParameters(argc, argv);

    m_moosAppName = sname;
    m_moosMissionFile = moosfile;
}

void GPIOController::run()
{
    RunInQtEventLoop(m_moosAppName, m_moosMissionFile);
}

bool GPIOController::RunInQtEventLoop(const std::string &sName, const std::string &sMissionFile)
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
    connect(&iterateTimer, &QTimer::timeout, this, &GPIOController::doMOOSWork);
    iterateTimer.start(1000.0/m_dfFreq);
    currentFrequency = m_dfFreq;
    return true;
}

bool GPIOController::doMOOSWork()
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

void GPIOController::notifyMOOSMsg(QString key, QString msg)
{
    Notify(key.toStdString(), msg.toStdString());
}
