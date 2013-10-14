#ifndef TOOLVISUALABCMENUDIALOG_H
#define TOOLVISUALABCMENUDIALOG_H

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

#endif // TOOLVISUALABCMENUDIALOG_H
