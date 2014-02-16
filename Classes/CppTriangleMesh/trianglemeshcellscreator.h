#ifndef TRIANGLEMESHCELLSCREATOR_H
#define TRIANGLEMESHCELLSCREATOR_H

#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/shared_ptr.hpp>
#include <boost/units/quantity.hpp>
#include <boost/units/systems/si/length.hpp>
#include "trianglemeshfwd.h"
#pragma GCC diagnostic pop

namespace ribi {
namespace trim {

///CellsCreator creates multiple layers of cells from a Template
///
///The next step will be
/// - freely delete the Cells that are not in the final mesh
/// - pass the desired cells to TriangleMeshBuilder to create the OpenFOAM files
struct CellsCreator
{
  CellsCreator(
    const boost::shared_ptr<const Template> t,
    const int n_layers,
    const boost::units::quantity<boost::units::si::length> layer_height
  );

  const std::vector<boost::shared_ptr<Cell>> GetCells() const noexcept { return m_cells; }

  private:
  const std::vector<boost::shared_ptr<Cell>> m_cells;

  const std::vector<boost::shared_ptr<Cell>> CreateCells(
    const boost::shared_ptr<const Template> t,
    const int n_layers,
    const boost::units::quantity<boost::units::si::length> layer_height
  ) const noexcept;

  static const std::vector<boost::shared_ptr<Face>> CreateHorizontalFaces(
    const boost::shared_ptr<const Template> t,
    const std::vector<boost::shared_ptr<Point>>& points,
    const int n_layers
  );

  static const std::vector<boost::shared_ptr<Point>> CreatePoints(
    const boost::shared_ptr<const Template> t,
    const int n_layers,
    const boost::units::quantity<boost::units::si::length> layer_height
  );



  static const std::vector<boost::shared_ptr<Face>> CreateVerticalFaces(
    const boost::shared_ptr<const Template> t,
    const std::vector<boost::shared_ptr<Point>>& points,
    const int n_layers
  );

  static const std::vector<boost::shared_ptr<Face>> FindKnownFacesBetween(
    const boost::shared_ptr<const Face> a, const boost::shared_ptr<const Face> b
  );

  static bool IsSubset(
    std::vector<boost::shared_ptr<Point>> a,
    std::vector<boost::shared_ptr<Point>> b
  ) noexcept;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace trim
} //~namespace ribi

#endif // TRIANGLEMESHCELLSCREATOR_H
