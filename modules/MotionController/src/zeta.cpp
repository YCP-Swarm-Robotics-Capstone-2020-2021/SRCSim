#include "zeta.h"

Zeta::Zeta() :
    xPos(0.0),
    yPos(0.0),
    attitude(0.0),
    theta(0.0),
    lambda(0.0)
{

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
    result.setLambda(z.getLambda()+this->lambda);
    result.setTheta(z.getTheta()+this->theta);
    return result;
}

Zeta Zeta::operator-(const Zeta& z)
{
    Zeta result;
    result.setxPos(this->xPos-z.getxPos());
    result.setyPos(this->yPos-z.getyPos());
    result.setAttitude(this->attitude-z.getAttitude());
    result.setLambda(this->lambda-z.getLambda());
    result.setTheta(this->theta-z.getTheta());
    return result;
}
Zeta Zeta::operator*(double& d)
{
    Zeta result;
    result.setxPos(this->xPos*d);
    result.setyPos(this->yPos*d);
    result.setAttitude(this->attitude*d);
    result.setLambda(this->lambda*d);
    result.setTheta(this->theta*d);
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

double Zeta::getTheta() const
{
    return theta;
}

void Zeta::setTheta(double value)
{
    theta = value;
}

double Zeta::getLambda() const
{
    return lambda;
}

void Zeta::setLambda(double value)
{
    lambda = value;
}

double Zeta::getyPos() const
{
    return yPos;
}

void Zeta::setyPos(double value)
{
    yPos = value;
}

QString Zeta::stringify()
{
    return "xPos="+QString::number(xPos)+", yPos="+QString::number(yPos)+",Theta="+QString::number(theta)+", Lambda="+QString::number(lambda)+", Attitude="+QString::number(attitude);
}
