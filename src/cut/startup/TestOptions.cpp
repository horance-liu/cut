#include <cut/startup/TestOptions.h>
#include <cut/core/TestRunner.h>
#include <cut/listener/text/ListAllPrinter.h>
#include <cut/listener/text/ProgressPrinter.h>
#include <cut/listener/text/TextResultPrinter.h>
#include <cut/listener/xml/XmlResultPrinter.h>
#include <regex>

CUT_NS_BEGIN

TestOptions::TestOptions() : desc("cut")
{
    desc.add({
        {"help,     h",   "help message"},
        {"filter,   f",   "--filter=pattern"},
        {"color,    c",   "--color=[yes|no]"},
        {"xml,      x",   "print test result into XML file"},
		{"list,     l",   "list all tests without running them"},
        {"progress, p",   "print test result in progress bar"},
        {"verbose,  v",   "verbosely list tests processed"},
        {"repeat,   r",   "how many times to repeat each test"}
    });

    clear();
}

void TestOptions::clear()
{
	options.clear();

    options["color"]  = "yes";
    options["repeat"] = "1";
}

int TestOptions::repeat() const
{
	return options.has("list") ? 1 : cui::string_as<int>(options["repeat"]);
}

bool TestOptions::verbose() const
{
	return options.has("verbose");
}

TestListener* TestOptions::makeTextPrinter() const
{
    if (options.has("list")) return new ListAllPrinter;
    if (options.has("progress")) return new ProgressPrinter;
    return new TextResultPrinter;
}

TestListener* TestOptions::makeXmlPrinter() const
{
    if (options.has("xml")) return new XmlResultPrinter;
    return new TestListener();
}

inline int TestOptions::help() const
{
    std::cout << desc;
    return EXIT_SUCCESS;
}

inline int TestOptions::go() const
{
    return __ROLE__(TestRunner).run() ? EXIT_SUCCESS : EXIT_FAILURE;
}

int TestOptions::run() const
{
    return options.has("help") ? help() : go();
}

void TestOptions::parse(int argc, const char** argv)
{
    options.parseArgs(argc, argv, desc);
}

bool TestOptions::colorful() const
{
    return options.has("color") && options["color"] == "yes";
}

inline bool TestOptions::matches(const std::string& name) const
{
    std::regex pattern(options["filter"]);
    return std::regex_match(name, pattern);
}

bool TestOptions::filter(const std::string& name) const
{
    return !options.has("filter") || matches(name);
}

CUT_NS_END
