#ifndef SWARMFORMATIONPAINTER_H
#define SWARMFORMATIONPAINTER_H

#include <QWidget>
#include <QPainter>
#include <algorithm>
#include <QDebug>
#include "zeta.h"
#include "styles.h"
enum Shape {
    SQUARE = 0,
    TRIANGLE,
    LINE,
    PENTAGON,
    PARALLELOGRAM,
    SHAPEENUMEND
};
class ZetaState{
public:
    Zeta zeta;
    Shape shape = SQUARE;
    int width = 1;
    int length = 1;
    double xoffset = 0;
    double yoffset = 0;
    int rotation = 0;


};


class SwarmFormationPainter : public QWidget
{
    Q_OBJECT
public:
    explicit SwarmFormationPainter(QWidget *parent = nullptr);
    ~SwarmFormationPainter();

    const QString getShapeSring(Shape shape){
        if(shape < SHAPEENUMEND){
            return QString::fromStdString(shapeArray[shape]);
        } else {
            return "";
        }
    }
signals:
    void emitZeta(QString);
public slots:
    void setDolphinList(QList<QString> list)
    {
        qDebug()<<"painting";
        m_dolphinList = list;
        std::sort(m_dolphinList.begin(), m_dolphinList.end());
        update();
        qDebug()<<" done painting";
    }

    void initZeta(int i);
    void setCurrentShape(int i){currentZeta[Zetaoption].shape = Shape(i); update();}
    void setCurrentWidth(int i){currentZeta[Zetaoption].width = i; update();}
    void setCurrentLength(int i){currentZeta[Zetaoption].length = i; update();}
    void setCurrentRotation(int i){currentZeta[Zetaoption].rotation = i; update();}
    void setFeetArenaView(int i){numFeetInArenaView = i; update();}
    void setXOffset(int i){currentZeta[Zetaoption].xoffset = i/12.0; update();}
    void setYOffset(int i){currentZeta[Zetaoption].yoffset = i/12.0; update();}
    void setZetaOption(QString s){Zetaoption =  s.right(1).toInt(); update();}
    void submitZetaPressed(double x=0, double y=0){
        setupZeta();
        currentZeta[Zetaoption].zeta.setxPos(currentZeta[Zetaoption].zeta.getxPos()+x);
        currentZeta[Zetaoption].zeta.setyPos(currentZeta[Zetaoption].zeta.getyPos()+y);
        currentZeta[Zetaoption].zeta.setxPos((currentZeta[Zetaoption].zeta.getxPos()-this->width()/2.0)*(double(numFeetInArenaView)/double(this->width())));
        currentZeta[Zetaoption].zeta.setyPos((currentZeta[Zetaoption].zeta.getyPos()-this->width()/2.0)*-(double(numFeetInArenaView)/double(this->height())));
        currentZeta[Zetaoption].zeta.setAttitude(-currentZeta[Zetaoption].rotation);
        QString shape = ",shape="+QString::fromStdString(shapeArray[currentZeta[Zetaoption].shape]);
        emit emitZeta(currentZeta[Zetaoption].zeta.stringify()+shape);
    }
public:
    QMap<int, ZetaState> currentZeta;

protected:
    virtual void paintEvent(QPaintEvent *event);
    void drawGrid();
    void drawBots();
    void initializeGL();

private:
    void setupZeta();

    const QList<std::string> shapeArray = {"SQUARE", "TRIANGLE", "LINE", "PENTAGON", "PARALLELOGRAM"};
    QList<QString> m_dolphinList;
    QMap<QString, QPair<QPair<double, double>,int>> setupMap;
    int Zetaoption = 0;
    int numFeetInArenaView = ARENA_WIDTH_HEIGHT_IN_FEET;
};

#endif // SWARMFORMATIONPAINTER_H
