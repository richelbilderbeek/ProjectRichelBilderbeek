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
    const std::string& class_name = "",
    const std::string& location = "",
    const std::string& object = ""
  );

  const std::string& GetClass() const noexcept { return m_class_name; }
  const std::string& GetLocation() const noexcept { return m_location; }
  const std::string& GetObject() const noexcept { return m_object; }

  private:

  std::string m_class_name;
  std::string m_location;
  std::string m_object;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif

  friend std::istream& operator>>(std::istream& is, Header& h);
};

bool operator==(const Header& lhs, const Header& rhs);
bool operator!=(const Header& lhs, const Header& rhs);
std::ostream& operator<<(std::ostream& os, const Header& f);
std::istream& operator>>(std::istream& is, Header& h);

} //~namespace foam
} //~namespace ribi

#endif // OPENFOAMHEADER_H
