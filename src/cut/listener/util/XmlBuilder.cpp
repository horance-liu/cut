#include <cut/listener/util/XmlBuilder.h>
#include <cut/listener/util/XmlNode.h>

CUT_NS_BEGIN

XmlBuilder::XmlBuilder(XmlNode* rootNode)
	: root(rootNode)
	, current(root)
{
}

void XmlBuilder::addChild(const std::string& value)
{
	addTo(current, value);
}

void XmlBuilder::addSibling(const std::string& value)
{
	addTo(current->getParent(), value);
}

void XmlBuilder::addToParent( const std::string& parent, const std::string& value)
{
    addTo(findNodeBy(parent), value);
}

inline void XmlBuilder::addTo( XmlNode* node, const std::string& name)
{
	current = new XmlNode(name);
	node->addChild(current);
}

XmlNode* XmlBuilder::findNodeBy(const std::string& name) const
{
	XmlNode* currentNode = current;

	while(currentNode != 0)
	{
		if (currentNode->getName() == name)
		{
		    return currentNode;
		}

		currentNode = currentNode->getParent();
	}

	return currentNode;
}

void XmlBuilder::doAddAttribute(const std::string& key, const std::string& value)
{
    current->addAttribute(key, value);
}

void XmlBuilder::doAddAttributeTo(const std::string& name, const std::string& key, const std::string& value)
{
    XmlNode* currentNode = current;
    current = findNodeBy(name);
    doAddAttribute(key, value);
    current = currentNode;
}

void XmlBuilder::doAddValue(const std::string& value)
{
    current->addValue(value);
}

const std::string& XmlBuilder::getParentName() const
{
    return current->getName();
}

CUT_NS_END
