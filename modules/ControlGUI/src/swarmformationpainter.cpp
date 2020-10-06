#include <QStyleOption>
#include "swarmformationpainter.h"


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
    if(this->width()<this->height())
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
    painter.drawRect(QRect((this->size().width()/2)-100,(this->size().height()/2)-50,200,100));
}
