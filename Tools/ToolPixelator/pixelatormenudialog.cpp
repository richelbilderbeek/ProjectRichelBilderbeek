#include "pixelatormenudialog.h"

#include <cassert>
#include <iostream>

#include "trace.h"

int ribi::PixelatorMenuDialog::ExecuteSpecific(const std::vector<std::string>& argv) noexcept
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
  return 0;
}

const ribi::About ribi::PixelatorMenuDialog::GetAbout() const noexcept
{
  About a(
    "Richel Bilderbeek",
    "Pixelator",
    "tool to pixelate image",
    "the 28th of November 2013",
    "2008-2014",
    "http://www.richelbilderbeek.nl/ToolPixelator.htm",
    GetVersion(),
    GetVersionHistory());
  //a.AddLibrary("ProFile version: " + QtCreatorProFile::GetVersion());
  return a;
}

const ribi::Help ribi::PixelatorMenuDialog::GetHelp() const noexcept
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

const boost::shared_ptr<const ribi::Program> ribi::PixelatorMenuDialog::GetProgram() const noexcept
{
  boost::shared_ptr<const ribi::Program> p {
    new ribi::ProgramPixelator
  };
  assert(p);
  return p;
}

const std::string ribi::PixelatorMenuDialog::GetVersion() const noexcept
{
  return "2.0";
}

const std::vector<std::string> ribi::PixelatorMenuDialog::GetVersionHistory() const noexcept
{
  return {
    "2008-03-01: version 1.0: initial Windows-only version",
    "2013-11-28: version 2.0: port to Qt"
  };
}

#ifndef NDEBUG
void ribi::PixelatorMenuDialog::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting ribi::PixelatorMenuDialog::Test");
  TRACE("Finished ribi::PixelatorMenuDialog::Test successfully");
}
#endif
