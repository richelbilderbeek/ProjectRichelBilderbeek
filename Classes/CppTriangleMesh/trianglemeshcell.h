#ifndef TRIANGLEMESHCELL_H
#define TRIANGLEMESHCELL_H

#include <iosfwd>
#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/checked_delete.hpp>
#include <boost/geometry.hpp>
#include <boost/shared_ptr.hpp>
#include "trianglemeshfwd.h"
#pragma GCC diagnostic pop

namespace ribi {
namespace trim {

///A Cell consists of Faces that surround the volume of the cell without openings
///Sure, the Faces can change...
struct Cell
{
  typedef boost::geometry::model::point<double,3,boost::geometry::cs::cartesian> Coordinat3D;

  std::vector<boost::shared_ptr<const Face>> GetFaces() const noexcept;
  std::vector<boost::shared_ptr<      Face>> GetFaces()       noexcept { return m_faces; }

  Coordinat3D CalculateCenter() const noexcept;

  int GetIndex() const noexcept { return m_index; }

  ///Sets the Faces of a Cell by their index
  void SetCorrectOrder() noexcept;

  void SetIndex(const int index) noexcept { m_index = index; }

  private:
  ~Cell() noexcept {}
  friend void boost::checked_delete<>(Cell* x);
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

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
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

#endif // TRIANGLEMESHCELL_H
