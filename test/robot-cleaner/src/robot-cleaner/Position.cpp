#include <robot-cleaner/Position.h>

Position::Position(int x, int y, const Orientation& orientation)
 : Point(x, y), Orientation(orientation)
{}

bool Position::operator!=(const Position& rhs) const
{
    return !(*this == rhs);
}

bool Position::operator==(const Position& rhs) const
{
    return static_cast<const Point&>(*this) == rhs &&
           static_cast<const Orientation&>(*this) == rhs;
}
