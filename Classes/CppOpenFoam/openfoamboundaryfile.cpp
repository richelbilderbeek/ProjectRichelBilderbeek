#include "openfoamboundaryfile.h"

#include <cassert>
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
#include "fileio.h"
#include "openfoamheader.h"
#include "openfoamboundaryfileitem.h"
#include "trace.h"
#pragma GCC diagnostic pop


ribi::foam::BoundaryFile::BoundaryFile(
  const Header header,
  const std::vector<BoundaryFileItem>& items)
  : m_header{header},
    m_items(items)
{
  #ifndef NDEBUG
  Test();
  #endif
}

bool ribi::foam::BoundaryFile::CanGet(const FaceIndex& face_index) const noexcept
{
  for (const BoundaryFileItem& item: m_items)
  {
    const int i = face_index.Get();
    const int min = item.GetStartFace().Get();
    const int max = min + item.GetNfaces();
    if (i >= min && i < max) return true;
  }
  return false;
}

ribi::foam::BoundaryFileItem& ribi::foam::BoundaryFile::Find(const FaceIndex& face_index) noexcept
{
  assert(CanGet(face_index));
  const int sz = static_cast<int>(m_items.size());
  for (int i=0; i!=sz; ++i)
  {
    const int j = face_index.Get();
    const int min = m_items[i].GetStartFace().Get();
    const int max = min + m_items[i].GetNfaces();
    if (j >= min && j < max) return m_items[i];
  }
  assert(!"Should not get here");
  throw std::logic_error("ribi::foam::BoundaryFile::Find");
}

const ribi::foam::Header ribi::foam::BoundaryFile::GetDefaultHeader() noexcept
{
  const std::string class_name = "polyBoundaryMesh";
  const std::string location   = "constant" + fileio::GetPathSeperator() + "polyMesh";
  const std::string note       = "";
  const std::string object     = "boundary";

  return Header(class_name,location,note,object);
}

const ribi::foam::BoundaryFile ribi::foam::BoundaryFile::Parse(std::istream& is)
{
  BoundaryFile b;
  is >> b;
  return b;
}

#ifndef NDEBUG
void ribi::foam::BoundaryFile::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting ribi::foam::BoundaryFile::Test");
  //Some initial data
  const Header header("some_name","some_location","some_object");
  std::vector<BoundaryFileItem> items;
  for (int i=1; i!=4; ++i)
  {
    const std::string name = "some_name" + boost::lexical_cast<std::string>(i);
    const std::string type = "some_type" + boost::lexical_cast<std::string>(i);
    const int n_faces = i;
    const FaceIndex start_face(i * i);
    BoundaryFileItem item(name,type,n_faces,start_face);
    items.push_back(item);
  }
  //operator==
  {
    const BoundaryFile b(header,items);
    const BoundaryFile c(header,items);
    assert(header == header);
    assert(b == c);
  }
  //operator!=
  {
    const BoundaryFile b(header,items);
    const Header other_header("some_other_name","some_other_location","some_other_object");
    assert(header != other_header);
    const BoundaryFile c(other_header,items);
    assert(b != c);
  }
  //operator!=
  {
    const BoundaryFile b(header,items);
    std::vector<BoundaryFileItem> other_items;
    for (int i=1; i!=3; ++i)
    {
      const std::string name = "some_other_name" + boost::lexical_cast<std::string>(i);
      const std::string type = "some_other_type" + boost::lexical_cast<std::string>(i);
      const int n_faces = i + 123;
      const FaceIndex start_face((i * i) + 456);
      BoundaryFileItem item(name,type,n_faces,start_face);
      other_items.push_back(item);
    }
    const BoundaryFile c(header,other_items);
    assert(b != c);
  }
  //Stream conversion
  {
    const BoundaryFile b(header,items);
    std::stringstream s;
    s << b;
    BoundaryFile c;
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
      BoundaryFile b(f);
      assert(!b.GetItems().empty());
    }
  }
  TRACE("Finished ribi::foam::Header::BoundaryFile successfully");
}
#endif

bool ribi::foam::operator==(const BoundaryFile& lhs,const BoundaryFile& rhs)
{
  if (lhs.GetHeader() != rhs.GetHeader())
  {
    //TRACE(lhs.GetHeader());
    //TRACE(rhs.GetHeader());
    return false;
  }
  const std::vector<BoundaryFileItem>& lhs_items = lhs.GetItems();
  const std::vector<BoundaryFileItem>& rhs_items = rhs.GetItems();
  if (lhs_items.size() != rhs_items.size())
  {
    //TRACE(lhs_items.size());
    //TRACE(rhs_items.size());
    return false;
  }
  return std::equal(lhs_items.begin(),lhs_items.end(),rhs_items.begin());
  /*
  const std::size_t n_items = lhs_items.size();
  for (std::size_t i=0; i!=n_items; ++i)
  {
    if (lhs_items[i] != rhs_items[i])
    {
      TRACE(lhs_items[i]);
      TRACE(rhs_items[i]);
      return false;
    }
  }
  return true;
  */
}

bool ribi::foam::operator!=(const BoundaryFile& lhs,const BoundaryFile& rhs)
{
  return !(lhs == rhs);
}

std::istream& ribi::foam::operator>>(std::istream& is, BoundaryFile& f)
{
  assert(f.m_items.empty()); //Make empty otherwise

  //Read header
  is >> f.m_header;

  //Read items
  int n_items = 0;
  {
    is >> n_items;
    assert(n_items > 0);
  }
  {
    std::string bracket_open;
    is >> bracket_open;
    assert(bracket_open == "(");
  }
  for (int i=0; i!= n_items; ++i)
  {
    BoundaryFileItem item;
    is >> item;
    f.m_items.push_back(item);
  }
  {
    std::string bracket_close;
    is >> bracket_close;
    assert(bracket_close == ")");
  }
  return is;
}

std::ostream& ribi::foam::operator<<(std::ostream& os, const BoundaryFile& f)
{
  os
    << f.GetHeader() << '\n'
    << "" << '\n'
    << f.m_items.size() << '\n'
    << "(" << '\n'
  ;

  for(const BoundaryFileItem item: f.m_items)
  {
    os << item << '\n';
  }

  os
    << ")" << '\n'
  ;
  return os;
}
