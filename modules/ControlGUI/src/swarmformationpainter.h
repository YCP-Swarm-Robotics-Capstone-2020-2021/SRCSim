#ifndef SWARMFORMATIONPAINTER_H
#define SWARMFORMATIONPAINTER_H

#include <QWidget>
#include <QPainter>
#include <algorithm>
#include <QDebug>
#include "zeta.h"
#include "styles.h"

class SwarmFormationPainter : public QWidget
{
    Q_OBJECT
public:
    explicit SwarmFormationPainter(QWidget *parent = nullptr);
    ~SwarmFormationPainter();

    enum Shape {
        SQUARE = 0,
        TRIANGLE,
        CIRCLE,
        PENTAGON,
        PARALLELOGRAM,
        SHAPEENUMEND
    };

    const QString getShapeSring(SwarmFormationPainter::Shape shape){
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

    void setCurrentShape(int i){currentShape = Shape(i); update();}
    void setCurrentWidth(int i){currentWidth = i; update();}
    void setCurrentLength(int i){currentLength = i; update();}
    void setCurrentRotation(int i){currentRotation = i; update();}
    void setFeetArenaView(int i){numFeetInArenaView = i; update();}
    void submitZetaPressed(double x=0, double y=0){
        xOffset += x;
        yOffset += y;
        setupZeta();
        currentZeta.setxPos(currentZeta.getxPos()+x);
        currentZeta.setyPos(currentZeta.getyPos()+y);
        currentZeta.setxPos((currentZeta.getxPos()-this->width()/2.0)*(double(numFeetInArenaView)/double(this->width())));
        currentZeta.setyPos((currentZeta.getyPos()-this->width()/2.0)*-(double(numFeetInArenaView)/double(this->height())));
        currentZeta.setAttitude(-currentRotation);
        emit emitZeta(currentZeta.stringify());
    }
public:
    Zeta currentZeta;
protected:
    virtual void paintEvent(QPaintEvent *event);
    void drawGrid();
    void drawBots();
    void initializeGL();

private:
    void setupZeta();

    const QList<std::string> shapeArray = {"SQUARE", "TRIANGLE", "CIRCLE", "PENTAGON", "PARALLELOGRAM"};
    QList<QString> m_dolphinList;
    QMap<QString, QPair<QPair<double, double>,int>> setupMap;
    Shape currentShape = Shape::SQUARE;
    int currentWidth = 1;
    int currentLength = 1;
    int currentRotation = 0;
    int numFeetInArenaView = ARENA_WIDTH_HEIGHT_IN_FEET;
    double xOffset = 0.0;
    double yOffset = 0.0;
};

#endif // SWARMFORMATIONPAINTER_H
