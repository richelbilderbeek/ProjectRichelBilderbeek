//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#include "testqtroundedrectitemmenudialog.h"

#include "trace.h"

const About TestQtRoundedRectItemMenuDialog::GetAbout()
{
  About a(
    "Richel Bilderbeek",
    "TestQtRoundedRectItem",
    "tests QtRoundedRectItemt",
    "the 20th of May 2013",
    "2012-2013",
    "http://www.richelbilderbeek.nl/ToolTestQtRoundedRectItem.htm",
    GetVersion(),
    GetVersionHistory());
  //a.AddLibrary("ProFile version: " + ProFile::GetVersion());
  a.AddLibrary("Trace version: " + Trace::GetVersion());
  return a;
}

const std::string TestQtRoundedRectItemMenuDialog::GetVersion()
{
  return "1.1";
}

const std::vector<std::string> TestQtRoundedRectItemMenuDialog::GetVersionHistory()
{
  std::vector<std::string> v;
  v.push_back("2012-12-21: version 1.0: initial version");
  v.push_back("2012-05-20: version 1.1: added menu");
  return v;
}

