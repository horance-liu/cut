#ifndef H8888DB62_21C7_4273_9936_AD379FB3BDCC
#define H8888DB62_21C7_4273_9936_AD379FB3BDCC

#include <cut/cut.h>
#include <vector>
#include <string>
#include <cui/algo/__string__.h>

CUT_NS_BEGIN

struct XmlNode
{
    explicit XmlNode(const std::string& name);
    ~XmlNode();

    void addChild(XmlNode* child);

    template <typename V>
    void addAttribute(const std::string& key, const V& value)
    {
        doAddAtribute(key, cui::toString(value));
    }

    template <typename V>
    void addValue(const V& value)
    {
        doAddValue(cui::toString(value));
    }

    const std::string& getName() const;
    XmlNode* getParent() const;

    std::string toXml() const;

private:
    void doAddValue(const std::string& value);
    void doAddAtribute(const std::string& key, const std::string& value);

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
    XmlNode* parent;
};

CUT_NS_END

#endif
