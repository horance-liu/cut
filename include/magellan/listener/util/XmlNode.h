#ifndef H8888DB62_21C7_4273_9936_AD379FB3BDCC
#define H8888DB62_21C7_4273_9936_AD379FB3BDCC

#include <l0-infra/std/Formatter.h>
#include <magellan/magellan.h>
#include <vector>
#include <string>

MAGELLAN_NS_BEGIN

struct XmlNode
{
    explicit XmlNode(const std::string& name);
    ~XmlNode();

    void addChild(XmlNode* child);
    void addAttribute(const std::string& key, const std::string& value);
    void addValue(const std::string& value);

    std::string toXml() const;

private:
    bool alone() const;
    std::string closeTag() const;

    void appendHead(std::ostream&) const;
    void appendTail(std::ostream&) const;
    void appendValue(std::ostream&) const;
    void appendChildren(std::ostream&) const;
    void appendContents(std::ostream&) const;

private:
    std::string name;
    std::string value;
    std::string attributes;

    std::vector<XmlNode*> children;
};

MAGELLAN_NS_END

#endif
