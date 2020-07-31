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


double pointtoTraj2(QPoint point, double x, double y){
    double attitude = 270;
    double xdiff = point.x()- x;
    double ydiff = point.y()- y;
    double phi;
    if (ydiff == 0 && xdiff == 0){
        return 0;
    }
    else if(xdiff >=0 && ydiff >= 0){
         phi = atan(xdiff/ydiff)*180/3.14159;
    }
    else if(xdiff <=0 && ydiff >= 0){
         phi = atan(ydiff/xdiff)*180/3.14159+90;
    }
    else if(xdiff <=0 && ydiff <= 0){
         phi = atan(xdiff/ydiff)*180/3.14159+180;
    }
    else{
         phi = atan(ydiff/xdiff)*180/3.14159+270;
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

     QPoint point;
     point.setX(0);
     point.setY(0);
     pointtoTraj2(point, 0, 0);
return 0;
}


