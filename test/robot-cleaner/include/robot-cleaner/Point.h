#ifndef H65A54D80_942C_4AB0_846B_A0568EA5200D
#define H65A54D80_942C_4AB0_846B_A0568EA5200D

struct Orientation;

struct Point
{
    Point(int x, int y);

    Point moveOn(int step, const Orientation& orientation) const;

    bool operator!=(const Point& rhs) const;
    bool operator==(const Point& rhs) const;

private:
    int x, y;
};

#endif
