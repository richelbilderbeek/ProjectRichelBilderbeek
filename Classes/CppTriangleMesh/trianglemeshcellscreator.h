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
#include "trianglemeshcreateverticalfacesstrategy.h"
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
  CellsCreator(const CellsCreator&) = delete;
  CellsCreator& operator=(const CellsCreator&) = delete;

  void Clear() noexcept { m_cells.clear(); }

  std::vector<boost::shared_ptr<Cell>> GetCells() noexcept;

  ///The Cells must be released, and this will clear CellsCreator its Cells
  ///This is important, because one can freely delete those released Cells
  ///and have a valid mesh. Would the Cells be copied, the mesh created would be
  ///invalid: the deleted Cells would always have a copy inside CellsCreator
  //const std::vector<boost::shared_ptr<Cell>> ReleaseCells() noexcept;

  private:
  friend class CellsCreatorFactory;

  CellsCreator(
    const boost::shared_ptr<const Template> t,
    const int n_layers,
    const boost::units::quantity<boost::units::si::length> layer_height,
    const CreateVerticalFacesStrategy strategy,
    const CellsCreatorFactory& lock //to force creation by CellsCreatorFactory
  );


  std::vector<boost::shared_ptr<Cell>> m_cells;

  const CreateVerticalFacesStrategy m_strategy;

  static void CheckCells(const std::vector<boost::shared_ptr<Cell>>& cells) noexcept;

  //Must be static: it is used in the constructor
  static std::vector<boost::shared_ptr<Cell>> CreateCells(
    const boost::shared_ptr<const Template> t,
    const int n_layers,
    const boost::units::quantity<boost::units::si::length> layer_height,
    const CreateVerticalFacesStrategy strategy
  ) noexcept;

  static std::vector<boost::shared_ptr<Face>> CreateHorizontalFaces(
    const boost::shared_ptr<const Template> t,
    const std::vector<boost::shared_ptr<Point>>& points,
    const int n_layers
  );

  static std::vector<boost::shared_ptr<Point>> CreatePoints(
    const boost::shared_ptr<const Template> t,
    const int n_layers,
    const boost::units::quantity<boost::units::si::length> layer_height
  );


  //Must be static: it is used in the constructor
  static std::vector<boost::shared_ptr<Face>> CreateVerticalFaces(
    const boost::shared_ptr<const Template> t,
    const std::vector<boost::shared_ptr<Point>>& points,
    const int n_layers,
    const CreateVerticalFacesStrategy strategy
  ) noexcept;

  static std::vector<boost::shared_ptr<Face>> FindKnownFacesBetween(
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
