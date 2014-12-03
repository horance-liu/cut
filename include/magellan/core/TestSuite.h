#ifndef _XQBZGMWOMI9Q1NW1QO2NOR2WRZOSTWAMCG6MQK2TZOV2MSWVLCBZUPKZ               
#define _XQBZGMWOMI9Q1NW1QO2NOR2WRZOSTWAMCG6MQK2TZOV2MSWVLCBZUPKZ

#include <magellan/core/Test.h>
#include <vector>

MAGELLAN_NS_BEGIN

struct TestSuite : Test
{
    explicit TestSuite(const std::string& name);    
    ~TestSuite();

    void addTest(const Test&);

private:
    OVERRIDE(void run(TestResult&) const);
    OVERRIDE(const std::string& getName() const);
    OVERRIDE(int getNumOfTestCases() const);

private:
    void doStartSuite(TestResult&) const;
    void doRunChildTests(TestResult&) const;
    void doEndSuite(TestResult&) const;

private:
    std::string name;
    std::vector<const Test*> tests;
};

MAGELLAN_NS_END

#endif

