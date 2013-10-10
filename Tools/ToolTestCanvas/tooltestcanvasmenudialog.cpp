#include "tooltestcanvasmenudialog.h"

#include "canvas.h"
#include "trace.h"

const ribi::About ribi::ToolTestCanvasMenuDialog::GetAbout()
{
  About a(
    "Richel Bilderbeek",
    "ToolTestCanvas",
    "tests the Canvas class",
    "the 28th of August 2013",
    "2013",
    "http://www.richelbilderbeek.nl/ToolTestCanvas.htm",
    GetVersion(),
    GetVersionHistory());
  a.AddLibrary("Canvas version: " + Canvas::GetVersion());
  a.AddLibrary("Trace version: " + Trace::GetVersion());
  return a;
}

const std::string ribi::ToolTestCanvasMenuDialog::GetVersion()
{
  return "1.0";
}

const std::vector<std::string> ribi::ToolTestCanvasMenuDialog::GetVersionHistory()
{
  return {
    "2013-08-28: version 1.0: initial desktop version"
  };
}
