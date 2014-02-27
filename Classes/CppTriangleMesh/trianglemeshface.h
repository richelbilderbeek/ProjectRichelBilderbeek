#ifndef TRIANGLEMESHFACE_H
#define TRIANGLEMESHFACE_H

#include <iosfwd>
#include <set>
#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/checked_delete.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>
#include "coordinat3d.h"
#include "trianglemeshfaceorientation.h"
#include "trianglemeshfwd.h"
#pragma GCC diagnostic pop

namespace ribi {
namespace trim {

///Sure, its points can change...
struct Face
{
  Face(const Face&) = delete;
  Face& operator=(const Face&) = delete;

  ///When the Face its points know their Layers, call DoExtractCoordinats
  bool CanExtractCoordinats() const noexcept;

  ///When the Face its points know their Layers, call this member function
  void DoExtractCoordinats() const;

  const std::set<ribi::Coordinat3D> GetCoordinats() const noexcept { return m_coordinats; }

  int GetIndex() const noexcept { return m_index; }

  ///nullptr if no neighbour
  const boost::shared_ptr<const Cell> GetNeighbour() const noexcept;

  FaceOrientation GetOrientation() const noexcept { return m_orientation; }

  ///nullptr if no owner, a Volume:m_cellindex type
  const boost::shared_ptr<const Cell> GetOwner() const noexcept;

  const boost::shared_ptr<const Point> GetPoint(const int index) const noexcept;

  const std::vector<boost::shared_ptr<Point>>& GetPoints() const noexcept { return m_points; }

  //void ReversePoints() noexcept;

  void SetBoundaryType(const std::string type) const noexcept { m_type = type; }

  ///Before saving a Face to OpenFOAM, its Points' winding needs to be set to the correct order:
  /// - if the Face is a boundary face, the normal needs to point outwards;
  ///   going away from the mesh; its points needs to be ordered clockwise
  ///   when viewed from its cell's center
  /// - if the Face is an internal face, the normal needs to point inside
  ///   the cell with the heighest index
  void SetCorrectWinding() noexcept;

  private:
  ~Face() noexcept {}
  friend void boost::checked_delete<>(Face* x);
  friend void boost::checked_delete<>(const Face* x);

  ///Cells this Face belongs to
  mutable std::vector<boost::weak_ptr<const Cell>> m_belongs_to;

  ///m_coordinats is used to speed up 'FaceExists', which compares a new Face
  ///with one already present, by comparing their sorted coordinats
  mutable std::set<ribi::Coordinat3D> m_coordinats;

  ///The index of this Face in an TriangleMeshBuilder vector. It is determined at the end
  mutable int m_index;

  const FaceOrientation m_orientation;

  ///m_points must be a std::vector instead of a std::set, as
  ///their orders matter (and changed by ReversePoints)
  std::vector<boost::shared_ptr<Point>> m_points;

  ///The type of boundary this Face belongs to. It is determined at the end
  ///By default it is BoundaryType::internalMesh: a Face that is between two cells
  mutable std::string m_type;

  friend class FaceFactory;
  ///Enforce a Face is only created by a FaceFactory
  Face(
    const std::vector<boost::shared_ptr<Point>>& points,
    const FaceOrientation any_orientation,
    const int index,
    const FaceFactory& lock
  );

  friend class CellFactory;
  void AddBelongsTo(boost::weak_ptr<const Cell> cell) const;

  ///Determined in the end
  friend class TriangleMeshBuilder;
  std::string GetBoundaryType() const noexcept { return m_type; }
  void SetIndex(const int index) const noexcept { m_index = index; }

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif

  friend std::ostream& operator<<(std::ostream& os, const Face& f);
};

bool operator==(const Face& lhs, const Face& rhs);
bool operator!=(const Face& lhs, const Face& rhs);
std::ostream& operator<<(std::ostream& os, const Face& f);

} //~namespace trim
} //~namespace ribi

#endif // TRIANGLEMESHFACE_H
