#include "toolmultiencrangermenudialog.h"
#include "loopreader.h"
#include "encranger.h"

const ribi::About ribi::ToolMultiEncrangerMenuDialog::GetAbout() noexcept
{
  About a(
    "Richel Bilderbeek",
    "ToolMultiEncranger",
    "multi-line Encranger encryption",
    "the 30th of September 2013",
    "?-2013",
    "http://www.richelbilderbeek.nl/ToolMultiEncranger.htm",
    GetVersion(),
    GetVersionHistory());
  a.AddLibrary("Encranger version: " + Encranger::GetVersion());
  a.AddLibrary("LoopReader version: " + LoopReader<int>::GetVersion());
  return a;
}

const std::string ribi::ToolMultiEncrangerMenuDialog::GetVersion() noexcept
{
  return "2.0";
}

const std::vector<std::string> ribi::ToolMultiEncrangerMenuDialog::GetVersionHistory() noexcept
{
  return {
    "20xx-xx-xx: Version 1.0: initial version programmed in C++ Builder",
    "2013-09-30: Version 2.0: port to Qt Creator, renamed application to ToolMultiEncranger"
  };
}
