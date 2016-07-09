#ifndef H9811B75A_15B3_4DF0_91B7_483C42F74473
#define H9811B75A_15B3_4DF0_91B7_483C42F74473

struct Point;

struct Orientation
{
    const Orientation& turnTo(bool left) const;
    Point moveOn(int x, int y, int step) const;

#define DECL_ORIENTATION(orientation) \
    static const Orientation orientation;

    DECL_ORIENTATION(east)
    DECL_ORIENTATION(south)
    DECL_ORIENTATION(west)
    DECL_ORIENTATION(north)

    bool operator!=(const Orientation& rhs) const;
    bool operator==(const Orientation& rhs) const;

private:
    Orientation(int order, int offset);

    int diff(int order) const;
    int xOffset() const;
    int yOffset() const;

private:
    int order;
    int offset;
};

#define EAST  Orientation::east
#define SOUTH Orientation::south
#define WEST  Orientation::west
#define NORTH Orientation::north

#endif
