#ifndef RIBI_TRIANGLEMESHCELLSCREATOR_H
#define RIBI_TRIANGLEMESHCELLSCREATOR_H

#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <boost/make_shared.hpp>
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
class CellsCreator
{

  friend class CellFactory;
  friend class Dialog;

  CellsCreator(const CellsCreator&) = delete;
  CellsCreator(CellsCreator&&) = delete;
  CellsCreator& operator=(const CellsCreator&) = delete;
  CellsCreator& operator=(const CellsCreator&&) = delete;

  void Clear() noexcept { m_cells.clear(); }

  std::vector<boost::shared_ptr<Cell>> GetCells() noexcept;

  private:
  friend class CellsCreatorFactory;

  //n_face_layers - 1 == n_cell_layers
  CellsCreator(
    const boost::shared_ptr<const Template> t,
    const int n_cell_layers,
    const boost::units::quantity<boost::units::si::length> layer_height,
    const CreateVerticalFacesStrategy strategy,
    const bool verbose,
    const CellsCreatorFactory& lock //to force creation by CellsCreatorFactory
  );
  ~CellsCreator() noexcept {}

  std::vector<boost::shared_ptr<Cell>> m_cells;

  const CreateVerticalFacesStrategy m_strategy;

  static void CheckCells(const std::vector<boost::shared_ptr<Cell>>& cells) noexcept;

  //Must be static: it is used in the constructor
  //n_face_layers - 1 == n_cell_layers
  static std::vector<boost::shared_ptr<Cell>> CreateCells(
    const boost::shared_ptr<const Template> t,
    const int n_face_layers,
    const boost::units::quantity<boost::units::si::length> layer_height,
    const CreateVerticalFacesStrategy strategy,
    const bool verbose
  ) noexcept;

  static std::vector<boost::shared_ptr<Face>> CreateHorizontalFaces(
    const boost::shared_ptr<const Template> t,
    const std::vector<boost::shared_ptr<Point>>& points,
    const int n_face_layers
  );

  static std::vector<boost::shared_ptr<Point>> CreatePoints(
    const boost::shared_ptr<const Template> t,
    const int n_face_layers,
    const boost::units::quantity<boost::units::si::length> layer_height
  );

  //Must be static: it is used in the constructor
  static std::vector<boost::shared_ptr<Face>> CreateVerticalFaces(
    const boost::shared_ptr<const Template> t,
    const std::vector<boost::shared_ptr<Point>>& points,
    const int n_face_layers,
    const boost::units::quantity<boost::units::si::length> layer_height,
    const CreateVerticalFacesStrategy strategy,
    const bool verbose
  ) noexcept;

  static std::vector<boost::shared_ptr<Face>> FindKnownFacesBetween(
    const boost::shared_ptr<const Face> a, const boost::shared_ptr<const Face> b
  );

  ///Adapter to call Geometry().IsPlane()
  static bool IsPlane(const std::vector<boost::shared_ptr<Point>>& v) noexcept;

  static bool IsSubset(
    std::vector<boost::shared_ptr<Point>> a,
    std::vector<boost::shared_ptr<Point>> b
  ) noexcept;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif

  friend void boost::checked_delete<>(      CellsCreator* x);
  friend void boost::checked_delete<>(const CellsCreator* x);
  friend class boost::detail::sp_ms_deleter<      CellsCreator>;
  friend class boost::detail::sp_ms_deleter<const CellsCreator>;
};

} //~namespace trim
} //~namespace ribi

#endif // RIBI_TRIANGLEMESHCELLSCREATOR_H
