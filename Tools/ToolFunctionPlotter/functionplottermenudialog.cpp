#include "functionplottermenudialog.h"
#include "profile.h"

const ribi::About ribi::FunctionPlotterMenuDialog::GetAbout()
{
  About a(
    "Richel Bilderbeek",
    "FunctionPlotter",
    "plots a function",
    "the 5th of December 2013",
    "2013",
    "http://www.richelbilderbeek.nl/FunctionPlotter.htm",
    GetVersion(),
    GetVersionHistory());
  //a.AddLibrary("Rectangle version: " + Rect::GetVersion());

  a.AddLibrary("Warp's FunctionParser version: 4.4.3");
  return a;
}

const std::string ribi::FunctionPlotterMenuDialog::GetVersion()
{
  return "2.0";
}

const std::vector<std::string> ribi::FunctionPlotterMenuDialog::GetVersionHistory()
{
  return {
    "2010-xx-xx: version 1.0: initial Windows-only version",
    "2010-xx-xx: version 1.1: added integration",
    "2013-12-05: version 2.0: port to Qt"
  };
}

