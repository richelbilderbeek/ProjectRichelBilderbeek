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
//#include <boost/math/constants/constants.hpp>
#include <boost/units/io.hpp>

#include <QRegExp>

#include "container.h"
#include "fileio.h"
#include "geometry.h"
#include "openfoammesh.h"
#include "plane.h"
#include "polyfile.h"
#include "polyfilefrompolygons.h"
#include "ribi_regex.h"
#include "richelbilderbeekprogram.h"
#include "trace.h"
#include "trianglefile.h"
#include "trianglemeshcellscreator.h"
#include "trianglemeshcellscreatorfactory.h"
#include "trianglemeshdialog.h"
#include "trianglemeshface.h"
#include "trianglemeshhelper.h"
#pragma GCC diagnostic pop

int ribi::TriangleMeshCreatorMenuDialog::ExecuteSpecific(const std::vector<std::string>& args) noexcept
{
  START_TRACE();
  #ifndef NDEBUG
  Test();
  #endif
  typedef boost::units::quantity<boost::units::si::area> Area;
  typedef boost::units::quantity<boost::units::si::length> Length;
  typedef boost::units::quantity<boost::units::si::plane_angle> Angle;
  using boost::units::si::meter;
  using boost::units::si::radian;
  using boost::units::si::square_meter;
  const double tau = boost::math::constants::two_pi<double>();
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
  if (!std::count(args.begin(),args.end(),"-r")
    && !std::count(args.begin(),args.end(),"--triangle_area")
    && !std::count(args.begin(),args.end(),"--triangle_max_area")
  )
  {
    std::cerr << "Parameter for Triangle area missing" << '\n';
    return 1;
  }
  Area triangle_max_area = 0.0 * boost::units::si::square_meters;
  for (int i=0; i!=argc-1; ++i)
  {
    if (args[i] == "-r"
      || args[i] == "--triangle_area"
      || args[i] == "--triangle_max_area"
    )
    {
      try
      {
        triangle_max_area
          = boost::lexical_cast<double>(args[i+1])
          * square_meter
        ;
      }
      catch (boost::bad_lexical_cast&)
      {
        std::cerr << "Please supply a value for Triangle maximum area" << std::endl;
        return 1;
      }
    }
  }
  if (triangle_max_area <= 0.0 * boost::units::si::square_meters)
  {
    std::cerr << "Please supply a positive non-zero value for the Triangle maximum area" << std::endl;
    return 1;
  }
  if (verbose)
  {
    std::cout << "Triangle maximum area: " << triangle_max_area << std::endl;
  }

  //Triangle quality (the minimum angle of a triangle corner)
  if (!std::count(args.begin(),args.end(),"-q")
    && !std::count(args.begin(),args.end(),"--triangle_quality")
    && !std::count(args.begin(),args.end(),"--triangle_min_angle")
  )
  {
    std::cerr << "Parameter for Triangle quality (the minimum angle of a triangle corner) is missing" << '\n';
    return 1;
  }
  Angle triangle_min_angle = 0.0 * radian;
  for (int i=0; i!=argc-1; ++i)
  {
    if (args[i] == "-q"
      || args[i] == "--triangle_quality"
      || args[i] == "--triangle_min_angle")
    {
      try
      {
        triangle_min_angle
          = Angle(
            boost::lexical_cast<double>(args[i+1])
            * 360 / tau
            * radian
          )
        ;
      }
      catch (boost::bad_lexical_cast&)
      {
        std::cerr << "Please supply a value for Triangle quality (the minimum angle of a triangle corner)" << std::endl;
        return 1;
      }
    }
  }
  if (triangle_min_angle.value() <= 0.0)
  {
    std::cerr << "Please supply a positive non-zero value for the Triangle quality (the minimum angle of a triangle corner)" << std::endl;
    return 1;
  }
  if (triangle_min_angle.value() >= 60.0 * tau / 360.0)
  {
    std::cerr << "Please supply a value lower than 60.0 degrees for the Triangle quality (the minimum angle of a triangle corner)" << std::endl;
    return 1;
  }
  if (verbose)
  {
    std::cout << "Triangle quality (the minimum angle of a triangle corner): "
      << triangle_min_angle << ", "
      << (triangle_min_angle * 360.0 / tau) << " degree"
      << std::endl
    ;
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

  const auto shapes = Geometry().WktToShapes(wkt);

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
    ribi::trim::Dialog d;
    d.SetShapes(shapes);
    d.SetTriangleParameters(triangle_min_angle,triangle_max_area,verbose);
    d.SetMeshParameters(
      n_layers,
      layer_height,
      strategy,
      ribi::trim::Dialog::CreateSculptFunctionRemoveRandom(fraction),
      ribi::trim::Dialog::CreateDefaultAssignBoundaryFunction(),
      ribi::trim::Dialog::CreateDefaultBoundaryToPatchFieldTypeFunction(),
      verbose
    );
    /*
    const ribi::trim::Dialog d(
    //const ribi::TriangleMeshCreatorMainDialog d(
      shapes,
      n_layers,
      layer_height,
      strategy,
      triangle_min_angle,
      triangle_max_area,
      ribi::trim::Dialog::CreateSculptFunctionRemoveRandom(fraction),
      ribi::trim::Dialog::CreateDefaultAssignBoundaryFunction(),
      ribi::trim::Dialog::CreateDefaultBoundaryToPatchFieldTypeFunction(),
      verbose
    );
    */
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
    "the 17th of June 2014",
    "2014-2014",
    "http://www.richelbilderbeek.nl/ToolTriangleMeshCreator.htm",
    GetVersion(),
    GetVersionHistory()
  );
  a.AddLibrary("Container version: " + Container().GetVersion());
  a.AddLibrary("FileIo version: " + fileio::FileIo().GetVersion());
  a.AddLibrary("Geometry version: " + Geometry().GetVersion());
  a.AddLibrary("ribi::foam::Mesh version: " + ribi::foam::Mesh::GetVersion());
  a.AddLibrary("Plane version: " + Plane::GetVersion());
  a.AddLibrary("PolyFile version: " + PolyFile::GetVersion());
  a.AddLibrary("PolyFileFromPolygons version: " + PolyFileFromPolygons::GetVersion());
  a.AddLibrary("ribi::Regex version: " + ribi::Regex::GetVersion());
  a.AddLibrary("Triangle version 1.6, by Jonathan Richard Shewchuk (http://www.cs.cmu.edu/~quake/triangle.html)");
  a.AddLibrary("TriangleFile version: " + TriangleFile::GetVersion());
  //a.AddLibrary("TriangleMesh version: " + TriangleMesh::GetVersion());
  return a;
}

ribi::Help ribi::TriangleMeshCreatorMenuDialog::GetHelp() const noexcept
{
  return Help(
    GetAbout().GetFileTitle(),
    GetAbout().GetFileDescription(),
    {
      Help::Option('z',"layer_height","the height of a layer, in meters"),
      Help::Option('w',"wkt","WKT of the shapes used as a base"),
      Help::Option('s',"strategy","how to create vertical faces, '1' or '2'"),
      Help::Option('n',"n_layers","the number of layers"),
      Help::Option('f',"fraction","fraction of cells to keep"),
      Help::Option('m',"show_mesh","show the generated 3D mesh"),
      Help::Option('r',"triangle_max_area","Triangle max area"),
      Help::Option('q',"triangle_min_angle","Triangle min angle"),
      Help::Option('b',"verbose","generate more output")
    },
    {
      GetAbout().GetFileTitle() + " --layer_height 1 --polygons POLYGON((1 1,-1 1,-1 -1,1 -1)) --strategy 1 --n_layers 3 --show_mesh --triangle_area 1.0 --triangle_quality 1.0 --verbose --fraction 0.75",
      GetAbout().GetFileTitle() + " -z 1 -p POLYGON((0 1,-1 -1,1 -1)),POLYGON((0 -1,-1 1,1 1)) -s 1 -n 3 -m -r 1.0 -q 1.0 -b --f 0.75",
    }
  );
}

boost::shared_ptr<const ribi::Program> ribi::TriangleMeshCreatorMenuDialog::GetProgram() const noexcept
{
  boost::shared_ptr<const ribi::Program> p {
    new ribi::ProgramTriangleMeshCreator
  };
  assert(p);
  return p;
}

std::string ribi::TriangleMeshCreatorMenuDialog::GetVersion() const noexcept
{
  return "1.9";
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
    "2014-05-23: version 1.7: added command line interface",
    "2014-05-23: version 1.8: support linestring as shape",
    "2014-06-17: version 1.9: allow non-surface as valid input",
    "2014-06-20: version 1.10: moved main dialog to TriangleMesh classes"
  };
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
        "--triangle_max_area", "10.0",
        "--triangle_min_angle", "20.0"
      }
    );
    d.Execute(
      {
        "TriangleMeshCreator",
        "-z", "1",
        "-p", "POLYGON((0 0,0 3,3 0)),POLYGON((1 1,0 2,2 0))",
        "-s", "1",
        "-n", "1",
        "-f", "0.75",
        //"-m",
        //"-b",
        "--triangle_area", "10.0",
        "--triangle_quality", "20.0"
      }
    );
    d.Execute(
      {
        "TriangleMeshCreator",
        "-z", "1",
        "-p", "POLYGON((10 10,10 -10,-10 -10,-10 10)),LINESTRING(5 5,5 -5,-5 -5,-5 5)",
        "-s", "1",
        "-n", "1",
        "-f", "0.75",
        //"-m",
        //"-b",
        "-r", "10.0",
        "-q", "20.0"
      }
    );
    d.Execute(
      {
        "TriangleMeshCreator",
        "-z", "1",
        "-p", "LINESTRING(5 5,5 -5,-5 -5,-5 5)",
        "-s", "1",
        "-n", "1",
        "-f", "0.75",
        //"-m",
        //"-b",
        "-r", "10.0",
        "-q", "20.0"
      }
    );
  }
  TRACE("Finished ribi::TriangleMeshCreatorMenuDialog::Test successfully");
}
#endif
