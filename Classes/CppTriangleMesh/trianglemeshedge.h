#ifndef TRIANGLEMESHEDGE_H
#define TRIANGLEMESHEDGE_H

#include <array>
#include <iosfwd>
#include <set>
#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/checked_delete.hpp>
#include <boost/geometry.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>
#include "trianglemeshfaceorientation.h"
#include "trianglemeshfwd.h"
#pragma GCC diagnostic pop

namespace ribi {
namespace trim {

///Sure, its points can change...
struct Edge
{
  Edge(const Edge&) = delete;
  Edge& operator=(const Edge&) = delete;

  const boost::shared_ptr<const Point> GetFrom() const noexcept { return m_points[0]; }
  const boost::shared_ptr<      Point> GetFrom()       noexcept { return m_points[0]; }

  int GetIndex() const noexcept { return m_index; }

  const boost::shared_ptr<const Point> GetTo() const noexcept { return m_points[1]; }
  const boost::shared_ptr<      Point> GetTo()       noexcept { return m_points[1]; }

  ///Reverse from and to
  void Reverse() noexcept;

  private:
  ~Edge() noexcept {}
  friend void boost::checked_delete<>(Edge* x);
  friend void boost::checked_delete<>(const Edge* x);

  ///Faces this Edge belongs to
  mutable std::vector<boost::weak_ptr<const Face>> m_belongs_to;

  ///The index of this Edge in an TriangleMeshBuilder vector. It is determined at the end
  mutable int m_index;

  ///m_points must be a std::vector instead of a std::set, as
  ///their orders matter (and changed by ReversePoints)
  std::array<boost::shared_ptr<Point>,2> m_points;

  friend class EdgeFactory;
  ///Enforce a Edge is only created by a EdgeFactory
  Edge(
    const std::array<boost::shared_ptr<Point>,2>& points,
    const int index,
    const EdgeFactory& lock
  );

  friend class FaceFactory;
  void AddBelongsTo(boost::weak_ptr<const Face> face) const;

  ///Determined in the end
  friend class TriangleMeshBuilder;
  void SetIndex(const int index) const noexcept { m_index = index; }

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif

  friend std::ostream& operator<<(std::ostream& os, const Edge& f);
};

bool operator==(const Edge& lhs, const Edge& rhs);
bool operator!=(const Edge& lhs, const Edge& rhs);
std::ostream& operator<<(std::ostream& os, const Edge& f);

} //~namespace trim
} //~namespace ribi

#endif // TRIANGLEMESHEDGE_H
