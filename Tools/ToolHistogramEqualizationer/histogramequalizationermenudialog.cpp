#include "histogramequalizationermenudialog.h"

#include <cassert>
#include <iostream>

#include "gaborfilter.h"
#include "gaborfilterwidget.h"

int ribi::HistogramEqualizationerMenuDialog::ExecuteSpecific(const std::vector<std::string>& argv) noexcept
{
  const int argc = static_cast<int>(argv.size());
  if (argc == 1)
  {
    std::cout << GetHelp() << '\n';
    return 1;
  }
  GaborFilterWidget w;
  std::cout << w << '\n';
  return 0;
}

const ribi::About ribi::HistogramEqualizationerMenuDialog::GetAbout() const noexcept
{
  About a(
    "Richel Bilderbeek",
    "GaborFilter",
    "tool to demonstrate Gabor filtering",
    "the 7th of July 2012",
    "2012",
    "http://www.richelbilderbeek.nl/HistogramEqualizationer.htm",
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
    "2010-xx-xx: version 1.0: initial Windows-only version",
    "2012-07-07: version 2.0: port to Qt"
  };
}
