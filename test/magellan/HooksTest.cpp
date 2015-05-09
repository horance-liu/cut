#include <magellan/def/FixtureDef.h>
#include <magellan/def/BeforeAllDef.h>
#include <magellan/def/AfterAllDef.h>
#include <magellan/def/TestDef.h>
#include "magellan/core/Asserter.h"
#include <iosfwd>
#include <hamcrest/core/def/IsDef.h>
#include <magellan/hook/runtime/Runtime.h>
#include <iostream>

USING_HAMCREST_NS
USING_MAGELLAN_NS

namespace
{
    std::stringstream before_all_stream;
    std::stringstream after_all_stream;

    BEFORE_ALL() { before_all_stream << "A"; }
    BEFORE_ALL() { before_all_stream << "B"; }

    AFTER_ALL() { after_all_stream << "C"; }
    AFTER_ALL() { after_all_stream << "D"; }
}

FIXTURE(HooksTest)
{
    TEARDOWN()
    {
        before_all_stream.str("");
        after_all_stream.str("");
    }
    
    TEST("should supoort keywards BEFORE_ALL")
    {
        Runtime::getIntance().ROLE(BeforeAllHookRegistry).execHooks();

        ASSERT_THAT(before_all_stream.str(), is(std::string("AB")));
    }

    TEST("should supoort keywards AFTER_ALL")
    {
        Runtime::getIntance().ROLE(AfterAllHookRegistry).execHooks();

        ASSERT_THAT(after_all_stream.str(), is(std::string("CD")));
    }
};
