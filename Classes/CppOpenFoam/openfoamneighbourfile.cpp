#include "openfoamneighbourfile.h"

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


#include "fileio.h"
#include "openfoamheader.h"
#include "openfoamneighbourfileitem.h"
#include "openfoamfaceindex.h"
#include "testtimer.h"
#include "trace.h"
#pragma GCC diagnostic pop


ribi::foam::NeighbourFile::NeighbourFile(
  const Header header,
  const std::vector<NeighbourFileItem>& items)
  : m_header{header},
    m_items(items)
{
  #ifndef NDEBUG
  Test();
  #endif
}

bool ribi::foam::NeighbourFile::CanGetItem(
  const FaceIndex& face_index) const noexcept
{
  assert(face_index.Get() >= 0);
  return face_index.Get() < static_cast<int>(m_items.size());
}

ribi::foam::Header ribi::foam::NeighbourFile::GetDefaultHeader() noexcept
{
  return Header("labelList","constant/polyMesh","","neighbour");
}

const ribi::foam::NeighbourFileItem& ribi::foam::NeighbourFile::GetItem(
  const FaceIndex& face_index) const noexcept
{
  #ifndef NDEBUG
  if(!CanGetItem(face_index))
  {
    TRACE("BREAK");
  }
  #endif
  assert(CanGetItem(face_index));
  return m_items[ static_cast<int>(face_index.Get()) ];
}

ribi::foam::NeighbourFile ribi::foam::NeighbourFile::Parse(std::istream& is)
{
  NeighbourFile b;
  is >> b;
  assert(is);
  return b;
}

ribi::foam::NeighbourFile ribi::foam::NeighbourFile::Parse(const std::string& filename)
{
  const std::string tmp_filename { fileio::FileIo().GetTempFileName() };
  fileio::FileIo().CopyFile(filename,tmp_filename);
  Header::CleanFile(tmp_filename);
  std::ifstream f(tmp_filename.c_str());
  const NeighbourFile file { Parse(f) };
  f.close();
  fileio::FileIo().DeleteFile(tmp_filename);
  return file;
}

void ribi::foam::NeighbourFile::SetItem(const FaceIndex& face_index, const NeighbourFileItem& item) noexcept
{
  assert(face_index.Get() >= 0);
  assert(face_index.Get() < static_cast<int>(m_items.size()));
  m_items[ face_index.Get() ] = item;
  assert(GetItem(face_index) == item);
}

#ifndef NDEBUG
void ribi::foam::NeighbourFile::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
  //Some initial data
  const Header header("some_name","some_location","some_object");
  std::vector<NeighbourFileItem> items;
  for (int i=1; i!=4; ++i)
  {
    NeighbourFileItem item(CellIndex(i * i));
    items.push_back(item);
  }
  //operator==
  {
    const NeighbourFile b(header,items);
    const NeighbourFile c(header,items);
    assert(header == header);
    assert(b == c);
  }
  //operator!=
  {
    const NeighbourFile b(header,items);
    const Header other_header("some_other_name","some_other_location","some_other_object");
    assert(header != other_header);
    const NeighbourFile c(other_header,items);
    assert(b != c);
  }
  //operator!=
  {
    const NeighbourFile b(header,items);
    std::vector<NeighbourFileItem> other_items;
    for (int i=1; i!=3; ++i)
    {
      NeighbourFileItem item(CellIndex(2 * i * i));
      other_items.push_back(item);
    }
    const NeighbourFile c(header,other_items);
    assert(b != c);
  }
  //Stream conversion
  {
    const NeighbourFile b(header,items);
    std::stringstream s;
    s << b;
    NeighbourFile c;
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
      if (!fileio::FileIo().IsRegularFile(filename))
      {
        TRACE("ERROR");
        TRACE(filename);
      }
      assert(fileio::FileIo().IsRegularFile(filename));
      NeighbourFile b(filename);
      assert( (!b.GetItems().empty() || b.GetItems().empty())
        && "If a mesh has no non-bhoundary cells, neighbour can be empty");
    }
  }
}
#endif

bool ribi::foam::operator==(const NeighbourFile& lhs,const NeighbourFile& rhs) noexcept
{
  if (lhs.GetHeader() != rhs.GetHeader())
  {
    return false;
  }
  const std::vector<NeighbourFileItem>& lhs_items = lhs.GetItems();
  const std::vector<NeighbourFileItem>& rhs_items = rhs.GetItems();
  if (lhs_items.size() != rhs_items.size())
  {
    return false;
  }
  return std::equal(lhs_items.begin(),lhs_items.end(),rhs_items.begin());
}

bool ribi::foam::operator!=(const NeighbourFile& lhs,const NeighbourFile& rhs) noexcept
{
  return !(lhs == rhs);
}

std::istream& ribi::foam::operator>>(std::istream& is, NeighbourFile& f)
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
      NeighbourFileItem item;
      is >> item;
      assert(is);
      f.m_items.push_back(item);
    }
  }
  else
  {
    assert(opening_bracket == '{');
    //Read once, push n_items times
    NeighbourFileItem item;
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

std::ostream& ribi::foam::operator<<(std::ostream& os, const NeighbourFile& f) noexcept
{
  os
    << f.GetHeader() << '\n'
    << "" << '\n'
    << f.m_items.size() << '\n'
    << "(" << '\n'
  ;

  for(const NeighbourFileItem item: f.m_items)
  {
    os << item << '\n';
  }

  os
    << ")" << '\n'
  ;
  return os;
}

