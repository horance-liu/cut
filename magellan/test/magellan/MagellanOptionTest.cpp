//#include "magellan/magellan.hpp"
//#include "magellan/core/TestRunner.h"
//#include "magellan/startup/TestOptions.h"
//#include "magellan/core/TestSuite.h"
//#include <fstream>
//#include <stdio.h>
//
//USING_HAMCREST_NS
//USING_MAGELLAN_NS
//
//namespace
//{
//    struct FakeTest : Test
//    {
//        std::string name {"fake test"};
//
//    private:
//        OVERRIDE(const std::string& getName () const)
//        {
//            return name;;
//        }
//
//        OVERRIDE(int countTestCases() const)
//        {
//            return 1;
//        }
//
//        OVERRIDE(int countChildTests() const)
//        {
//            return 1;
//        }
//
//        OVERRIDE(void run(TestResult&))
//        {
//        }
//    };
//}
//
//FIXTURE(MagellanXmlOptionsTest)
//{
//    RUNTIME(TestOptions, options);
//    RUNTIME(TestRunner, runner);
//
//    SETUP()
//    {
//        suite = new TestSuite("Tests");
//        suite->addTest(new FakeTest());
//        remove(xmlFile.c_str());
//        orignalFormat = options.outPutXml()? "xml":"term";
//    }
//
//    TEARDOWN()
//    {
//        giveXmlOption({
//                [&]{return std::string{"-x="+orignalFormat};}().c_str(),
//                });
//    }
//
//    std::string orignalFormat;
//    TestSuite* suite;
//    const std::string xmlFile{"result.xml"};
//
//    static const char** to_argv(std::vector<const char*>&& options)
//    {
//        const char** argv = new const char*[options.size()];
//
//        for (auto i = 0; i < options.size(); i++)
//        {
//            argv[i] = options[i];
//        }
//
//        return argv;
//    }
//
//    void giveXmlOption(bool isXml)
//    {
//      	auto argvXml = to_argv({" ","-x=xml"});
//       	auto argvNoXml = to_argv({" ", "-x=term"});
//        options.parse(2, isXml?argvXml:argvNoXml);
//    }
//
//    void checkFileExist(bool isExist)
//    {
//        std::fstream file;
//        file.open(xmlFile.c_str(), std::ios::in);
//        ASSERT_THAT(file.good(), is(isExist));
//
//        file.close();
//    }
//
//    void runTest()
//    {
//        runner.run(suite);
//    }
//
//    TEST("output xml when give --format=xml")
//    {
//        giveXmlOption(true);
//        runTest();
//        checkFileExist(true);
//    }
//
//    TEST("not output xml when give --format=term")
//    {
//        giveXmlOption(false);
//        runTest();
//        checkFileExist(false);
//    }
//
//};
//
