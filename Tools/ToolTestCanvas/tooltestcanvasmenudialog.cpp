//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#include "tooltestcanvasmenudialog.h"

#include "canvas.h"
#include "trace.h"

const About ToolTestCanvasMenuDialog::GetAbout()
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

const std::string ToolTestCanvasMenuDialog::GetVersion()
{
  return "1.0";
}

const std::vector<std::string> ToolTestCanvasMenuDialog::GetVersionHistory()
{
  std::vector<std::string> v;
  v.push_back("2013-08-28: version 1.0: initial desktop version");
  return v;
}
