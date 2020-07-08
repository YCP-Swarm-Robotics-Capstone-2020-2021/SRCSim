#include "zeta.h"

Zeta::Zeta() :
    position(0.0),
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
    result.setPosition(z.getPosition()+this->position);
    result.setAttitude(z.getAttitude()+this->attitude);
    result.setLambda(z.getLambda()+this->lambda);
    result.setTheta(z.getTheta()+this->theta);
    return result;
}

Zeta Zeta::operator-(const Zeta& z)
{
    Zeta result;
    result.setPosition(this->position-z.getPosition());
    result.setAttitude(this->attitude-z.getAttitude());
    result.setLambda(this->lambda-z.getLambda());
    result.setTheta(this->theta-z.getTheta());
    return result;
}
Zeta Zeta::operator*(double& d)
{
    Zeta result;
    result.setPosition(this->position*d);
    result.setAttitude(this->attitude*d);
    result.setLambda(this->lambda*d);
    result.setTheta(this->theta*d);
    return result;
}

double Zeta::getPosition() const
{
    return position;
}

void Zeta::setPosition(double value)
{
    position = value;
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

QString Zeta::stringify()
{
    return "Position="+QString::number(position)+",Theta="+QString::number(theta)+", Lambda="+QString::number(lambda)+", Attitude="+QString::number(attitude);
}
