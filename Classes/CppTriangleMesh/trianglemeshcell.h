#ifndef TRIANGLEMESHCELL_H
#define TRIANGLEMESHCELL_H

#include <iosfwd>
#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/checked_delete.hpp>
#include <boost/shared_ptr.hpp>
#include "coordinat3d.h"
#include "trianglemeshfwd.h"
#pragma GCC diagnostic pop

namespace ribi {
namespace trim {

///A Cell consists of Faces that surround the volume of the cell without openings
///Sure, the Faces can change...
struct Cell
{
  const std::vector<boost::shared_ptr<const Face>> GetFaces() const noexcept;
  const std::vector<boost::shared_ptr<      Face>> GetFaces()       noexcept { return m_faces; }

  const ribi::Coordinat3D CalculateCenter() const noexcept;

  ///Can be used later
  int GetIndex() const noexcept { return m_index; }
  void SetIndex(const int index) noexcept { m_index = index; }

  private:
  ~Cell() noexcept {}
  friend void boost::checked_delete<>(Cell* x);
  friend void boost::checked_delete<>(const Cell* x);

  const std::vector<boost::shared_ptr<Face>> m_faces;
  int m_index;

  friend class CellFactory;
  Cell(const std::vector<boost::shared_ptr<Face>>& faces);

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

bool operator==(const Cell& lhs, const Cell& rhs);
bool operator!=(const Cell& lhs, const Cell& rhs);
std::ostream& operator<<(std::ostream& os, const Cell& cell);

} //~namespace trim
} //~namespace ribi

#endif // TRIANGLEMESHCELL_H
