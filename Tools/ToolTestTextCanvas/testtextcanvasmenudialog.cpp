#include "testtextcanvasmenudialog.h"

#include <cassert>
#include <iostream>

#include "fileio.h"
#include "richelbilderbeekprogram.h"
#include "testtimer.h"
#include "textcanvas.h"
#include "trace.h"

ribi::TestTextCanvasMenuDialog::TestTextCanvasMenuDialog()
{
  #ifndef NDEBUG
  Test();
  #endif
}

int ribi::TestTextCanvasMenuDialog::ExecuteSpecific(const std::vector<std::string>& argv) noexcept
{
  const int argc = static_cast<int>(argv.size());
  if (argc != 1)
  {
    std::cout << GetHelp() << '\n';
    return 1;
  }
  //Specify the dimensions of the canvas equal to the screen
  //Coordinat (0,0) is the top-left coordinat
  //Coordinat (79,23) is the bottom-right coordinat
  const int maxx = 69;
  const int maxy = 13;

  for (int i=0; i!=2; ++i)
  {
    const CanvasCoordinatSystem coordinat_system
      = i % 2 ? CanvasCoordinatSystem::graph : CanvasCoordinatSystem::screen;
    TextCanvas c(maxx, maxy, coordinat_system);
    for (int j=0; j!=400; ++j)
    {
      const int x = -maxx + (std::rand() % (2 * maxx));
      const int y = -maxy + (std::rand() % (2 * maxy));
      const std::string s = fileio::FileIo().GetTempFileName();
      c.PutText(x,y,s);
    }
    std::cout << c;
    std::cout << std::endl;
    std::cout << std::endl;
  }
  return 0;
}

ribi::About ribi::TestTextCanvasMenuDialog::GetAbout() const noexcept
{
  About a(
    "Richel Bilderbeek",
    "TestTextCanvas",
    "tests the TextCanvas class",
    "the 9th of January 2014",
    "2014-2015",
    "http://www.richelbilderbeek.nl/ToolTestTextCanvas.htm",
    GetVersion(),
    GetVersionHistory());
  a.AddLibrary("TextCanvas version: " + TextCanvas::GetVersion());
  a.AddLibrary("Trace version: " + Trace::GetVersion());
  return a;
}

ribi::Help ribi::TestTextCanvasMenuDialog::GetHelp() const noexcept
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

boost::shared_ptr<const ribi::Program> ribi::TestTextCanvasMenuDialog::GetProgram() const noexcept
{
  const boost::shared_ptr<const Program> p {
    new ProgramTestTextCanvas
  };
  assert(p);
  return p;
}

std::string ribi::TestTextCanvasMenuDialog::GetVersion() const noexcept
{
  return "1.0";
}

std::vector<std::string> ribi::TestTextCanvasMenuDialog::GetVersionHistory() const noexcept
{
  return {
    "2014-01-09: version 1.0: initial version"
  };
}

#ifndef NDEBUG
void ribi::TestTextCanvasMenuDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  ribi::TextCanvas();
  const TestTimer test_timer(__func__,__FILE__,1.0);
}
#endif
