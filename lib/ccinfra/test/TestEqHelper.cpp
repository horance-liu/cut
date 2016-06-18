#include "magellan/magellan.hpp"
#include "ccinfra/base/EqHelper.h"

USING_HAMCREST_NS
USING_CCINFRA_NS

namespace
{
    struct Complex
    {
        Complex(int r, int i) : real(r), image(i)
        {
        }

        __DECL_COMP(Complex);

    private:
        int real;
        int image;
    };

    __DEF_EQUALS(Complex)
    {
        return (real == rhs.real) && (image == rhs.image);
    }

    __DEF_COMP(Complex)
    {
        if(real == rhs.real) return image < rhs.image;
        return real < rhs.real;
    }
}

FIXTURE(EqHelperTest)
{
	TEST("should compare complex correctly when defined compare operator by eq helper")
	{
	    ASSERT_THAT(Complex(3, 1) == Complex(3, 1), be_true());
	    ASSERT_THAT(Complex(3, 0) != Complex(3, 1), be_true());
	    ASSERT_THAT(Complex(3, 0) < Complex(3, 1), be_true());
	    ASSERT_THAT(Complex(2, 8) < Complex(3, 0), be_true());
	    ASSERT_THAT(Complex(2, 8) <= Complex(3, 0), be_true());
	    ASSERT_THAT(Complex(2, 8) > Complex(1, 10), be_true());
	    ASSERT_THAT(Complex(2, 8) >= Complex(2, 7), be_true());
	    ASSERT_THAT(Complex(2, 8) >= Complex(2, 8), be_true());
	}
};



