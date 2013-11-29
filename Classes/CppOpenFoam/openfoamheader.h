#ifndef OPENFOAMHEADER_H
#define OPENFOAMHEADER_H

#include <iosfwd>
#include <string>

namespace ribi {
namespace foam {

///The header that is above all OpenFoam files
struct Header
{
  ///In order of appearance in the text
  Header(
    const std::string& class_name,
    const std::string& location,
    const std::string& object
  );

  private:

  const std::string m_class_name;
  const std::string m_location;
  const std::string m_object;

  friend std::ostream& operator<<(std::ostream& os, const Header& f);
};

std::ostream& operator<<(std::ostream& os, const Header& f);

} //~namespace foam
} //~namespace ribi

#endif // OPENFOAMHEADER_H
