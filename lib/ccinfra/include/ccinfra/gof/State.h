#ifndef HC723AA1A_FCCD_45CE_A091_FC328E700922
#define HC723AA1A_FCCD_45CE_A091_FC328E700922

#include "ccinfra/base/Keywords.h"
#include "ccinfra/gof/Singleton.h"

#define __USING_GOF_STATE struct GofState;      \
                          GofState *state

#define __DEF_GOF_STATE_INTERFACE(Object) DEF_INTERFACE(Object::GofState)

#define __DEF_GOF_STATE(Object, S)              \
DEF_SINGLETON(Object::S) IMPLEMENTS(Object::GofState)

#define __GOTO_STATE(S) goto##S##State()

#define __HAS_STATE(S)  struct S;               \
                        void __GOTO_STATE(S)

#define __REGISTER_STATE(Object, S)             \
void Object::__GOTO_STATE(S)                    \
{                                               \
   state = &S::getInstance();                   \
}                                               \


#endif
