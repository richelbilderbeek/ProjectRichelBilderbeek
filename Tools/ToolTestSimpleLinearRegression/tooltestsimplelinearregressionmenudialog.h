#ifndef TOOLTESTAPPROXIMATORMENUDIALOG_H
#define TOOLTESTAPPROXIMATORMENUDIALOG_H

#include <string>
#include <vector>

#include "about.h"

///GUI independent ToolTestSimpleLinearRegression menu dialog
struct ToolTestSimpleLinearRegressionMenuDialog
{
  static const About GetAbout();
  static const std::string GetVersion();
  static const std::vector<std::string> GetVersionHistory();
};

#endif // TOOLTESTAPPROXIMATORMENUDIALOG_H
