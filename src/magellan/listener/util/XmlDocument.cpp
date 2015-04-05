#include <magellan/listener/util/XmlDocument.h>
#include "magellan/listener/util/XmlNode.h"

MAGELLAN_NS_BEGIN

XmlDocument::XmlDocument
    ( const std::string &root
    , const std::string &styleSheet)
    : encoding("ISO-8859-1")
    , styleSheet(styleSheet)
    , root(new XmlNode(root))
    , standalone(true)
{
}

XmlDocument::~XmlDocument()
{
    delete root;
}

std::string XmlDocument::toString() const
{
    std::string asString = "<?xml version=\"1.0\" encoding='" + encoding + "'";

    if (standalone)
        asString += " standalone='yes'";

    asString += " ?>\n";

    if (!styleSheet.empty())
        asString += "<?xml-stylesheet type=\"text/xsl\" href=\"" + styleSheet + "\"?>\n";

    asString += root->toXml();

    return asString;
}

MAGELLAN_NS_END
