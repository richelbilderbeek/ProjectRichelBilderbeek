#ifndef TESTTRIANGLEMESHMAINDIALOG_H
#define TESTTRIANGLEMESHMAINDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"

#include <boost/geometry.hpp>
#include <boost/geometry/geometries/point_xy.hpp>
#include <boost/geometry/geometries/polygon.hpp>
#include <boost/shared_ptr.hpp>

#include "trianglemeshcreateverticalfacesstrategy.h"
#pragma GCC diagnostic pop

namespace ribi {

struct TestTriangleMeshMainDialog
{
  TestTriangleMeshMainDialog(
    const std::vector<boost::geometry::model::polygon<boost::geometry::model::d2::point_xy<double>>>& shapes,
    const bool show_mesh,
    const int n_layers,
    const ::ribi::trim::CreateVerticalFacesStrategy strategy,
    const std::string& renumberMesh_command
  );
  int GetTicks() const noexcept { return m_ticks; }

  private:

  //Something to store
  int m_ticks;
};

} //~namespace ribi

#endif // TESTTRIANGLEMESHMAINDIALOG_H
