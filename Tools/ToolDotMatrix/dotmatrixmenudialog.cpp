#include "dotmatrixmenudialog.h"

#include <cassert>
#include <iostream>
#include <iterator>
#include <sstream>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/shared_ptr.hpp>
#include <boost/lexical_cast.hpp>

#include <QImage>

#include "dotmatrixstring.h"
#include "fileio.h"
#include "testtimer.h"
#include "richelbilderbeekprogram.h"
#include "trace.h"
#pragma GCC diagnostic pop


int ribi::DotMatrixMenuDialog::ExecuteSpecific(const std::vector<std::string>& argv) noexcept
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
  std::string text = "";
  for (int i=0; i!=argc-1; ++i) //-1 because next argument will be used
  {
    if (argv[i] == "-t" || argv[i] == "--text")
    {
      text = argv[i + 1];
      break;
    }
  }
  if (text.empty())
  {
    std::cout
      << "Please supply a text and supply it correctly,\n"
      << "for example:\n"
      << "  DotMatrix -t my_text\n";
    return 1;
  }
  int spacing = 1;
  for (int i=0; i!=argc-1; ++i) //-1 because next argument will be used
  {
    if (argv[i] == "-s" || argv[i] == "--spacing")
    {
      const std::string s = argv[i + 1];
      try
      {
        spacing = boost::lexical_cast<int>(s);
        if (spacing < 0)
        {
          std::cout << "Spacing must be zero or a positive number\n";
          return 1;
        }
      }
      catch (boost::bad_lexical_cast&)
      {
        std::cout << "Spacing must be a number\n";
        return 1;
      }
      break;
    }
  }
  std::string filename = "";
  for (int i=0; i!=argc-1; ++i) //-1 because next argument will be used
  {
    if (argv[i] == "-f" || argv[i] == "--filename")
    {
      filename = argv[i + 1];
      break;
    }
  }

  const boost::shared_ptr<const ribi::DotMatrixString> m {
    new ribi::DotMatrixString(text,spacing)
  };

  if (!filename.empty())
  {
    m->CreateImage()->save(filename.c_str());
  }

  std::cout << *m << '\n';

  return 0;
}

ribi::About ribi::DotMatrixMenuDialog::GetAbout() const noexcept
{
  About a(
    "Richel Bilderbeek",
    "DotMatrix",
    "generates a dot matrix font",
    "the 11th of October 2013",
    "2013-2014",
    "http://www.richelbilderbeek.nl/ToolDotMatrix.htm",
    GetVersion(),
    GetVersionHistory());
  //a.AddLibrary("Canvas version: " + Canvas::GetVersion());
  a.AddLibrary("Trace version: " + Trace::GetVersion());
  return a;
}

ribi::Help ribi::DotMatrixMenuDialog::GetHelp() const noexcept
{
  return ribi::Help(
    GetAbout().GetFileTitle(),
    GetAbout().GetFileDescription(),
    {
      Help::Option('f',"filename","Save the text to an image file"),
      Help::Option('t',"text","The text to convert to file or ASCII art"),
      Help::Option('s',"spacing","Set the spacing in pixels, default: 1"),
    },
    {
      "DotMatrix -t \"Hello world\"",
      "DotMatrix --text \"Hello world\" -s 0",
      "DotMatrix -t \"Hello world\" -f myfile.png",
      "DotMatrix -t \"Hello world\" --filename myfile.png --spacing 0",
    }
  );
}

boost::shared_ptr<const ribi::Program> ribi::DotMatrixMenuDialog::GetProgram() const noexcept
{
  const boost::shared_ptr<const ribi::Program> p(new ProgramDotMatrix);
  assert(p);
  return p;
}

std::string ribi::DotMatrixMenuDialog::GetVersion() const noexcept
{
  return "2.2";
}

std::vector<std::string> ribi::DotMatrixMenuDialog::GetVersionHistory() const noexcept
{
  return {
    "2009-xx-xx: version 1.0: initial VCL desktop version",
    "2013-10-11: version 2.0: port to Qt",
    "2013-11-01: version 2.1: improved console version"
    "2014-02-10: version 2.2: added multi-line version"
  };
}

#ifndef NDEBUG
void ribi::DotMatrixMenuDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);

  //Command line tests
  {
    DotMatrixMenuDialog d;
    const std::string filename { fileio::FileIo().GetTempFileName(".png") };
    d.Execute( { "DotMatrix", "-t", "\"Hello world\"" } );
    d.Execute( { "DotMatrix", "--text", "\"Hello world\"", "-s", "0" } );

    assert(!fileio::FileIo().IsRegularFile(filename));
    d.Execute( { "DotMatrix", "-t", "\"Hello world\"", "-f", filename } );
    assert(fileio::FileIo().IsRegularFile(filename));

    fileio::FileIo().DeleteFile(filename);

    assert(!fileio::FileIo().IsRegularFile(filename));
    d.Execute( { "DotMatrix", "--text", "\"Hello world\"", "-f", filename, "--spacing", "1" } );
    assert(fileio::FileIo().IsRegularFile(filename));

    fileio::FileIo().DeleteFile(filename);
  }
}
#endif
