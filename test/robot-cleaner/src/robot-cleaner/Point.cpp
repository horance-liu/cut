#include "robot-cleaner/Point.h"
#include "robot-cleaner/Orientation.h"

Point::Point(int x, int y)
  : x(x), y(y)
{}

Point Point::moveOn(int step, const Orientation& orientation) const
{
    return orientation.moveOn(x, y, step);
}

DEF_EQUALS(Point)
{
    return FIELD_EQ(x) && FIELD_EQ(y);
}
