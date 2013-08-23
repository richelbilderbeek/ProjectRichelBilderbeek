#ifndef TOOLTESTMULTIAPPROXIMATORMENUDIALOG_H
#define TOOLTESTMULTIAPPROXIMATORMENUDIALOG_H

#include <string>
#include <vector>

#include "about.h"

///GUI independent ToolTestMultiApproximator menu dialog
struct ToolTestMultiApproximatorMenuDialog
{
  static const About GetAbout();
  static const std::string GetVersion();
  static const std::vector<std::string> GetVersionHistory();
};

#endif // TOOLTESTMULTIAPPROXIMATORMENUDIALOG_H
