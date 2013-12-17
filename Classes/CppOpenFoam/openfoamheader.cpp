#include "openfoamheader.h"

#include <cassert>
#include <ostream>
#include <sstream>
#include <stdexcept>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/algorithm/string/trim.hpp>

#include "fileio.h"
#include "trace.h"
#pragma GCC diagnostic pop

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
  assert( (location.empty() || location[0] != '\"' )
    && "A location may not start with a quotation mark"
  );
  assert( (location.empty() || location[ location.size() - 1 ] != '\"' )
    && "A location may not end with a quotation mark"
  );
  #endif
}

void ribi::foam::Header::CleanFile(
  const std::string& filename) noexcept
{
  #ifndef NDEBUG
  if(!fileio::IsRegularFile(filename))
  {
    TRACE("ERROR");
  }
  #endif

  assert(fileio::IsRegularFile(filename));
  //v is dirty
  const std::vector<std::string> v { fileio::FileToVector(filename) };
  //w will be clean
  std::vector<std::string> w;
  std::transform(v.begin(),v.end(),std::back_inserter(w),
    [](std::string s)
    {
      std::replace(s.begin(),s.end(),'\t',' ');
      boost::algorithm::trim(s);
      if (s.size() >= 2 && s.substr(0,2) == "//") s = std::string();
      return s;
    }
  );
  //w is clean
  assert(fileio::IsRegularFile(filename));
  fileio::VectorToFile(w,filename,fileio::CopyMode::allow_overwrite);
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
  if (lhs.GetClass() != rhs.GetClass())
  {
    //TRACE("Classes differ:");
    //TRACE(lhs.GetClass());
    //TRACE(rhs.GetClass());
    return false;
  }
  //Compare location independent of OS path seperator
  {
    std::string lhs_location = lhs.GetLocation();
    std::string rhs_location = rhs.GetLocation();
    std::replace(lhs_location.begin(),lhs_location.end(),'\\','/');
    std::replace(rhs_location.begin(),rhs_location.end(),'\\','/');
    if (lhs_location != rhs_location)
    {
      //TRACE("Locations differ:");
      //TRACE(lhs.GetLocation());
      //TRACE(rhs.GetLocation());
      return false;
    }
  }
  if (lhs.GetObject() != rhs.GetObject())
  {
    //TRACE("Object differ:");
    //TRACE(lhs.GetObject());
    //TRACE(rhs.GetObject());
    return false;
  }
  return true;
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
    << "  location \"" << f.GetLocation() << "\";\n"
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
    assert(is);
    while (title != "FoamFile")
    {
      assert(title.size() >= 2);

      //Eat comment
      if (title.substr(0,2) == std::string("/*"))
      {
        std::string s;
        while (s.size() < 2 || s.substr(s.size()-2,2) != std::string("*/"))
        {
          is >> s;
          assert(is);
        }
      }
      //Try reading title after comment again
      is >> title;
      assert(is);
    }
    if (title != "FoamFile")
    {
      std::stringstream s;
      s << "Stream incorrectly assumed to be an OpenFOAM header. "
        << "OpenFOAM header start with 'FoamFile'. "
        << "This file starts with  '"
        << title << "' instead";
      throw std::runtime_error(s.str());
    }
  }
  {
    std::string bracket_open;
    is >> bracket_open;
    assert(is);
    assert(bracket_open == "{");
  }
  while (1)
  {
    std::string s;
    is >> s;
    assert(is);
    if (s == "version")
    {
      std::string t;
      is >> t;
      assert(is);
      assert(t == "2.0;"  );
    }
    else if (s == "format" )
    {
      std::string t;
      is >> t;
      assert(is);
      assert(t == "ascii;");
    }
    else if (s == "class"  )
    {
      std::string class_name;
      is >> class_name;
      assert(is);
      assert(class_name.back() == ';');
      class_name.pop_back();
      assert(class_name.back() != ';');
      h.m_class_name = class_name;
    }
    else if (s == "location")
    {
      std::string location;
      is >> location;
      assert(is);
      assert(location.size() > 3);
      assert(location[0] == '\"');
      assert(location[ location.size() - 2] == '\"');
      assert(location[ location.size() - 1] == ';');
      location = location.substr(1,location.size() - 3);

      assert( (location.empty() || location[0] != '\"' )
        && "A location may not start with a quotation mark"
      );
      assert( (location.empty() || location[ location.size() - 1 ] != '\"' )
        && "A location may not end with a quotation mark"
      );
      assert( (location.empty() || location[ location.size() - 1 ] != ';' )
        && "A location may not end with a semicolon"
      );

      h.m_location = location;
    }
    else if (s == "note")
    {
      //Read until ;
      std::string s;
      is >> s;
      assert(is);
      assert(!s.empty());
      while (s.back() != ';')
      {
        std::string t;
        is >> t;
        assert(is);
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
      assert(is);
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
