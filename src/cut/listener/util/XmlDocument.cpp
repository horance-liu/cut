#include <cut/listener/util/XmlDocument.h>
#include <cut/listener/util/XmlNode.h>

CUT_NS_BEGIN

XmlDocument::XmlDocument
    ( const std::string &root
    , const std::string &styleSheet)
    : encoding("ISO-8859-1")
    , styleSheet(styleSheet)
    , standalone(true)
{
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

CUT_NS_END
