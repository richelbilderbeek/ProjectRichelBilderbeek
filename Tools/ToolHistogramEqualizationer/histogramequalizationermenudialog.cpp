#include "histogramequalizationermenudialog.h"

#include <cassert>
#include <iostream>

int ribi::HistogramEqualizationerMenuDialog::ExecuteSpecific(const std::vector<std::string>& argv) noexcept
{
  const int argc = static_cast<int>(argv.size());
  if (argc == 1)
  {
    std::cout << GetHelp() << '\n';
    return 1;
  }
  assert(!"TODO");
  return 1;
}

const ribi::About ribi::HistogramEqualizationerMenuDialog::GetAbout() const noexcept
{
  About a(
    "Richel Bilderbeek",
    "HistogramEqualization",
    "tool to perform a histogram equalization",
    "the 28th of November 2013",
    "2008-2013",
    "http://www.richelbilderbeek.nl/ToolHistogramEqualizationer.htm",
    GetVersion(),
    GetVersionHistory());
  //a.AddLibrary("ProFile version: " + QtCreatorProFile::GetVersion());
  return a;
}

const ribi::Help ribi::HistogramEqualizationerMenuDialog::GetHelp() const noexcept
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

const boost::shared_ptr<const ribi::Program> ribi::HistogramEqualizationerMenuDialog::GetProgram() const noexcept
{
  boost::shared_ptr<const ribi::Program> p {
    new ribi::ProgramGaborFilter
  };
  assert(p);
  return p;
}

const std::string ribi::HistogramEqualizationerMenuDialog::GetVersion() const noexcept
{
  return "2.0";
}

const std::vector<std::string> ribi::HistogramEqualizationerMenuDialog::GetVersionHistory() const noexcept
{
  return {
    "2008-07-11: version 1.0: initial Windows-only version",
    "2013-11-28: version 2.0: port to Qt"
  };
}
