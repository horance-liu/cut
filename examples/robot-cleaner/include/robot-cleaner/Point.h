#ifndef H65A54D80_942C_4AB0_846B_A0568EA5200D
#define H65A54D80_942C_4AB0_846B_A0568EA5200D

#include "magellan/infra/std/EqHelper.h"

struct Orientation;

struct Point
{
    Point(int x, int y);

    Point moveOn(int step, const Orientation& orientation) const;

    DECL_EQUALS(Point);

private:
    int x, y;
};

#endif
