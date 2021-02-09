#ifndef GLOBAL_H
#define GLOBAL_H

#endif // GLOBAL_H

#include <QMutex>
#include <QSemaphore>
#include "Stage-4.3/stage.hh"

class Robot {
public:
  Stg::ModelPosition *position;
  double xPos;
  double yPos;
  double attitude;
  double forward_speed;
  double side_speed;
  double turn_speed;
  double current_speed;
  bool line_detected = false;
};

extern QList<Robot> RobotList;

