#include "k3opeenrijmenudialog.h"

#include <cassert>

#include "connectthree.h"
#include "connectthreewidget.h"

const ribi::About ribi::K3OpEenRijMenuDialog::GetAbout()
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

const std::string ribi::K3OpEenRijMenuDialog::GetVersion()
{
  return "6.0";
}

const std::vector<std::string> ribi::K3OpEenRijMenuDialog::GetVersionHistory()
{
  const std::vector<std::string> v {
    "2007-01-03: version 3.0: initial C++ Builder verion",
    "2009-12-31: version 4.0: replaced Kathleen by Josje, game arena always visible, made screens smaller, removed useless JPEGs",
    "2013-08-06: version 5.0: port to Qt Creator",
    "2013-08-06: version 5.1: allow selection of both Kathleen and Josje",
    "2013-08-09: version 6.0: implemented suggestions and bugfixes from Mark Wiering's report"
  };
  return v;
}
