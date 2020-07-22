#include "zeta.h"

Zeta::Zeta() :
    xPos(0.0),
    yPos(0.0),
    attitude(0.0)
{
    theta = {};
    lambda ={};

}

Zeta::~Zeta()
{

}

Zeta Zeta::operator+(const Zeta& z)
{
    Zeta result;
    result.setxPos(z.getxPos()+this->xPos);
    result.setyPos(z.getyPos()+this->yPos);
    result.setAttitude(z.getAttitude()+this->attitude);
    result.setWholeLambda(z.getWholeLambda()+this->lambda);
    result.setWholeTheta(z.getWholeTheta()+this->theta);
    return result;
}

Zeta Zeta::operator-(const Zeta& z)
{
    Zeta result;
    result.setxPos(this->xPos-z.getxPos());
    result.setyPos(this->yPos-z.getyPos());
    result.setAttitude(this->attitude-z.getAttitude());
    result.setWholeLambda(subtractList(this->lambda, z.getWholeLambda()));
    result.setWholeTheta(subtractList(this->theta,z.getWholeTheta()));
    return result;
}
Zeta Zeta::operator*(double& d)
{
    Zeta result;
    result.setxPos(this->xPos*d);
    result.setyPos(this->yPos*d);
    result.setAttitude(this->attitude*d);
    result.setWholeLambda(multiplyList(this->lambda, d));
    result.setWholeTheta(multiplyList(this->theta, d));
    return result;
}

double Zeta::getxPos() const
{
    return xPos;
}

void Zeta::setxPos(double value)
{
    xPos = value;
}

double Zeta::getAttitude() const
{
    return attitude;
}

void Zeta::setAttitude(double value)
{
    attitude = value;
}

double Zeta::getTheta(int i) const
{
   if(i < theta.size()){
        return theta[i];
   }
   return 361;
}

void Zeta::setTheta(int i, double value)
{
    if(i < theta.size()){
        theta[i] = value;
    }
}

QList<double> Zeta::getWholeTheta() const
{
    return theta;
}

void Zeta::setWholeTheta(QList<double> ntheta)
{
    theta = ntheta;
}

double Zeta::getLambda(int i) const
{
    if(i < lambda.size()){
        return lambda[i];
    }
    return -1;

}

void Zeta::setLambda(int i, double value)
{
    if(i < lambda.size()){
    lambda[i] = value;
    }
}

QList<double> Zeta::getWholeLambda() const
{
    return lambda;
}

void Zeta::setWholeLambda(QList<double> nlambda)
{
    lambda = nlambda;
}

double Zeta::getyPos() const
{
    return yPos;
}

void Zeta::setyPos(double value)
{
    yPos = value;
}

void Zeta::addtoTheta(double d){
    theta.append(d);
}

void Zeta::addtoLambda(double d){
    lambda.append(d);
}

void Zeta::scale(double d){
    for(int  i = 0; i< lambda.size(); i++){
        lambda[i] *= d;
    }
}

QList<double> Zeta::subtractList(QList<double> lista, QList<double> listb){
    QList<double> toReturn = {};
    for(int i = 0; i< lista.size() || i< listb.size(); i++){
        if(i >= lista.size()){
            toReturn[i] = -listb[i];
        }
        else if(i >= listb.size()){
            toReturn[i] = lista[i];
        }
        toReturn[i] = lista[i] - listb[i];
    }
    return toReturn;

}

QList<double> Zeta::multiplyList(QList<double> lista, double d){
    for(int  i = 0; i< lista.size(); i++){
        lista[i] *= d;
    }
    return lista;
}

QString Zeta::stringify()
{
    QString slambda = "(";
    QString stheta = "(";
    for(int i = 0; i<lambda.size(); i++){
        slambda += QString::number(lambda[i]) + "| ";
    }
    slambda = ")";

    for(int i = 0; i<theta.size(); i++){
        stheta += QString::number(theta[i]) + "| ";
    }
    stheta = ")";

    return "xPos="+QString::number(xPos)+", yPos="+QString::number(yPos)+",Theta="+stheta+", Lambda="+slambda+", Attitude="+QString::number(attitude);
}
