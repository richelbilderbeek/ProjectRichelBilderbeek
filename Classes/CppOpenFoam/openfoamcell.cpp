#include "openfoamcell.h"

ribi::foam::Cell::Cell(
    const std::vector<boost::shared_ptr<Face> >& faces,
    const boost::shared_ptr<Cell> neighbour
  )
  : m_faces(faces),
    m_neighbour(neighbour)
{

}
