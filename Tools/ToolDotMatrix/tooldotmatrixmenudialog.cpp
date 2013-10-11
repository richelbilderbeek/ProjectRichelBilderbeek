#include "tooldotmatrixmenudialog.h"

#include "trace.h"

const ribi::About ribi::ToolDotMatrixMenuDialog::GetAbout()
{
  About a(
    "Richel Bilderbeek",
    "DotMatrix",
    "generates a dot matrix font",
    "the 11th of October 2013",
    "2013",
    "http://www.richelbilderbeek.nl/ToolDotMatrix.htm",
    GetVersion(),
    GetVersionHistory());
  //a.AddLibrary("Canvas version: " + Canvas::GetVersion());
  a.AddLibrary("Trace version: " + Trace::GetVersion());
  return a;
}

const std::string ribi::ToolDotMatrixMenuDialog::GetVersion()
{
  return "2.0";
}

const std::vector<std::string> ribi::ToolDotMatrixMenuDialog::GetVersionHistory()
{
  return {
    "2009-xx-xx: version 1.0: initial VCL desktop version",
    "2013-10-11: version 2.0: port to Qt"
  };
}
