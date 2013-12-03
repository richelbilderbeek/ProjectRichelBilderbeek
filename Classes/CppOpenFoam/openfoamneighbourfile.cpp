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

#include "filename.h"
#include "openfoamheader.h"
#include "openfoamneighbourfileitem.h"
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

const ribi::foam::Header ribi::foam::NeighbourFile::GetDefaultHeader() noexcept
{
  return Header("labelList","constant/polyMesh","neighbour");
}

const ribi::foam::NeighbourFile ribi::foam::NeighbourFile::Parse(std::istream& is)
{
  NeighbourFile b;
  is >> b;
  return b;
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
    NeighbourFileItem item(i * i);
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
      NeighbourFileItem item(2 * i * i);
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
  for (int i=0; i!=n_items; ++i)
  {
    NeighbourFileItem item;
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

