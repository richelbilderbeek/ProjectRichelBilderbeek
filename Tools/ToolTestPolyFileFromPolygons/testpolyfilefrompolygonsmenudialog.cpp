//---------------------------------------------------------------------------
/*
TestPolyFileFromPolygons, tests the PolyFileFromPolygons class
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
//From http://www.richelbilderbeek.nl/ToolTestPolyFileFromPolygons.htm
//---------------------------------------------------------------------------
#include "testpolyfilefrompolygonsmenudialog.h"

#include <cassert>
#include <iostream>
#include <memory>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <boost/lexical_cast.hpp>
#include <boost/units/io.hpp>

#include "ribi_regex.h"
#include "container.h"
#include "fileio.h"
#include "geometry.h"
#include "richelbilderbeekprogram.h"
#include "trace.h"
#include "testtimer.h"
#include "plane.h"
#include "polyfile.h"
#include "polyfilefrompolygons.h"
#include "testpolyfilefrompolygonsmaindialog.h"
#pragma GCC diagnostic pop

ribi::TestPolyFileFromPolygonsMenuDialog::TestPolyFileFromPolygonsMenuDialog()
{
  #ifndef NDEBUG
  Test();
  #endif
}
int ribi::TestPolyFileFromPolygonsMenuDialog::ExecuteSpecific(const std::vector<std::string>& args) noexcept
{
  bool silent{false};
  if (std::count(args.begin(),args.end(),"-s") || std::count(args.begin(),args.end(),"--silent"))
  {
    silent = true;
  }

  typedef boost::geometry::model::d2::point_xy<double> Coordinat;
  typedef boost::geometry::model::polygon<Coordinat> Polygon;

  const int argc = static_cast<int>(args.size());

  //Verbosity
  bool verbose = false;
  if (std::count(args.begin(),args.end(),"-b") || std::count(args.begin(),args.end(),"--verbose"))
  {
    verbose = true;
    if (!silent) { std::cout << "Verbose mode" << std::endl; }
  }

  //Polygons
  if (!std::count(args.begin(),args.end(),"-p")
    && !std::count(args.begin(),args.end(),"--polygon")
    && !std::count(args.begin(),args.end(),"--polygons")
  )
  {
    if (!silent) { std::cerr << "Parameter for polygons missing" << '\n'; }
    return 1;
  }

  std::vector<Polygon> polygons;
  for (int i=0; i!=argc-1; ++i)
  {
    if (args[i] == "-p" || args[i] == "--polygon" || args[i] == "--polygons")
    {
      const std::string text = args[i+1];
      if (verbose) { std::cout << "Parsing polygons '" << text << "'" << std::endl; }
      const auto regex = Regex().GetRegexPolygon();
      const auto lines = Regex().GetRegexMatches(text,regex);
      for (const std::string& line: lines)
      {
        if (verbose) { std::cout << "Parsing polygon '" << line << "'" << std::endl; }
        Polygon polygon;
        try
        {
          boost::geometry::read_wkt(line,polygon);
          polygons.push_back(polygon);
        }
        catch (boost::geometry::read_wkt_exception& e)
        {
          //No problem
        }
      }
    }
  }
  if (polygons.empty())
  {
    if (!silent) { std::cerr << "Please supply a value for polygon, e.g. 'POLYGON((1 1,1 -1,1 -1))" << std::endl; }
    return 1;

  }
  if (verbose)
  {
    if (!silent) {
      std::cout << "Number of polygons: " << polygons.size() << std::endl
        << "Polygons (as SVG text): " << Geometry().ToSvg(polygons) << std::endl;
    }
  }

  try
  {
    const TestPolyFileFromPolygonsMainDialog d(polygons);
    if (!silent) {std::cout << d << std::endl;}
    return 0;
  }
  catch (std::exception& e)
  {
    if (!silent) { std::cerr << "ERROR: Exception caught: " << e.what() << std::endl; }
    return 1;
  }
  catch (...)
  {
    if (!silent) { std::cerr << "ERROR: Unknown exception caught!" << std::endl; }
    return 1;
  }
}

ribi::About ribi::TestPolyFileFromPolygonsMenuDialog::GetAbout() const noexcept
{
  
  About a(
    "Richel Bilderbeek",
    "TestPolyFileFromPolygons",
    "tests the PolyFileFromPolygons class",
    "the 12th of June 2014",
    "2014-2015",
    "http://www.richelbilderbeek.nl/ToolTestPolyFileFromPolygons.htm",
    GetVersion(),
    GetVersionHistory()
  );
  a.AddLibrary("Container version: " + Container().GetVersion());
  a.AddLibrary("FileIo version: " + fileio::FileIo().GetVersion());
  a.AddLibrary("Geometry version: " + Geometry().GetVersion());
  a.AddLibrary("Plane version: " + Plane::GetVersion());
  a.AddLibrary("PolyFile version: " + PolyFile::GetVersion());
  a.AddLibrary("PolyFileFromPolygons version: " + PolyFileFromPolygons::GetVersion());
  return a;
}

ribi::Help ribi::TestPolyFileFromPolygonsMenuDialog::GetHelp() const noexcept
{
  return Help(
    this->GetAbout().GetFileTitle(),
    this->GetAbout().GetFileDescription(),
    {
      Help::Option('b',"verbose","generate more output"),
      Help::Option('p',"polygons","the shapes used as a base"),
      Help::Option('s',"silent","produce no output")
    },
    {
      GetAbout().GetFileTitle() + " --polygons POLYGON((1 1,-1 1,-1 -1,1 -1)) --verbose",
      GetAbout().GetFileTitle() + " -p POLYGON((0 1,-1 -1,1 -1)),POLYGON((0 -1,-1 1,1 1)) -b",
    }
  );
}

boost::shared_ptr<const ribi::Program> ribi::TestPolyFileFromPolygonsMenuDialog::GetProgram() const noexcept
{
  boost::shared_ptr<const ribi::Program> p {
    new ribi::ProgramTestPolyFileFromPolygons
  };
  assert(p);
  return p;
}


std::string ribi::TestPolyFileFromPolygonsMenuDialog::GetVersion() const noexcept
{
  return "1.2";
}

std::vector<std::string> ribi::TestPolyFileFromPolygonsMenuDialog::GetVersionHistory() const noexcept
{
  return {
    "2014-06-02: version 1.0: initial version, supported polygons only",
    "2014-06-12: version 1.1: added support for linestring",
    "2014-08-08: version 1.2: added silent flag to console version"
  };
}

#ifndef NDEBUG
void ribi::TestPolyFileFromPolygonsMenuDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  {
    Container();
    fileio::FileIo();
    boost::shared_ptr<Plane> plane{
      new Plane(
        Plane::Coordinat3D(1.0,0.0,0.0),
        Plane::Coordinat3D(0.0,1.0,0.0),
        Plane::Coordinat3D(0.0,0.0,1.0)
      )
    };
    TestPolyFileFromPolygonsMainDialog( {} );
  }
  const bool verbose{false};
  const TestTimer test_timer(__func__,__FILE__,1.0);
  {
    TestPolyFileFromPolygonsMenuDialog d;
    if (verbose) { TRACE("Create triangle with long notation"); }
    d.Execute(
      {
        "TestPolyFileFromPolygonsMenuDialog",
        "--polygons",
        "POLYGON((0 0,0 1,1 0))",
        "--silent"
      }
    );
    if (verbose) { TRACE("Create two triangles with short notation"); }
    d.Execute(
      {
        "TestPolyFileFromPolygonsMenuDialog",
        "-p",
        "POLYGON((0 0,0 1,1 0)),POLYGON((1 1,1 2,2 1))",
        "--silent"
      }
    );
  }
}
#endif
