#include "magellan/magellan.hpp"
#include "magellan/startup/TestOptions.h"

USING_MAGELLAN_NS
USING_HAMCREST_NS

FIXTURE(FilterTest)
{
	TestOptions options;
	SETUP()
	{
		options.clear();
	}

    static const char** to_argv(std::vector<const char*>&& options)
    {
        const char** argv = new const char*[options.size()];

        for (auto i = 0; i < options.size(); i++)
        {
            argv[i] = options[i];
        }

        return argv;
    }

	TEST("fake should be filtered when set filter=fake")
	{
		options.parse(2, to_argv({"", "-f=fake"}));
		ASSERT_THAT(options.doFilter("fake"), is(true));
	}

	TEST("fake_face should be filtered when set filter=fake.*")
    {
		options.parse(2, to_argv({"", "-f=fake.*"}));
		ASSERT_THAT(options.doFilter("fake_face"), is(true));
	}

	TEST("face should be filtered when set filter=fake")
	{
		options.parse(2, to_argv({"", "-f=fake"}));
		ASSERT_THAT(options.doFilter("face"), is(false));
	}
};


