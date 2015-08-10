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

	SETUP()
	{
		options.clear();
	}

	template <typename Asserter>
	void given_options_then(const std::vector<std::string>& config, Asserter asserter)
	{
        Args args({"", "-f=fake"});

        options.parse(args.argc(), args.argv());
        asserter();
	}

	TEST("fake should be filtered when set filter=fake")
	{
	    given_options_then({"", "-f=fake"}, [this]{
	        ASSERT_THAT(options.filter("fake"), be_true());
	    });
	}

	TEST("fake_face should be filtered when set filter=fake.*")
    {
// TODO
//        given_options_then({"", "-f=fake.*"}, [this]{
//            ASSERT_THAT(options.filter("fake_face"), be_true());
//        });
	}

    TEST("face should be filtered when set filter=fake")
    {
        given_options_then({"", "-f=fake"}, [this]{
            ASSERT_THAT(options.filter("face"), be_false());
        });
    }
};
