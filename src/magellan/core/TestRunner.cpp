#include "magellan/core/TestRunner.h"
#include "magellan/startup/TestOptions.h"
#include "magellan/listener/text/ListAllPrinter.h"
#include "magellan/listener/text/ProgressPrinter.h"
#include "magellan/listener/text/TextResultPrinter.h"
#include "magellan/listener/xml/XmlResultPrinter.h"
#include "magellan/core/TestResult.h"
#include "magellan/ext/RepeatedTest.h"
#include "magellan/auto/TestFactorySuite.h"
#include "l0-infra/std/ScopeExit.h"

MAGELLAN_NS_BEGIN

inline TestListener* TestRunner::makeTextPrinter() const
{
    if (ROLE(TestOptions).list())
    {
        return new ListAllPrinter;
    }
    else if (ROLE(TestOptions).progress())
    {
        return new ProgressPrinter;
    }
    else
    {
        return new TextResultPrinter;
    }
}

inline TestListener* TestRunner::makeXmlPrinter() const
{
    if (ROLE(TestOptions).xml())
    {
        return new XmlResultPrinter;
    }
    else
    {
        return new TestListener();
    }
}

inline void TestRunner::addListeners(TestResult& result) const
{
    result.add(makeTextPrinter());
    result.add(makeXmlPrinter());
}

inline bool TestRunner::run(Test* test)
{
    SCOPE_EXIT([=]{ delete test; });
                        
    TestResult result;
    addListeners(result);

    RepeatedTest repeated(*test, ROLE(TestOptions).repeat());
    result.run(repeated);

    return result.isSucc();
}

bool TestRunner::run(int argc, const char** argv)
{
    ROLE(TestOptions).parse(argc, argv);

    if (ROLE(TestOptions).help())
    {
        std::cout << ROLE(TestOptions).description();
        return true;
    }

    TestFactory& factory = ROLE(TestFactorySuite);
    return run(factory.make());
}

MAGELLAN_NS_END
