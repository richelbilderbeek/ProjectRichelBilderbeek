#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <iostream>

#include <boost/math/constants/constants.hpp>
#include <boost/geometry.hpp>
#include <boost/geometry/geometries/point_xy.hpp>
#include <boost/units/systems/si/length.hpp>

#include "Shiny.h"

#include "fileio.h"
#include "filename.h"
#include "openfoamfilenames.h"
#include "openfoamfiles.h"
#include "openfoammesh.h"
#include "trace.h"
#include "trianglefile.h"
#include "trianglemeshbuilder.h"
#include "trianglemeshcellscreator.h"
#include "trianglemeshtemplate.h"
#include "xml.h"
#pragma GCC diagnostic pop

///Help adding constness a bit
template <class T>
const std::vector<boost::shared_ptr<const T> > AddConst(
  const std::vector<boost::shared_ptr<T> > v)
{
  return std::vector<boost::shared_ptr<const T> >(v.begin(),v.end());
}


void DoMain()
{
  START_TRACE();
  PROFILE_FUNC();
  const bool show_mesh = true;
  const std::string filename_result_mesh { "mesh.ply" };

  //Write a house, let Triangle.exe work on it
  std::string filename_node; //Triangle.exe output file
  std::string filename_ele;  //Triangle.exe output file
  std::string filename_poly; //Triangle.exe output file
  {
    const std::vector<boost::geometry::model::d2::point_xy<double>> points {
      {0.5, 2.0}, //0
      {1.0, 1.0}, //1
      {1.0, 0.0}, //2
      {0.0, 0.0}, //3
      {0.0, 1.0}  //4
    };
    boost::geometry::model::polygon<boost::geometry::model::d2::point_xy<double>> v;
    boost::geometry::append(v, points);
    ribi::TriangleFile f( {v} );
    const double quality = 5.0;
    const double area = 2.0;
    f.ExecuteTriangle(
      filename_node,
      filename_ele,
      filename_poly,
      quality,area);
  }

  //Read data from Triangle.exe output
  {
    const int n_layers = 10;
    const boost::shared_ptr<const ribi::trim::Template> t {
      new ribi::trim::Template(
        filename_node,
        filename_ele
      )
    };

    TRACE_FUNC();
    //Create cells from this template
    const boost::units::quantity<boost::units::si::length> layer_height(
      1.0 * boost::units::si::meter
    );

    const boost::shared_ptr<const ribi::trim::CellsCreator> c {
      new ribi::trim::CellsCreator(t,n_layers,layer_height)
    };

    //Remove some random cells
    std::vector<boost::shared_ptr<ribi::trim::Cell>> cells { c->GetCells() };
    std::random_shuffle(cells.begin(),cells.end());
    std::reverse(cells.begin(),cells.end());
    std::random_shuffle(cells.begin(),cells.end());
    cells.resize(cells.size() * 3 / 4);

    //Assign boundaries to the faces
    //AssignBoundaries(cells);

    PROFILER_UPDATE();
    PROFILER_OUTPUT("shiny_output.txt");

    TRACE_FUNC();

    //Build the OpenFOAM files
    const ribi::trim::TriangleMeshBuilder builder(
      cells,
      filename_result_mesh
    );
    TRACE_FUNC();
  }

  if (show_mesh)
  {
    std::stringstream s;
    s
      << "C:\\Progra~1\\VCG\\Meshlab\\meshlab.exe "
      << filename_result_mesh;
    const int error = std::system(s.str().c_str());
    if (error) std::cout << "WARNING: cannot display mesh" << '\n';
  }
}

//SchmeshCreator is a program that generates
//- a mesh directly, in .ply format: this is just for a quick check
//- files to be read by paraFOAM
int main()
{
  PROFILE_FUNC();
  try
  {
    DoMain();
    PROFILER_UPDATE();
    PROFILER_OUTPUT("shiny_output.txt");
    return 0;
  }
  catch (std::exception& e)
  {
    std::cerr << "ERROR: Exception caught: " << e.what() << std::endl;
    PROFILER_UPDATE();
    PROFILER_OUTPUT("shiny_output.txt");
    return 1;
  }
  catch (...)
  {
    std::cerr << "ERROR: Unknown exception caught!" << std::endl;
    PROFILER_UPDATE();
    PROFILER_OUTPUT("shiny_output.txt");
    return 1;
  }
}
/*

  const double pi = boost::math::constants::pi<double>();
  using boost::units::si::radian;

*/
