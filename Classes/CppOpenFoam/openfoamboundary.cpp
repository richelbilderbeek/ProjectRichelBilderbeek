#include "openfoamboundary.h"

ribi::foam::Boundary::Boundary(
  const std::vector<boost::shared_ptr<Face> >& faces,
  const std::string& name,
  const std::string& type
  )
  : m_faces(faces),
    m_name(name),
    m_type(type)
{

}
