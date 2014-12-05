#ifndef _OPTIONSREPOSITRY_H_
#define _OPTIONSREPOSITRY_H_

#include <magellan/base/magellan.h>
#include <infra/base/Keywords.h>

MAGELLAN_NS_BEGIN

struct OptionsRepositry
{
    static OptionsRepositry& getInstance();
    ABSTRACT(void initArgs(char** argv));
};

MAGELLAN_NS_END

#endif /* _OPTIONSREPOSITRY_H_ */
