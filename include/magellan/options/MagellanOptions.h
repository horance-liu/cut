#ifndef MAGELLANOPTIONS_Wed_Apr_22_21_09_13_2015_H
#define MAGELLANOPTIONS_Wed_Apr_22_21_09_13_2015_H

#include <l0-infra/dci/Role.h>
#include <magellan/magellan.h>

MAGELLAN_NS_BEGIN

DEFINE_ROLE(MagellanOptions)
{
  static MagellanOptions& getInstance();

  ABSTRACT(void parseArgs(int argc, const char** argv));
  ABSTRACT(bool colorOn() const);
  
};

#define OPTIONS MagellanOptions::getInstance()

MAGELLAN_NS_END

#endif
