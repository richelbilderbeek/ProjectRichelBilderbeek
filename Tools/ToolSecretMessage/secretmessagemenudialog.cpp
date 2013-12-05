#include "secretmessagemenudialog.h"
#include "trace.h"

const ribi::About ribi::SecretMessage::MenuDialog::GetAbout() const noexcept
{
  About a(
    "Richel Bilderbeek",
    "SecretMessage",
    "tool to add secret messages to images",
    "the 3rd of August 2012",
    "2009-2012",
    "http://www.richelbilderbeek.nl/ToolSecretMessage.htm",
    GetVersion(),
    GetVersionHistory());
  //a.AddLibrary("ProFile version: " + ProFile::GetVersion());
  a.AddLibrary("Trace version: " + Trace::GetVersion());
  return a;
}

const std::string ribi::SecretMessage::MenuDialog::GetVersion() const noexcept
{
  return "2.0";
}

const std::vector<std::string> ribi::SecretMessage::MenuDialog::GetVersionHistory() const noexcept
{
  return {
    "2009-01-11: version 1.0: initial Windows-only version",
    "2012-08-03: version 2.0: port to Qt Creator"
  };
}
