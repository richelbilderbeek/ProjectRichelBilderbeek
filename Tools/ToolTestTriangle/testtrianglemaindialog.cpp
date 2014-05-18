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

#include <boost/geometry.hpp>
#include <boost/geometry/geometries/point_xy.hpp>
#include <boost/make_shared.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/units/systems/si.hpp>



#include "fileio.h"
#include "openfoamcontroldictfile.h"
#include "openfoamfilenames.h"
#include "openfoamfvschemesfile.h"
#include "openfoamfvsolutionfile.h"
#include "openfoampressurefile.h"
#include "openfoamtemperaturefile.h"
#include "openfoamthermophysicalpropertiesfile.h"
#include "openfoamvelocityfieldfile.h"
#include "trace.h"
#include "trianglefile.h"
#include "trianglemeshbuilder.h"
#include "trianglemeshcell.h"
#include "trianglemeshcellscreator.h"
#include "trianglemeshcellscreatorfactory.h"
#include "trianglemeshface.h"
#include "trianglemeshhelper.h"
#include "trianglemeshpoint.h"
#include "trianglemeshtemplate.h"
#include "trianglemeshcreateverticalfacesstrategies.h"
#pragma GCC diagnostic pop

ribi::TestTriangleMainDialog::TestTriangleMainDialog(
  const std::vector<boost::geometry::model::polygon<boost::geometry::model::d2::point_xy<double>>>& shapes,
  const double triangle_area,
  const double triangle_quality,
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
      triangle_quality,
      triangle_area
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
  typedef boost::geometry::model::polygon<boost::geometry::model::d2::point_xy<double>> Coordinat2D;
  ribi::trim::CellsCreatorFactory();

  //Create a simple mesh
  try
  {
    const double pi { boost::math::constants::pi<double>() };
    const std::vector<Coordinat2D> shapes {
      ribi::TriangleFile::CreateShapePolygon(4,pi * 0.125,1.0) //1 cube
    };
    const double triangle_quality = 5.0;
    const double triangle_area = 2.0;
    const bool verbose = false;
    const ribi::TestTriangleMainDialog d(
      shapes,
      triangle_quality,
      triangle_area,
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
