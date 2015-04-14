#include "magellan/core/TestRunner.h"
#include "magellan/core/TestResult.h"
#include "magellan/core/Test.h"
#include "magellan/listener/text/TextResultPrinter.h"
#include "l0-infra/std/ScopeExit.h"
#include "magellan/listener/xml/XmlResultPrinter.h"
#include <fstream>
#include <iosfwd>

using std::ios;

MAGELLAN_NS_BEGIN

TestRunner::TestRunner(std::ostream& out)
  : out(out)
{
}

namespace
{
    void writeXmlFile(const std::string& s, const char* fileName = "./test_xml.xml")
    {
        std::fstream file;

        file.open(fileName, ios::out);

        if (file)
        {
            file << s;
        }

        file.close();
    }
}

bool TestRunner::run(Test* test)
{
    SCOPE_EXIT([=]{ delete test; });

    TestResult result;
    result.add(new TextResultPrinter(out));

    // just test; need refactor when MAGELLAN::TEST_FLAG == xml ok
    XmlResultPrinter *xmlPrt = new XmlResultPrinter();
    result.add(xmlPrt);

    result.runTest(*test);

    writeXmlFile(xmlPrt->toXml());

    return result.isSucc();
}

MAGELLAN_NS_END
