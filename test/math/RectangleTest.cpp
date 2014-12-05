#include <magellan/core/TestCaller.h>

//template <typename Fixture>
//struct MetaTestFixture
//{
//    typedef void (Fixture::*Method)() const;
//
//    static void registerTestMethod(const std::string& desc, Method method)
//    {
//    }
//
//    static void registerAutoTestCases()
//    {
//    }
//};
//
//struct AutoTestFixture
//{
//    virtual void registerTestMethods() = 0;
//    virtual ~AutoTestFixture();
//};
//
//template <typename Fixture>
//struct GenericAutoTestFixture : AutoTestFixture
//{
//    virtual void registerTestMethods() override
//    {
//        MetaTestFixture<Fixture>::registerAutoTestCases();
//    }
//};
//
//struct AutoTestFixtureRepository
//{
//    template <typename AutoTestFixture>
//    static void registerFixture(const std::string& name)
//    {
//        getRepo().push_back(new AutoTestFixture(name));
//    }
//
//    static void registerAllTestCases()
//    {
//        for (auto fixture : getRepo())
//        {
////            fixture->registerTestCases();
//        }
//    }
//
//private:
//    static std::vector<AutoTestFixture*>& getRepo()
//    {
//        static std::vector<AutoTestFixture*> fixtures;
//        return fixtures;
//    }
//};
//
//struct Rectangle;
//
//static struct Rectangle_Fixture
//{
//    Rectangle_Fixture()
//    {
//        AutoTestFixtureRepository::registerFixture
//            <GenericAutoTestFixture<Rectangle> >("Rectangle");
//    }
//} Rectangle_Fixture_100;
//
//template <typename Fixture>
//struct GenericTestFixture
//{
//    typedef Fixture FixtureType;
//};
//
//struct Rectangle : GenericTestFixture<Rectangle>, MAGELLAN_NS::TestFixture
//{
//    void setUp()
//    {
//
//    }
//
//    void tearDown()
//    {
//
//    }
//
//    struct TestMethod
//    {
//        TestMethod()
//        {
//            MetaTestFixture<FixtureType>::registerTestMethod
//                ("should be get area", &FixtureType::method_120);
//        }
//    } method_10000;
//
//    void method_120() const
//    {
//    }
//};

//FIXTURE(Rectangle)
//{
//    SETUP()
//    {
//
//    }
//
//    TEARDOWN()
//    {
//
//    }
//
//    TEST("should be get area")
//    {
//    }
//};
