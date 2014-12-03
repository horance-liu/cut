#ifndef INLGWPGKWEOIT_58395JFLSG_RUTOOJVN_HRYOQOJNO6847201
#define INLGWPGKWEOIT_58395JFLSG_RUTOOJVN_HRYOQOJNO6847201

#include <infra/base/Keywords.h>

namespace details
{
    template <typename T>
    struct Role
    {
        virtual ~Role() {}
    };
}

#define DEFINE_ROLE(type) struct type : ::details::Role<type>

#endif

