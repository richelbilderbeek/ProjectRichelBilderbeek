//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#include "tooltestmultiapproximatormenudialog.h"

#include "approximator.h"
#include "multiapproximator.h"
#include "trace.h"

const About ToolTestMultiApproximatorMenuDialog::GetAbout()
{
  About a(
    "Richel Bilderbeek",
    "ToolTestMultiApproximator",
    "tests the MultiApproximator class",
    "the 23rd of August 2013",
    "2013",
    "http://www.richelbilderbeek.nl/ToolTestMultiApproximator.htm",
    GetVersion(),
    GetVersionHistory());
  a.AddLibrary("Approximator version: " + Approximator<>::GetVersion());
  a.AddLibrary("MultiApproximator version: " + MultiApproximator<>::GetVersion());
  a.AddLibrary("Trace version: " + Trace::GetVersion());
  return a;
}

const std::string ToolTestMultiApproximatorMenuDialog::GetVersion()
{
  return "1.0";
}

const std::vector<std::string> ToolTestMultiApproximatorMenuDialog::GetVersionHistory()
{
  std::vector<std::string> v;
  v.push_back("2013-08-23: version 1.0: initial version");
  return v;
}
