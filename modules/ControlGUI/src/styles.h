#ifndef STYLES_H
#define STYLES_H
#include <string>
#include <QKeyEvent>

#ifndef PI
#define PI 3.141592653589
#endif

const int TEXT_FONT_SIZE = 20;
const std::string WARNING_FONT_COLOR = "firebrick";
const std::string CAUTION_FONT_COLOR = "orange";
const std::string ADVISORY_FONT_COLOR = "blue";
const std::string NORMAL_FONT_COLOR = "darkgreen";

//Swarm Page Defines
const int SWARM_DISPLAY_FONTSIZE = 2;
const int ARENA_WIDTH_HEIGHT_IN_FEET = 6;
const double ROBOT_HEIGHT_IN_FEET = .5;
const double ROBOT_WIDTH_IN_FEET = 0.25;

//Teleop Keyboard Keys
const Qt::Key forwardKey = Qt::Key_W;
const Qt::Key leftKey = Qt::Key_A;
const Qt::Key reverseKey = Qt::Key_S;
const Qt::Key rightKey = Qt::Key_D;

#endif // STYLES_H
