#include "magellan/magellan.hpp"
#include "magellan/listener/util/XmlNode.h"
#include "magellan/listener/util/XmlBuilder.h"

USING_MAGELLAN_NS
USING_HAMCREST_NS

FIXTURE(XmlBuilderTest)
{
    XmlNode node {"bookstore"};
	XmlBuilder builder {&node};

	void expectXml(const std::string& expected)
	{
		ASSERT_THAT(node.toXml(), is(expected));
	}

	TEST("build root node")
	{
		expectXml("<bookstore/>");
	}

	TEST("build 1 child")
	{
		builder.addChild("book");

		expectXml("<bookstore>"
				  "<book/>"
				  "</bookstore>");
	}

	TEST("build 1 string attribute")
	{
		builder.addChild("book");
		builder.addAttribute("genre", "fantasy");

		expectXml("<bookstore>"
				  "<book genre='fantasy'/>"
				  "</bookstore>");
	}

	TEST("build 2 string attributes")
	{
		builder.addChild("book");
		builder.addAttribute("genre", "fantasy");
		builder.addAttribute("ISBN", "2-3632-4");

		expectXml("<bookstore>"
				  "<book genre='fantasy' ISBN='2-3632-4'/>"
				  "</bookstore>");
	}

    TEST("build 1 child and add 1 attributes to parent")
    {
        builder.addChild("book");
        builder.addAttribute("genre", "fantasy");
        builder.addAttribute("ISBN", "2-3632-4");
        builder.addAttributeTo("bookstore", "address", "xi'an");

        expectXml("<bookstore address='xi&apos;an'>"
                  "<book genre='fantasy' ISBN='2-3632-4'/>"
                  "</bookstore>");
    }

	TEST("build 1 child 1 value")
	{
		builder.addChild("book");
		builder.addValue("This is about wolf Legacy!");

		expectXml("<bookstore>"
				  "<book>"
				  "This is about wolf Legacy!"
				  "</book>"
				  "</bookstore>");
	}

	TEST("build 1 child and 1 sibling")
	{
		builder.addChild("book");
		builder.addSibling("book");

		expectXml("<bookstore>"
				  "<book/>"
				  "<book/>"
				  "</bookstore>");
	}

	TEST("build 2 sibling and multi childrens")
	{
		builder.addtoParent("bookstore", "book");
		builder.addChild("title");
		builder.addValue("The Legacy of the Wolf");
		builder.addSibling("price");
		builder.addValue("59.5");

		builder.addtoParent("bookstore", "book");
		builder.addChild("title");
		builder.addValue("The Legacy of the Panda");
		builder.addSibling("price");
		builder.addValue("89.9");

		expectXml("<bookstore>"
				  "<book>"
				  "<title>"
				  "The Legacy of the Wolf"
				  "</title>"
				  "<price>"
				  "59.5"
				  "</price>"
				  "</book>"
				  "<book>"
				  "<title>"
				  "The Legacy of the Panda"
				  "</title>"
				  "<price>"
				  "89.9"
				  "</price>"
	              "</book>"
				  "</bookstore>");
	}
};
