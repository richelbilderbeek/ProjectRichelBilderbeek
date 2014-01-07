#include "imagerotatermenudialog.h"

#include <cassert>
#include <iostream>

#include "trace.h"

int ribi::ImageRotaterMenuDialog::ExecuteSpecific(const std::vector<std::string>& argv) noexcept
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

const ribi::About ribi::ImageRotaterMenuDialog::GetAbout() const noexcept
{
  About a(
    "Richel Bilderbeek",
    "ImageRotater",
    "tool to rotate images",
    "the 29th of November 2013",
    "2007-2014",
    "http://www.richelbilderbeek.nl/Toolimagerotater.htm",
    GetVersion(),
    GetVersionHistory());
  //a.AddLibrary("ProFile version: " + QtCreatorProFile::GetVersion());
  return a;
}

const ribi::Help ribi::ImageRotaterMenuDialog::GetHelp() const noexcept
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

const boost::shared_ptr<const ribi::Program> ribi::ImageRotaterMenuDialog::GetProgram() const noexcept
{
  boost::shared_ptr<const ribi::Program> p {
    new ribi::ProgramImageRotater
  };
  assert(p);
  return p;
}

const std::string ribi::ImageRotaterMenuDialog::GetVersion() const noexcept
{
  return "2.0";
}

const std::vector<std::string> ribi::ImageRotaterMenuDialog::GetVersionHistory() const noexcept
{
  return {
    "2007-xx-xx: version 1.0: initial Windows-only version",
    "2013-11-29: version 2.0: port to Qt"
  };
}

#ifndef NDEBUG
void ribi::ImageRotaterMenuDialog::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting ribi::ImageRotaterMenuDialog::Test");
  TRACE("Finished ribi::ImageRotaterMenuDialog::Test successfully");
}
#endif
