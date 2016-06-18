#include <cut/cut.hpp>
#include <cut/listener/util/XmlNode.h>

USING_HAMCREST_NS
USING_CUT_NS

FIXTURE(XmlNodeTest)
{
    XmlNode node {"person"};

    void expectXml(const std::string& expected)
    {
        ASSERT_THAT(node.toXml(), is(expected));
    }

    TEST("single node")
    {
        expectXml("<person/>");
    }

    TEST("string attribute")
    {
        node.addAttribute("age", "12");
        expectXml("<person age='12'/>");
    }

//    TEST("char attribute")
//    {
//        node.addAttribute("age", 'X');
//        expectXml("<person age='X'/>");
//    }

    TEST("short attribute")
    {
        node.addAttribute("age", (short)12);
        expectXml("<person age='12'/>");
    }

    TEST("negative int attribute")
    {
        node.addAttribute("age", -12);
        expectXml("<person age='-12'/>");
    }

    TEST("positive int attribute")
    {
        node.addAttribute("age", 12);
        expectXml("<person age='12'/>");
    }

    TEST("long attribute")
    {
        node.addAttribute("age", long(12));
        expectXml("<person age='12'/>");
    }

    TEST("float attribute")
    {
        node.addAttribute("age", 12.0f);
        expectXml("<person age='12.00'/>");
    }

    TEST("float attribute")
    {
        node.addAttribute("age", 12.0);
        expectXml("<person age='12.00'/>");
    }

    TEST("attribute value contains <")
    {
        node.addAttribute("age", "<10");
        expectXml("<person age='&lt;10'/>");
    }

    TEST("attribute value contains >")
    {
        node.addAttribute("age", ">10");
        expectXml("<person age='&gt;10'/>");
    }

    TEST("attribute value contains '")
    {
        node.addAttribute("age", "'ten'");
        expectXml("<person age='&apos;ten&apos;'/>");
    }

    TEST("attribute value contains \"")
    {
        node.addAttribute("age", "\"ten\"");
        expectXml("<person age='&quot;ten&quot;'/>");
    }

    TEST("attribute value contains &")
    {
        node.addAttribute("age", "&ten");
        expectXml("<person age='&amp;ten'/>");
    }

    TEST("int value")
    {
        node.addValue(12);
        expectXml("<person>"
                  "12"
                  "</person>");
    }

//    TEST("char value")
//    {
//        node.addValue('X');
//        expectXml("<person>"
//                  "X"
//                  "</person>");
//    }

    TEST("float value")
    {
        node.addValue(12.00f);
        expectXml("<person>"
                  "12.00"
                  "</person>");
    }

    TEST("string value")
    {
        node.addValue("bob");
        expectXml("<person>"
                  "bob"
                  "</person>");
    }

    TEST("string value contains <")
    {
        node.addValue("<bob");
        expectXml("<person>"
                  "&lt;bob"
                  "</person>");
    }

    TEST("string value contains >")
    {
        node.addValue(">bob");
        expectXml("<person>"
                  "&gt;bob"
                  "</person>");
    }

    TEST("string value contains &")
    {
        node.addValue("&bob");
        expectXml("<person>"
                  "&amp;bob"
                  "</person>");
    }

    TEST("string value contains '")
    {
        node.addValue("'bob'");
        expectXml("<person>"
                  "&apos;bob&apos;"
                  "</person>");
    }

    TEST("string value contains \"")
    {
        node.addValue("\"bob\"");
        expectXml("<person>"
                  "&quot;bob&quot;"
                  "</person>");
    }

    TEST("2 attributes")
    {
        node.addAttribute("age", "30");
        node.addAttribute("address", "china");

        expectXml("<person age='30' address='china'/>");
    }

    TEST("1 child")
    {
        node.addChild(new XmlNode("hobbies"));

        expectXml("<person>"
                  "<hobbies/>"
                  "</person>");
    }

    TEST("1 child and 1 attribute")
    {
        node.addAttribute("age", "30");
        node.addChild(new XmlNode("hobbies"));

        expectXml("<person age='30'>"
                  "<hobbies/>"
                  "</person>");
    }

    TEST("1 child and 2 attributes")
    {
        node.addAttribute("age", "30");
        node.addAttribute("address", "china");

        node.addChild(new XmlNode("hobbies"));

        expectXml("<person age='30' address='china'>"
                  "<hobbies/>"
                  "</person>");
    }

    TEST("2 children and 2 attributes")
    {
        node.addAttribute("age", "30");
        node.addAttribute("address", "china");

        node.addChild(new XmlNode("hobbies"));
        node.addChild(new XmlNode("profession"));

        expectXml("<person age='30' address='china'>"
                  "<hobbies/>"
                  "<profession/>"
                  "</person>");
    }

    TEST("root parent is null")
    {
        ASSERT_THAT(nullptr, eq(node.getParent()));
        ASSERT_THAT("person", eq(node.getName()));
    }

    TEST("1 child parent is root")
    {
        XmlNode* child = new XmlNode("hobbies");
        node.addChild(child);

        ASSERT_THAT(&node, eq(child->getParent()));
        ASSERT_THAT("hobbies", eq(child->getName()));
    }
};
