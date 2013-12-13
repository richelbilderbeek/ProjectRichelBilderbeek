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

#include "filename.h"
#include "openfoamheader.h"
#include "openfoamneighbourfileitem.h"
#include "openfoamfaceindex.h"
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

const ribi::foam::CellIndex ribi::foam::NeighbourFile::FindMaxCellIndex() const noexcept
{
  CellIndex i = (*std::max_element(
    m_items.begin(),
    m_items.end(),
    [](const NeighbourFileItem& lhs, const NeighbourFileItem& rhs)
    {
      return lhs.GetCellIndex() < rhs.GetCellIndex();
    }
  )).GetCellIndex();

  ++i;
  return i;
}

const ribi::foam::Header ribi::foam::NeighbourFile::GetDefaultHeader() noexcept
{
  return Header("labelList","constant/polyMesh","","neighbour");
}

const ribi::foam::NeighbourFileItem& ribi::foam::NeighbourFile::GetItem(
  const FaceIndex& face_index) const noexcept
{
  assert(CanGetItem(face_index));
  return m_items[ static_cast<int>(face_index.Get()) ];
}

const ribi::foam::NeighbourFile ribi::foam::NeighbourFile::Parse(std::istream& is)
{
  NeighbourFile b;
  is >> b;
  assert(is);
  return b;
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
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting ribi::foam::NeighbourFile::Test");
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
  {
    const std::string filename { GetDefaultHeader().GetObject() };
    {
      QFile f( (std::string(":/CppOpenFoam/files/") + filename).c_str() );
      f.copy(filename.c_str());
    }
    {
      assert(fileio::IsRegularFile(filename));
      std::ifstream f(filename.c_str());
      NeighbourFile b(f);
      assert(!b.GetItems().empty());
    }
  }
  TRACE("Finished ribi::foam::Header::NeighbourFile successfully");
}
#endif

bool ribi::foam::operator==(const NeighbourFile& lhs,const NeighbourFile& rhs)
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

bool ribi::foam::operator!=(const NeighbourFile& lhs,const NeighbourFile& rhs)
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
  TRACE(opening_bracket);
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

std::ostream& ribi::foam::operator<<(std::ostream& os, const NeighbourFile& f)
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

