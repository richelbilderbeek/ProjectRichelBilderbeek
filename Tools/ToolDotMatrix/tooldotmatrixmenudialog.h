#ifndef TOOLDOTMATRIXMENUDIALOG_H
#define TOOLDOTMATRIXMENUDIALOG_H

#include <string>
#include <vector>

#include "about.h"

namespace ribi {

///GUI independent ToolDotMatrix menu dialog
struct ToolDotMatrixMenuDialog
{
  static const About GetAbout();
  static const std::string GetVersion();
  static const std::vector<std::string> GetVersionHistory();
};

} //~namespace ribi

#endif // TOOLDOTMATRIXMENUDIALOG_H
