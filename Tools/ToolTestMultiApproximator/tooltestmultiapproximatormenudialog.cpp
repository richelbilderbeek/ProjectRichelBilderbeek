#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "tooltestmultiapproximatormenudialog.h"

#include "approximator.h"
#include "multiapproximator.h"
#include "trace.h"

#pragma GCC diagnostic pop

const ribi::About ribi::ToolTestMultiApproximatorMenuDialog::GetAbout()
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

const std::string ribi::ToolTestMultiApproximatorMenuDialog::GetVersion()
{
  return "1.1";
}

const std::vector<std::string> ribi::ToolTestMultiApproximatorMenuDialog::GetVersionHistory()
{
  return {
    "2013-08-23: version 1.0: initial version",
    "2013-08-23: version 1.1: display conversion from MultiApproximator to Approximator"
  };
}
