#include "openfoamboundaryfileitem.h"

#include <cassert>
#include <iostream>

#include "trace.h"

ribi::foam::BoundaryFileItem::BoundaryFileItem(
  const std::string& name,
  const std::string& type,
  const int n_faces,
  const FaceIndex n_start_face
  )
  :
    m_n_faces{n_faces},
    m_name{name},
    m_start_face{n_start_face},
    m_type{type}
{
  #ifndef NDEBUG
  Test();
  #endif
  assert(m_n_faces >= 0);
  assert(m_start_face.Get() >= 0);
}

const ribi::foam::FaceIndex ribi::foam::BoundaryFileItem::GetEndFace() const noexcept
{
  return m_start_face + FaceIndex(m_n_faces);
}

#ifndef NDEBUG
void ribi::foam::BoundaryFileItem::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting ribi::foam::BoundaryFileItem::Test");
  const BoundaryFileItem i("some_name","some_type",123,FaceIndex(456));
  std::stringstream s;
  s << i;
  BoundaryFileItem j;
  s >> j;
  if (i != j)
  {
    TRACE(i);
    TRACE(j);
  }
  assert(i == j);
  TRACE("Finished ribi::foam::BoundaryFileItem::Test successfully");
}
#endif

bool ribi::foam::operator==(const BoundaryFileItem& lhs, const BoundaryFileItem& rhs)
{
  return
       lhs.GetName() == rhs.GetName()
    && lhs.GetNfaces() == rhs.GetNfaces()
    && lhs.GetStartFace() == rhs.GetStartFace()
    && lhs.GetType() == rhs.GetType()
  ;
}

bool ribi::foam::operator!=(const BoundaryFileItem& lhs, const BoundaryFileItem& rhs)
{
  return !(lhs == rhs);
}

std::ostream& ribi::foam::operator<<(std::ostream& os, const BoundaryFileItem& item)
{
  os
    << "  " << item.GetName() << '\n'
    << "  {" << '\n'
    << "    type " << item.GetType() << ";\n"
    << "    nFaces " << item.GetNfaces() << ";\n"
    << "    startFace " << item.GetStartFace() << ";\n"
    << "  }" << '\n';
  return os;
}

std::istream& ribi::foam::operator>>(std::istream& is, BoundaryFileItem& f)
{
  {
    is >> f.m_name;
  }
  {
    std::string bracket_open;
    is >> bracket_open;
    assert(bracket_open == std::string("{"));
  }
  {
    std::string type_text;
    is >> type_text;
    assert(type_text == std::string("type"));
  }
  {
    is >> f.m_type;
    assert(f.m_type.back() == ';');
    f.m_type.pop_back();
    assert(f.m_type.back() != ';');
  }
  {
    std::string n_faces_text;
    is >> n_faces_text;
    assert(n_faces_text == std::string("nFaces"));
  }
  {
    is >> f.m_n_faces;
  }
  {
    std::string semicolon;
    is >> semicolon;
    #ifndef NDEBUG
    if (semicolon != std::string(";"))
    {
      TRACE(semicolon);
    }
    #endif
    assert(semicolon == std::string(";"));
  }
  {
    std::string start_face_text;
    is >> start_face_text;
    #ifndef NDEBUG
    if (start_face_text != std::string("startFace"))
    {
      TRACE(start_face_text);
    }
    #endif
    assert(start_face_text == std::string("startFace"));
  }
  {
    is >> f.m_start_face;
  }
  {
    std::string semicolon;
    is >> semicolon;
    assert(semicolon == std::string(";"));
  }
  {
    std::string bracket_close;
    is >> bracket_close;
    assert(bracket_close == std::string("}"));
  }
  return is;
}
