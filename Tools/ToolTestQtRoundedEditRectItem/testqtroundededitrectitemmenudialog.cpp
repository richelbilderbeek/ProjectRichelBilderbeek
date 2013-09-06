

#include "testqtroundededitrectitemmenudialog.h"

#include "trace.h"

const ribi::About ribi::TestQtRoundedEditRectItemMenuDialog::GetAbout()
{
  About a(
    "Richel Bilderbeek",
    "TestQtRoundedEditRectItemWidget",
    "tests QtRoundedEditRectItemWidget",
    "the 31st of December 2012",
    "2012",
    "http://www.richelbilderbeek.nl/ToolTestQtRoundedEditRectItemWidget.htm",
    GetVersion(),
    GetVersionHistory());
  //a.AddLibrary("ProFile version: " + ProFile::GetVersion());
  a.AddLibrary("Trace version: " + Trace::GetVersion());
  return a;
}

const std::string ribi::TestQtRoundedEditRectItemMenuDialog::GetVersion()
{
  return "1.1";
}

const std::vector<std::string> ribi::TestQtRoundedEditRectItemMenuDialog::GetVersionHistory()
{
  std::vector<std::string> v;
  v.push_back("2012-12-21: version 1.0: initial version");
  v.push_back("2012-12-31: version 1.1: added menu");
  return v;
}

