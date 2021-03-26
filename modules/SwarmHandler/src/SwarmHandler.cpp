/************************************************************/
/*    NAME: Josiah Sam                                             */
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
    zetaControl->setxPos(-2);
    zetaControl->setyPos(-2);
    zetaControl->setAttitude(0.0);
    zetaControl->setWholeLambda(QList<double>{4, 4, 4, 4});
    zetaControl->setWholeTheta(QList<double>{-90, -90, -90, -90});
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
  else if (key == "DOLPHIN_DISCONNECTED"){
      string id;
      MOOSValFromString(id , msg.GetString(), "id");
      registration->remove(QString::fromStdString(id));
  }
  else if(key == "Zeta_Cmd"){
      double xPos,yPos, att;
      string theta, lambda;
      QList<double> thetalist, lambdalist;
      std::string shape;
      MOOSValFromString(xPos , msg.GetString(), "xPos");
      MOOSValFromString(yPos , msg.GetString(), "yPos");
      MOOSValFromString(att , msg.GetString(), "Attitude");
      MOOSValFromString(theta , msg.GetString(), "Theta");
      MOOSValFromString(lambda , msg.GetString(), "Lambda");
      MOOSValFromString(shape , msg.GetString(), "shape");
      thetalist = toDoubleList(QString::fromStdString(theta).split("|"));
      lambdalist = toDoubleList(QString::fromStdString(lambda).split("|"));
      zetaControl->setxPos(xPos);
      zetaControl->setyPos(yPos);
      zetaControl->setWholeTheta(thetalist);
      zetaControl->setAttitude(att*PI/180.0);
      zetaControl->setWholeLambda(lambdalist);
      currentShape = QString::fromStdString(shape);
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
    else if(checkState(EnumDefs::VehicleStates::SWARMSTANDBY)){
        Notify("Change_State","State="+QString::number(EnumDefs::VehicleStates::SWARMRUN).toStdString(),MOOSTime());
    }
    else if(checkState(EnumDefs::VehicleStates::SWARMRUN)){
        for(QString it : m_neighbors){
            Notify(it.toStdString()+"_Neighbor_Zeta", "id= Narwhal, " +zetaControl->stringify().toStdString(),MOOSTime());
        }
        if(!inRun){
            inRun = true;
            m_first_time = MOOSTime();
        }
        if(currentShape == "LINE" && MOOSTime()-m_first_time > m_move_delay){
            incrementLineZeta();
        }
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
 if(param == "xincrement") {
   xIncrement = QString::fromStdString(value).toDouble();
   handled = true;
 }
 else if(param == "yincrement") {
   yIncrement = QString::fromStdString(value).toDouble();
   handled = true;
 }
 else if(param == "rotincrement") {
   rotationIncrement = QString::fromStdString(value).toDouble();
   handled = true;
 }
 else if(param == "movedelay") {
   m_move_delay = QString::fromStdString(value).toDouble();
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
Register("Zeta_Cmd", 0);
Register("DOLPHIN_DISCONNECTED", 0);
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
    if(dolphin == registration->end().value()){
        dolphin = new Robot(EnumDefs::VehicleStates::STANDBY);
    }
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
    inRun = false;
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
        iter.value()->podMates->append("Narwhal");
        m_neighbors.append(iter.key());
        if(numRobotsInSwarm != 1){
            iter++;
            QString next = iter.key();
            iter--;
            iter.value()->podMates->append(next);
            QString previous = iter.key();
            iter++;
            while(iter != registration->end()){
                iter.value()->podMates->append(previous);
                previous=iter.key();
                iter++;
                if(iter != registration->end()){
                    QString next = iter.key();
                    iter--;
                    iter.value()->podMates->append(next);
                    iter++;
                }
            }
            iter--;
            iter.value()->podMates->append("Narwhal");
        }
        iter.value()->podMates->append("Narwhal");
        m_neighbors.append("Dolphin"+QString::number(numRobotsInSwarm-1));
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
            //Don't think we need to multiply by lambda here
            iter.value()->xOffset = /*zetaControl->getLambda(link)**/(1.0-(linkageOffsetCounts[link]/(double)linkageBotCounts[link]));
            iter.value()->yOffset = 0.0;
            linkageOffsetCounts[link]--;
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
            message += iter.value()->podMates->value(0);
            for(int i = 1; i<iter.value()->podMates->count(); i++){
                message += "|"+iter.value()->podMates->value(i);
            }
            Notify(iter.key().toStdString()+"_Zeta_Init", message.toStdString(), MOOSTime());
        }
        iter++;
    }
}

QList<double> SwarmHandler::toDoubleList(QList<QString> input){
    QList<double> toReturn;
    for(int i=0; i<input.size(); i++){
     toReturn.append(input[i].toDouble());
    }
    return toReturn;
}

void SwarmHandler::incrementLineZeta()
{
    zetaControl->setxPos(zetaControl->getxPos()+xIncrement);
    zetaControl->setyPos(zetaControl->getyPos()+yIncrement);
    zetaControl->setAttitude(zetaControl->getAttitude()+rotationIncrement);
}
