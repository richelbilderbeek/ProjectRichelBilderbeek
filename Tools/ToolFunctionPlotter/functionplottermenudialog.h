#ifndef FUNCTIONPLOTTERMENUDIALOG_H
#define FUNCTIONPLOTTERMENUDIALOG_H

#include <string>
#include <vector>

#include "about.h"

namespace ribi {

///GUI independent SurfacePlotter menu dialog
struct FunctionPlotterMenuDialog
{
  static const About GetAbout();
  static const std::string GetVersion();
  static const std::vector<std::string> GetVersionHistory();
};

} //namespace ribi

#endif // FUNCTIONPLOTTERMENUDIALOG_H
