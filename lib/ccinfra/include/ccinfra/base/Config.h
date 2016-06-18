#ifndef H05B2224D_B926_4FC0_A936_67B52B8A98DA
#define H05B2224D_B926_4FC0_A936_67B52B8A98DA

//////////////////////////////////////////////////////////////////////////
#define __SUPPORT_STATIC_ASSERT       0
#define __SUPPORT_VARIADIC_TEMPLATES  0
#define __SUPPORT_RVALUE_REF          0
#define __SUPPORT_DECL_TYPE           0
#define __SUPPORT_AUTO_TYPE           0
#define __SUPPORT_LAMBDA              0
#define __SUPPORT_STRONG_TYPE_ENUM    0
#define __SUPPORT_RANGE_BASED_FOR     0
#define __SUPPORT_DEFAULT_DELETE_FUNC 0
#define __SUPPORT_VIRTUAL_OVERRIDE    0
#define __SUPPORT_NULL_PTR            0
#define __SUPPORT_GENERAL_CONST_EXPR  0

#if defined(__GNUC__) && defined(__GXX_EXPERIMENTAL_CXX0X__) 

    #if ((__GNUC__ > 4) || (__GNUC__ == 4 && __GNUC_MINOR__ >= 3))
        #undef  __SUPPORT_STATIC_ASSERT
        #define __SUPPORT_STATIC_ASSERT      1

        #undef  __SUPPORT_VARIADIC_TEMPLATES
        #define __SUPPORT_VARIADIC_TEMPLATES 1

        #undef  __SUPPORT_RVALUE_REF
        #define __SUPPORT_RVALUE_REF         1
    #endif

    #if ((__GNUC__ > 4) || (__GNUC__ == 4 && __GNUC_MINOR__ >= 4))
        #undef  __SUPPORT_DECL_TYPE
        #define __SUPPORT_DECL_TYPE          1

        #undef  __SUPPORT_AUTO_TYPE
        #define __SUPPORT_AUTO_TYPE          1
    #endif

    #if ((__GNUC__ > 4) || (__GNUC__ == 4 && __GNUC_MINOR__ >= 5))
        #undef  __SUPPORT_LAMBDA
        #define __SUPPORT_LAMBDA             1
    #endif

    #if ((__GNUC__ > 4) || (__GNUC__ == 4 && __GNUC_MINOR__ >= 6))
        #undef  __SUPPORT_STRONG_TYPE_ENUM
        #define __SUPPORT_STRONG_TYPE_ENUM    1
        
        #undef  __SUPPORT_RANGE_BASED_FOR
        #define __SUPPORT_RANGE_BASED_FOR     1

        #undef  __SUPPORT_DEFAULT_DELETE_FUNC 
        #define __SUPPORT_DEFAULT_DELETE_FUNC 1

        #undef  __SUPPORT_NULL_PTR
        #define __SUPPORT_NULL_PTR            1

        #undef  __SUPPORT_GENERAL_CONST_EXPR
        #define __SUPPORT_GENERAL_CONST_EXPR  1
    #endif

    #if ((__GNUC__ > 4) || (__GNUC__ == 4 && __GNUC_MINOR__ >= 7))
        #undef  __SUPPORT_VIRTUAL_OVERRIDE
        #define __SUPPORT_VIRTUAL_OVERRIDE    1
    #endif

#endif

#endif

