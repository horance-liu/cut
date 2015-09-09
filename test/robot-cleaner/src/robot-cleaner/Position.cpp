#include "robot-cleaner/Position.h"

Position::Position(int x, int y, const Orientation& orientation)
 : Point(x, y), Orientation(orientation)
{}

DEF_EQUALS(Position)
{
    return SUPER_EQ(Point) && SUPER_EQ(Orientation);
}
