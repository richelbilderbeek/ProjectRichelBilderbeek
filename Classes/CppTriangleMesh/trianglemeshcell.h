#ifndef RIBI_TRIANGLEMESHCELL_H
#define RIBI_TRIANGLEMESHCELL_H

#include <iosfwd>
#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <boost/checked_delete.hpp>
#include <boost/geometry.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/signals2.hpp>
#include "trianglemeshfwd.h"
#pragma GCC diagnostic pop

namespace ribi {
namespace trim {

///A Cell consists of Faces that surround the volume of the cell without openings
///Sure, the Faces can change...
class Cell
{
  friend class Dialog;
  friend class CellsCreator;
  friend class CellsCreatorFactory;
  friend class Face;
  friend class TriangleMeshBuilder;
  friend class TriangleMeshBuilderImpl;

  typedef boost::geometry::model::point<double,3,boost::geometry::cs::cartesian> Coordinat3D;

  std::vector<boost::shared_ptr<const Face>> GetFaces() const noexcept;
  std::vector<boost::shared_ptr<      Face>> GetFaces()       noexcept { return m_faces; }

  Coordinat3D CalculateCenter() const noexcept;

  int GetIndex() const noexcept { return m_index; }

  ///Sets the Faces of a Cell by their index
  void SetCorrectOrder() noexcept;

  void SetIndex(const int index) noexcept;

  static const int sm_cell_no_index = -2;

  private:
  ~Cell() noexcept;
  friend void boost::checked_delete<>(      Cell* x);
  friend void boost::checked_delete<>(const Cell* x);

  std::vector<boost::shared_ptr<Face>> m_faces;
  int m_index;

  friend class CellFactory;
  //Enforce that only CellFactory can create a Cell
  Cell(
    const std::vector<boost::shared_ptr<Face>>& faces,
    const int index,
    const CellFactory& lock
  );
  Cell(const Cell&) = delete;
  Cell(      Cell&&) = delete;
  Cell& operator=(const Cell& ) = delete;
  Cell& operator=(      Cell&&) = delete;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif

  friend bool operator==(const Cell& lhs, const Cell& rhs) noexcept;
  friend bool operator!=(const Cell& lhs, const Cell& rhs) noexcept;
  friend std::ostream& operator<<(std::ostream& os, const Cell& cell) noexcept;
};

bool operator==(const Cell& lhs, const Cell& rhs) noexcept;
bool operator!=(const Cell& lhs, const Cell& rhs) noexcept;
std::ostream& operator<<(std::ostream& os, const Cell& cell) noexcept;

bool operator<(const boost::shared_ptr<const Cell>& lhs, const boost::shared_ptr<      Cell>& rhs) = delete;
bool operator<(const boost::shared_ptr<const Cell>& lhs, const boost::shared_ptr<const Cell>& rhs) = delete;
bool operator<(const boost::shared_ptr<      Cell>& lhs, const boost::shared_ptr<      Cell>& rhs) = delete;
bool operator<(const boost::shared_ptr<      Cell>& lhs, const boost::shared_ptr<const Cell>& rhs) = delete;

} //~namespace trim
} //~namespace ribi

#endif // RIBI_TRIANGLEMESHCELL_H
