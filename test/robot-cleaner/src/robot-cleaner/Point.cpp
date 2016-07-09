#include <robot-cleaner/Point.h>
#include <robot-cleaner/Orientation.h>

Point::Point(int x, int y)
  : x(x), y(y)
{}

Point Point::moveOn(int step, const Orientation& orientation) const
{
    return orientation.moveOn(x, y, step);
}

bool Point::operator!=(const Point& rhs) const
{
    return !(*this == rhs);
}

bool Point::operator==(const Point& rhs) const
{
    return this->x == rhs.x && this->y == rhs.y;
}
