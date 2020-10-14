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

    double getxPos() const;
    void setxPos(double value);

    double getAttitude() const;
    void setAttitude(double value);

    double getTheta(int x) const;
    void setTheta(int i, double value);

    QList<double> getWholeTheta() const;
    void setWholeTheta(QList<double> ntheta);

    double getLambda(int x) const;
    void setLambda(int i, double value);

    QList<double> getWholeLambda() const;
    void setWholeLambda(QList<double> nlambda);

    double getyPos() const;
    void setyPos(double value);

    void addtoTheta(double d);

    void addtoLambda(double d);

    void scale(double d);

    QList<double> addList(QList<double> lista, QList<double> listb);

    QList<double> subtractList(QList<double> lista, QList<double> listb);

    QList<double> multiplyList(QList<double> lista, double d);



private:
    double xPos, yPos, attitude;
    QList<double> theta, lambda;
};

#endif // ZETA_H
