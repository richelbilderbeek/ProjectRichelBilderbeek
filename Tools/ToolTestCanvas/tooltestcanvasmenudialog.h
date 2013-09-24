#ifndef TOOLTESTCANVASMENUDIALOG_H
#define TOOLTESTCANVASMENUDIALOG_H

#include <string>
#include <vector>

#include "about.h"

namespace ribi {

///GUI independent ToolTestCanvas menu dialog
struct ToolTestCanvasMenuDialog
{
  static const About GetAbout();
  static const std::string GetVersion();
  static const std::vector<std::string> GetVersionHistory();
};

} //~namespace ribi

#endif // TOOLTESTCANVASMENUDIALOG_H
