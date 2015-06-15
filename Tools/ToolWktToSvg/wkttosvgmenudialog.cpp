//---------------------------------------------------------------------------
/*
WktToSvg, tool to convert WKT to SVG
Copyright (C) 2014-2015 Richel Bilderbeek

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program. If not, see <http://www.gnu.org/licenses/>.
*/
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/ToolWktToSvg.htm
//---------------------------------------------------------------------------
#include "wkttosvgmenudialog.h"

#include <cassert>
#include <iostream>
#include <memory>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <boost/lexical_cast.hpp>

#include <QRegExp>

#include "fileio.h"
#include "richelbilderbeekprogram.h"
#include "testtimer.h"
#include "trace.h"
#include "wkttosvgmaindialog.h"
#pragma GCC diagnostic pop

ribi::WktToSvgMenuDialog::WktToSvgMenuDialog()
{
  #ifndef NDEBUG
  Test();
  #endif
}

int ribi::WktToSvgMenuDialog::ExecuteSpecific(const std::vector<std::string>& args) noexcept
{
  const int argc = static_cast<int>(args.size());

  //Verbosity
  bool verbose = false;
  if (std::count(args.begin(),args.end(),"-b") || std::count(args.begin(),args.end(),"--verbose"))
  {
    verbose = true;
    std::cout << "Verbose mode" << std::endl;
  }

  //WKT
  std::string wkt = "";
  for (int i=0; i!=argc-1; ++i)
  {
    if (args[i] == "-w" || args[i] == "--wkt" || args[i] == "--WKT")
    {
      wkt = args[i+1];
      break;
    }
  }
  if (wkt.empty())
  {
    std::cerr << "Please supply a WKT, e.g. 'POLYGON((1 1,1 -1,1 -1))" << std::endl;
    return 1;

  }
  if (verbose)
  {
    std::cout << "WKT: " << wkt << '\n';
  }

  //Stroke width
  double stroke_width = 1.0;
  for (int i=0; i!=argc-1; ++i)
  {
    if (args[i] == "-x" || args[i] == "--stroke_width")
    {
      try
      {
        stroke_width = boost::lexical_cast<double>(args[i+1]);
      }
      catch (boost::bad_lexical_cast&)
      {
        std::cerr
          << "You supplied a stroke width of '" << args[i+1] << "'\n"
          << "Please supply a value of stroke width, for example '1.0'" << std::endl
        ;
        return 1;
      }
      break;
    }
  }
  if (stroke_width <= 0.0)
  {
    std::cerr
      << "You supplied a stroke width of " << stroke_width << '\n'
      << "Please supply a positive value of stroke width" << std::endl;
    return 1;

  }
  if (verbose)
  {
    std::cout << "stroke_width: " << stroke_width << '\n';
  }

  //Silent
  bool silent = false;
  if (std::count(args.begin(),args.end(),"-s") || std::count(args.begin(),args.end(),"--silent"))
  {
    silent = true;
  }

  try
  {
    const WktToSvgMainDialog d(wkt,stroke_width);
    if (!silent)
    {
      std::cout << d.GetSvg() << std::endl;
    }
    return 0;
  }
  catch (std::exception& e)
  {
    std::cerr << "ERROR: Exception caught: " << e.what() << std::endl;
    return 1;
  }
  catch (...)
  {
    std::cerr << "ERROR: Unknown exception caught!" << std::endl;
    return 1;
  }
}

ribi::About ribi::WktToSvgMenuDialog::GetAbout() const noexcept
{
  
  About a(
    "Richel Bilderbeek",
    "WktToSvg",
    "tool to convert WKT to SVG",
    "the 12th of June 2014",
    "2014-2015",
    "http://www.richelbilderbeek.nl/ToolWktToSvg.htm",
    GetVersion(),
    GetVersionHistory()
  );
  a.AddLibrary("FileIo version: " + fileio::FileIo().GetVersion());
  return a;
}

ribi::Help ribi::WktToSvgMenuDialog::GetHelp() const noexcept
{
  return Help(
    this->GetAbout().GetFileTitle(),
    this->GetAbout().GetFileDescription(),
    {
      Help::Option('b',"verbose","generate more output"),
      Help::Option('s',"silent","no final output"),
      Help::Option('w',"wkt","the WTK string"),
      Help::Option('x',"stroke_width","the stroke width (1.0 by default)")
    },
    {
      GetAbout().GetFileTitle() + " --wtk POLYGON((1 1,-1 1,-1 -1,1 -1)) --verbose",
      GetAbout().GetFileTitle() + " -w POLYGON((0 1,-1 -1,1 -1)),LINESTRING((0 -1,-1 1,1 1)) -b",
      GetAbout().GetFileTitle() + " -w LINESTRING((0 -1,-1 1,1 1)) --stroke_width 0.1",
    }
  );
}

boost::shared_ptr<const ribi::Program> ribi::WktToSvgMenuDialog::GetProgram() const noexcept
{
  boost::shared_ptr<const ribi::Program> p {
    new ribi::ProgramWktToSvg
  };
  assert(p);
  return p;
}

std::string ribi::WktToSvgMenuDialog::GetVersion() const noexcept
{
  return "1.3";
}

std::vector<std::string> ribi::WktToSvgMenuDialog::GetVersionHistory() const noexcept
{
  return {
    "2014-06-10: version 1.0: initial version, supports polygon only",
    "2014-06-10: version 1.1: added support for linestring",
    "2014-06-12: version 1.2: added stroke_width parameter",
    "2014-06-12: version 1.3: removed verbose option in desktop version"
  };
}

#ifndef NDEBUG
void ribi::WktToSvgMenuDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  WktToSvgMenuDialog().GetAbout();
  WktToSvgMenuDialog().GetHelp();
  WktToSvgMainDialog("",1.0);
  const TestTimer test_timer(__func__,__FILE__,1.0);
  const bool verbose{false};
  if (verbose) { TRACE("Construction"); }
  {
    WktToSvgMenuDialog d;
  }
  if (verbose) { TRACE("Run with simple polygon"); }
  {
    WktToSvgMenuDialog().Execute(
      {
        "WktToSvgMenuDialog",
        "--wkt", "POLYGON((1 1,-1 1,-1 -1,1 -1))",
        "--silent"
        //"--verbose"
      }
    );
  }
  if (verbose) { TRACE("Run with simple linestring"); }
  {
    WktToSvgMenuDialog().Execute(
      {
        "WktToSvgMenuDialog",
        "--wkt", "LINESTRING(1 1,-1 1,-1 -1,1 -1)",
        "-s"
        //"--verbose"
      }
    );
  }
  if (verbose) { TRACE("Run with simple polygons"); }
  {
    WktToSvgMenuDialog().Execute(
      {
        "WktToSvgMenuDialog",
        "-w", "POLYGON((0 1,-1 -1,1 -1)),POLYGON((0 -1,-1 1,1 1))",
        "-s"
        //"-b"
      }
    );
  }
  if (verbose) { TRACE("Run with simple polygon and linestring"); }
  {
    WktToSvgMenuDialog().Execute(
      {
        "WktToSvgMenuDialog",
        "-w", "POLYGON((0 1,-1 -1,1 -1)),LINESTRING(0 -1,-1 1,1 1,0 -1)",
        "-s",
        //"-b",
        "-x", "3.1415926"
      }
    );
  }
}
#endif
