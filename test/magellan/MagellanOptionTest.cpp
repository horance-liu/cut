#include "magellan/magellan.hpp"
#include "magellan/core/TestRunner.h"
#include "magellan/startup/TestOptions.h"
#include "magellan/core/TestSuite.h"
#include <fstream>
#include <stdio.h>

USING_HAMCREST_NS
USING_MAGELLAN_NS

#if 0

namespace
{
    struct FakeTest:Test
    {
        OVERRIDE(const std::string& getName () const)
        {
            static std::string name("fake test");
            return name;;
        }
        OVERRIDE(int countTestCases() const)
        {
            return 1;
        }
        OVERRIDE(int countChildTests() const)
        {
            return 1;
        }
        OVERRIDE(void run(TestResult&))
        {
        }
    };
}

FIXTURE(MagellanXmlOptionsTest)
{
    RUNTIME(TestOptions, options);


    SETUP()
    {
        suite = new TestSuite("Tests");
        suite->addTest(new FakeTest());
        runner = new TestRunner();
        remove(xmlFile.c_str());
        orignalFormat = options.outPutXml()? "xml":"term";
        orignalXmlFile = options.getXmlPath();
    }

    TEARDOWN()
    {
        delete runner;
        runner = 0;
        giveXmlOption({
                [&]{return std::string{"-x="+orignalFormat};}().c_str(),                      
                [&]{return std::string{"-d="+orignalXmlFile};}().c_str(),
            });
    }
    std::string orignalFormat;
    std::string orignalXmlFile;
    TestSuite* suite ;
    TestRunner* runner;
    const std::string xmlFile{"test.xml"};

    static const char** to_argv(std::vector<const char*>&& options)
    {
        const char** argv = new const char*[options.size()];

        for (auto i = 0; i < options.size(); i++)
        {
            argv[i] = options[i];
        }

        return argv;
    }

    void giveXmlOption(std::vector<const char*>&& opts)
    {
        auto argv = to_argv(std::move(opts));

        SCOPE_EXIT([=] { delete [] argv; });
        std::cout<<opts.size()<<std::endl;
        std::cout<<argv[1]<<std::endl;
        options.capatureOptionsFrom(opts.size(), argv);
    }

    void checkFileExist(bool isExist)
    {
        std::fstream file;
        file.open(xmlFile.c_str(), std::ios::in);
        ASSERT_THAT(file.good(), is(isExist));

        file.close();
    }

    void runTest()
    {
        runner->run(suite);
    }

    TEST("output xml when give --format=xml and path")
    {
        giveXmlOption({
                "",
                "--format=xml",
                [&]{return std::string{"-d="+xmlFile};}().c_str()
            });
        runTest();
        checkFileExist(true);
    }

    TEST("not output xml when give --format=xml without path")
    {
        giveXmlOption({
                "",
                "--format=xml",
            });
        runTest();
        checkFileExist(false);
    }

    TEST("not output xml when give --path without format")
    {
        giveXmlOption({
                "",
                "--format=term",
                [&]{return std::string{"-d="+xmlFile};}().c_str()
            });
        runTest();
        checkFileExist(false);
    }
    
};

#endif
