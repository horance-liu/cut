#ifndef HA569F0D0_5A46_4EAE_AE57_2500191C1EEE
#define HA569F0D0_5A46_4EAE_AE57_2500191C1EEE

#include "magellan/infra/dci/Role.h"

//////////////////////////////////////////////////////////////
#define DECL_EQUALS(cls)            \
bool operator==(const cls&) const;    \
bool operator!=(const cls&) const

//////////////////////////////////////////////////////////////
#define FIELD_EQ(name)  this->name == rhs.name
#define SUPER_EQ(super) SELF_CONST(*this, super) == rhs

//////////////////////////////////////////////////////////////
#define DEF_EQUALS(cls)                                   \
bool cls::operator!=(const cls& rhs) const                  \
{                                                           \
    return !(*this == rhs);                                 \
}                                                           \
bool cls::operator==(const cls& rhs) const

#endif

