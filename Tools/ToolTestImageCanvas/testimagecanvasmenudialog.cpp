#include "testimagecanvasmenudialog.h"

#include <cassert>
#include <fstream>
#include <iostream>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/lexical_cast.hpp>
#include <boost/scoped_ptr.hpp>
#include <QFile>

#include "fileio.h"
#include "imagecanvas.h"
#include "richelbilderbeekprogram.h"
#include "trace.h"
#include "testtimer.h"
#pragma GCC diagnostic pop

int ribi::TestImageCanvasMenuDialog::ExecuteSpecific(const std::vector<std::string>& argv) noexcept
{
  #ifndef NDEBUG
  Test();
  #endif
  const int argc = static_cast<int>(argv.size());
  if (argc != 3 || argc != 4)
  {
    std::cout << GetHelp() << '\n';
    return 1;
  }
  {
    const std::string s { argv[1] };
    if (!fileio::FileIo().IsRegularFile(s))
    {
      std::cout
        << "Error: '" << s << "' is not found.\n"
        << "Please supply an existing file as "
        << GetAbout().GetFileTitle()
        << " its first argument\n";
      return 1;
    }
  }
  if (argc == 4)
  {
    const std::string s { argv[3] };
    try
    {
      const int n_cols = boost::lexical_cast<int>(s);
      if (n_cols < 5)
      {
        std::cout
          << "Error: the number of columns must be at least 5.\n"
          << "Please supply a number above 5 as "
          << GetAbout().GetFileTitle()
          << " its third argument\n";
        return 1;
      }
    }
    catch (boost::bad_lexical_cast&)
    {
      std::cout
        << "Error: '" << s << "' is not an integer number.\n"
        << "Please supply a number as"
        << GetAbout().GetFileTitle()
        << " AsciiArter its third argument\n";
      return 1;

    }
  }

  assert(argc >= 3);
  const std::string from_name { argv[1] };
  std::string to_name { argv[2] };
  const int n_cols = (argc == 4 ? boost::lexical_cast<int>(argv[3]) : 78);

  const boost::shared_ptr<const ImageCanvas> d {
    new ImageCanvas(from_name,n_cols)
  };
  //const std::vector<std::string> v { d.GetAsciiArt() };
  std::ofstream f(to_name.c_str());
  f << (*d);
  //std::copy(v.begin(),v.end(),std::ostream_iterator<std::string>(f,"\n"));
  return 0;
}

ribi::About ribi::TestImageCanvasMenuDialog::GetAbout() const noexcept
{
  About a(
    "Richel Bilderbeek",
    "TestImageCanvas",
    "tests the ImageCanvas class",
    "the 9th of January 2014",
    "2014-2015",
    "http://www.richelbilderbeek.nl/TooTestImageCanvas.htm",
    GetVersion(),
    GetVersionHistory());
  a.AddLibrary("Canvas version: " + Canvas::GetVersion());
  a.AddLibrary("ImageCanvas version: " + ImageCanvas::GetVersion());
  a.AddLibrary("Trace version: " + Trace::GetVersion());
  return a;
}

ribi::Help ribi::TestImageCanvasMenuDialog::GetHelp() const noexcept
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

boost::shared_ptr<const ribi::Program> ribi::TestImageCanvasMenuDialog::GetProgram() const noexcept
{
  const boost::shared_ptr<const Program> p {
    new ProgramTestImageCanvas
  };
  assert(p);
  return p;
}

std::string ribi::TestImageCanvasMenuDialog::GetVersion() const noexcept
{
  return "1.0";
}

std::vector<std::string> ribi::TestImageCanvasMenuDialog::GetVersionHistory() const noexcept
{
  return {
    "2014-01-09: version 1.0: initial version"
  };
}

#ifndef NDEBUG
void ribi::TestImageCanvasMenuDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
  {
    const std::string temp_filename { fileio::FileIo().GetTempFileName() };
    {
      const std::string resource_filename { ":/CppImageCanvas/images/R.png" };
      QFile qfile(resource_filename.c_str());
      qfile.copy(temp_filename.c_str());
      if (!fileio::FileIo().IsRegularFile(temp_filename))
      {
        TRACE("ERROR");
        TRACE(resource_filename);
        TRACE("Resource filename must exist");
      }
    }
    assert(fileio::FileIo().IsRegularFile(temp_filename));
    for (int i=0; i!=4; ++i)
    {
      const CanvasColorSystem color_system
        = i / 2 ? CanvasColorSystem::invert : CanvasColorSystem::normal;
      const CanvasCoordinatSystem coordinat_system
        = i % 2 ? CanvasCoordinatSystem::graph : CanvasCoordinatSystem::screen;
      const boost::shared_ptr<const ImageCanvas> c {
        new ImageCanvas(temp_filename,20,color_system,coordinat_system)
      };
      std::stringstream s;
      s << (*c);
      TRACE(s.str());
      assert(!s.str().empty());
    }
    fileio::FileIo().DeleteFile(temp_filename);
  }
}
#endif
