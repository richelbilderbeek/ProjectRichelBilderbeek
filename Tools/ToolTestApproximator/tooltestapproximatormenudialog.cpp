//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#include "tooltestapproximatormenudialog.h"

#include "approximator.h"
#include "trace.h"

const ribi::About ribi::ToolTestApproximatorMenuDialog::GetAbout()
{
  About a(
    "Richel Bilderbeek",
    "ToolTestApproximator",
    "tests the Approximator class",
    "the 28th of August 2013",
    "2013",
    "http://www.richelbilderbeek.nl/ToolTestApproximator.htm",
    GetVersion(),
    GetVersionHistory());
  a.AddLibrary("Approximator version: " + Approximator<>::GetVersion());
  a.AddLibrary("Trace version: " + Trace::GetVersion());
  return a;
}

const std::string ribi::ToolTestApproximatorMenuDialog::GetVersion()
{
  return "1.1";
}

const std::vector<std::string> ribi::ToolTestApproximatorMenuDialog::GetVersionHistory()
{
  const std::vector<std::string> v {
    "2013-08-28: version 1.0: initial version",
    "2013-09-05: version 1.1: transition to namespace ribi"
  };

  return v;
}
