#include <cut/cut.hpp>
#include <cut/hook/registry/HookRegistries.h>
#include <sstream>

USING_CUM_NS
USING_CUT_NS

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
        Runtime::getIntance().__ROLE__(BeforeAllHookRegistry).execHooks();

        ASSERT_THAT(before_all_stream.str(), is(std::string("AB")));
    }

    TEST("should supoort keywards AFTER_ALL")
    {
        Runtime::getIntance().__ROLE__(AfterAllHookRegistry).execHooks();

        ASSERT_THAT(after_all_stream.str(), is(std::string("CD")));
    }
};
