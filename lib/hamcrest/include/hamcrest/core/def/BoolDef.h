#ifndef HC854C71C_B9DB_406F_ADF6_779E2B16ED4D
#define HC854C71C_B9DB_406F_ADF6_779E2B16ED4D

#include <hamcrest/core/def/IsDef.h>

HAMCREST_NS_BEGIN

inline Matcher<bool>* be_true()  { return is(true);  }
inline Matcher<bool>* be_false() { return is(false); }

HAMCREST_NS_END

#endif
