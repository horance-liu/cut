#ifndef _XQBZGMWOMI9Q1NW1QO2NOR2WRZOSTWAMCG6MQK2TZOV2MSWVLCBZUPKZ               
#define _XQBZGMWOMI9Q1NW1QO2NOR2WRZOSTWAMCG6MQK2TZOV2MSWVLCBZUPKZ

#include <vector>
#include "magellan/core/Test.h"

MAGELLAN_NS_BEGIN

struct TestSuite : Test
{
    explicit TestSuite(const std::string& name);
    ~TestSuite();

    void addTest(Test*);
    void runBare(TestResult &result);

private:
    OVERRIDE(const std::string& getName() const);
    OVERRIDE(int countTestCases() const);
    OVERRIDE(int countChildTests() const);
    OVERRIDE(void run(TestResult&));

private:
    const std::string name;
    std::vector<Test*> tests;
};

MAGELLAN_NS_END

#endif

