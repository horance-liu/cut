#ifndef _XQBZGMWOMI9Q1NW1QO2NOR2WRZOSTWAMCG6MQK2TZOV2MSWVLCBZUPKZ               
#define _XQBZGMWOMI9Q1NW1QO2NOR2WRZOSTWAMCG6MQK2TZOV2MSWVLCBZUPKZ

#include <magellan/core/Test.h>
#include <vector>

MAGELLAN_NS_BEGIN

struct TestSuite : Test
{
    explicit TestSuite(const std::string& name);    
    ~TestSuite();

    void addTest(Test*);
    void runBare(TestResult &result);

private:
    OVERRIDE(void run(TestResult&));
    OVERRIDE(const std::string& getName() const);
    OVERRIDE(int countTestCases() const);

private:
    void doStartSuite(TestResult&);
    void doRunChildTests(TestResult&);
    void doEndSuite(TestResult&);

private:
    std::string name;
    std::vector<Test*> tests;
};

MAGELLAN_NS_END

#endif

