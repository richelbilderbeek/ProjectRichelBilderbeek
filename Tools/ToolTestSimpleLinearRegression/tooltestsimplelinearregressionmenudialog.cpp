//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#include "tooltestsimplelinearregressionmenudialog.h"

#include "trace.h"

const About ToolTestSimpleLinearRegressionMenuDialog::GetAbout()
{
  About a(
    "Richel Bilderbeek",
    "ToolTestSimpleLinearRegression",
    "tests a simple linear regression",
    "the 27nd of August 2013",
    "2013",
    "http://www.richelbilderbeek.nl/ToolTestSimpleLinearRegression.htm",
    GetVersion(),
    GetVersionHistory());
  a.AddLibrary("Trace version: " + Trace::GetVersion());
  return a;
}

const std::string ToolTestSimpleLinearRegressionMenuDialog::GetVersion()
{
  return "1.0";
}

const std::vector<std::string> ToolTestSimpleLinearRegressionMenuDialog::GetVersionHistory()
{
  std::vector<std::string> v;
  v.push_back("2013-08-27: version 1.0: initial version");
  return v;
}
