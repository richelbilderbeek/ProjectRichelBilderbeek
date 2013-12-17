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
#include "openfoamboundaryindex.h"
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

const ribi::foam::BoundaryFileItem ribi::foam::BoundaryFile::GetItem(const ribi::foam::BoundaryIndex& boundary_index) const noexcept
{
  assert(boundary_index.Get() >= 0);
  assert(boundary_index < GetMaxBoundaryIndex());
  return m_items[ boundary_index.Get() ];
}

const ribi::foam::BoundaryIndex ribi::foam::BoundaryFile::GetMaxBoundaryIndex() const noexcept
{
  return BoundaryIndex(static_cast<int>(m_items.size()));
}

const ribi::foam::BoundaryFile ribi::foam::BoundaryFile::Parse(std::istream& is)
{
  BoundaryFile b;
  is >> b;
  assert(is);
  return b;
}

const ribi::foam::BoundaryFile ribi::foam::BoundaryFile::Parse(const std::string& filename)
{
  const std::string tmp_filename { fileio::GetTempFileName() };
  fileio::CopyFile(filename,tmp_filename);
  Header::CleanFile(tmp_filename);
  std::ifstream f(tmp_filename.c_str());
  const ribi::foam::BoundaryFile file { Parse(f) };
  f.close();
  fileio::DeleteFile(tmp_filename);
  return file;
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
  for (int test_index = 0; test_index!=5; ++test_index)
  {
    std::string filename_appendix;
    switch (test_index)
    {
      case 0: filename_appendix = "_1x1x1"; break;
      case 1: filename_appendix = "_1x1x2"; break;
      case 2: filename_appendix = "_1x2x2"; break;
      case 3: filename_appendix = "_2x2x2"; break;
      case 4: filename_appendix = "_3x4x5"; break;
      default: assert(!"Should never get here");
        throw std::logic_error("foam::Files::CreateTestFiles: unknown test index");
    }
    assert(!filename_appendix.empty());
    const std::string filename_base { GetDefaultHeader().GetObject() };
    const std::string filename = filename_base + filename_appendix;
    const std::string resources_path { ":/CppOpenFoam/files/" + filename };

    {
      QFile f( resources_path.c_str() );
      f.copy(filename.c_str());
    }
    {
      if (!fileio::IsRegularFile(filename))
      {
        TRACE("ERROR");
        TRACE(filename);
      }
      assert(fileio::IsRegularFile(filename));
      BoundaryFile b(filename);
      if (b.GetItems().empty())
      {
        TRACE("ERROR");
      }
      assert( (!b.GetItems().empty() || b.GetItems().empty())
        && "If a mesh has no non-boundary cells, neighbour can be empty");
    }
  }
  TRACE("Finished ribi::foam::Header::BoundaryFile successfully");
}
#endif

bool ribi::foam::operator==(const BoundaryFile& lhs,const BoundaryFile& rhs)
{
  if (lhs.GetHeader() != rhs.GetHeader())
  {
    //TRACE("Headers differ:");
    //TRACE(lhs.GetHeader());
    //TRACE(rhs.GetHeader());
    return false;
  }
  const std::vector<BoundaryFileItem>& lhs_items = lhs.GetItems();
  const std::vector<BoundaryFileItem>& rhs_items = rhs.GetItems();
  if (lhs_items.size() != rhs_items.size())
  {
    //TRACE("Number of items differ:");
    //TRACE(lhs_items.size());
    //TRACE(rhs_items.size());
    return false;
  }
  const bool all_items_equal {
    std::equal(lhs_items.begin(),lhs_items.end(),rhs_items.begin())
  };
  //if (!all_items_equal)
  //{
  //  TRACE("Items differ:");
  //  TRACE(all_items_equal);
  //}
  return all_items_equal;
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
  assert(is);

  //Read items
  int n_items = 0;
  char opening_bracket = '\0';
  {
    //Eat comment
    char c = '\0';
    is >> c;
    assert(is);
    if (c >= '0' && c <= '9')
    {
      while (c != '(' && c != '{')
      {
        //Start eating n_items
        n_items *= 10;
        const int n = c - '0';
        assert(n >= 0 && n <= 9);
        n_items += n;
        is >> c;
        assert(is);
      }
    }
    opening_bracket = c;
    #ifndef NDEBUG
    if (!(opening_bracket == '(' || opening_bracket == '{'))
    {
      TRACE(opening_bracket);
      TRACE("ERROR");
    }
    #endif
    assert(opening_bracket == '(' || opening_bracket == '{');
  }
  assert(opening_bracket == '(' || opening_bracket == '{');
  if (opening_bracket == '(')
  {
    for (int i=0; i!=n_items; ++i)
    {
      BoundaryFileItem item;
      is >> item;
      assert(is);
      f.m_items.push_back(item);
    }
  }
  else
  {
    assert(opening_bracket == '{');
    //Read once, push n_items times
    BoundaryFileItem item;
    is >> item;
    assert(is);
    for (int i=0; i!=n_items; ++i)
    {
      f.m_items.push_back(item);
    }
  }
  //Eat comments until bracket close
  {
    char bracket_close = '\0';
    while (bracket_close != ')' && bracket_close != '}')
    {
      is >> bracket_close;
      assert(is);
    }
    assert(bracket_close == ')' || bracket_close == '}');
    assert(
         (opening_bracket == '(' && bracket_close == ')')
      || (opening_bracket == '{' && bracket_close == '}')
    );
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
