#include "tooltestcanvasmenudialog.h"

#include <cassert>
#include <iostream>

#include "canvas.h"
#include "trace.h"

int ribi::ToolTestCanvasMenuDialog::ExecuteSpecific(const std::vector<std::string>& argv) noexcept
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

const ribi::About ribi::ToolTestCanvasMenuDialog::GetAbout() const noexcept
{
  About a(
    "Richel Bilderbeek",
    "ToolTestCanvas",
    "tests the Canvas class",
    "the 28th of August 2013",
    "2013",
    "http://www.richelbilderbeek.nl/ToolTestCanvas.htm",
    GetVersion(),
    GetVersionHistory());
  a.AddLibrary("Canvas version: " + Canvas::GetVersion());
  a.AddLibrary("Trace version: " + Trace::GetVersion());
  return a;
}

const ribi::Help ribi::ToolTestCanvasMenuDialog::GetHelp() const noexcept
{
  return Help(
    this->GetAbout().GetFileTitle(),
    this->GetAbout().GetFileDescription(),
    {

    },
    {

    }
  );
}

const boost::shared_ptr<const ribi::Program> ribi::ToolTestCanvasMenuDialog::GetProgram() const noexcept
{
  const boost::shared_ptr<const Program> p {
    new ProgramTestCanvas
  };
  assert(p);
  return p;
}

const std::string ribi::ToolTestCanvasMenuDialog::GetVersion() const noexcept
{
  return "1.1";
}

const std::vector<std::string> ribi::ToolTestCanvasMenuDialog::GetVersionHistory() const noexcept
{
  return {
    "2013-08-28: version 1.0: initial desktop version",
    "2013-11-05: version 1.1: conformized for ProjectRichelBilderbeekConsole"
  };
}
