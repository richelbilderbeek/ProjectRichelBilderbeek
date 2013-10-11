#include "toolprimeexpertmenudialog.h"
#include "trace.h"

const ribi::About ribi::PrimeExpertMenuDialog::GetAbout()
{
  About a(
    "Richel Bilderbeek",
    "PrimeExpert",
    "solver of quadratic equations",
    "the 11th of Oktober 2013",
    "2008-2013",
    "http://www.richelbilderbeek.nl/ToolPrimeExpert.htm",
    GetVersion(),
    GetVersionHistory());
  a.AddLibrary("Trace version: " + Trace::GetVersion());
  return a;
}

const std::string ribi::PrimeExpertMenuDialog::GetVersion()
{
  return "2.1";
}

const std::vector<std::string> ribi::PrimeExpertMenuDialog::GetVersionHistory()
{
  return {
    "2008-07-12: Version 1.0: initial version in C++ Builder",
    "2011-02-26: Version 2.0: port to Qt Creator",
    "2013-10-11: Version 2.1: conformized for ProjectRichelBilderbeek"
  };
}
