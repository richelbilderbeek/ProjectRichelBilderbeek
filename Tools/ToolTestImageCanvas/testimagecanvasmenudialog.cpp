#include "testimagecanvasmenudialog.h"

#include <cassert>
#include <iostream>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <QFile>

#include "fileio.h"
#include "imagecanvas.h"
#include "trace.h"
#pragma GCC diagnostic pop

int ribi::TestImageCanvasMenuDialog::ExecuteSpecific(const std::vector<std::string>& argv) noexcept
{
  #ifndef NDEBUG
  Test();
  #endif
  const int argc = static_cast<int>(argv.size());
  if (argc != 1)
  {
    std::cout << GetHelp() << '\n';
    return 1;
  }
  /*
  //Specify the dimensions of the canvas equal to the screen
  //Coordinat (0,0) is the top-left coordinat
  //Coordinat (79,23) is the bottom-right coordinat
  const int maxx = 79;
  const int maxy = 23;

  for (int i=0; i!=4; ++i)
  {
    const ribi::Canvas::ColorSystem color_system
      = i % 2 ? ribi::Canvas::ColorSystem::normal : ribi::Canvas::ColorSystem::invert;
    const ribi::Canvas::CoordinatSystem coordinat_system
      = i / 2 ? ribi::Canvas::CoordinatSystem::graph : ribi::Canvas::CoordinatSystem::screen;
    ImageCanvas c( maxx, maxy, coordinat_system);
    std::cout << c;
    std::cout << std::endl;
  }
  */
  return 0;
}

const ribi::About ribi::TestImageCanvasMenuDialog::GetAbout() const noexcept
{
  About a(
    "Richel Bilderbeek",
    "TestImageCanvas",
    "tests the ImageCanvas class",
    "the 9th of January 2014",
    "2014-2014",
    "http://www.richelbilderbeek.nl/TooTestImageCanvas.htm",
    GetVersion(),
    GetVersionHistory());
  a.AddLibrary("ImageCanvas version: " + ImageCanvas::GetVersion());
  a.AddLibrary("Trace version: " + Trace::GetVersion());
  return a;
}

const ribi::Help ribi::TestImageCanvasMenuDialog::GetHelp() const noexcept
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

const boost::shared_ptr<const ribi::Program> ribi::TestImageCanvasMenuDialog::GetProgram() const noexcept
{
  const boost::shared_ptr<const Program> p {
    new ProgramTestImageCanvas
  };
  assert(p);
  return p;
}

const std::string ribi::TestImageCanvasMenuDialog::GetVersion() const noexcept
{
  return "1.0";
}

const std::vector<std::string> ribi::TestImageCanvasMenuDialog::GetVersionHistory() const noexcept
{
  return {
    "2014-01-09: version 1.0: initial version"
  };
}

#ifndef NDEBUG
void ribi::TestImageCanvasMenuDialog::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting ribi::TooTestImageCanvasMenuDialog::Test");
  {
    const std::string temp_filename { fileio::GetTempFileName() };
    {
      const std::string resource_filename { ":/CppImageCanvas/images/R.png" };
      QFile qfile(resource_filename.c_str());
      qfile.copy(temp_filename.c_str());
      if (!fileio::IsRegularFile(temp_filename))
      {
        TRACE("ERROR");
        TRACE(resource_filename);
        TRACE("Resource filename must exist");
      }
    }
    assert(fileio::IsRegularFile(temp_filename));
    for (int i=0; i!=4; ++i)
    {
      const CanvasColorSystem color_system
        = i / 2 ? CanvasColorSystem::invert : CanvasColorSystem::normal;
      const CanvasCoordinatSystem coordinat_system
        = i % 2 ? CanvasCoordinatSystem::graph : CanvasCoordinatSystem::screen;
      ImageCanvas c(temp_filename,20,color_system,coordinat_system);
      std::stringstream s;
      s << c;
      assert(!s.str().empty());
    }
    fileio::DeleteFile(temp_filename);
  }
  TRACE("Finished ribi::TooTestImageCanvasMenuDialog::Test successfully");
}
#endif
