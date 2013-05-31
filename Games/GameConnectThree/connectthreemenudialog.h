#ifndef CONNECTTHREEMENUDIALOG_H
#define CONNECTTHREEMENUDIALOG_H

//---------------------------------------------------------------------------
#include <string>
#include <vector>
#include "about.h"
//---------------------------------------------------------------------------
///
struct ConnectThreeMenuDialog
{
  static const About GetAbout();
  static const std::string GetVersion();
  static const std::vector<std::string> GetVersionHistory();
};
//---------------------------------------------------------------------------
#endif // CONNECTTHREEMENUDIALOG_H
