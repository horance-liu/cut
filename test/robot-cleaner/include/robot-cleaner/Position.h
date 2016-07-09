#ifndef H722C49C6_D285_4885_88D1_97A11D669EE1
#define H722C49C6_D285_4885_88D1_97A11D669EE1

#include <robot-cleaner/Point.h>
#include <robot-cleaner/Orientation.h>

struct Position : Point, Orientation
{
    Position(int x, int y, const Orientation& orientation);

    bool operator!=(const Position& rhs) const;
    bool operator==(const Position& rhs) const;
};

#endif
