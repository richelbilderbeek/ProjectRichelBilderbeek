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
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "testtrianglemaindialog.h"

#include <fstream>

#include <boost/make_shared.hpp>
#include "fileio.h"
#include "geometry.h"
#include "polyfile.h"
#include "trace.h"
#include "trianglefile.h"
#include "trianglemeshtemplate.h"
#pragma GCC diagnostic pop

ribi::TestTriangleMainDialog::TestTriangleMainDialog(
  const std::vector<boost::geometry::model::polygon<boost::geometry::model::d2::point_xy<double>>>& shapes,
  const Area triangle_max_area,
  const Angle triangle_min_angle,
  const bool verbose
)
  : m_filename_result_mesh(ribi::fileio::FileIo().GetTempFileName(".ply"))
{
  
  #ifndef NDEBUG
  Test();
  #endif

  if (verbose) { std::clog << "Write some geometries, let Triangle.exe work on it" << std::endl; }
  std::string filename_node;
  std::string filename_ele;
  std::string filename_poly;
  {
    ribi::TriangleFile f(shapes);
    //#define TODO_ISSUE_207
    #ifdef  TODO_ISSUE_207
    f.ExecuteTriangle(
    #else
    f.ExecuteTriangleExe(
    #endif
      filename_node,
      filename_ele,
      filename_poly,
      triangle_min_angle,
      triangle_max_area
    );
  }

  if (verbose) { std::clog << "Read data from Triangle.exe output" << std::endl; }

  const boost::shared_ptr<const ribi::trim::Template> t
    = boost::make_shared<ribi::trim::Template>(
      filename_node,
      filename_ele
  );
  assert(t);
}

#ifndef NDEBUG
void ribi::TestTriangleMainDialog::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting ribi::TestTriangleMainDialog::Test");
  //Create a simple mesh
  try
  {
    const double pi { boost::math::constants::pi<double>() };
    const Polygons shapes
      = { Geometry().CreateShapePolygon(4,pi * 0.125,1.0) } //1 cube
    ;
    const Angle triangle_min_angle
      = 20.0 //Degrees
      * (boost::math::constants::two_pi<double>() / 360.0) //Degrees to radians conversion
      * boost::units::si::radians //Radians
    ;
    const Area triangle_max_area = 1.0 * boost::units::si::square_meter;
    const bool verbose = false;
    const ribi::TestTriangleMainDialog d(
      shapes,
      triangle_max_area,
      triangle_min_angle,
      verbose
    );
  }
  catch (std::exception& e)
  {
    assert(!"Should not get here");
  }
  catch (...)
  {
    assert(!"Should not get here");
  }
  TRACE("Finished ribi::TestTriangleMainDialog::Test successfully");
}
#endif
