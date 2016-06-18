#include <quantity/base/Quantity.h>

template <typename Unit>
Quantity<Unit>::Quantity(const Amount amount, const Unit unit)
  : amountInBaseUnit(unit * amount)
{
}

template <typename Unit>
bool Quantity<Unit>::operator==(const Quantity& rhs) const
{
    return amountInBaseUnit == rhs.amountInBaseUnit;
}

template <typename Unit>
bool Quantity<Unit>::operator!=(const Quantity& rhs) const
{
    return !(*this == rhs);
}
