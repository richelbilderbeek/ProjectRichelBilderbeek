#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "tooltestapproximatormenudialog.h"

#include "approximator.h"
#include "trace.h"

#pragma GCC diagnostic pop

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
  return {
    "2013-08-28: version 1.0: initial version",
    "2013-09-05: version 1.1: transition to namespace ribi"
  };
}
