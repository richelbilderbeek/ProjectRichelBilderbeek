#include "valentinecarddecryptermenudialog.h"

#include <cassert>
#include <iostream>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/math/constants/constants.hpp>

#include <QFile>

#include "fileio.h"
//#include "imagecanvas.h"
#include "valentinecarddecryptermaindialog.h"
#include "trace.h"
#pragma GCC diagnostic pop

int ribi::ValentineCardDecrypterMenuDialog::ExecuteSpecific(const std::vector<std::string>& argv) noexcept
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
  if (!fileio::IsRegularFile(filename))
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

  std::cout << (*canvas) << std::endl;
  return 0;
}

const ribi::About ribi::ValentineCardDecrypterMenuDialog::GetAbout() const noexcept
{
  About a(
    "Richel Bilderbeek",
    "ValentineCardDecrypter",
    "tool to decrypt a valentine card",
    "the 18th of February 2014",
    "2014",
    "http://www.richelbilderbeek.nl/ToolValentineCardDecrypter.htm",
    GetVersion(),
    GetVersionHistory());
  a.AddLibrary("Canvas version: " + Canvas::GetVersion());
  a.AddLibrary("ImageCanvas version: " + ImageCanvas::GetVersion());
  return a;
}

const ribi::Help ribi::ValentineCardDecrypterMenuDialog::GetHelp() const noexcept
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

const boost::shared_ptr<const ribi::Program> ribi::ValentineCardDecrypterMenuDialog::GetProgram() const noexcept
{
  boost::shared_ptr<const ribi::Program> p {
    new ribi::ProgramValentineCardDecrypter
  };
  assert(p);
  return p;
}

const std::string ribi::ValentineCardDecrypterMenuDialog::GetVersion() const noexcept
{
  return "1.0";
}

const std::vector<std::string> ribi::ValentineCardDecrypterMenuDialog::GetVersionHistory() const noexcept
{
  return {
    "2014-02-18: version 1.0: initial version"
  };
}

#ifndef NDEBUG
void ribi::ValentineCardDecrypterMenuDialog::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting ribi::ValentineCardDecrypterMenuDialog::Test");
  //ValentineCardDecrypterMenuDialog d;
  TRACE("Finished ribi::ValentineCardDecrypterMenuDialog::Test successfully");
}
#endif
