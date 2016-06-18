#ifndef HE781FE8C_8C1B_490C_893C_B3412F6CB478
#define HE781FE8C_8C1B_490C_893C_B3412F6CB478

#include <quantity/base/Amount.h>

template <typename Unit>
struct Quantity
{
    Quantity(const Amount amount, const Unit unit);

    bool operator==(const Quantity&) const;
    bool operator!=(const Quantity&) const;

private:
    const Amount amountInBaseUnit;
};

#endif
