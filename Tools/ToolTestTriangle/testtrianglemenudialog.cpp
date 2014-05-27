//---------------------------------------------------------------------------
/*
TestTriangle, compare Triangle to its C++ equivalent
Copyright (C) 2014-2014 Richel Bilderbeek

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
#include <boost/units/io.hpp>

#include <QRegExp>

#include "fileio.h"
#include "geometry.h"
#include "plane.h"
#include "richelbilderbeekprogram.h"
#include "trace.h"
#include "trianglefile.h"
#include "testtrianglemaindialog.h"
#pragma GCC diagnostic pop

int ribi::TestTriangleMenuDialog::ExecuteSpecific(const std::vector<std::string>& args) noexcept
{
  #ifndef NDEBUG
  Test();
  #endif

  typedef boost::geometry::model::d2::point_xy<double> Coordinat;
  typedef boost::geometry::model::polygon<Coordinat> Polygon;
  typedef boost::units::quantity<boost::units::si::plane_angle> Angle;
  typedef boost::units::quantity<boost::units::si::area> Area;
  using boost::units::si::square_meter;
  using boost::units::si::radian;

  const int argc = static_cast<int>(args.size());

  //Verbosity
  bool verbose = false;
  if (std::count(args.begin(),args.end(),"-b") || std::count(args.begin(),args.end(),"--verbose"))
  {
    verbose = true;
    std::cout << "Verbose mode" << std::endl;
  }

  //Triangle area
  if (!std::count(args.begin(),args.end(),"-r")
    && !std::count(args.begin(),args.end(),"--triangle_area")
    && !std::count(args.begin(),args.end(),"--triangle_max_area")
  )
  {
    std::cerr << "Parameter for Triangle area missing" << '\n';
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
        std::cerr << "Please supply a value for Triangle max area" << std::endl;
        return 1;
      }
    }
  }
  if (triangle_max_area <= 0.0 * square_meter)
  {
    std::cerr << "Please supply a positive non-zero value for the Triangle max area" << std::endl;
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
    std::cerr << "Parameter for Triangle quality (a minimum angle) missing" << '\n';
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
        std::cerr << "Please supply a value for Triangle quality (a minimum angle)" << std::endl;
        return 1;
      }
    }
  }
  if (triangle_min_angle <= 0.0 * radian )
  {
    std::cerr << "Please supply a positive non-zero value for the Triangle quality (a minimum angle)" << std::endl;
    return 1;
  }
  if (triangle_min_angle >= (boost::math::constants::two_pi<double>() / 3.0) * radian )
  {
    std::cerr
      << "Please supply a value less than 60 degrees for the Triangle quality (a minimum angle):"
      << "A triangle cannot have three corners each of at least 60 degrees"
      << std::endl;
    return 1;
  }
  if (verbose)
  {
    std::cout << "Triangle quality (minimum angle): " << triangle_min_angle << std::endl;
  }

  //Polygons
  if (!std::count(args.begin(),args.end(),"-p")
    && !std::count(args.begin(),args.end(),"--polygon")
    && !std::count(args.begin(),args.end(),"--polygons")
  )
  {
    std::cerr << "Parameter for polygons missing" << '\n';
    return 1;
  }

  std::vector<Polygon> polygons;
  for (int i=0; i!=argc-1; ++i)
  {
    if (args[i] == "-p" || args[i] == "--polygon" || args[i] == "--polygons")
    {
      const std::string text = args[i+1];
      if (verbose) { std::cout << "Parsing polygons '" << text << "'" << std::endl; }
      const QRegExp regex(GetPolygonRegex().c_str());
      //const boost::xpressive::sregex regex = boost::xpressive::sregex::compile(GetPolygonRegex());
      const std::vector<std::string> lines = GetRegexMatches(text,regex);
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
    std::cerr << "Please supply a value for polygon, e.g. 'POLYGON((1 1,1 -1,1 -1))" << std::endl;
    return 1;

  }
  if (verbose)
  {
    std::cout << "Number of polygons: " << polygons.size() << std::endl;
    std::cout << "Polygons (as SVG text): " << Geometry().ToSvgStr(polygons) << std::endl;
  }

  try
  {
    const TestTriangleMainDialog d(
      polygons,
      triangle_max_area,
      triangle_min_angle,
      verbose
    );
    if (verbose)
    {
      std::cout << std::endl //Because Triangle does not do an endl itself
        << "Created file '" << d.GetFilename() << "' successfully" << std::endl;
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

ribi::About ribi::TestTriangleMenuDialog::GetAbout() const noexcept
{
  
  About a(
    "Richel Bilderbeek",
    "TestTriangle",
    "compare Triangle to its C++ equivalent",
    "the 27th of May 2014",
    "2014-2014",
    "http://www.richelbilderbeek.nl/ToolTestTriangle.htm",
    GetVersion(),
    GetVersionHistory()
  );
  a.AddLibrary("FileIo version: " + fileio::FileIo().GetVersion());
  a.AddLibrary("Geometry version: " + Geometry().GetVersion());
  const std::unique_ptr<Plane> plane(
    new Plane(
      Plane::Coordinat3D(0.0,0.0,0.0),
      Plane::Coordinat3D(1.0,0.0,0.0),
      Plane::Coordinat3D(0.0,1.0,0.0)
    )
  );
  assert(plane);
  a.AddLibrary("Plane version: " + plane->GetVersion());
  a.AddLibrary("Triangle version 1.6, by Jonathan Richard Shewchuk (http://www.cs.cmu.edu/~quake/triangle.html)");
  a.AddLibrary("TriangleFile version: " + TriangleFile::GetVersion());
  return a;
}

ribi::Help ribi::TestTriangleMenuDialog::GetHelp() const noexcept
{
  return Help(
    this->GetAbout().GetFileTitle(),
    this->GetAbout().GetFileDescription(),
    {
      Help::Option('p',"polygons","the shapes used as a base"),
      Help::Option('r',"triangle_area","Triangle maximum area"),
      Help::Option('q',"triangle_min_angle","Triangle minimum angle"),
      Help::Option('b',"verbose","generate more output")
    },
    {
      GetAbout().GetFileTitle() + " --polygons POLYGON((1 1,-1 1,-1 -1,1 -1)) --triangle_area 1.0 --triangle_quality 1.0 --verbose",
      GetAbout().GetFileTitle() + " -p POLYGON((0 1,-1 -1,1 -1)),POLYGON((0 -1,-1 1,1 1)) -r 1.0 -q 1.0 -b",
    }
  );
}

std::string ribi::TestTriangleMenuDialog::GetPolygonRegex()
{
  return
    "(POLYGON\\(\\(.*\\)\\))"
  ;
}

boost::shared_ptr<const ribi::Program> ribi::TestTriangleMenuDialog::GetProgram() const noexcept
{
  boost::shared_ptr<const ribi::Program> p {
    new ribi::ProgramTestTriangle
  };
  assert(p);
  return p;
}

//From http://www.richelbilderbeek.nl/CppGetRegexMatches.htm
std::vector<std::string> ribi::TestTriangleMenuDialog::GetRegexMatches(
  const std::string& s,
  const QRegExp& r_original
) noexcept
{
  QRegExp r(r_original);
  r.setMinimal(true); //QRegExp must be non-greedy
  std::vector<std::string> v;
  int pos = 0;
  while ((pos = r.indexIn(s.c_str(), pos)) != -1)
  {
    const QString q = r.cap(1);
    if (q.isEmpty()) break;
    v.push_back(q.toStdString());
    pos += r.matchedLength();
  }

  return v;
}

std::string ribi::TestTriangleMenuDialog::GetVersion() const noexcept
{
  return "1.3";
}

std::vector<std::string> ribi::TestTriangleMenuDialog::GetVersionHistory() const noexcept
{
  return {
    "2014-05-09: version 1.0: initial version, uses Windows executable only",
    "2014-05-18: version 1.1: uses Linux executable additionally",
    "2014-05-23: version 1.2: added command line interface",
    "2014-05-27: version 1.3: added units to Triangle parameters, fixed bug in desktop version that was detected by this"
  };
}

#ifndef NDEBUG
void ribi::TestTriangleMenuDialog::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting ribi::TestTriangleMenuDialog::Test");
  {
    TestTriangleMenuDialog d;
    d.Execute( {"TestTriangleMenuDialog", "--help" } );
    d.Execute(
      {
        "TestTriangleMenuDialog",
        "--polygons", "POLYGON((1 1,-1 1,-1 -1,1 -1))",
        //"--verbose",
        "--triangle_area", "1.0",
        "--triangle_quality", "1.0"
      }
    );
    d.Execute(
      {
        "TestTriangleMenuDialog",
        "-p", "POLYGON((0 1,-1 -1,1 -1)),POLYGON((0 -1,-1 1,1 1))",
        "-b",
        "-r", "1.0",
        "-q", "1.0"
      }
    );
    assert(1==2);
  }
  TRACE("Finished ribi::TestTriangleMenuDialog::Test successfully");
}
#endif
