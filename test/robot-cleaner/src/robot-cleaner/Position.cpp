#include <robot-cleaner/Position.h>

Position::Position(int x, int y, const Orientation& orientation)
 : Point(x, y), Orientation(orientation)
{}

__DEF_EQUALS(Position)
{
    return __SUPER_EQ(Point) && __SUPER_EQ(Orientation);
}
