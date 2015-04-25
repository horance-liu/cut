#ifndef INCL_DCM_H7349D344_AAC4_47D0_8E42_DF1F7EC0C2A4
#define INCL_DCM_H7349D344_AAC4_47D0_8E42_DF1F7EC0C2A4

#include <l0-infra/dci/Role.h>
#include <magellan/magellan.h>
#include <string>

MAGELLAN_NS_BEGIN

DEFINE_ROLE(MagellanOptions)
{
  static MagellanOptions& getInstance();

  ABSTRACT(void capatureOptionsFrom(int argc, const char** argv));

  ABSTRACT(bool colorOn() const);
  ABSTRACT(bool hasHelpOption() const);
  ABSTRACT(void handlerHelpOption() const);
  ABSTRACT(bool outPutXml() const);
  ABSTRACT(const std::string& getXmlPath()const);
  ABSTRACT(bool handlerFilterOptionBy(const std::string& name) const);
};

#define OPTIONS MagellanOptions::getInstance()

MAGELLAN_NS_END

#endif
