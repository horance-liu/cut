#ifndef HA5559C9B_84A7_4876_BDDD_B95BC2FF503B
#define HA5559C9B_84A7_4876_BDDD_B95BC2FF503B

#include "magellan/magellan.hpp"

MAGELLAN_NS_BEGIN

struct XmlNode;

struct XmlBuilder
{
    XmlBuilder(XmlNode* rootNode);

    void addChild(const std::string& value);
    void addSibling(const std::string& value);
    void addtoParent(const std::string& parent, const std::string& value);

    template <typename V>
    void addAttribute(const std::string& key, const V& value)
    {
        doAddAttribute(key, stdext::toString(value));
    }

    template <typename V>
    void addAttributeTo(const std::string& name, const std::string& key, const V& value)
    {
        doAddAttributeTo(name, key, stdext::toString(value));
    }

    template <typename V>
    void addValue(const V& value)
    {
        doAddValue(stdext::toString(value));
    }

    const std::string& getParentName() const;

private:
    XmlNode* findNodeBy(const std::string& name) const;

    void doAddAttribute(const std::string& key, const std::string& value);
    void doAddAttributeTo(const std::string& name, const std::string& key, const std::string& value);
    void doAddValue(const std::string& value);
    void addTo(XmlNode* node, const std::string& value);

private:
    XmlNode* root;
    XmlNode* current;
};

MAGELLAN_NS_END

#endif
