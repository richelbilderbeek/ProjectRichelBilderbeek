#ifndef VISUALABCMENUDIALOG_H
#define VISUALABCMENUDIALOG_H

#include <string>
#include <vector>

#include "about.h"

namespace ribi {

struct VisualAbcMenuDialog
{
  static const About GetAbout();
  static const std::string GetVersion();
  static const std::vector<std::string> GetVersionHistory();
};

} //~namespace ribi

#endif // VISUALABCMENUDIALOG_H
