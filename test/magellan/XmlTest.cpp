#include "magellan/magellan.hpp"
#include "magellan/listener/util/XmlNode.h"

USING_MAGELLAN_NS
USING_HAMCREST_NS

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
};
