#include "openfoamface.h"

ribi::foam::Face::Face(
  const boost::shared_ptr<CellIndex> neighbour,
  const boost::shared_ptr<CellIndex> owner,
  const std::vector<Point>& points
)
  : m_neighbour(neighbour),
    m_owner(owner),
    m_points(points)
{

}
