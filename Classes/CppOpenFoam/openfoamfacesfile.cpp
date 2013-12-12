#include "openfoamfacesfile.h"

#include <cassert>
#include <fstream>
#include <iostream>
#include <stdexcept>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"

#include <boost/algorithm/string/trim.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/lexical_cast.hpp>

#include <QFile>

#include "filename.h"
#include "openfoamheader.h"
#include "openfoamfacesfileitem.h"
#include "openfoamfaceindex.h"
#include "openfoamparseerror.h"
#include "trace.h"
#pragma GCC diagnostic pop


ribi::foam::FacesFile::FacesFile(
  const Header header,
  const std::vector<FacesFileItem>& items)
  : m_header{header},
    m_items(items)
{
  #ifndef NDEBUG
  Test();
  #endif
}

bool ribi::foam::FacesFile::CanGetItem(const ribi::foam::FaceIndex& face_index) const noexcept
{
  assert(face_index.Get() >= 0);
  return face_index.Get() < static_cast<int>(m_items.size());
}

const ribi::foam::Header ribi::foam::FacesFile::GetDefaultHeader() noexcept
{
  return Header("faceList","constant/polyMesh","","faces");
}

const ribi::foam::FacesFileItem& ribi::foam::FacesFile::GetItem(const ribi::foam::FaceIndex& face_index) const noexcept
{
  assert(CanGetItem(face_index));
  return m_items[ face_index.Get() ];
}

const ribi::foam::FaceIndex ribi::foam::FacesFile::GetMaxFaceIndex() const noexcept
{
  return FaceIndex(static_cast<int>(m_items.size()));
}

const ribi::foam::FacesFile ribi::foam::FacesFile::Parse(std::istream& is)
{
  FacesFile b;
  is >> b;
  return b;
}

#ifndef NDEBUG
void ribi::foam::FacesFile::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting ribi::foam::FacesFile::Test");
  //Some initial data
  const Header header("some_name","some_location","some_object");
  std::vector<FacesFileItem> items;
  for (int i=1; i!=4; ++i)
  {
    FacesFileItem item( std::vector<PointIndex>(i,PointIndex(i)));
    items.push_back(item);
  }
  //operator==
  {
    const FacesFile b(header,items);
    const FacesFile c(header,items);
    assert(header == header);
    assert(b == c);
  }
  //operator!=
  {
    const FacesFile b(header,items);
    const Header other_header("some_other_name","some_other_location","some_other_object");
    assert(header != other_header);
    const FacesFile c(other_header,items);
    assert(b != c);
  }
  //operator!=
  {
    const FacesFile b(header,items);
    std::vector<FacesFileItem> other_items;
    for (int i=1; i!=3; ++i)
    {
      FacesFileItem item( std::vector<PointIndex>(i+1,PointIndex(i*i)) );
      other_items.push_back(item);
    }
    const FacesFile c(header,other_items);
    assert(b != c);
  }
  //Stream conversion
  {
    const FacesFile b(header,items);
    std::stringstream s;
    s << b;
    FacesFile c;
    s >> c;
    if (b != c)
    {
      TRACE(b);
      TRACE(c);
    }
    assert(b == c);
  }
  //Read from testing file
  {
    const std::string filename { GetDefaultHeader().GetObject() };
    {
      QFile f( (std::string(":/CppOpenFoam/files/") + filename).c_str() );
      f.copy(filename.c_str());
    }
    {
      assert(fileio::IsRegularFile(filename));
      std::ifstream f(filename.c_str());
      FacesFile b(f);
      assert(!b.GetItems().empty());
    }
  }
  TRACE("Finished ribi::foam::Header::FacesFile successfully");
}
#endif

bool ribi::foam::operator==(const FacesFile& lhs,const FacesFile& rhs)
{
  if (lhs.GetHeader() != rhs.GetHeader())
  {
    return false;
  }
  const std::vector<FacesFileItem>& lhs_items = lhs.GetItems();
  const std::vector<FacesFileItem>& rhs_items = rhs.GetItems();
  if (lhs_items.size() != rhs_items.size())
  {
    return false;
  }
  return std::equal(lhs_items.begin(),lhs_items.end(),rhs_items.begin());
}

bool ribi::foam::operator!=(const FacesFile& lhs,const FacesFile& rhs)
{
  return !(lhs == rhs);
}

std::istream& ribi::foam::operator>>(std::istream& is, FacesFile& f)
{
  assert(f.m_items.empty()); //Make empty otherwise

  //Read header
  is >> f.m_header;

  //Read items
  int n_items = 0;
  {
    is >> n_items;
    assert(n_items > 0);
    TRACE(n_items);
  }
  {
    std::string bracket_open;
    is >> bracket_open;
    assert(bracket_open == "(");
  }
  for (int i=0; i!=n_items; ++i)
  {
    try
    {
      FacesFileItem item;
      is >> item;
      f.m_items.push_back(item);
    }
    catch(ParseError&)
    {
      throw ParseError("faces",i + f.m_header.GetNumberOfLines());
    }
  }
  {
    std::string bracket_close;
    is >> bracket_close;
    assert(bracket_close == ")");
  }
  return is;
}

std::ostream& ribi::foam::operator<<(std::ostream& os, const FacesFile& f)
{
  os
    << f.GetHeader() << '\n'
    << "" << '\n'
    << f.m_items.size() << '\n'
    << "(" << '\n'
  ;

  for(const FacesFileItem item: f.m_items)
  {
    os << item << '\n';
  }

  os
    << ")" << '\n'
  ;
  return os;
}
