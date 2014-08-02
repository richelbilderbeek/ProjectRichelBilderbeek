#include "openfoamboundaryfileitem.h"

#include <cassert>
#include <iostream>

#include "openfoampatchfieldtypes.h"
#include "testtimer.h"
#include "trace.h"

ribi::foam::BoundaryFileItem::BoundaryFileItem(
  const std::string& name,
  const PatchFieldType patch_field_type,
  const int n_faces,
  const FaceIndex n_start_face
  )
  :
    m_n_faces{n_faces},
    m_name{name},
    m_start_face{n_start_face},
    m_type{patch_field_type}
{
  #ifndef NDEBUG
  Test();
  #endif
  assert(m_n_faces >= 0);
  assert(m_start_face.Get() >= 0);
}

ribi::foam::FaceIndex ribi::foam::BoundaryFileItem::GetEndFace() const noexcept
{
  return m_start_face + FaceIndex(m_n_faces);
}

#ifndef NDEBUG
void ribi::foam::BoundaryFileItem::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
  const BoundaryFileItem i("some_name",PatchFieldType::empty,123,FaceIndex(456));
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
}
#endif

bool ribi::foam::operator==(const BoundaryFileItem& lhs, const BoundaryFileItem& rhs) noexcept
{
  return
       lhs.GetName() == rhs.GetName()
    && lhs.GetNfaces() == rhs.GetNfaces()
    && lhs.GetStartFace() == rhs.GetStartFace()
    && lhs.GetType() == rhs.GetType()
  ;
}

bool ribi::foam::operator!=(const BoundaryFileItem& lhs, const BoundaryFileItem& rhs) noexcept
{
  return !(lhs == rhs);
}

std::ostream& ribi::foam::operator<<(std::ostream& os, const BoundaryFileItem& item) noexcept
{
  os
    << "    " << item.GetName() << '\n'
    << "    {" << '\n'
    << "        type " << item.GetType() << ";\n"
    << "        nFaces " << item.GetNfaces() << ";\n"
    << "        startFace " << item.GetStartFace() << ";\n"
    << "    }" << '\n';
  return os;
}

std::istream& ribi::foam::operator>>(std::istream& is, BoundaryFileItem& f)
{
  {
    is >> f.m_name;
    assert(is);
  }
  {
    std::string bracket_open;
    is >> bracket_open;
    assert(is);
    assert(bracket_open == "{");
  }
  {
    std::string type_text;
    is >> type_text;
    assert(is);
    assert(type_text == "type");
  }
  {
    std::string type_str;
    is >> type_str;
    assert(is);
    assert(type_str.back() == ';');
    type_str.pop_back();
    assert(type_str.back() != ';');
    f.m_type = PatchFieldTypes::ToType(type_str);
  }
  {
    std::string n_faces_text;
    is >> n_faces_text;
    assert(is);
    assert(n_faces_text == "nFaces");
  }
  {
    is >> f.m_n_faces;
  }
  {
    std::string semicolon;
    is >> semicolon;
    assert(is);
    #ifndef NDEBUG
    if (semicolon != ";")
    {
      TRACE(semicolon);
    }
    #endif
    assert(semicolon == ";");
  }
  {
    std::string start_face_text;
    is >> start_face_text;
    assert(is);
    #ifndef NDEBUG
    if (start_face_text != "startFace")
    {
      TRACE(start_face_text);
    }
    #endif
    assert(start_face_text == "startFace");
  }
  {
    is >> f.m_start_face;
    assert(is);
  }
  {
    std::string semicolon;
    is >> semicolon;
    assert(is);
    assert(semicolon == ";");
  }
  {
    std::string bracket_close;
    is >> bracket_close;
    assert(is);
    assert(bracket_close == "}");
  }
  return is;
}
