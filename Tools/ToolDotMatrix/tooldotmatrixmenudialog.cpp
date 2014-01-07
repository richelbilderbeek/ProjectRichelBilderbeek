#include "tooldotmatrixmenudialog.h"

#include <cassert>
#include <iostream>
#include <iterator>
#include <sstream>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/shared_ptr.hpp>
#include <boost/lexical_cast.hpp>
#include "dotmatrixstring.h"
#include "trace.h"
#pragma GCC diagnostic pop


int ribi::ToolDotMatrixMenuDialog::ExecuteSpecific(const std::vector<std::string>& argv) noexcept
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
    if (argv[i] == std::string("-t") || argv[i] == std::string("--text"))
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
    if (argv[i] == std::string("-s") || argv[i] == std::string("--spacing"))
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

  const boost::shared_ptr<const ribi::DotMatrixString> m {
    new ribi::DotMatrixString(text,spacing)
  };
  std::cout << *m << '\n';
  return 0;
}

const ribi::About ribi::ToolDotMatrixMenuDialog::GetAbout() const noexcept
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

const ribi::Help ribi::ToolDotMatrixMenuDialog::GetHelp() const noexcept
{
  return ribi::Help(
    this->GetAbout().GetFileTitle(),
    this->GetAbout().GetFileDescription(),
    {
      //Options
      Help::Option('t',"text","Convert a text to dot matrix ASCII art"),
      Help::Option('s',"spacing","Set the spacing in pixels, default: 1")
    },
    {
      //Example uses
      "DotMatrix -t \"Hello world\""
      "DotMatrix --text \"Hello world\" -s 0"
    }
  );
}

const boost::shared_ptr<const ribi::Program> ribi::ToolDotMatrixMenuDialog::GetProgram() const noexcept
{
  const boost::shared_ptr<const ribi::Program> p(new ProgramDotMatrix);
  assert(p);
  return p;
}

const std::string ribi::ToolDotMatrixMenuDialog::GetVersion() const noexcept
{
  return "2.1";
}

const std::vector<std::string> ribi::ToolDotMatrixMenuDialog::GetVersionHistory() const noexcept
{
  return {
    "2009-xx-xx: version 1.0: initial VCL desktop version",
    "2013-10-11: version 2.0: port to Qt",
    "2013-11-01: version 2.1: improved console version"
  };
}

#ifndef NDEBUG
void ribi::ToolDotMatrixMenuDialog::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting ribi::ToolDotMatrixMenuDialog::Test");
  const std::string text = "Hello world";
  const int spacing = 1;
  const boost::shared_ptr<const ribi::DotMatrixString> m {
    new ribi::DotMatrixString(text,spacing)
  };
  std::stringstream s;
  s << *m;
  assert(!s.str().empty());
  TRACE("Finished ribi::ToolDotMatrixMenuDialog::Test successfully");
}
#endif
