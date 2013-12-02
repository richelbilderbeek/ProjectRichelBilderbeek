#include "openfoamheader.h"

#include <cassert>
#include <ostream>

#include "trace.h"

ribi::foam::Header::Header(
    const std::string& class_name,
    const std::string& location,
    const std::string& object
  )
  : m_class_name(class_name),
    m_location(location),
    m_object(object)
{
  #ifndef NDEBUG
  Test();
  #endif
}

#ifndef NDEBUG
void ribi::foam::Header::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting ribi::foam::Header::Test");
  const Header h("some_name","some_location","some_object");
  std::stringstream s;
  s << h;
  Header i;
  s >> i;
  if (h != i)
  {
    TRACE(h);
    TRACE(i);
  }
  assert(h == i);
  TRACE("Finished ribi::foam::Header::Test successfully");
}
#endif

bool ribi::foam::operator==(const ribi::foam::Header& lhs, const ribi::foam::Header& rhs)
{
  return
       lhs.GetClass()    == rhs.GetClass()
    && lhs.GetLocation() == rhs.GetLocation()
    && lhs.GetObject()   == rhs.GetObject()
  ;
}

bool ribi::foam::operator!=(const ribi::foam::Header& lhs, const ribi::foam::Header& rhs)
{
  return !(lhs == rhs);
}

std::ostream& ribi::foam::operator<<(std::ostream& os, const Header& f)
{
  os
    << "FoamFile" << '\n'
    << "{" << '\n'
    << "  version  " << "2.0"           << ";\n"
    << "  format   " << "ascii"         << ";\n"
    << "  class    " << f.GetClass()    << ";\n"
    << "  location " << f.GetLocation() << ";\n"
    << "  object   " << f.GetObject()   << ";\n"
    << "}" << '\n'
  ;
  return os;
}

std::istream& ribi::foam::operator>>(std::istream& is, Header& h)
{
  {
    std::string title;
    is >> title;
    assert(title == "FoamFile");
  }
  {
    std::string bracket_open;
    is >> bracket_open;
    assert(bracket_open == "{");
  }
  {
    std::string version_text;
    is >> version_text;
    assert(version_text == "version");
  }
  {
    std::string version;
    is >> version;
    assert(version == "2.0;");
  }
  {
    std::string format_text;
    is >> format_text;
    assert(format_text == "format");
  }
  {
    std::string format;
    is >> format;
    assert(format == "ascii;");
  }
  {
    std::string class_name_text;
    is >> class_name_text;
    assert(class_name_text == "class");
  }
  {
    std::string class_name;
    is >> class_name;
    assert(class_name.back() == ';');
    class_name.pop_back();
    assert(class_name.back() != ';');
    h.m_class_name = class_name;
  }
  {
    std::string location_text;
    is >> location_text;
    #ifndef NDEBUG
    if(location_text != "location") { TRACE(location_text); }
    #endif
    assert(location_text == "location");
  }
  {
    std::string location;
    is >> location;
    assert(location.back() == ';');
    location.pop_back();
    assert(location.back() != ';');
    h.m_location = location;
  }
  {
    std::string object_text;
    is >> object_text;
    assert(object_text == "object");
  }
  {
    std::string object;
    is >> object;
    assert(object.back() == ';');
    object.pop_back();
    assert(object.back() != ';');
    h.m_object = object;
  }
  {
    std::string bracket_close;
    is >> bracket_close;
    assert(bracket_close == "}");
  }
  return is;
}
