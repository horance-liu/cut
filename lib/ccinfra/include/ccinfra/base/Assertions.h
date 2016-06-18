#ifndef H5712E60C_DEF5_4A3B_93C1_C074CD80C63C
#define H5712E60C_DEF5_4A3B_93C1_C074CD80C63C

#include <ccinfra/base/Status.h>
#include <ccinfra/log/log.h>
#include <ccinfra/base/NullPtr.h>

CCINFRA_NS_BEGIN

#define __FAILED_BOOL_ACTION      return false
#define __FAILED_STATUS_ACTION    return CCINFRA_FAILURE;
#define __STATUS_ACTION           return __status;
#define __VOID_ACTION             return;
#define __NIL_ACTION              return 0;
#define __PEEK_ACTION    
#define __RESULT_ACTION(status)   return status;

//////////////////////////////////////////////////////////////////////////
#define __WARNING_NOT_TRUE(exp)             \
  WARN_LOG("assertion failed: "#exp)


#define __CCINFRA_EXPECT_TRUE(exp, action)  \
do {                                        \
    if (!(exp))                             \
    {                                       \
        __WARNING_NOT_TRUE(exp);            \
        action;                             \
    }                                       \
} while (0)

#define CCINFRA_EXPECT_TRUE_R(exp, status)  \
    __CCINFRA_EXPECT_TRUE(exp, __RESULT_ACTION(status))

#define CCINFRA_EXPECT_TRUE(exp)            \
  __CCINFRA_EXPECT_TRUE(exp, __FAILED_STATUS_ACTION)

#define CCINFRA_EXPECT_FALSE(exp)           \
    __CCINFRA_EXPECT_TRUE(!(exp), __FAILED_STATUS_ACTION)

#define CCINFRA_EXPECT_FALSE_R(exp, status) \
    __CCINFRA_EXPECT_TRUE(!(exp), __RESULT_ACTION(status))

#define CCINFRA_EXPECT_TRUE_NIL(exp)        \
  __CCINFRA_EXPECT_TRUE(exp, __NIL_ACTION)

#define CCINFRA_EXPECT_TRUE_VOID(exp)       \
  __CCINFRA_EXPECT_TRUE(exp, __VOID_ACTION)

#define CCINFRA_EXPECT_TRUE_BOOL(exp)       \
  __CCINFRA_EXPECT_TRUE(exp, __FAILED_BOOL_ACTION)

///////////////////////////////////////////////////////////////
#define  __NOT_TRUE(exp)                    \
    ERR_LOG("assertion failed: "#exp)

#define __CCINFRA_ASSERT_TRUE(exp, action)  \
do {                                        \
    if (!(exp))                             \
    {                                       \
        __NOT_TRUE(exp);                    \
        action;                             \
    }                                       \
} while (0)

#define CCINFRA_ASSERT_TRUE_R(exp, status)  \
    __CCINFRA_ASSERT_TRUE(exp, __RESULT_ACTION(status))

#define CCINFRA_ASSERT_TRUE(exp)            \
  __CCINFRA_ASSERT_TRUE(exp, __FAILED_STATUS_ACTION)

#define CCINFRA_ASSERT_FALSE(exp)           \
    __CCINFRA_ASSERT_TRUE(!(exp), __FAILED_STATUS_ACTION)

#define CCINFRA_ASSERT_FALSE_R(exp, status) \
    __CCINFRA_ASSERT_TRUE(!(exp), __RESULT_ACTION(status))

#define CCINFRA_ASSERT_TRUE_NIL(exp)        \
  __CCINFRA_ASSERT_TRUE(exp, __NIL_ACTION)

#define CCINFRA_PEEK_TRUE(exp)              \
  __CCINFRA_ASSERT_TRUE(exp, __PEEK_ACTION)

#define CCINFRA_ASSERT_TRUE_VOID(exp)       \
  __CCINFRA_ASSERT_TRUE(exp, __VOID_ACTION)

#define CCINFRA_ASSERT_TRUE_BOOL(exp)       \
  __CCINFRA_ASSERT_TRUE(exp, __FAILED_BOOL_ACTION)

//////////////////////////////////////////////////////////////////////////
#define __CCINFRA_ASSERT_TRUE_POST(exp, action, returnAction) \
do {                                        \
    if (!(exp))                             \
    {                                       \
        __NOT_TRUE(exp);                    \
        action;                             \
        returnAction;                       \
    }                                       \
} while (0)

#define CCINFRA_ASSERT_TRUE_POST(exp, action)   \
  __CCINFRA_ASSERT_TRUE_POST(exp, action, __FAILED_STATUS_ACTION)


//////////////////////////////////////////////////////////////////////////
#define __WARNING_CALL(call, status)            \
  WARN_LOG(#call" = [%X]", status)

#define __CCINFRA_EXPECT_SUCC_CALL(call, action)\
do {                                            \
    Status __status = call;                     \
    if (__CCINFRA_FAILED(__status))             \
    {                                           \
        __WARNING_CALL(call, __status);         \
        action;                                 \
    }                                           \
} while (0)

#define CCINFRA_EXPECT_SUCC_CALL_R(call, status)    \
   __CCINFRA_EXPECT_SUCC_CALL(call, __RESULT_ACTION(status))

#define CCINFRA_EXPECT_SUCC_CALL(call)              \
   __CCINFRA_EXPECT_SUCC_CALL(call, __STATUS_ACTION)

#define CCINFRA_EXPECT_SUCC_CALL_BOOL(call)         \
    __CCINFRA_EXPECT_SUCC_CALL(call, __FAILED_BOOL_ACTION)

#define CCINFRA_EXPECT_SUCC_CALL_VOID(call)         \
   __CCINFRA_EXPECT_SUCC_CALL(call, __VOID_ACTION)

#define CCINFRA_EXPECT_SUCC_CALL_NIL(call)          \
   __CCINFRA_EXPECT_SUCC_CALL(call, __NIL_ACTION)

/////////////////////////////////////////////////////////////////////
#define __FAIL_CALL(call, status)               \
  ERR_LOG(#call" = [%X]", status)

#define __CCINFRA_ASSERT_SUCC_CALL(call, action)\
do {                                            \
    Status __status = call;                     \
    if (__CCINFRA_FAILED(__status))             \
    {                                           \
        __FAIL_CALL(call, __status);            \
        action;                                 \
    }                                           \
} while (0)

#define CCINFRA_ASSERT_SUCC_CALL_R(call, status)\
    __CCINFRA_ASSERT_SUCC_CALL(call, __RESULT_ACTION(status))

#define CCINFRA_ASSERT_SUCC_CALL(call)          \
   __CCINFRA_ASSERT_SUCC_CALL(call, __STATUS_ACTION)

#define CCINFRA_ASSERT_SUCC_CALL_BOOL(call)     \
    __CCINFRA_ASSERT_SUCC_CALL(call, __FAILED_BOOL_ACTION)

#define CCINFRA_ASSERT_SUCC_CALL_VOID(call)     \
   __CCINFRA_ASSERT_SUCC_CALL(call, __VOID_ACTION)

#define CCINFRA_ASSERT_SUCC_CALL_NIL(call)      \
   __CCINFRA_ASSERT_SUCC_CALL(call, __NIL_ACTION)

/*no return even though call failed.*/
#define CCINFRA_PEEK_SUCC_CALL(call)            \
   __CCINFRA_ASSERT_SUCC_CALL(call, __PEEK_ACTION)

//////////////////////////////////////////////////////////////////////////

#define __CCINFRA_ASSERT_SUCC_CALL_FINALLY(call, action, returnAction)  \
do {                                                \
    Status __status = call;                         \
    if (__CCINFRA_FAILED(__status))                 \
    {                                               \
        __FAIL_CALL(call, __status);                \
        action;                                     \
        returnAction;                               \
    }                                               \
} while (0)

#define CCINFRA_ASSERT_SUCC_CALL_FINALLY(exp, action)\
  __CCINFRA_ASSERT_SUCC_CALL_FINALLY(exp, action, __FAILED_STATUS_ACTION)

//////////////////////////////////////////////////////////////////////////
#define __CCINFRA_ASSERT_NO_REAL_FAIL(call, action)  \
do {                                                 \
    Status __status = call;                          \
    if(__status == CCINFRA_NOTHING_CHANGED)          \
    {                                                \
        return CCINFRA_SUCCESS;                      \
    }                                                \
    else if (__CCINFRA_FAILED(__status))             \
    {                                                \
        __FAIL_CALL(call, __status);                 \
        action;                                      \
    }                                                \
} while (0)

#define CCINFRA_ASSERT_NO_REAL_FAIL(call)            \
    __CCINFRA_ASSERT_NO_REAL_FAIL(call, __STATUS_ACTION)

//////////////////////////////////////////////////////////////////////////
#define __NIL_PTR(ptr)                               \
    ERR_LOG("assertion failed: unexpected null ptr: "#ptr)

#define __CCINFRA_ASSERT_VALID_PTR(ptr, action)      \
do {                                                 \
    if ((ptr) == __null_ptr)                         \
    {                                                \
        __NIL_PTR(ptr);                              \
        action;                                      \
    }                                                \
} while (0)

#define CCINFRA_ASSERT_VALID_PTR_R(ptr, status)     \
    __CCINFRA_ASSERT_VALID_PTR(ptr, __RESULT_ACTION(status))

#define CCINFRA_ASSERT_VALID_PTR(ptr)               \
  __CCINFRA_ASSERT_VALID_PTR(ptr, __FAILED_STATUS_ACTION)

#define CCINFRA_ASSERT_VALID_PTR_BOOL(ptr)          \
   __CCINFRA_ASSERT_VALID_PTR(ptr, __FAILED_BOOL_ACTION)

#define CCINFRA_ASSERT_VALID_PTR_VOID(ptr)          \
  __CCINFRA_ASSERT_VALID_PTR(ptr, __VOID_ACTION)

#define CCINFRA_PEEK_VALID_PTR(ptr)                 \
  __CCINFRA_ASSERT_VALID_PTR(ptr, __PEEK_ACTION)

#define CCINFRA_ASSERT_VALID_PTR_NIL(ptr)           \
  __CCINFRA_ASSERT_VALID_PTR(ptr, __NIL_ACTION)

#define __CCINFRA_ASSERT_VALID_PTR_FINALLY(ptr, action, returnAction)  \
    if ((ptr) == __null_ptr)                        \
    {                                               \
        __NIL_PTR(ptr);                             \
        action;                                     \
        returnAction;                               \
    }

#define CCINFRA_PEEK_VALID_PTR_FINALLY(ptr, action)         \
    __CCINFRA_ASSERT_VALID_PTR_FINALLY(ptr, action, __PEEK_ACTION)

#define CCINFRA_ASSERT_VALID_PTR_NIL_FINALLY(ptr, action)   \
    __CCINFRA_ASSERT_VALID_PTR_FINALLY(ptr, action, __NIL_ACTION)

CCINFRA_NS_END

#endif
