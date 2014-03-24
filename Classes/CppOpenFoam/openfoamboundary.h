#ifndef OPENFOAMBOUNDARY_H
#define OPENFOAMBOUNDARY_H

#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/shared_ptr.hpp>
#include "openfoamfwd.h"
#include "openfoampatchfieldtype.h"
#pragma GCC diagnostic pop

namespace ribi {
namespace foam {

///A Boundary contains Faces that form a surface boundary
struct Boundary
{
  explicit Boundary(
    const std::vector<boost::shared_ptr<Face> >& faces,
    const std::string& name,
    const PatchFieldType type
  ) noexcept;

  const std::vector<boost::shared_ptr<      Face> >& GetFaces() noexcept { return m_faces; }
        std::vector<boost::shared_ptr<const Face> >  GetFaces() const noexcept;
  const std::string& GetName() const noexcept { return m_name; }
  PatchFieldType GetType() const noexcept { return m_type; }


  private:
  const std::vector<boost::shared_ptr<Face> > m_faces;
  const std::string m_name;
  const PatchFieldType m_type;

  friend std::ostream& operator<<(std::ostream& os, const Boundary& boundary) noexcept;
};

std::ostream& operator<<(std::ostream& os, const Boundary& boundary) noexcept;

} //namespace foam
} //namespace ribi

#endif // OPENFOAMBOUNDARY_H
