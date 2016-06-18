#ifndef HAB5F8A92_D5A1_4A91_A403_4CE8D5DAC957
#define HAB5F8A92_D5A1_4A91_A403_4CE8D5DAC957

#include <cut/cut.hpp>
#include <string>

CUT_NS_BEGIN

struct XmlNode;

struct XmlDocument
{
    XmlDocument(const std::string& root, const std::string& styleSheet = "");
    ~XmlDocument();

    std::string toString() const;

protected:
    std::string encoding;
    std::string styleSheet;
    XmlNode* root;
    bool standalone;
};

CUT_NS_END

#endif
