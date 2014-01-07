#include "secretmessagemenudialog.h"

#include <cassert>
#include <iostream>

#include "trace.h"

int ribi::SecretMessage::MenuDialog::ExecuteSpecific(const std::vector<std::string>& argv) noexcept
{
  #ifndef NDEBUG
  Test();
  #endif
  const int argc = static_cast<int>(argv.size());
  if (argc == 1)
  {
    std::cout << GetHelp() << '\n';
    return 1;
  }
  assert(!"TODO");
  return 1;
}

const ribi::About ribi::SecretMessage::MenuDialog::GetAbout() const noexcept
{
  About a(
    "Richel Bilderbeek",
    "SecretMessage",
    "tool to add secret messages to images",
    "the 3rd of August 2012",
    "2009-2014",
    "http://www.richelbilderbeek.nl/ToolSecretMessage.htm",
    GetVersion(),
    GetVersionHistory());
  //a.AddLibrary("ProFile version: " + ProFile::GetVersion());
  a.AddLibrary("Trace version: " + Trace::GetVersion());
  return a;
}

const ribi::Help ribi::SecretMessage::MenuDialog::GetHelp() const noexcept
{
  return ribi::Help(
    this->GetAbout().GetFileTitle(),
    this->GetAbout().GetFileDescription(),
    {

    },
    {

    }
  );
}

const boost::shared_ptr<const ribi::Program> ribi::SecretMessage::MenuDialog::GetProgram() const noexcept
{
  boost::shared_ptr<const ribi::Program> p {
    new ribi::ProgramSecretMessage
  };
  assert(p);
  return p;
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

#ifndef NDEBUG
void ribi::SecretMessage::MenuDialog::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting ribi::SecretMessage::MenuDialog::Test");
  TRACE("Finished ribi::SecretMessage::MenuDialog::Test successfully");
}
#endif
