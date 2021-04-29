#include <QStyleOption>
#include "swarmformationpainter.h"
#include <math.h>
#include <iostream>


SwarmFormationPainter::SwarmFormationPainter(QWidget *parent) : QWidget (parent)
{
    this->setStyleSheet("border: 1px solid black;");
}

SwarmFormationPainter::~SwarmFormationPainter()
{

}

void SwarmFormationPainter::paintEvent(QPaintEvent *event)
{
    QStyleOption opt;
    if(this->width() < this->height())
        this->resize(this->width(), this->width());
    else
        this->resize(this->height(), this->height());

    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);

    QPainter painter(this);
    painter.setBrush(Qt::DiagCrossPattern);


    QPen pen;

    pen.setColor(Qt::green);
    pen.setWidth(5);

    painter.setPen(pen);
    setupZeta();
    drawGrid();
    drawBots();
}

void SwarmFormationPainter::drawGrid()
{
    QPainter painter(this);
    QPen originPen, pen;
    pen.setWidth(1);
    pen.setColor(Qt::gray);
    pen.setStyle(Qt::DashLine);

    originPen.setWidth(1);
    originPen.setColor(Qt::black);
    originPen.setStyle(Qt::SolidLine);
    painter.setPen(pen);

    painter.setPen(pen);
    for(int i = 1; i<=numFeetInArenaView; i++){
        painter.drawLine(0,(this->height()/numFeetInArenaView)*i, this->width(),(this->height()/numFeetInArenaView)*i );
        painter.drawLine((this->width()/numFeetInArenaView)*i, 0, (this->width()/numFeetInArenaView)*i,this->height());
    }
    painter.setPen(originPen);
    painter.drawLine(0, (this->height()/2), this->width(), (this->height()/2));
    painter.drawLine((this->width()/2), 0, (this->width()/2), this->height());
}

void SwarmFormationPainter::drawBots()
{
    //1/6 of width = 1 foot
    //Robots are approx 3/4 ft x 1/2 ft
    int roboWidth = int((this->width()/numFeetInArenaView)*ROBOT_WIDTH_IN_FEET);
    int roboHeight = int((this->width()/numFeetInArenaView)*ROBOT_HEIGHT_IN_FEET);

    QPainter painter(this);
    QPen roboPen, textPen, linePen;
    painter.setBrush(Qt::SolidPattern);
    roboPen.setWidth(2);
    roboPen.setColor(Qt::green);

    textPen.setWidth(SWARM_DISPLAY_FONTSIZE);
    textPen.setColor(Qt::black);

    linePen.setWidth(2);
    linePen.setColor(Qt::green);

    painter.setPen(textPen);
    QFontMetrics fm(painter.font());

    int numLinkagesInFormation = currentZeta[Zetaoption].zeta.getWholeTheta().size();
    std::cout<<"Zetaoption is "<< Zetaoption<<std::endl;
    int linkageBotCounts[numLinkagesInFormation];
    int linkageOffsetCounts[numLinkagesInFormation];
    for(int i = 0; i<numLinkagesInFormation; i++){
        linkageBotCounts[i] = 0;
        linkageOffsetCounts[i] = 0;
    }

    //Setup Linkage assignments.
    auto iter = m_dolphinList.begin();
    for(int i = 0; i<m_dolphinList.size(); i++, iter++){
        setupMap[*iter].second = i%numLinkagesInFormation; //linkage Assignment
        linkageBotCounts[i%numLinkagesInFormation]++;
        linkageOffsetCounts[i%numLinkagesInFormation]++;
    }

    iter = m_dolphinList.begin();
    while(iter != m_dolphinList.end()){
        int link = setupMap[*iter].second;
        setupMap[*iter].first.first = (1.0-(linkageOffsetCounts[link]/(double)linkageBotCounts[link]));
        setupMap[*iter].first.second = 0.0;
        linkageOffsetCounts[link]--;
        iter++;
    }

    iter = m_dolphinList.begin();
    while(iter != m_dolphinList.end()){
        QPointF point = QPointF((setupMap[*iter].first.first*currentZeta[Zetaoption].zeta.getLambda(setupMap[*iter].second)), (setupMap[*iter].first.second*currentZeta[Zetaoption].zeta.getLambda(setupMap[*iter].second)));
        for(int i = setupMap[*iter].second-1; i>=0; i--){
            double x = point.x();
            double y = point.y();
            point.setX((x*cos(currentZeta[Zetaoption].zeta.getTheta(i)*PI/180.0) - y*sin(currentZeta[Zetaoption].zeta.getTheta(i)*PI/180.0)));
            point.setY((x*sin(currentZeta[Zetaoption].zeta.getTheta(i)*PI/180.0) + y*cos(currentZeta[Zetaoption].zeta.getTheta(i)*PI/180.0)));
            point.setX(point.x() + currentZeta[Zetaoption].zeta.getLambda(i));
        }
        setupMap[*iter].first.first = ((point.x()*(this->width()/numFeetInArenaView)*cos(currentZeta[Zetaoption].zeta.getAttitude())-point.y()*(this->width()/numFeetInArenaView)*sin(currentZeta[Zetaoption].zeta.getAttitude()))+currentZeta[Zetaoption].zeta.getxPos());
        setupMap[*iter].first.second = ((point.x()*(this->height()/numFeetInArenaView)*sin(currentZeta[Zetaoption].zeta.getAttitude())+point.y()*(this->height()/numFeetInArenaView)*cos(currentZeta[Zetaoption].zeta.getAttitude()))+currentZeta[Zetaoption].zeta.getyPos());
        iter++;
    }

    painter.setPen(linePen);
    QPoint linePoint(currentZeta[Zetaoption].zeta.getxPos(), currentZeta[Zetaoption].zeta.getyPos());
    QPoint nextPoint(linePoint.x()+(currentZeta[Zetaoption].zeta.getLambda(0)*(this->width()/numFeetInArenaView)*cos(currentZeta[Zetaoption].zeta.getAttitude())),
                     linePoint.y()+(currentZeta[Zetaoption].zeta.getLambda(0)*(this->height()/numFeetInArenaView)*sin(currentZeta[Zetaoption].zeta.getAttitude())));
    int angle = currentZeta[Zetaoption].zeta.getAttitude()*180.0/PI;
    for(int i = 1; i<=numLinkagesInFormation; i++){
        painter.drawLine(linePoint.x(), linePoint.y(), nextPoint.x(), nextPoint.y());
        linePoint.setX(nextPoint.x());
        linePoint.setY(nextPoint.y());
        angle += (currentZeta[Zetaoption].zeta.getTheta(i-1));
        nextPoint.setX(linePoint.x()+(currentZeta[Zetaoption].zeta.getLambda(i)*(this->width()/numFeetInArenaView)*cos(angle*PI/180.0)));
        nextPoint.setY(linePoint.y()+(currentZeta[Zetaoption].zeta.getLambda(i)*(this->height()/numFeetInArenaView)*sin(angle*PI/180.0)));
    }

    iter = m_dolphinList.begin();
    while(iter != m_dolphinList.end()){
        painter.setPen(roboPen);
        painter.drawRect(setupMap[*iter].first.first-roboWidth/2, setupMap[*iter].first.second-roboHeight/2, roboWidth, roboHeight);
        painter.setPen(textPen);
        painter.drawText(int(setupMap[*iter].first.first-(fm.width(*iter))/2), int(setupMap[*iter].first.second-roboHeight/2-fm.height()/2), *iter);
        iter++;
    }

}

void SwarmFormationPainter::setupZeta(int index)
{
    if(index < 0){
        index = Zetaoption;
    }
    QPair<double, double> formationXY = {this->width()/2, this->height()/2};
    double length = sqrt(currentZeta[index].width*currentZeta[index].width+currentZeta[index].length*currentZeta[index].length);
    Zeta newShape;
    switch(currentZeta[index].shape){
        case Shape::SQUARE:
            newShape.setxPos(formationXY.first-((currentZeta[index].xoffset+(double(currentZeta[index].width)/2.0))*this->width()/numFeetInArenaView));
            newShape.setyPos(formationXY.second+((currentZeta[index].yoffset+(double(currentZeta[index].length)/2.0))*this->height()/numFeetInArenaView));
            newShape.setAttitude(double(currentZeta[index].rotation)*PI/180);
            newShape.setWholeTheta({-90, -90, -90, -90});
            newShape.setWholeLambda(QList<double>{double(currentZeta[index].width),
                                                     double(currentZeta[index].length),
                                                     double(currentZeta[index].width),
                                                     double(currentZeta[index].length)});
            break;
        case Shape::TRIANGLE:
            newShape.setxPos(formationXY.first-((currentZeta[index].xoffset+(double(length)/2.0))*this->width()/numFeetInArenaView));
            newShape.setyPos(formationXY.second+(currentZeta[index].yoffset+((double(length)/2.0))*this->height()/numFeetInArenaView));
            newShape.setAttitude(double(currentZeta[index].rotation)*PI/180);
            newShape.setWholeTheta({-120, -120, -120});
            newShape.setWholeLambda(QList<double>{double(length),
                                                     double(length),
                                                     double(length)});
            break;
        case Shape::LINE:
            newShape.setxPos(formationXY.first-((currentZeta[index].xoffset+(double(currentZeta[index].length)/2.0))*this->width()/numFeetInArenaView));
            newShape.setyPos(formationXY.second+((currentZeta[index].yoffset))*this->height()/numFeetInArenaView);
            newShape.setAttitude(double(currentZeta[index].rotation)*PI/180);
            newShape.setWholeTheta({-90});
            newShape.setWholeLambda(QList<double>{double(currentZeta[index].length)});
                break;
        case Shape::PENTAGON:
            newShape.setxPos(formationXY.first-((currentZeta[index].xoffset+(double(length)/2.0))*this->width()/numFeetInArenaView));
            newShape.setyPos(formationXY.second+((currentZeta[index].yoffset+(double(length)/2.0))*this->height()/numFeetInArenaView));
            newShape.setAttitude(double(currentZeta[index].rotation)*PI/180);
            newShape.setWholeTheta({-72, -72, -72, -72, -72});
            newShape.setWholeLambda(QList<double>{double(length),
                                                     double(length),
                                                     double(length),
                                                     double(length),
                                                     double(length)});
            break;
        case Shape::PARALLELOGRAM:
            newShape.setxPos(formationXY.first-((currentZeta[index].xoffset+(double(currentZeta[index].width)/2.0))*this->width()/numFeetInArenaView));
            newShape.setyPos(formationXY.second+((currentZeta[index].yoffset+(double(currentZeta[index].length)/2.0))*this->height()/numFeetInArenaView));
            newShape.setAttitude(double(currentZeta[index].rotation)*PI/180);
            newShape.setWholeTheta({-60, -120, -60, -120});
            newShape.setWholeLambda(QList<double>{double(currentZeta[index].width),
                                                     double(currentZeta[index].length),
                                                     double(currentZeta[index].width),
                                                     double(currentZeta[index].length)});
            break;
        default:
            break;
    }
    currentZeta[index].zeta = newShape;

}
void SwarmFormationPainter::initZeta(int i)
{
    ZetaState toadd;
    for(int j =0; j<i; j++){
        currentZeta.insert(j, toadd);
    }

}
