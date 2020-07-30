/************************************************************/
/*    NAME: Kyle Leatherman                                              */
/*    ORGN: YCP                                             */
/*    FILE: main_testing.cpp                                        */
/*    DATE: 07/29/2020                                         */
/************************************************************/

#include "zeta.h"

using namespace std;

QList<double> subtractList2(QList<double> lista, QList<double> listb){
    QList<double> toReturn = {};
    for(int i = 0; i< lista.size() || i< listb.size(); i++){
        if(i >= lista.size()){
            toReturn.append( -listb[i]);
        }
        else if(i >= listb.size()){
           toReturn.append(lista[i]);
        }
        else{
            toReturn.append( lista[i] - listb[i]);
        }
    }
    return toReturn;

}
QList<double> addList2(QList<double> lista, QList<double> listb){
    QList<double> toReturn = {};
    for(int i = 0; i< lista.size() || i< listb.size(); i++){
        if(i >= lista.size()){
            toReturn.append( listb[i]);
        }
        else if(i >= listb.size()){
            toReturn.append(  lista[i]);
        }
        else{
            toReturn.append( lista[i] + listb[i]);
        }
    }
    return toReturn;

}

int mainTest()
{
    Zeta object1 = Zeta();
    Zeta object2 = Zeta();
    Zeta object3;


   for(int i = 0; i<3; i++){
        object1.addtoTheta(3);
        object1.addtoLambda(3);
    }
    object1.setAttitude(3);
    object1.setxPos(3);
    object1.setyPos(3);

    for(int i = 0; i<3; i++){
         object2.addtoTheta(2);
         object2.addtoLambda(2);
     }
     object2.setAttitude(2);
     object2.setxPos(2);
     object2.setyPos(2);

     object3.setxPos(object1.getxPos()-object2.getxPos());
     object3.setyPos(object1.getyPos()-object2.getyPos());
     object3.setAttitude(object1.getAttitude()-object2.getAttitude());
     object3.setWholeLambda(subtractList2(object1.getWholeLambda(), object2.getWholeLambda()));
     object3.setWholeTheta(subtractList2(object1.getWholeTheta(),object2.getWholeTheta()));

     object3.setxPos(object1.getxPos()+object2.getxPos());
     object3.setyPos(object1.getyPos()+object2.getyPos());
     object3.setAttitude(object1.getAttitude()+object2.getAttitude());
     object3.setWholeLambda(addList2(object1.getWholeLambda(), object2.getWholeLambda()));
     object3.setWholeTheta(addList2(object1.getWholeTheta(),object2.getWholeTheta()));

return 0;
}


