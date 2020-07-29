/************************************************************/
/*    NAME: Kyle Leatherman                                              */
/*    ORGN: YCP                                             */
/*    FILE: MotionController.cpp                                        */
/*    DATE: 06/08/2020                                         */
/************************************************************/
#include <iterator>
#include "ivp/MBUtils.h"
#include "ivp/ACTable.h"
#include "MotionController.h"

using namespace std;

//---------------------------------------------------------
// Constructor

MotionController::MotionController()
{
    entryZone = new QLabel("Enter input");
    podmates = new QMap<QString, Zeta>();
    srand(time(NULL));
}

//---------------------------------------------------------
// Destructor

MotionController::~MotionController()
{
}

//---------------------------------------------------------
// Procedure: OnNewMail

bool MotionController::OnNewMail(MOOSMSG_LIST &NewMail)
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

  if(key == "Current_Pos"){
    handleCurrentPos(msg);
  }
  else if(key == "Current_State"){
      handleCurrentState(msg);
  }
  else if(key == "Zeta_Init"){
      handleZetaInit(msg);
  }
  else if(key == "Neighbor_Zeta"){
      handleNeighborZeta(msg);
  }
  else if(key != "APPCAST_REQ") // handled by AppCastingMOOSApp
    reportRunWarning("Unhandled Mail: " + key);
}

return(true);
}

//---------------------------------------------------------
// Procedure: OnConnectToServer

bool MotionController::OnConnectToServer()
{
registerVariables();
return(true);
}

//---------------------------------------------------------
// Procedure: Iterate()
//            happens AppTick times per second

bool MotionController::Iterate()
{
AppCastingMOOSApp::Iterate();
// Do your thing here!
switch(state){
    case EnumDefs::VehicleStates::TELEOP:{
        QString moveData = "id="+ id +",Speed="+ QString::number(roboSpeed) + ",Curv=" + QString::number(roboCurv);
        Notify("Speed_Curv", moveData.toStdString(), MOOSTime());
        break;
    }
    case EnumDefs::VehicleStates::STANDBY:{
        QString moveData = "id="+ id +",Speed="+ QString::number(0) + ",Curv=" + QString::number(0);
        Notify("Speed_Curv", moveData.toStdString(), MOOSTime());
        break;
    }
    case EnumDefs::VehicleStates::ALLSTOP:{
        QString moveData = "id="+ id +",Speed="+ QString::number(0) + ",Curv=" + QString::number(0);
        Notify("Speed_Curv", moveData.toStdString(), MOOSTime());
        break;
    }
    case EnumDefs::VehicleStates::DEMOMODE:{
        demoRun();
        break;
    }
    case EnumDefs::VehicleStates::SWARMINIT:{
        QString moveData = "id="+ id +",Speed="+ QString::number(0) + ",Curv=" + QString::number(0);
        Notify("Speed_Curv", moveData.toStdString(), MOOSTime());
        state = swarmInit();
        moveData = "State=" + QString::number(state);
        Notify("Change_State", moveData.toStdString(), MOOSTime());
        break;
    }
    case EnumDefs::VehicleStates::SWARMSTANDBY:{
        QString moveData = "id="+ id +",Speed="+ QString::number(0) + ",Curv=" + QString::number(0);
        Notify("Speed_Curv", moveData.toStdString(), MOOSTime());
        break;
    }
    case EnumDefs::VehicleStates::SWARMRUN:{
        swarmRun();
        break;
    }
    default:{
        MOOSDebugWrite("MotionController: Invalid state");
        break;
    }
}



//AppCastingMOOSApp::PostReport();
return(true);
}

//---------------------------------------------------------
// Procedure: OnStartUp()
//            happens before connection is open

bool MotionController::OnStartUp()
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
     boundary -= id.mid(7).toDouble()+0.5;
     Notify("Boundary", boundary, MOOSTime());
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

void MotionController::registerVariables()
{
AppCastingMOOSApp::RegisterVariables();
Register("Current_State");
Register("Current_Pos");
Register("Zeta_Init");
Register("Neighbor_Zeta");
}


//------------------------------------------------------------
// Procedure: buildReport()

bool MotionController::buildReport()
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

bool MotionController::handleCurrentPos(CMOOSMsg &msg){
     if(!msg.IsString()){
        return MOOSFail("MotionController::handleCurrentPos - You did not input a string you ninny");
     }
     MOOSValFromString(x , msg.GetString(), "xPos");
     MOOSValFromString(y , msg.GetString(), "yPos");
     MOOSValFromString(attitude , msg.GetString(), "attitude");
     return true;
}

bool MotionController::handleCurrentState(CMOOSMsg &msg){
     if(!msg.IsString()){
        return MOOSFail("MotionController::handleCurrentState - You did not input a string you ninny");
     }
     int x;
     MOOSValFromString(x , msg.GetString(), "State");
     state = EnumDefs::VehicleStates(x);



     return true;
}

bool MotionController::handleZetaInit(CMOOSMsg &msg){
     if(!msg.IsString()){
        return MOOSFail("MotionController::handleCurrentState - You did not input a string you ninny");
     }
     string ids;
     QList<QString> idlist;
     MOOSValFromString(xlinkoff , msg.GetString(), "xOffset");
     MOOSValFromString(ylinkoff , msg.GetString(), "yOffset");
     MOOSValFromString(linknum , msg.GetString(), "linkageNum");
     MOOSValFromString(numlinks, msg.GetString(), "numLinks");
     MOOSValFromString(ids , msg.GetString(), "neighborIds");
     idlist = QString::fromStdString(ids).split("|");
     for(int i = 0; i< idlist.size(); i++){
         podmates->insert(idlist[i], Zeta());
     }
     swarmflag = true;



     return true;
}

bool MotionController::handleNeighborZeta(CMOOSMsg &msg){
    if(!msg.IsString()){
       return MOOSFail("MotionController::handleCurrentState - You did not input a string you ninny");
    }
    string id;
    double xPos,yPos, att;
    string theta, lambda;
    QList<double> thetalist, lambdalist;
    MOOSValFromString(id , msg.GetString(), "id");
    MOOSValFromString(xPos , msg.GetString(), "xPos");
    MOOSValFromString(yPos , msg.GetString(), "yPos");
    MOOSValFromString(att , msg.GetString(), "Attitude");
    MOOSValFromString(theta , msg.GetString(), "Theta");
    MOOSValFromString(lambda , msg.GetString(), "Lambda");
    thetalist = toDoubleList(QString::fromStdString(theta).split("|"));
    lambdalist = toDoubleList(QString::fromStdString(lambda).split("|"));
    podmates->find(QString::fromStdString(id))->setxPos(xPos);
    podmates->find(QString::fromStdString(id))->setyPos(yPos);
    podmates->find(QString::fromStdString(id))->setAttitude(att);
    podmates->find(QString::fromStdString(id))->setWholeTheta(thetalist);
    podmates->find(QString::fromStdString(id))->setWholeLambda(lambdalist);
    return true;
}

QList<double> MotionController::toDoubleList(QList<QString> input){
    QList<double> toReturn;
    for(int i=0; i<input.size(); i++){
     toReturn.append(input[i].toDouble());
    }
    return toReturn;
}

void MotionController::run(){
    Run(m_moosAppName,m_moosMissionFile);
}

void MotionController::startProcess(const std::string &sname, const std::string &moosfile, int argc, char **argv){

    SetCommandLineParameters(argc, argv);

    m_moosAppName = sname;
    m_moosMissionFile = moosfile;
    start();
}

void MotionController::demoRun()
{
    if(x >= -boundary && y >= boundary){ //Quadrant 1
        if((attitude>10.0 && attitude<180.0)){ //Pointing down
            roboCurv = -90.0; //clockwise
            roboSpeed = turn_speed;
        } else if (attitude<350.0 && attitude>=180.0){
            roboCurv = 90.0;
            roboSpeed = turn_speed;
        } else { //Not facing right way
            roboSpeed = max_speed;
            roboCurv = 0.0;
        }
    } else if (x < -boundary && y >= -boundary) { //Quadrant 2
        if((attitude>100.0 && attitude<270.0)){ //Pointing down
            roboCurv = -90.0; //clockwise
            roboSpeed = turn_speed;
        } else if (attitude<80.0 || attitude >= 270.0){
            roboCurv = 90.0;
            roboSpeed = turn_speed;
        } else { //Not facing right way
            roboSpeed = max_speed;
            roboCurv = 0.0;
        }
    } else if (x <= boundary && y < -boundary) { //Quadrant 3
        if((attitude>190.0 && attitude<360.0)){ //Pointing down
            roboCurv = -90.0; //clockwise
            roboSpeed = turn_speed;
        } else if (attitude<170.0 && attitude >= 0.0){
            roboCurv = 90.0;
            roboSpeed = turn_speed;
        } else { //Not facing right way
            roboSpeed = max_speed;
            roboCurv = 0.0;
        }
    } else if (x >= boundary && y < boundary) { //Quadrant 4
        if((attitude>280.0 || attitude<90.0)){ //Pointing down
            roboCurv = -90.0; //clockwise
            roboSpeed = turn_speed;
        } else if (attitude<260.0 && attitude >= 90.0){
            roboCurv = 90.0;
            roboSpeed = turn_speed;
        } else { //Not facing right way
            roboSpeed = max_speed;
            roboCurv = 0.0;
        }
    } else {
        roboSpeed = max_speed;
        roboCurv = 0.0;
    }
    QString moveData = "id="+ id +",Speed="+ QString::number(roboSpeed) + ",Curv=" + QString::number(roboCurv);
    Notify("Speed_Curv", moveData.toStdString(), MOOSTime());
}

QPoint MotionController::linktoref(){
    QPoint point = QPoint(xlinkoff*CurrentZeta.getLambda(linknum), ylinkoff*CurrentZeta.getLambda(linknum));
    for( int i = linknum-1; i>=0; i--){
        point.setX(point.x()*cos(-CurrentZeta.getTheta(i)) - point.y()*sin(-CurrentZeta.getTheta(i)));
        point.setY(point.x()*sin(-CurrentZeta.getTheta(i)) + point.y()*cos(-CurrentZeta.getTheta(i)));
        point.setX(point.x() + CurrentZeta.getLambda(i));
    }
    return point;
}

double MotionController::pointtoTraj(QPoint point){
    double xdiff = point.x()- x;
    double ydiff = point.y()- y;
    double phi;
    if(xdiff >=0 && ydiff >= 0){
         phi = atan(xdiff/ydiff);
    }
    else if(xdiff <=0 && ydiff >= 0){
         phi = atan(ydiff/xdiff)+90;
    }
    else if(xdiff <=0 && ydiff <= 0){
         phi = atan(xdiff/ydiff)+180;
    }
    else{
         phi = atan(ydiff/xdiff)+270;
    }
    phi += attitude;
    if(phi > 360){
        phi -= 360;
    }
    else if( phi < 0 ){
        phi += 360;
    }
    return phi;

}

void MotionController::swarmRun(){
    Zeta DiffZeta = Zeta();
    for(int i=0; i<podmates->size(); i++){
        Notify(podmates->keys()[i].toStdString()+"_Neighbor_Zeta", "id="+ id.toStdString()+", "+ CurrentZeta.stringify().toStdString(), MOOSTime());
    }
    for(int i=0; i<podmates->size(); i++){
        DiffZeta = DiffZeta + podmates->values()[i] - (CurrentZeta - podmates->values()[i])*kappa;
    }
    CurrentZeta = CurrentZeta + DiffZeta * dt;
    goalpoint= linktoref();
    goalpoint.setX(goalpoint.x()+CurrentZeta.getxPos());
    goalpoint.setY(goalpoint.y()+CurrentZeta.getyPos());
    goalangle = pointtoTraj(goalpoint);

}

EnumDefs::VehicleStates MotionController::swarmInit(){
    QPoint point;
    if(!swarmflag){
        return EnumDefs::SWARMINIT;
    }
    for(int i = 0; i<numlinks; i++){
        CurrentZeta.addtoTheta(rand() % 360);
        CurrentZeta.addtoLambda(rand() % 7+0.1);
    }
    CurrentZeta.setAttitude(attitude);
    point = linktoref();
    CurrentZeta.setxPos(x-point.x());
    CurrentZeta.setyPos(y-point.y());
    return EnumDefs::SWARMSTANDBY;

}
void MotionController::robotMover(){
        if(attitude < goalangle-10){
            roboCurv = 90.0;
            roboSpeed = turn_speed;
        }
        else if(attitude > goalangle+10){
            roboCurv = -90.0;
            roboSpeed = turn_speed;
        }
        else{
            if((x > goalpoint.x()-0.5 && x <goalpoint.x()+0.5)&& (y > goalpoint.y()-0.5 && y <goalpoint.y()+0.5)){
                roboSpeed = 0;
                roboCurv = 0;
            }
            else{
                roboSpeed = max_speed;
                roboCurv = 0;
            }
        }
        QString moveData = "id="+ id +",Speed="+ QString::number(roboSpeed) + ",Curv=" + QString::number(roboCurv);
        Notify("Speed_Curv", moveData.toStdString(), MOOSTime());

}
