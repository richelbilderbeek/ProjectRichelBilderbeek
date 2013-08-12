#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorUnableToFindNumericLiteralOperatorOperatorQ.htm
#if !(__GNUC__ >= 4 && __GNUC_MINOR__ >= 8)
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif
#endif

//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#include "k3opeenrijmenudialog.h"


#include "connectthree.h"
#include "connectthreewidget.h"

#include <cassert>

const About K3OpEenRijMenuDialog::GetAbout()
{
  About a(
    "Richel Bilderbeek",
    "K3OpEenRij",
    "connect-three game",
    "the 6th of August 2013",
    "2007-2013",
    "http://www.richelbilderbeek.nl/GameK3OpEenRij.htm",
    GetVersion(),
    GetVersionHistory());
  a.AddLibrary("ConnectThree version: " + ConnectThree::GetVersion());
  a.AddLibrary("ConnectThreeWidget version: " + ConnectThreeWidget::GetVersion());
  a.AddLibrary("Special thanks to Mark Wiering for his excellent bug reports");
  return a;
}

const std::string K3OpEenRijMenuDialog::GetVersion()
{
  return "6.0";
}

const std::vector<std::string> K3OpEenRijMenuDialog::GetVersionHistory()
{
  std::vector<std::string> v;

  v.push_back("2007-01-03: version 3.0: initial C++ Builder verion, ");
  v.push_back("2009-12-31: version 4.0: replaced Kathleen by Josje, game arena always visible, made screens smaller, removed useless JPEGs");
  v.push_back("2013-08-06: version 5.0: port to Qt Creator");
  v.push_back("2013-08-06: version 5.1: allow selection of both Kathleen and Josje");
  v.push_back("2013-08-09: version 6.0: implemented suggestions and bugfixes from Mark Wiering's report");
  return v;
}
