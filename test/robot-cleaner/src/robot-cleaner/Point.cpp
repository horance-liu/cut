#include <robot-cleaner/Point.h>
#include <robot-cleaner/Orientation.h>

Point::Point(int x, int y)
  : x(x), y(y)
{}

Point Point::moveOn(int step, const Orientation& orientation) const
{
    return orientation.moveOn(x, y, step);
}

__DEF_EQUALS(Point)
{
    return __FIELD_EQ(x) && __FIELD_EQ(y);
}
