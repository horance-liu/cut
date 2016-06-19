#include <cut/cut.hpp>
#include <cut/startup/TestOptions.h>
#include <regex>

#include <cpo/core/Args.h>

USING_CUT_NS
USING_CUM_NS
USING_CUB_NS

FIXTURE(FilterTest)
{
	TestOptions &options = RUNTIME(TestOptions);

	TEARDOWN()
	{
	    options.clear();
	}

	template <typename Asserter>
	void given_options_then(const std::vector<std::string>& config, Asserter asserter)
	{
        cpo::Args args(config);
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
