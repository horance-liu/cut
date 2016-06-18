#include <cut/listener/util/XmlNode.h>
#include <sstream>

CUT_NS_BEGIN

XmlNode::XmlNode(const std::string& name)
    : name(name)
    , parent(0)
{
}

XmlNode::~XmlNode()
{
    for (auto child : children)
    {
        delete child;
    }
}

void XmlNode::addChild(XmlNode* child)
{
    child->parent = this;
    children.push_back(child);
}

namespace
{
    inline void to(char c, std::string& escaped)
    {
        switch (c)
        {
        case '<':
            escaped += "&lt;";
            break;
        case '>':
            escaped += "&gt;";
            break;
        case '&':
            escaped += "&amp;";
            break;
        case '\'':
            escaped += "&apos;";
            break;
        case '"':
            escaped += "&quot;";
            break;
        default:
            escaped += c;
        }
    }

    inline std::string escape(const std::string& value)
    {
        std::string escaped;

        for (auto c : value)
        {
            to(c, escaped);
        }

        return escaped;
    }
}

void XmlNode::doAddAtribute(const std::string& key, const std::string& value)
{
    attributes += " ";
    attributes += key;
    attributes += "='";
    attributes += escape(value);
    attributes += "'";
}

void XmlNode::doAddValue(const std::string& value)
{
    this->value = escape(value);
}

inline bool XmlNode::alone() const
{
    return children.empty() && value.empty();
}

inline std::string XmlNode::closeTag() const
{
    return alone() ? "/" : "";
}

inline void XmlNode::appendHead(std::ostream& ss) const
{
    ss << "<"
       << name
       << attributes
       << closeTag()
       << ">";
}

inline void XmlNode::appendTail(std::ostream& ss) const
{
    if (!alone())
    {
        ss << "</" << name << ">";
    }
}

inline void XmlNode::appendValue(std::ostream& ss) const
{
    if (!value.empty())
    {
        ss << value;
    }
}

inline void XmlNode::appendChildren(std::ostream& ss) const
{
    for (auto child : children)
    {
        child->appendContents(ss);
    }
}

inline void XmlNode::appendContents(std::ostream& ss) const
{
    appendHead(ss);
    appendValue(ss);
    appendChildren(ss);
    appendTail(ss);
}

std::string XmlNode::toXml() const
{
    std::ostringstream ss;
    appendContents(ss);

    return ss.str();
}

const std::string& XmlNode::getName() const
{
    return name;
}

XmlNode* XmlNode::getParent() const
{
    return parent;
}

CUT_NS_END
