#include "openfoamheader.h"

#include <cassert>
#include <ostream>

#include "trace.h"

ribi::foam::Header::Header(
    const std::string& class_name,
    const std::string& location,
    const std::string& note,
    const std::string& object
  )
  : m_class_name(class_name),
    m_location(location),
    m_note(note),
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
  const Header h("some_name","some_location","some_note","some_object");
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
    if (title != "FoamFile")
    {
      std::stringstream s;
      s << "Stream assumed to be an OpenFOAM header,"
        << "does not start with 'FoamFile', but with '"
        << title << "' instead";
      throw std::runtime_error(s.str());
    }
  }
  {
    std::string bracket_open;
    is >> bracket_open;
    assert(bracket_open == "{");
  }
  while (1)
  {
    std::string s;
    is >> s;
    if (s == "version")
    {
      std::string t;
      is >> t;
      assert(t == "2.0;"  );
    }
    else if (s == "format" )
    {
      std::string t;
      is >> t;
      assert(t == "ascii;");
    }
    else if (s == "class"  )
    {
      std::string class_name;
      is >> class_name;
      assert(class_name.back() == ';');
      class_name.pop_back();
      assert(class_name.back() != ';');
      h.m_class_name = class_name;
    }
    else if (s == "location")
    {
      std::string location;
      is >> location;
      assert(location.back() == ';');
      location.pop_back();
      assert(location.back() != ';');
      h.m_location = location;
    }
    else if (s == "note")
    {
      //Read until ;
      std::string s;
      is >> s;
      assert(!s.empty());
      while (s.back() != ';')
      {
        std::string t;
        is >> t;
        s += t;
      }
      assert(s.back() == ';');
      s.pop_back();
      assert(s.back() != ';');
      h.m_note = s;
    }
    else if (s == "object")
    {
      std::string object;
      is >> object;
      assert(object.back() == ';');
      object.pop_back();
      assert(object.back() != ';');
      h.m_object = object;
    }
    else if (s == "}")
    {
      break;
    }
  }
  return is;
}
