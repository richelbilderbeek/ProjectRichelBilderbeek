#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif

//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#include "testqtroundededitrectitemmenudialog.h"

#include "trace.h"

const About TestQtRoundedEditRectItemMenuDialog::GetAbout()
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

const std::string TestQtRoundedEditRectItemMenuDialog::GetVersion()
{
  return "1.1";
}

const std::vector<std::string> TestQtRoundedEditRectItemMenuDialog::GetVersionHistory()
{
  std::vector<std::string> v;
  v.push_back("2012-12-21: version 1.0: initial version");
  v.push_back("2012-12-31: version 1.1: added menu");
  return v;
}

