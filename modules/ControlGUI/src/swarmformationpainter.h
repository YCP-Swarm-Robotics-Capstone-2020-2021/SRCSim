#ifndef SWARMFORMATIONPAINTER_H
#define SWARMFORMATIONPAINTER_H

#include <QWidget>
#include <QPainter>

class SwarmFormationPainter : public QWidget
{
    Q_OBJECT
public:
    explicit SwarmFormationPainter(QWidget *parent = nullptr);
    ~SwarmFormationPainter();

signals:

public slots:

protected:
    int heightForWidth(int w) const {return w;}
    virtual void paintEvent(QPaintEvent *event);
    void initializeGL();

private:
};

#endif // SWARMFORMATIONPAINTER_H
