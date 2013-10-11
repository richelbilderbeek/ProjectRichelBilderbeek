#ifndef TOOLPRIMEEXPERTMENUDIALOG_H
#define TOOLPRIMEEXPERTMENUDIALOG_H

#include <string>
#include <vector>

#include "about.h"

namespace ribi {

///GUI independent PrimeExpert menu dialog
struct PrimeExpertMenuDialog
{
  static const About GetAbout();
  static const std::string GetVersion();
  static const std::vector<std::string> GetVersionHistory();
};

} //~namespace ribi

#endif // TOOLPRIMEEXPERTMENUDIALOG_H
