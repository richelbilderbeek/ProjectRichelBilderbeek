#ifndef OPENFOAMBOUNDARY_H
#define OPENFOAMBOUNDARY_H

#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/shared_ptr.hpp>
#include "openfoamfwd.h"
#pragma GCC diagnostic pop

namespace ribi {
namespace foam {

///A Boundary contains Faces that form a surface boundary
struct Boundary
{
  Boundary(
    const std::vector<boost::shared_ptr<Face> >& faces,
    const std::string& name,
    const std::string& type
  );

  private:
  const std::vector<boost::shared_ptr<Face> > m_faces;
  const std::string m_name;
  const std::string m_type;
};

} //namespace foam
} //namespace ribi

#endif // OPENFOAMBOUNDARY_H
