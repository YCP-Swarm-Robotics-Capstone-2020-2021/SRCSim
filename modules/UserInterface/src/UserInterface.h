/************************************************************/
/*    NAME: Kyle                                              */
/*    ORGN: YCP                                             */
/*    FILE: UserInterface.h                                          */
/*    DATE: 06/22/2020                                         */
/************************************************************/

#ifndef UserInterface_HEADER
#define UserInterface_HEADER

#include <QObject>
#include <iterator>
#include <MOOS/libMOOS/MOOSLib.h>
#include "MOOS/libMOOS/Thirdparty/AppCasting/AppCastingMOOSApp.h"
#include <ivp/MBUtils.h>
#include <ivp/ACTable.h>
#include <QString>
#include <QThread>
#include <VehicleStateDefines.h>


class UserInterface : public QThread, public AppCastingMOOSApp
{
    Q_OBJECT
public:
  UserInterface();
  ~UserInterface();

  void startProcess(const std::string & , const std::string &, int argc, char * argv[]);


 protected: // Standard MOOSApp functions to overload
   bool OnNewMail(MOOSMSG_LIST &NewMail);
   bool Iterate();
   bool OnConnectToServer();
   bool OnStartUp();

 protected: // Standard AppCastingMOOSApp function to overload
   bool buildReport();

 protected:
   void registerVariables();
   void run();

 private: // Configuration variables
   std::string m_moosAppName,m_moosMissionFile;
   EnumDefs::VehicleStates State;
   int robotId = 0;
   int maxBots = 0;

signals:
   void informMaxBots(int maxBots);

public slots:
   void updateState(int state){State = (EnumDefs::VehicleStates)state;}
   void updateBot(int id){robotId = id;}
   void sendMessage(){
       if(robotId == maxBots || State == EnumDefs::VehicleStates::SWARMMODE){
           QString stateData ="State="+ QString::number(State);
           Notify("Change_State", stateData.toStdString(), MOOSTime());
       }
       else{
           QString stateData = "id=Dolphin"+ QString::number(robotId) + ",State="+ QString::number(State);
           QString mesName = "Dolphin"+ QString::number(robotId)+"_Change_State";
           Notify(mesName.toStdString(), stateData.toStdString(), MOOSTime());
       }

   }
};

#endif 
