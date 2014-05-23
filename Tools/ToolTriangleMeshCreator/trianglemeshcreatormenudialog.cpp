//---------------------------------------------------------------------------
/*
TriangleMeshCreator, creates a 3D mesh using Triangle,
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
//From http://www.richelbilderbeek.nl/ToolTriangleMeshCreator.htm
//---------------------------------------------------------------------------
#include "trianglemeshcreatormenudialog.h"

#include <cassert>
#include <iostream>
#include <memory>
#include <string>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <boost/lexical_cast.hpp>
#include <boost/math/constants/constants.hpp>
#include <boost/units/io.hpp>
//#include <boost/xpressive/xpressive.hpp>

#include <QRegExp>

#include "fileio.h"
#include "geometry.h"
#include "plane.h"
#include "richelbilderbeekprogram.h"
#include "trace.h"
#include "trianglefile.h"
#include "trianglemeshcellscreator.h"
#include "trianglemeshcellscreatorfactory.h"
#include "trianglemeshcreatormaindialog.h"
#include "trianglemeshface.h"
#include "trianglemeshhelper.h"
#pragma GCC diagnostic pop

int ribi::TriangleMeshCreatorMenuDialog::ExecuteSpecific(const std::vector<std::string>& args) noexcept
{
  START_TRACE();
  #ifndef NDEBUG
  Test();
  #endif
  typedef boost::geometry::model::d2::point_xy<double> Coordinat;
  typedef boost::units::quantity<boost::units::si::length> Length;
  typedef boost::geometry::model::polygon<Coordinat> Polygon;
  using boost::units::si::meter;

  const int argc = static_cast<int>(args.size());

  //Verbosity
  bool verbose = false;
  if (std::count(args.begin(),args.end(),"-b") || std::count(args.begin(),args.end(),"--verbose"))
  {
    verbose = true;
    std::cout << "Verbose mode" << std::endl;
  }

  //Show mesh
  bool show_mesh = false;
  if (std::count(args.begin(),args.end(),"-m") || std::count(args.begin(),args.end(),"--show_mesh"))
  {
    show_mesh = true;
  }
  if (verbose)
  {
    std::cout << "Show mesh: " << (show_mesh ? "Yes" : "No") << std::endl;
  }

  //Layer height
  if (!std::count(args.begin(),args.end(),"-z") && !std::count(args.begin(),args.end(),"--layer_height"))
  {
    std::cerr << "Parameter for layer height missing" << '\n';
    return 1;
  }
  Length layer_height(0.0 * boost::units::si::meter);
  for (int i=0; i!=argc-1; ++i)
  {
    if (args[i] == "-z" || args[i] == "--layer_height")
    {
      try
      {
        layer_height = Length(boost::lexical_cast<double>(args[i+1]) * meter);
      }
      catch (boost::bad_lexical_cast&)
      {
        std::cerr << "Please supply a value for the layer height, e.g. '3.14'" << std::endl;
        return 1;
      }
    }
  }
  if (layer_height <= 0.0 * meter)
  {
    std::cerr << "Please supply a positive non-zero value for the layer height, e.g. '3.14'" << std::endl;
    return 1;
  }
  if (verbose)
  {
    std::cout << "Layer height: " << layer_height << std::endl;
  }

  //Create vertical faces strategy
  if (!std::count(args.begin(),args.end(),"-s") && !std::count(args.begin(),args.end(),"--strategy"))
  {
    std::cerr << "Parameter for vertical faces creation strategy missing" << '\n';
    return 1;
  }
  ribi::trim::CreateVerticalFacesStrategy strategy
    = ribi::trim::CreateVerticalFacesStrategy::one_face_per_square;
  for (int i=0; i!=argc-1; ++i)
  {
    if (args[i] == "-s" || args[i] == "--strategy")
    {
      try
      {
        int value = boost::lexical_cast<int>(args[i+1]);
        switch (value)
        {
          case 1:
            strategy = ribi::trim::CreateVerticalFacesStrategy::one_face_per_square;
            break;
          case 2:
            strategy = ribi::trim::CreateVerticalFacesStrategy::two_faces_per_square;
            break;
          default:
          {
            std::cerr << "Please supply either a '1' or '2' for the vertical faces strategy" << std::endl;
            return 1;
          }
        }
      }
      catch (boost::bad_lexical_cast&)
      {
        std::cerr << "Please supply a value for the vertical faces strategy, either '1' or '2'" << std::endl;
        return 1;
      }
    }
  }
  if (verbose)
  {
    std::cout
      << "Create vertical faces strategy: "
      << (strategy == ribi::trim::CreateVerticalFacesStrategy::one_face_per_square
          ? "One face"
          : "Two faces"
        )
      << " per square"
      << std::endl;
  }

  //Number of layers
  if (!std::count(args.begin(),args.end(),"-n") && !std::count(args.begin(),args.end(),"--n_layers"))
  {
    std::cerr << "Parameter for number of layers missing" << '\n';
    return 1;
  }
  int n_layers = 0;
  for (int i=0; i!=argc-1; ++i)
  {
    if (args[i] == "-n" || args[i] == "--n_layers")
    {
      try
      {
        n_layers = boost::lexical_cast<int>(args[i+1]);
      }
      catch (boost::bad_lexical_cast&)
      {
        std::cerr << "Please supply a value for number of layers" << std::endl;
        return 1;
      }
    }
  }
  if (n_layers <= 0)
  {
    std::cerr << "Please supply a positive non-zero value for the number of layers" << std::endl;
    return 1;
  }
  if (verbose)
  {
    std::cout << "Number of layers: " << n_layers << std::endl;
  }

  //Triangle area
  if (!std::count(args.begin(),args.end(),"-r") && !std::count(args.begin(),args.end(),"--triangle_area"))
  {
    std::cerr << "Parameter for Triangle area missing" << '\n';
    return 1;
  }
  double triangle_area = 0.0;
  for (int i=0; i!=argc-1; ++i)
  {
    if (args[i] == "-r" || args[i] == "--triangle_area")
    {
      try
      {
        triangle_area = boost::lexical_cast<double>(args[i+1]);
      }
      catch (boost::bad_lexical_cast&)
      {
        std::cerr << "Please supply a value for Triangle area" << std::endl;
        return 1;
      }
    }
  }
  if (triangle_area <= 0.0)
  {
    std::cerr << "Please supply a positive non-zero value for the Triangle area" << std::endl;
    return 1;
  }
  if (verbose)
  {
    std::cout << "Triangle area: " << triangle_area << std::endl;
  }

  //Triangle quality
  if (!std::count(args.begin(),args.end(),"-q") && !std::count(args.begin(),args.end(),"--triangle_quality"))
  {
    std::cerr << "Parameter for Triangle quality missing" << '\n';
    return 1;
  }
  double triangle_quality = 0.0;
  for (int i=0; i!=argc-1; ++i)
  {
    if (args[i] == "-q" || args[i] == "--triangle_quality")
    {
      try
      {
        triangle_quality = boost::lexical_cast<double>(args[i+1]);
      }
      catch (boost::bad_lexical_cast&)
      {
        std::cerr << "Please supply a value for Triangle quality" << std::endl;
        return 1;
      }
    }
  }
  if (triangle_quality <= 0.0)
  {
    std::cerr << "Please supply a positive non-zero value for the Triangle quality" << std::endl;
    return 1;
  }
  if (verbose)
  {
    std::cout << "Triangle quality: " << triangle_quality << std::endl;
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


  //Fraction
  if (!std::count(args.begin(),args.end(),"-f") && !std::count(args.begin(),args.end(),"--fraction"))
  {
    std::cerr << "Parameter for fraction of cells to keep" << '\n';
    return 1;
  }
  double fraction = 0.0;
  for (int i=0; i!=argc-1; ++i)
  {
    if (args[i] == "-f" || args[i] == "--fraction")
    {
      try
      {
        fraction = boost::lexical_cast<double>(args[i+1]);
      }
      catch (boost::bad_lexical_cast&)
      {
        std::cerr << "Please supply a value for fraction of cells to keep" << std::endl;
        return 1;
      }
    }
  }
  if (fraction < 0.0 || fraction > 1.0)
  {
    std::cerr << "Please supply a value between zero and one for the fraction of cells to keep" << std::endl;
    return 1;
  }
  if (verbose)
  {
    std::cout << "Fraction of cells to keep: " << fraction << std::endl;
  }

  try
  {
    const ribi::TriangleMeshCreatorMainDialog d(
      polygons,
      n_layers,
      layer_height,
      strategy,
      triangle_quality,
      triangle_area,
      ribi::TriangleMeshCreatorMainDialog::CreateSculptFunctionRemoveRandom(fraction),
      ribi::TriangleMeshCreatorMainDialog::CreateDefaultAssignBoundaryFunction(),
      ribi::TriangleMeshCreatorMainDialog::CreateDefaultBoundaryToPatchFieldTypeFunction(),
      verbose
    );
    if (show_mesh)
    {
      assert(ribi::fileio::FileIo().IsRegularFile(d.GetFilename()));
      std::stringstream s;
      s
        #ifdef _WIN32
        << "C:\\Progra~1\\VCG\\Meshlab\\meshlab.exe "
        #else
        << "meshlab "
        #endif
        << d.GetFilename()
      ;
      const int error = std::system(s.str().c_str());
      if (error) std::cout << "WARNING: cannot display mesh" << '\n';
    }

    const std::string checkMesh_command(
      std::string(
        R"(C:\cfd\blueCFD-SingleCore-2.1\OpenFOAM-2.1\etc\batchrc.bat )")
      + R"("WM_COMPILER=mingw-w32" "WM_PRECISION_OPTION=DP" "WM_MPLIB=""" )"
        // Changing to drive D is important...
      + "&& D: "
        // ...although this also indicates the drive
      + "&& cd " + ribi::fileio::FileIo().GetPath(args[0]) + " "
      + "&& cd .. "
      + (verbose ? "&& dir " : "")
      + "&& checkMesh"
    );
    if (verbose) { TRACE(checkMesh_command); }
    std::system(checkMesh_command.c_str());
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

ribi::About ribi::TriangleMeshCreatorMenuDialog::GetAbout() const noexcept
{
  
  About a(
    "Richel Bilderbeek",
    "TriangleMeshCreator",
    "Create a 3D mesh using Triangle",
    "the 23rd of May 2014",
    "2014-2014",
    "http://www.richelbilderbeek.nl/ToolTriangleMeshCreator.htm",
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

ribi::Help ribi::TriangleMeshCreatorMenuDialog::GetHelp() const noexcept
{
  return Help(
    GetAbout().GetFileTitle(),
    GetAbout().GetFileDescription(),
    {
      Help::Option('z',"layer_height","the height of a layer, in meters"),
      Help::Option('p',"polygons","the shapes used as a base"),
      Help::Option('s',"strategy","how to create vertical faces, '1' or '2'"),
      Help::Option('n',"n_layers","the number of layers"),
      Help::Option('f',"fraction","fraction of cells to keep"),
      Help::Option('m',"show_mesh","show the generated 3D mesh"),
      Help::Option('r',"triangle_area","Triangle area"),
      Help::Option('q',"triangle_quality","Triangle quality"),
      Help::Option('b',"verbose","generate more output")
    },
    {
      GetAbout().GetFileTitle() + " --layer_height 1 --polygons POLYGON((1 1,-1 1,-1 -1,1 -1)) --strategy 1 --n_layers 3 --show_mesh --triangle_area 1.0 --triangle_quality 1.0 --verbose --fraction 0.75",
      GetAbout().GetFileTitle() + " -z 1 -p POLYGON((0 1,-1 -1,1 -1)),POLYGON((0 -1,-1 1,1 1)) -s 1 -n 3 -m -r 1.0 -q 1.0 -b --f 0.75",
    }
  );
}

std::string ribi::TriangleMeshCreatorMenuDialog::GetPolygonRegex()
{
  return
    "(POLYGON\\(\\(.*\\)\\))"
  ;
}

boost::shared_ptr<const ribi::Program> ribi::TriangleMeshCreatorMenuDialog::GetProgram() const noexcept
{
  boost::shared_ptr<const ribi::Program> p {
    new ribi::ProgramTriangleMeshCreator
  };
  assert(p);
  return p;
}

//From http://www.richelbilderbeek.nl/CppGetRegexMatches.htm
std::vector<std::string> ribi::TriangleMeshCreatorMenuDialog::GetRegexMatches(
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

std::string ribi::TriangleMeshCreatorMenuDialog::GetVersion() const noexcept
{
  return "1.7";
}

std::vector<std::string> ribi::TriangleMeshCreatorMenuDialog::GetVersionHistory() const noexcept
{
  return {
    "2014-xx-xx: version 1.0: initial version, named 'TestTriangleMesh', console version only",
    "2014-03-07: version 1.1: initial versioning",
    "2014-04-25: version 1.2: renamed to 'TriangleMeshCreator'",
    "2014-04-28: version 1.3: bugfixes",
    "2014-05-06: version 1.4: added desktop version"
    "2014-05-08: version 1.5: preview of shape, use both TRIANGLE.EXE area and quality parameter, preview of Triangle.exe output",
    "2014-05-11: version 1.6: also calls meshlab under Linux",
    "2014-05-23: version 1.7: added command line interface"
  };
}

std::vector<std::string> ribi::TriangleMeshCreatorMenuDialog::SeperateString(
  const std::string& input,
  const char seperator) noexcept
{
  std::vector<std::string> v;
  boost::algorithm::split(v,input,
    std::bind2nd(std::equal_to<char>(),seperator),
    boost::algorithm::token_compress_on);
  return v;
}

#ifndef NDEBUG
void ribi::TriangleMeshCreatorMenuDialog::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting ribi::TriangleMeshCreatorMenuDialog::Test");
  /*
  typedef boost::geometry::model::d2::point_xy<double> Coordinat;
  //typedef boost::geometry::model::point<double,3,boost::geometry::cs::cartesian> Coordinat3D;
  //typedef boost::units::quantity<boost::units::si::length> Length;
  typedef boost::geometry::model::polygon<Coordinat> Polygon;
  using boost::units::si::meter;

  const bool test_smaller_mesh = false;
  if (test_smaller_mesh)
  {
    try
    {
      const double pi = boost::math::constants::pi<double>();
      const std::vector<Polygon> shapes {
        ribi::TriangleFile::CreateShapePolygon(4,pi * 0.125,1.0) //1 cube
        //ribi::TriangleFile::CreateShapePolygon(5,pi * 0.250,1.0) //1 cube
      };
      const int n_layers = 3;
      const boost::units::quantity<boost::units::si::length> layer_height(
        1.0 * boost::units::si::meter
      );
      ribi::trim::CreateVerticalFacesStrategy strategy
      = ribi::trim::CreateVerticalFacesStrategy::one_face_per_square;

      const double triangle_area = 2.0;
      const double triangle_quality = 5.0;
      const bool verbose = false;
      const ribi::TriangleMeshCreatorMainDialog d(
        shapes,
        n_layers,
        layer_height,
        strategy,
        triangle_quality,
        triangle_area,
        ribi::TriangleMeshCreatorMainDialog::CreateSculptFunctionRemoveRandom(0.75),
        ribi::TriangleMeshCreatorMainDialog::CreateDefaultAssignBoundaryFunction(),
        ribi::TriangleMeshCreatorMainDialog::CreateDefaultBoundaryToPatchFieldTypeFunction(),
        verbose
      );
      //TRACE(checkMesh_command);
      //std::system(checkMesh_command.c_str());
    }
    catch (std::exception& e)
    {
      assert(!"Should not get here");
    }
    catch (...)
    {
      assert(!"Should not get here");
    }
  }
  */
  {
    const QRegExp regex(GetPolygonRegex().c_str());
    const std::vector<std::string> lines
      = GetRegexMatches("POLYGON((0 0,0 1,1 0,1 1)),POLYGON((0 0,0 1,1 0,1 1))",regex);
    if (lines.size() != 2)
    {
      TRACE("ERROR");
      TRACE(lines.size());
      for (auto line: lines) { TRACE(line); }
    }
    assert(lines.size() == 2);
  }

  {
    TriangleMeshCreatorMenuDialog d;
    d.Execute( {"TriangleMeshCreator", "--help" } );
    d.Execute(
      {
        "TriangleMeshCreator",
        "--layer_height", "1",
        "--polygons", "POLYGON((1 1,-1 1,-1 -1,1 -1))",
        "--strategy", "1",
        "--n_layers", "1",
        "--fraction", "0.75",
        //"--show_mesh",
        //"--verbose",
        "--triangle_area", "1.0",
        "--triangle_quality", "1.0"
      }
    );
    d.Execute(
      {
        "TriangleMeshCreator",
        "-z", "1",
        "-p", "POLYGON((0 1,-1 -1,1 -1)),POLYGON((0 -1,-1 1,1 1))",
        "-s", "1",
        "-n", "1",
        "-f", "0.75",
        //"-m",
        //"-b",
        "-r", "1.0",
        "-q", "1.0"
      }
    );
  }
  TRACE("Finished ribi::TriangleMeshCreatorMenuDialog::Test successfully");
}
#endif
