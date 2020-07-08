#ifndef ZETA_H
#define ZETA_H
#include <QObject>
class Zeta
{
public:
    Zeta();
    ~Zeta();
    QString stringify();
    Zeta operator+(const Zeta& z);
    Zeta operator-(const Zeta& z);
    Zeta operator*(double& d);

    double getPosition() const;
    void setPosition(double value);

    double getAttitude() const;
    void setAttitude(double value);

    double getTheta() const;
    void setTheta(double value);

    double getLambda() const;
    void setLambda(double value);

private:
    double position, attitude, theta, lambda;
};

#endif // ZETA_H
