#include <cut/cut.hpp>

USING_CUT_NS
USING_CUM_NS

FIXTURE(ExceptionTest)
{
    void f() {
      throw std::runtime_error("error on runtime");
    }

    TEST("throw std::exception")
    {
        ASSERT_TRUE(throwing<std::runtime_error>([this] {
            f();
        }));
    }
};
