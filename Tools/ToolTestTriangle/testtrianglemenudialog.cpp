//---------------------------------------------------------------------------
/*
TestTriangle, compare Triangle to its C++ equivalent
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
//From http://www.richelbilderbeek.nl/ToolTestTriangle.htm
//---------------------------------------------------------------------------
#include "testtrianglemenudialog.h"

#include <cassert>
#include <iostream>
#include <memory>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <boost/lexical_cast.hpp>
#include <boost/timer.hpp>
#include <boost/units/io.hpp>

//#include <QRegExp>

#include "container.h"
#include "fileio.h"
#include "testtimer.h"
#include "geometry.h"
#include "plane.h"
#include "polyfile.h"
#include "ribi_regex.h"
#include "polyfilefrompolygons.h"
#include "richelbilderbeekprogram.h"
#include "trace.h"
#include "trianglefile.h"
#include "testtrianglemaindialog.h"
#include "trianglemeshdialog.h"
#pragma GCC diagnostic pop

ribi::TestTriangleMenuDialog::TestTriangleMenuDialog()
{
  #ifndef NDEBUG
  Test();
  #endif
}

int ribi::TestTriangleMenuDialog::ExecuteSpecific(const std::vector<std::string>& args) noexcept
{
  typedef boost::geometry::model::d2::point_xy<double> Coordinat;
  typedef boost::geometry::model::linestring<Coordinat> Linestring;
  typedef boost::geometry::model::polygon<Coordinat> Polygon;
  typedef std::vector<Linestring> Linestrings;
  typedef std::vector<Polygon> Polygons;
  typedef boost::units::quantity<boost::units::si::plane_angle> Angle;
  typedef boost::units::quantity<boost::units::si::area> Area;
  typedef std::pair<Polygons,Linestrings> Shapes;
  using boost::units::si::square_meter;
  using boost::units::si::radian;

  const int argc = static_cast<int>(args.size());

  bool silent{false};
  if (std::count(args.begin(),args.end(),"-s") || std::count(args.begin(),args.end(),"--silent"))
  {
    silent = true;
  }
  //Verbosity
  bool verbose = false;

  if (std::count(args.begin(),args.end(),"-b") || std::count(args.begin(),args.end(),"--verbose"))
  {
    if (!silent)
    {
      verbose = true;
      std::cout << "Verbose mode" << std::endl;
    }
  }

  //Do profile
  bool do_profile = false;
  if (std::count(args.begin(),args.end(),"-p") || std::count(args.begin(),args.end(),"--profile"))
  {
    do_profile = true;
  }
  if (verbose)
  {
    std::cout << "Show profiler info: " << (do_profile ? "Yes" : "No") << std::endl;
  }

  //Triangle area
  if (!std::count(args.begin(),args.end(),"-r")
    && !std::count(args.begin(),args.end(),"--triangle_area")
    && !std::count(args.begin(),args.end(),"--triangle_max_area")
  )
  {
    if (!silent) { std::cerr << "Parameter for Triangle area missing" << '\n'; }
    return 1;
  }
  Area triangle_max_area = 0.0 * square_meter;
  for (int i=0; i!=argc-1; ++i)
  {
    if (args[i] == "-r" || args[i] == "--triangle_area" || args[i] == "--triangle_max_area")
    {
      try
      {
        triangle_max_area = boost::lexical_cast<double>(args[i+1])* square_meter;
      }
      catch (boost::bad_lexical_cast&)
      {
        if (!silent) { std::cerr << "Please supply a value for Triangle max area" << std::endl; }
        return 1;
      }
    }
  }
  if (triangle_max_area <= 0.0 * square_meter)
  {
    if (!silent) { std::cerr << "Please supply a positive non-zero value for the Triangle max area" << std::endl; }
    return 1;
  }
  if (verbose)
  {
    std::cout << "Triangle max area: " << triangle_max_area << std::endl;
  }

  //Triangle quality
  if ( !std::count(args.begin(),args.end(),"-q")
    && !std::count(args.begin(),args.end(),"--triangle_quality")
    && !std::count(args.begin(),args.end(),"--triangle_min_angle")
  )
  {
    if (!silent) { std::cerr << "Parameter for Triangle quality (a minimum angle) missing" << '\n'; }
    return 1;
  }
  Angle triangle_min_angle = 0.0 * radian;
  for (int i=0; i!=argc-1; ++i)
  {
    if (args[i] == "-q" || args[i] == "--triangle_quality" || args[i] == "--triangle_min_angle")
    {
      try
      {
        triangle_min_angle
          = boost::lexical_cast<double>(args[i+1]) //Degrees
          * (boost::math::constants::two_pi<double>() / 360.0) //Degrees to radian
          * radian
        ;
      }
      catch (boost::bad_lexical_cast&)
      {
        if (!silent) { std::cerr << "Please supply a value for Triangle quality (a minimum angle)" << std::endl; }
        return 1;
      }
    }
  }
  if (triangle_min_angle <= 0.0 * radian )
  {
    if (!silent) { std::cerr << "Please supply a positive non-zero value for the Triangle quality (a minimum angle)" << std::endl; }
    return 1;
  }
  if (triangle_min_angle >= (boost::math::constants::two_pi<double>() / 3.0) * radian )
  {
    if (!silent)
    {
      std::cerr
        << "Please supply a value less than 60 degrees for the Triangle quality (a minimum angle):"
        << "A triangle cannot have three corners each of at least 60 degrees"
        << std::endl;
    }
    return 1;
  }
  if (verbose)
  {
    std::cout << "Triangle quality (minimum angle): " << triangle_min_angle << std::endl;
  }

  //WKT
  Shapes shapes;
  if (!std::count(args.begin(),args.end(),"-w")
    && !std::count(args.begin(),args.end(),"--wkt")
    && !std::count(args.begin(),args.end(),"--WKT")
  )
  {
    if (!silent) { std::cerr << "Parameter for WKT missing" << '\n'; }
    return 1;
  }

  for (int i=0; i!=argc-1; ++i)
  {
    if (args[i] == "-w" || args[i] == "--wkt" || args[i] == "--WKT")
    {
      const std::string text = args[i+1];
      if (verbose) { std::cout << "Parsing WKT '" << text << "'" << std::endl; }
      shapes = Geometry().WktToShapes(text);
    }
  }
  if (shapes.first.empty() && shapes.second.empty())
  {
    if (!silent)
    {
      std::cerr << "No shapes found, please suppy a WKT with at least one shape, e.g. 'POLYGON((1 1,1 -1,1 -1))" << std::endl;
    }
    return 1;

  }
  if (verbose)
  {
    std::cout
      << "Number of polygons: " << shapes.first.size() << '\n'
      << "Number of linestrings: " << shapes.second.size() << '\n'
      << "Shapes (as SVG text): " << Geometry().ToSvg(shapes) << '\n'
    ;
  }

  try
  {
    boost::timer timer;

    trim::Dialog d;
    d.SetShapes(shapes);
    d.SetTriangleParameters(triangle_min_angle,triangle_max_area,verbose);
    d.CreateTriangleMesh();
    std::cout << std::endl; //Because Triangle does not do an endl itself

    if(do_profile)
    {
      const double t_secs = timer.elapsed();
      const int n_triangle_output_eles = Container().Count(d.GetTriangleOutputEle(),'\n');
      const int n_triangle_output_nodes = Container().Count(d.GetTriangleOutputNode(),'\n');
      const int n_triangle_output_polys = Container().Count(d.GetTriangleOutputPoly(),'\n');
      if (!silent)
      {
        std::cout
          << t_secs << " "
          << n_triangle_output_eles << " "
          << n_triangle_output_nodes << " "
          << n_triangle_output_polys << " "
          #ifndef NDEBUG
          << "Debug"
          #else
          << "Release"
          #endif
          << std::endl
        ;
      }
    }

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

ribi::About ribi::TestTriangleMenuDialog::GetAbout() const noexcept
{
  
  About a(
    "Richel Bilderbeek",
    "TestTriangle",
    "compare Triangle to its C++ equivalent",
    "the 8th of August 2014",
    "2014-2015",
    "http://www.richelbilderbeek.nl/ToolTestTriangle.htm",
    GetVersion(),
    GetVersionHistory()
  );
  a.AddLibrary("Container version: " + Container().GetVersion());
  a.AddLibrary("FileIo version: " + fileio::FileIo().GetVersion());
  a.AddLibrary("Geometry version: " + Geometry().GetVersion());
  a.AddLibrary("Plane version: " + Plane::GetVersion());
  a.AddLibrary("PolyFile version: " + PolyFile::GetVersion());
  a.AddLibrary("PolyFileFromPolygons version: " + PolyFileFromPolygons::GetVersion());
  a.AddLibrary("ribi::Regex version: " + ribi::Regex::GetVersion());
  a.AddLibrary("Triangle version 1.6, by Jonathan Richard Shewchuk (http://www.cs.cmu.edu/~quake/triangle.html)");
  a.AddLibrary("TriangleFile version: " + TriangleFile::GetVersion());
  a.AddLibrary("ribi::trim::Dialog version: " + ribi::trim::Dialog::GetVersion());
  return a;
}

ribi::Help ribi::TestTriangleMenuDialog::GetHelp() const noexcept
{
  return Help(
    this->GetAbout().GetFileTitle(),
    this->GetAbout().GetFileDescription(),
    {
      Help::Option('b',"verbose","generate more output"),
      Help::Option('p',"profile","add profiling information"),
      Help::Option('q',"triangle_min_angle","Triangle minimum angle"),
      Help::Option('r',"triangle_area","Triangle maximum area"),
      Help::Option('s',"silent","no output"),
      Help::Option('w',"wkt","WKT of the shapes used as a base")
    },
    {
      GetAbout().GetFileTitle() + " --wkt POLYGON((1 1,-1 1,-1 -1,1 -1)) --triangle_area 1.0 --triangle_quality 1.0 --verbose",
      GetAbout().GetFileTitle() + " -w POLYGON((0 1,-1 -1,1 -1)),LINESTRING(0 -1,-1 1,1 1,0 -1) -r 1.0 -q 1.0 -b",
    }
  );
}

boost::shared_ptr<const ribi::Program> ribi::TestTriangleMenuDialog::GetProgram() const noexcept
{
  boost::shared_ptr<const ribi::Program> p {
    new ribi::ProgramTestTriangle
  };
  assert(p);
  return p;
}

std::string ribi::TestTriangleMenuDialog::GetVersion() const noexcept
{
  return "1.9";
}

std::vector<std::string> ribi::TestTriangleMenuDialog::GetVersionHistory() const noexcept
{
  return {
    "2014-05-09: version 1.0: initial version, uses Windows executable only",
    "2014-05-18: version 1.1: uses Linux executable additionally",
    "2014-05-23: version 1.2: added command line interface",
    "2014-05-27: version 1.3: added units to Triangle parameters, fixed bug in desktop version that was detected by this",
    "2014-06-03: version 1.4: assume Triangle starts counting from index zero, desktop version responds to all positive values",
    "2014-06-12: version 1.5: support linestrings",
    "2014-06-17: version 1.6: don't crash desktop version if final result is empty",
    "2014-06-24: version 1.7: use of trim::Dialog in desktop version",
    "2014-06-26: version 1.8: use of trim::Dialog in console version",
    "2014-08-08: version 1.9: increased use of TDD"
  };
}

#ifndef NDEBUG
void ribi::TestTriangleMenuDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  const bool verbose{false};
  if (verbose) { TRACE("Test classes used by this one"); }
  {
    fileio::FileIo();
    Geometry();
    PolyFile( Vertices() );
    PolyFileFromPolygons( Geometry().WktToShapes("POLYGON((1 1,-1 1,-1 -1,1 -1))") );
    TriangleFile( Geometry().WktToShapes("POLYGON((1 1,-1 1,-1 -1,1 -1))") );
    trim::Dialog();
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
  if (verbose) { TRACE("Construction"); }
  {
    TestTriangleMenuDialog d;
  }
  if (verbose) { TRACE("Simple run with polygon only"); }
  {
    TestTriangleMenuDialog().Execute(
      {
        "TestTriangleMenuDialog",
        "--wkt", "POLYGON((1 1,-1 1,-1 -1,1 -1))",
        "--silent",
        //"--verbose",
        "--triangle_area", "1.0",
        "--triangle_quality", "1.0"
      }
    );
  }
  if (verbose) { TRACE("Simple run with polygon and linestring"); }
  {
    TestTriangleMenuDialog().Execute(
      {
        "TestTriangleMenuDialog",
        "-w", "POLYGON((1 1,1 -1,-1 -1,-1 1)),LINESTRING(0 0,0 2,2 2,0 0)",
        "--silent",
        //"--verbose",
        "-r", "1.0",
        "-q", "1.0"
      }
    );
  }
}
#endif
