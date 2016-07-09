#include <robot-cleaner/Orientation.h>
#include <robot-cleaner/Point.h>

namespace
{
    const Orientation* orientations[4] = { nullptr };

    inline int numOfTurnTo(bool left)
    {
        return left ? 3 : 1;
    }
}

const Orientation& Orientation::turnTo(bool left) const
{
    return *orientations[(order + numOfTurnTo(left)) % 4];
}

inline int Orientation::diff(int order) const
{
    return orientations[order]->offset;
}

inline int Orientation::xOffset() const
{
    return diff(order);
}

inline int Orientation::yOffset() const
{
    return diff(3-order);
}

Point Orientation::moveOn(int x, int y, int step) const
{
    return Point(x+step*xOffset(), y+step*yOffset());
}

inline Orientation::Orientation(int order, int offset)
  : order(order), offset(offset)
{
    orientations[order] = this;
}

#define DEF_ORIENTATION(orientation, order, offset) \
const Orientation Orientation::orientation(order, offset);

DEF_ORIENTATION(east,  0, 1)
DEF_ORIENTATION(south, 1, 0)
DEF_ORIENTATION(west,  2, -1)
DEF_ORIENTATION(north, 3, 0)

bool Orientation::operator!=(const Orientation& rhs) const
{
    return !(*this == rhs);
}

bool Orientation::operator==(const Orientation& rhs) const
{
    return order == rhs.order && offset == rhs.offset;
}
