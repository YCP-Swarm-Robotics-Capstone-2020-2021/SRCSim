/************************************************************/
/*    NAME: jsam                                              */
/*    ORGN: YCP                                             */
/*    FILE: SwarmHandler.cpp                                        */
/*    DATE: 07/23/2020                                         */
/************************************************************/
#include <iterator>
#include "ivp/MBUtils.h"
#include "ivp/ACTable.h"
#include "SwarmHandler.h"

using namespace std;

//---------------------------------------------------------
// Constructor

SwarmHandler::SwarmHandler()
{
    registration = new QMap<QString, Robot*>();
    zetaControl = new Zeta();
}

//---------------------------------------------------------
// Destructor

SwarmHandler::~SwarmHandler()
{
    delete registration;
    delete  zetaControl;
}

//---------------------------------------------------------
// Procedure: OnNewMail

bool SwarmHandler::OnNewMail(MOOSMSG_LIST &NewMail)
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

  if(key == "Reg_In"){
      qDebug() << "Received Reg_In message.";
      onRegistration(msg);
  }
  else if(key == "Current_State"){
      std::cout << "We Received Current State Message.";
      onCurrentState(msg);
  }
  else if(key == "Change_State"){
      onChangeState(msg);
  }
  else if(key != "APPCAST_REQ") {// handled by AppCastingMOOSApp
    reportRunWarning("Unhandled Mail: " + key);
    std::cout << "Bad message: "<<key<<std::endl;
  }
}

return(true);
}

//---------------------------------------------------------
// Procedure: OnConnectToServer

bool SwarmHandler::OnConnectToServer()
{
registerVariables();
return(true);
}

//---------------------------------------------------------
// Procedure: Iterate()
//            happens AppTick times per second

bool SwarmHandler::Iterate()
{
AppCastingMOOSApp::Iterate();
// Do your thing here!
//AppCastingMOOSApp::PostReport();
    QMap<QString, Robot*>::iterator i = registration->begin();
    QString messageData = "Bot_Ids=";
    for(; i != registration->end(); i++){
        messageData += i.key()+":"+QString::number(i.value()->state)+"|";
    }
    Notify("Registered_Bots", messageData.toStdString(), MOOSTime());
    if(checkState(EnumDefs::VehicleStates::SWARMINIT)){
        initializeSwarm();
    }
return(true);
}

//---------------------------------------------------------
// Procedure: OnStartUp()
//            happens before connection is open

bool SwarmHandler::OnStartUp()
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

void SwarmHandler::registerVariables()
{
AppCastingMOOSApp::RegisterVariables();
// Register("FOOBAR", 0);
Register("Change_State", 0);
Register("Current_State", 0);
Register("Reg_In", 0);
}


//------------------------------------------------------------
// Procedure: buildReport()

bool SwarmHandler::buildReport()
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

void SwarmHandler::onRegistration(CMOOSMsg &msg)
{
    std::string id;
    if(!msg.IsString()){
        MOOSDebugWrite("SwarmHandler: Received a Reg_In message that was not of type string.");
        return;
    }
    if(!MOOSValFromString(id, msg.GetString(), "id")){
        MOOSDebugWrite("SwarmHandler: Unable to retreive id from Reg_In message.");
        return;
    }
    MOOSDebugWrite("SwarmHandler: "+id+" registration message received. Sending acknowledgment.");
    registration->insert(QString::fromStdString(id), new Robot(EnumDefs::VehicleStates::STANDBY));
    Notify(id+"_Reg_Ack", "true", MOOSTime());
}

bool SwarmHandler::onCurrentState(CMOOSMsg &msg)
{
    std::string id;
    int state;
    EnumDefs::VehicleStates newState;
    if(!msg.IsString()){
        MOOSDebugWrite("SwarmHandler: Received a CurrentString message that is not a string.");
        return MOOSFail("SwarmHandler: CurrentState message received that is not a string.");
    }
    if(!MOOSValFromString(id, msg.GetString(), "id")){
        MOOSDebugWrite("SwarmHandler: Unable to get id out of Current_State message.");
        return MOOSFail("SwarmHandler: Unable to get id out of Current_State message.");
    }
    if(!MOOSValFromString(state, msg.GetString(), "State")){
        MOOSDebugWrite("SwarmHandler: Unable to get State out of Current_State message.");
        return MOOSFail("SwarmHandler: Unable to get State out of Current_State message.");
    }
    newState = EnumDefs::VehicleStates(state);
    Robot *dolphin = registration->find(QString::fromStdString(id)).value();
    dolphin->state = newState;
    registration->insert(QString::fromStdString(id), dolphin);
    return true;
}

bool SwarmHandler::onChangeState(CMOOSMsg &msg)
{
    int intState;
    if(!msg.IsString()){
        MOOSDebugWrite("SwarmHandler: Received a Change_String message that is not a string.");
        return MOOSFail("SwarmHandler: Change_State message received that is not a string.");
    }
    if(!MOOSValFromString(intState, msg.GetString(), "State")){
        MOOSDebugWrite("SwarmHandler: Unable to get id out of Current_State message.");
        return MOOSFail("SwarmHandler: Unable to get id out of Current_State message.");
    }
    state = EnumDefs::VehicleStates(intState);
    if(state == EnumDefs::VehicleStates::SWARMMODE){
        zetaControl->setxPos(-2);
        zetaControl->setyPos(-2);
        zetaControl->setAttitude(0);
        zetaControl->setWholeLambda(QList<double>{4, 4, 4, 4});
        zetaControl->setWholeTheta(QList<double>{-90, -90, -90, -90});
    }
    return true;

}

bool SwarmHandler::checkState(EnumDefs::VehicleStates state)
{
    if(registration->count()<1){
        return false;
    }
    QMap<QString, Robot*>::iterator iter = registration->begin();
    while(iter != registration->end()){
        if(iter.value()->state != state){
            return false;
        }
        iter++;
    }
    return true;
}

void SwarmHandler::initializeSwarm()
{
    int numRobotsInSwarm = registration->count();
    int numLinkagesInFormation = zetaControl->getWholeLambda().count();
    int linkageBotCounts[numLinkagesInFormation];
    int linkageOffsetCounts[numLinkagesInFormation];
    for(int i = 0; i<numLinkagesInFormation; i++){
        linkageBotCounts[i] = 0;
        linkageOffsetCounts[i] = 0;
    }
    QMap<QString, Robot*>::iterator iter = registration->begin();

    //Setup topology of the formation
    if(!SwarmInitialized){
        iter.value()->podMates->append(QList<QString>{"Narwhal", iter++.key()});
        while(iter != registration->end()--){
            iter.value()->podMates = new QList<QString>{iter--.key(), (iter++)++.key()};
        }
        iter.value()->podMates=new QList<QString>{iter--.key()};

        //Setup Linkage assignments.
        iter = registration->begin();
        for(int i = 0; i<numRobotsInSwarm; i++, iter++){
            iter.value()->linkageAssignment = i%numLinkagesInFormation;
            linkageBotCounts[i%numLinkagesInFormation]++;
            linkageOffsetCounts[i%numLinkagesInFormation]++;
        }

        iter = registration->begin();
        while(iter != registration->end()){
            int link = iter.value()->linkageAssignment;
            iter.value()->xOffset = zetaControl->getLambda(link)*(1.0-(linkageOffsetCounts[link]/(double)linkageBotCounts[link]));
            iter.value()->yOffset = 0.0;
            iter++;
        }
        SwarmInitialized = true;
    }

    iter = registration->begin();
    while(iter != registration->end()){
        if(iter.value()->state == EnumDefs::SWARMINIT){
            QString message = "xOffset="+QString::number(iter.value()->xOffset) +
                              ", yOffset="+QString::number(iter.value()->yOffset) +
                              ", linkageNum="+QString::number(iter.value()->linkageAssignment) +
                              ", numLinks="+QString::number(numLinkagesInFormation)+
                              ", neighborIds=";
            for(int i = 0; i<iter.value()->podMates->count(); i++){
                message += iter.value()->podMates->value(i);
            }
            Notify(iter.key().toStdString()+"_ZetaInit", message.toStdString(), MOOSTime());
        }
        iter++;
    }
}
