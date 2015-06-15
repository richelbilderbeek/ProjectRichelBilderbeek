#include "imagerotatermenudialog.h"

#include <cassert>
#include <iostream>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/math/constants/constants.hpp>

#include <QFile>

#include "fileio.h"
#include "imagecanvas.h"
#include "imagerotatermaindialog.h"
#include "richelbilderbeekprogram.h"
#include "testtimer.h"
#include "trace.h"
#pragma GCC diagnostic pop

int ribi::ImageRotaterMenuDialog::ExecuteSpecific(const std::vector<std::string>& argv) noexcept
{
  #ifndef NDEBUG
  Test();
  #endif
  const int argc = static_cast<int>(argv.size());
  if (argc != 5
    || argv[1] == argv[3]
    || (argv[1] != "-f" && argv[1] != "--filename" && argv[1] != "-r" && argv[1] != "--rotation")
    || (argv[3] != "-f" && argv[3] != "--filename" && argv[3] != "-r" && argv[3] != "--rotation")
  )
  {
    std::cout << GetHelp() << '\n';
    return 1;
  }

  std::string filename;
  if (argv[1] == "-f" || argv[1] == "--filename") filename = argv[2];
  if (argv[3] == "-f" || argv[3] == "--filename") filename = argv[4];
  if (!fileio::FileIo().IsRegularFile(filename))
  {
    std::cout << "Please supply the filename of an existing file" << std::endl;
    return 1;
  }
  std::string angle_str;
  if (argv[1] == "-r" || argv[1] == "--rotation") angle_str = argv[2];
  if (argv[3] == "-r" || argv[3] == "--rotation") angle_str = argv[4];
  double angle = 0.0;
  try
  {
    angle = boost::lexical_cast<double>(angle_str);
  }
  catch (boost::bad_lexical_cast&)
  {
    std::cout << "Please supply a number for the rotation" << std::endl;
    return 1;
  }
  const double pi = boost::math::constants::pi<double>();

  const QImage source(filename.c_str());
  assert(!source.isNull());
  QImage target(source);
  assert(!target.isNull());

  ImageRotaterMainDialog::Rotate(source,target,pi * angle / 180.0);

  const std::string target_filename = fileio::FileIo().GetTempFileName(".png");
  target.save(target_filename.c_str());

  const boost::shared_ptr<ImageCanvas> canvas {
    new ImageCanvas(target_filename,40) //,CanvasColorSystem::invert)
  };
  std::cout << (*canvas) << std::endl;
  return 0;
}

ribi::About ribi::ImageRotaterMenuDialog::GetAbout() const noexcept
{
  About a(
    "Richel Bilderbeek",
    "ImageRotater",
    "tool to rotate images",
    "the 6th of February 2014",
    "2007-2015",
    "http://www.richelbilderbeek.nl/ToolImageRotater.htm",
    GetVersion(),
    GetVersionHistory()
  );
  a.AddLibrary("Canvas version: " + Canvas::GetVersion());
  a.AddLibrary("ImageCanvas version: " + ImageCanvas::GetVersion());
  a.AddLibrary("TestTimer version: " + TestTimer::GetVersion());
  a.AddLibrary("Trace version: " + Trace::GetVersion());
  return a;
}

ribi::Help ribi::ImageRotaterMenuDialog::GetHelp() const noexcept
{
  return ribi::Help(
    GetAbout().GetFileTitle(),
    GetAbout().GetFileDescription(),
    {
      Help::Option('f',"filename","Image filename"),
      Help::Option('r',"rotation","Rotation angle in degrees")
    },
    {
      GetAbout().GetFileTitle() + " -f MyFile.png -r 45",
      GetAbout().GetFileTitle() + " --filename MyFile.png --rotation 135"
    }
  );
}

boost::shared_ptr<const ribi::Program> ribi::ImageRotaterMenuDialog::GetProgram() const noexcept
{
  boost::shared_ptr<const ribi::Program> p {
    new ribi::ProgramImageRotater
  };
  assert(p);
  return p;
}

std::string ribi::ImageRotaterMenuDialog::GetVersion() const noexcept
{
  return "2.1";
}

std::vector<std::string> ribi::ImageRotaterMenuDialog::GetVersionHistory() const noexcept
{
  return {
    "2007-xx-xx: version 1.0: initial Windows-only version",
    "2013-11-29: version 2.0: port to Qt",
    "2014-02-06: version 2.1: added command-line version"
  };
}

#ifndef NDEBUG
void ribi::ImageRotaterMenuDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  fileio::FileIo();

  const TestTimer test_timer(__func__,__FILE__,1.0);
  ImageRotaterMenuDialog d;
  const std::string filename { fileio::FileIo().GetTempFileName(".png") };
  QFile file(":/imagerotater/images/R.png");
  file.copy(filename.c_str());
  d.Execute( { "ImageRotaterMenuDialog", "-f", filename, "-r", "30.0" } );
  fileio::FileIo().DeleteFile(filename);
}
#endif
