#ifndef TOOLTESTAPPROXIMATORMENUDIALOG_H
#define TOOLTESTAPPROXIMATORMENUDIALOG_H

#include <string>
#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "about.h"
#pragma GCC diagnostic pop

namespace ribi {

///GUI independent ToolTestSimpleLinearRegression menu dialog
struct ToolTestSimpleLinearRegressionMenuDialog
{
  static const About GetAbout();
  static const std::string GetVersion();
  static const std::vector<std::string> GetVersionHistory();
};

} //~namespace ribi

#endif // TOOLTESTAPPROXIMATORMENUDIALOG_H
