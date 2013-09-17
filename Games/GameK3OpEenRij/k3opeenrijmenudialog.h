#ifndef K3OPEENRIJMENUDIALOG_H
#define K3OPEENRIJMENUDIALOG_H

#include <string>
#include <vector>
#include "about.h"

namespace ribi {

///
struct K3OpEenRijMenuDialog
{
  static const About GetAbout();
  static const std::string GetVersion();
  static const std::vector<std::string> GetVersionHistory();
};

} //~namespace ribi

#endif // K3OPEENRIJMENUDIALOG_H
