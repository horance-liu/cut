#include <type_traits>

#define STATIC_ASSERT_TRUE(bool_expr) \
    static_assert((bool_expr), "static assert "#bool_expr" fail")

#define STATIC_ASSERT_FALSE(expr) \
    STATIC_ASSERT_TRUE(!(expr))

#define STATIC_ASSERT_TYPE(expect_type, expr) \
    STATIC_ASSERT_TRUE((std::is_same<expect_type, decltype(expr)>::value))

#define STATIC_ASSERT_SAME_TYPE(expect_type, actual_type) \
    STATIC_ASSERT_TRUE((std::is_same<expect_type, actual_type>::value))

#define STATIC_ASSERT_RVALUE_REF(expr) \
    STATIC_ASSERT_TRUE(std::is_rvalue_reference<decltype(expr)>::value)

#define STATIC_ASSERT_LVALUE_REF(expr) \
    STATIC_ASSERT_TRUE(std::is_lvalue_reference<decltype(expr)>::value)
