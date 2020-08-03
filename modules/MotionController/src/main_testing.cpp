/************************************************************/
/*    NAME: Kyle Leatherman                                              */
/*    ORGN: YCP                                             */
/*    FILE: main_testing.cpp                                        */
/*    DATE: 07/29/2020                                         */
/************************************************************/

#include "zeta.h"
#include <QPoint>
#include <math.h>

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
    Zeta narwhal = Zeta();
    Zeta object2 = Zeta();
    Zeta object3;
    double dt = 1.0;
    double kappa = 1.0;
    int linknum=2;
    double xOff = 0;
    double yOff = 0;


   for(int i = 0; i<4; i++){
        narwhal.addtoTheta(-90);
        narwhal.addtoLambda(4);
    }
    narwhal.setAttitude(0);
    narwhal.setxPos(-2);
    narwhal.setyPos(-2);

    for(int i = 0; i<3; i++){
         object2.addtoTheta(0);
         object2.addtoLambda(0);
     }
     object2.setAttitude(0);
     object2.setxPos(0);
     object2.setyPos(0);

    while(false){
        Zeta object1 = Zeta();
        object1 = object1 - (object2-narwhal)*kappa;
        double numNeighbors = 1.0;
        object1 = object1*numNeighbors;

        object2 = object2 + object1*dt;
    }

    QPoint point = QPoint(xOff*narwhal.getLambda(linknum), yOff*narwhal.getLambda(linknum));
    for( int i = linknum-1; i>=0; i--){
        double x = point.x();
        double y = point.y();
        double sine = sin(-narwhal.getTheta(i)*3.14159265/180.0);
        double cose = cos(-narwhal.getTheta(i)*3.14159265/180.0);
        point.setX(x*cose - y*sine);
        point.setY(x*sine+ y*cose);
        x = point.x();
        point.setX(x+ narwhal.getLambda(i));
    }
    point.setX(point.x()+narwhal.getxPos());
    point.setY(point.y()+narwhal.getyPos());
     /*object3.setxPos(object1.getxPos()-object2.getxPos());
     object3.setyPos(object1.getyPos()-object2.getyPos());
     object3.setAttitude(object1.getAttitude()-object2.getAttitude());
     object3.setWholeLambda(subtractList2(object1.getWholeLambda(), object2.getWholeLambda()));
     object3.setWholeTheta(subtractList2(object1.getWholeTheta(),object2.getWholeTheta()));

     object3.setxPos(object1.getxPos()+object2.getxPos());
     object3.setyPos(object1.getyPos()+object2.getyPos());
     object3.setAttitude(object1.getAttitude()+object2.getAttitude());
     object3.setWholeLambda(addList2(object1.getWholeLambda(), object2.getWholeLambda()));
     object3.setWholeTheta(addList2(object1.getWholeTheta(),object2.getWholeTheta()));*/
return 0;
}


