#include "secretmessagemenudialog.h"
#include "trace.h"
//---------------------------------------------------------------------------
namespace SecretMessage {
//---------------------------------------------------------------------------
const About MenuDialog::GetAbout()
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
//---------------------------------------------------------------------------
const std::string MenuDialog::GetVersion()
{
  return "2.0";
}
//---------------------------------------------------------------------------
const std::vector<std::string> MenuDialog::GetVersionHistory()
{
  std::vector<std::string> v;
  v.push_back("2009-01-11: version 1.0: initial Windows-only version");
  return v;
}
//---------------------------------------------------------------------------
} //~namespace SecretMessage
//---------------------------------------------------------------------------
