#ifndef TOOLTESTMULTIAPPROXIMATORMENUDIALOG_H
#define TOOLTESTMULTIAPPROXIMATORMENUDIALOG_H

#include <string>
#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "about.h"
#pragma GCC diagnostic pop


namespace ribi {

///GUI independent ToolTestMultiApproximator menu dialog
struct ToolTestMultiApproximatorMenuDialog
{
  static const About GetAbout();
  static const std::string GetVersion();
  static const std::vector<std::string> GetVersionHistory();
};

} //~namespace ribi

#endif // TOOLTESTMULTIAPPROXIMATORMENUDIALOG_H
