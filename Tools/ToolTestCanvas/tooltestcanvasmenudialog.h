#ifndef TOOLTESTCANVASMENUDIALOG_H
#define TOOLTESTCANVASMENUDIALOG_H

#include <string>
#include <vector>

#include "about.h"

///GUI independent ToolTestCanvas menu dialog
struct ToolTestCanvasMenuDialog
{
  static const About GetAbout();
  static const std::string GetVersion();
  static const std::vector<std::string> GetVersionHistory();
};

#endif // TOOLTESTCANVASMENUDIALOG_H
