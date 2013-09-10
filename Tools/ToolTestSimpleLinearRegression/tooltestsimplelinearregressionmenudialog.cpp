#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "tooltestsimplelinearregressionmenudialog.h"

#include "trace.h"
#pragma GCC diagnostic pop

const ribi::About ribi::ToolTestSimpleLinearRegressionMenuDialog::GetAbout()
{
  About a(
    "Richel Bilderbeek",
    "ToolTestSimpleLinearRegression",
    "tests a simple linear regression",
    "the 28th of August 2013",
    "2013",
    "http://www.richelbilderbeek.nl/ToolTestSimpleLinearRegression.htm",
    GetVersion(),
    GetVersionHistory());
  a.AddLibrary("Trace version: " + Trace::GetVersion());
  return a;
}

const std::string ribi::ToolTestSimpleLinearRegressionMenuDialog::GetVersion()
{
  return "1.1";
}

const std::vector<std::string> ribi::ToolTestSimpleLinearRegressionMenuDialog::GetVersionHistory()
{
  return {
    "2013-08-27: version 1.0: initial version",
    "2013-08-28: version 1.1: isolated and templated SimpleLinearRegression class"
  };
}
