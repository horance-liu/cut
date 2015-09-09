#include "magellan/magellan.hpp"
#include "magellan/startup/TestOptions.h"
#include "l0-infra/std/Args.h"
#include <regex>

USING_MAGELLAN_NS
USING_HAMCREST_NS
USING_STDEXT_NS

FIXTURE(FilterTest)
{
	TestOptions options;

	template <typename Asserter>
	void given_options_then(const std::vector<std::string>& config, Asserter asserter)
	{
        Args args(config);
        options.parse(args.argc(), args.argv());
        asserter();
	}

	TEST("should be filter")
	{
	    given_options_then({"", "-f=fake"}, [this]{
	        ASSERT_THAT(options.filter("fake"), be_true());
	    });
	}

    TEST("should not be filter")
    {
        given_options_then({"", "-f=fake"}, [this]{
            ASSERT_THAT(options.filter("face"), be_false());
        });
    }

	TEST("fixture::any of test case")
    {
        given_options_then({"", "-f=fake::.*"}, [this]{
            ASSERT_THAT(options.filter("fake::face to north"), be_true());
        });
	}
};
