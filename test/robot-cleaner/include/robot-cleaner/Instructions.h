#ifndef HC37C3D94_43F1_4677_BD56_34CB78EFEC75
#define HC37C3D94_43F1_4677_BD56_34CB78EFEC75

#include <cui/dci/__Role__.h>
#include <vector>

struct Point;
struct Orientation;

__TRAIT__(Instruction)
{
    __ABSTRACT__(void exec(Point& point, Orientation& orientation) const);
};

Instruction* left();
Instruction* right();

Instruction* forward_n(int n);
Instruction* backward_n(int n);
Instruction* repeat(Instruction*, int n);

inline Instruction* forward()
{ return forward_n(1);  }

inline Instruction* backward()
{ return backward_n(1); }

inline Instruction* round()
{ return repeat(right(), 2); }

Instruction* __sequential(std::vector<Instruction*>&&);

#define sequential(...) __sequential({ __VA_ARGS__ })

#endif
