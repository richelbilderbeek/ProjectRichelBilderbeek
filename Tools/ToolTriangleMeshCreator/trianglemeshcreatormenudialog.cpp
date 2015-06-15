//---------------------------------------------------------------------------
/*
TriangleMeshCreator, creates a 3D mesh using Triangle,
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
#include <boost/units/io.hpp>
#include <boost/units/systems/si.hpp>
#include <boost/math/constants/constants.hpp>
#include <boost/timer.hpp>

#include "container.h"
#include "fileio.h"
#include "geometry.h"
#include "openfoammesh.h"
#include "plane.h"
#include "polyfile.h"
#include "polyfilefrompolygons.h"
#include "testtimer.h"
#include "ribi_regex.h"
#include "richelbilderbeekprogram.h"
#include "trace.h"
#include "trianglefile.h"
#include "trianglemeshdialog.h"
#include "trianglemeshcreateverticalfacesstrategies.h"
#include "trianglemeshcellscreator.h"
#include "trianglemeshcellscreatorfactory.h"
#include "trianglemeshtemplate.h"
#pragma GCC diagnostic pop

ribi::TriangleMeshCreatorMenuDialog::TriangleMeshCreatorMenuDialog()
{
  #ifndef NDEBUG
  Test();
  #endif
}

int ribi::TriangleMeshCreatorMenuDialog::ExecuteSpecific(const std::vector<std::string>& args) noexcept
{
  START_TRACE();
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
  if (std::count(args.begin(),args.end(),"-m") || std::count(args.begin(),args.end(),"--show_mesh") || std::count(args.begin(),args.end(),"--showmesh"))
  {
    show_mesh = true;
  }
  if (verbose)
  {
    std::cout << "Show mesh: " << (show_mesh ? "Yes" : "No") << std::endl;
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

  const double triangle_min_angle_max_degrees = 60.0;
  const Angle triangle_min_angle_max_radians(triangle_min_angle_max_degrees * tau * radian / 360.0);

  double triangle_min_angle_degrees = 0.0;
  Angle triangle_min_angle = 0.0 * radian;
  for (int i=0; i!=argc-1; ++i)
  {
    if (args[i] == "-q"
      || args[i] == "--triangle_quality"
      || args[i] == "--triangle_min_angle")
    {
      try
      {
        triangle_min_angle_degrees = boost::lexical_cast<double>(args[i+1]);
        triangle_min_angle = Angle(triangle_min_angle_degrees * tau * radian / 360.0);
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
  if (triangle_min_angle >= triangle_min_angle_max_radians)
  {
    std::cerr << "Please supply a value lower than 60.0 degrees for the Triangle quality "
      << "(the minimum angle of a triangle corner,"
      << "you supplied the value " << triangle_min_angle_degrees << ")"
      << std::endl;
    return 1;
  }
  if (verbose)
  {
    std::cout << "Triangle quality (the minimum angle of a triangle corner): "
      << triangle_min_angle << ", "
      << triangle_min_angle_degrees << " degree"
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

  ///no_check_mesh
  bool check_mesh = true;
  if (!std::count(args.begin(),args.end(),"-c") && !std::count(args.begin(),args.end(),"--no-check-mesh"))
  {
    check_mesh = false;
  }
  if (verbose)
  {
    std::cout << "Check mesh: " << check_mesh << std::endl;
  }

  try
  {
    boost::timer timer;
    ribi::trim::Dialog d;
    d.SetShapes(shapes);
    d.SetTriangleParameters(triangle_min_angle,triangle_max_area,verbose);
    d.CreateTriangleMesh();
    assert(d.GetTriangleFile());
    d.Set3dMeshParameters(
      n_layers,
      layer_height,
      strategy,
      ribi::trim::Dialog::CreateSculptFunctionRemoveRandom(fraction),
      ribi::trim::Dialog::CreateDefaultAssignBoundaryFunction(),
      ribi::trim::Dialog::CreateDefaultBoundaryToPatchFieldTypeFunction(),
      verbose
    );
    d.Create3dMesh();

    if(do_profile)
    {
      const double t_secs = timer.elapsed();
      //const int n_triangle_input_edges = d.GetTriangleFile()->GetTriangleInputNedges();
      //const int n_triangle_input_vertices = d.GetTriangleFile()->GetTriangleInputNvertices();
      const int n_triangle_output_eles = Container().Count(d.GetTriangleOutputEle(),'\n');
      const int n_triangle_output_nodes = Container().Count(d.GetTriangleOutputNode(),'\n');
      const int n_triangle_output_polys = Container().Count(d.GetTriangleOutputPoly(),'\n');
      std::cout
        << '\n' //Because Triangle does not terminate its output
        << t_secs << " "
        //<< n_triangle_input_edges << " "
        //<< n_triangle_input_vertices << " "
        << n_triangle_output_eles << " "
        << n_triangle_output_nodes << " "
        << n_triangle_output_polys << " "
        << d.GetNfaces() << " "
        << d.GetNcells() << " "
        #ifndef NDEBUG
        << "Debug"
        #else
        << "Release"
        #endif
        << std::endl
      ;
    }

    if (show_mesh)
    {
      d.Show3dMesh();
    }
    //Can only check 3D mesh with a fully known path
    if (check_mesh && fileio::FileIo().IsRegularFile(args[0]))
    {
      d.Check3dMesh(args[0]);
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

ribi::About ribi::TriangleMeshCreatorMenuDialog::GetAbout() const noexcept
{
  
  About a(
    "Richel Bilderbeek",
    "TriangleMeshCreator",
    "Create a 3D mesh using Triangle",
    "the 9th of August 2014",
    "2014-2015",
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
  a.AddLibrary("TestTimer version: " + TestTimer::GetVersion());
  a.AddLibrary("Triangle version 1.6, by Jonathan Richard Shewchuk (http://www.cs.cmu.edu/~quake/triangle.html)");
  a.AddLibrary("TriangleFile version: " + TriangleFile::GetVersion());
  a.AddLibrary("TriangleMesh version: " + trim::Dialog::GetVersion());
  return a;
}

ribi::Help ribi::TriangleMeshCreatorMenuDialog::GetHelp() const noexcept
{
  return Help(
    GetAbout().GetFileTitle(),
    GetAbout().GetFileDescription(),
    {
      Help::Option('b',"verbose","generate more output"),
      Help::Option('c',"no-check-mesh","do not check the resulting 3D mesh"),
      Help::Option('f',"fraction","fraction of cells to keep"),
      Help::Option('m',"show_mesh","show the generated 3D mesh"),
      Help::Option('n',"n_layers","the number of layers"),
      Help::Option('p',"profile","add profiling information"),
      Help::Option('q',"triangle_min_angle","Triangle min angle"),
      Help::Option('r',"triangle_max_area","Triangle max area"),
      Help::Option('s',"strategy","how to create vertical faces, '1' or '2'"),
      Help::Option('t',"test","tests the program extensively"),
      Help::Option('w',"wkt","WKT of the shapes used as a base"),
      Help::Option('z',"layer_height","the height of a layer, in meters")
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
  return "1.11";
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
    "2014-06-24: version 1.10: moved main dialog to TriangleMesh classes, changed GUI in desktop version to show all data in all steps",
    "2014-08-09: version 1.11: increased use of TDD"
  };
}

#ifndef NDEBUG
void ribi::TriangleMeshCreatorMenuDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }

  Geometry();
  ribi::trim::Dialog();

  const TestTimer test_timer(__func__,__FILE__,1.0);
  const bool verbose{false};
  if (verbose) { TRACE("Constructor"); }
  {
    TriangleMeshCreatorMenuDialog();
  }
  if (verbose) { TRACE("Simple run"); }
  {
    TriangleMeshCreatorMenuDialog().Execute(
      {
        "TriangleMeshCreator",
        "--layer_height", "1",
        "--WKT", "POLYGON((1 1,-1 1,-1 -1,1 -1))",
        "--strategy", "1",
        "--n_layers", "1",
        "--fraction", "0.75",
        //"--show_mesh",
        //"--verbose",
        "--triangle_max_area", "10.0",
        "--triangle_min_angle", "20.0",
        "--profile"
      }
    );
  }
}
#endif

void ribi::TriangleMeshCreatorMenuDialog::TestDeep() noexcept
{
  const bool verbose{false};

  if (verbose) { TRACE("Trying out to build cells from the hardest testing templates"); }
  {
    using ribi::trim::Cell;
    using ribi::trim::CellsCreator;
    using ribi::trim::CellsCreatorFactory;
    using ribi::trim::CreateVerticalFacesStrategy;
    using ribi::trim::CreateVerticalFacesStrategies;
    using ribi::trim::Dialog;
    using ribi::trim::Template;
    //This is the longest test by far
    //const TestTimer test_timer(boost::lexical_cast<std::string>(__LINE__),__FILE__,1.0);
    for (CreateVerticalFacesStrategy strategy: CreateVerticalFacesStrategies().GetAll())
    {
      const boost::shared_ptr<Template> my_template {
        Template::CreateTest(3)
      };

      const int n_cell_layers = 2;
      const boost::shared_ptr<CellsCreator> cells_creator{
        CellsCreatorFactory().Create(
          my_template,
          n_cell_layers,
          1.0 * boost::units::si::meter,
          strategy,
          verbose
        )
      };
      const std::vector<boost::shared_ptr<Cell>> cells { cells_creator->GetCells() };
      assert(cells.size() > 0);
    }
  }

  if (verbose) { TRACE("Testing case 1"); }
  TriangleMeshCreatorMenuDialog().Execute(
    {
      "TriangleMeshCreator",
      "--layer_height", "1",
      "--WKT", "POLYGON((1 1,-1 1,-1 -1,1 -1))",
      "--strategy", "1",
      "--n_layers", "1",
      "--fraction", "0.75",
      //"--show_mesh",
      //"--verbose",
      "--triangle_max_area", "10.0",
      "--triangle_min_angle", "20.0",
      "--profile"
    }
  );
  if (verbose) { TRACE("Testing case 2"); }
  TriangleMeshCreatorMenuDialog().Execute(
    {
      "TriangleMeshCreator",
      "-z", "1",
      "-w", "POLYGON((0 0,0 3,3 0)),POLYGON((1 1,0 2,2 0))",
      "-s", "1",
      "-n", "1",
      "-f", "0.75",
      //"-m",
      //"-b",
      "--triangle_area", "10.0",
      "--triangle_quality", "20.0",
      "--profile"
    }
  );
  if (verbose) { TRACE("Testing case 3"); }
  TriangleMeshCreatorMenuDialog().Execute(
    {
      "TriangleMeshCreator",
      "-z", "1",
      "-w", "POLYGON((10 10,10 -10,-10 -10,-10 10)),LINESTRING(5 5,5 -5,-5 -5,-5 5)",
      "-s", "1",
      "-n", "1",
      "-f", "0.75",
      //"-m",
      //"-b",
      "-r", "10.0",
      "-q", "20.0",
      "--profile"
    }
  );
  if (verbose) { TRACE("Testing case 4"); }
  TriangleMeshCreatorMenuDialog().Execute(
    {
      "TriangleMeshCreator",
      "-z", "1",
      "-w", "LINESTRING(5 5,5 -5,-5 -5,-5 5)",
      "-s", "1",
      "-n", "1",
      "-f", "0.75",
      //"-m",
      //"-b",
      "-r", "10.0",
      "-q", "20.0",
      "--profile"
    }
  );
  if (verbose) { TRACE("Testing mesh of issue #221"); }

  TriangleMeshCreatorMenuDialog().Execute(
    {
      "TriangleMeshCreator",
      "--layer_height","1",
      "--WKT", "POLYGON((10 10,10 -10,-10 -10,-10 10))",
      "--strategy", "1",
      "--n_layers", "10",
      "--fraction", "0.9",
      "--triangle_max_area", "0.1",
      "--triangle_min_angle", "20.0",
      "--show_mesh",
      "--profile"
    }
  );
  if (verbose) { TRACE("Tested all cases"); }
}
