#include "openfoamheader.h"

#include <ostream>

ribi::foam::Header::Header(
    const std::string& class_name,
    const std::string& location,
    const std::string& object
  )
  : m_class_name(class_name),
    m_location(location),
    m_object(object)
{

}

std::ostream& ribi::foam::operator<<(std::ostream& os, const Header& f)
{
  os
    << "FoamFile" << '\n'
    << "{" << '\n'
    << "  version  " << "2.0"          << ";\n"
    << "  format   " << "ascii"        << ";\n"
    << "  class    " << f.m_class_name << ";\n"
    << "  location " << f.m_location   << ";\n"
    << "  object   " << f.m_object     << ";\n"
    << "}" << '\n'
  ;
  return os;
}
