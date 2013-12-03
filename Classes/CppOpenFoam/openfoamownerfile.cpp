#include "openfoamownerfile.h"

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
#include "openfoamownerfileitem.h"
#include "trace.h"
#pragma GCC diagnostic pop


ribi::foam::OwnerFile::OwnerFile(
  const Header header,
  const std::vector<OwnerFileItem>& items)
  : m_header{header},
    m_items(items)
{
  #ifndef NDEBUG
  Test();
  #endif
}

const ribi::foam::Header ribi::foam::OwnerFile::GetDefaultHeader() noexcept
{
  return Header("labelList","constant/polyMesh","owner");
}

const ribi::foam::OwnerFile ribi::foam::OwnerFile::Parse(std::istream& is)
{
  OwnerFile b;
  is >> b;
  return b;
}

#ifndef NDEBUG
void ribi::foam::OwnerFile::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting ribi::foam::OwnerFile::Test");
  //Some initial data
  const Header header("some_name","some_location","some_object");
  std::vector<OwnerFileItem> items;
  for (int i=1; i!=4; ++i)
  {
    OwnerFileItem item(i * i);
    items.push_back(item);
  }
  //operator==
  {
    const OwnerFile b(header,items);
    const OwnerFile c(header,items);
    assert(header == header);
    assert(b == c);
  }
  //operator!=
  {
    const OwnerFile b(header,items);
    const Header other_header("some_other_name","some_other_location","some_other_object");
    assert(header != other_header);
    const OwnerFile c(other_header,items);
    assert(b != c);
  }
  //operator!=
  {
    const OwnerFile b(header,items);
    std::vector<OwnerFileItem> other_items;
    for (int i=1; i!=3; ++i)
    {
      OwnerFileItem item(2 * i * i);
      other_items.push_back(item);
    }
    const OwnerFile c(header,other_items);
    assert(b != c);
  }
  //Stream conversion
  {
    const OwnerFile b(header,items);
    std::stringstream s;
    s << b;
    OwnerFile c;
    s >> c;
    if (b != c)
    {
      TRACE(b);
      TRACE(c);
    }
    assert(b == c);
  }
  TRACE("Finished ribi::foam::Header::OwnerFile successfully");
}
#endif

bool ribi::foam::operator==(const OwnerFile& lhs,const OwnerFile& rhs)
{
  if (lhs.GetHeader() != rhs.GetHeader())
  {
    return false;
  }
  const std::vector<OwnerFileItem>& lhs_items = lhs.GetItems();
  const std::vector<OwnerFileItem>& rhs_items = rhs.GetItems();
  if (lhs_items.size() != rhs_items.size())
  {
    return false;
  }
  return std::equal(lhs_items.begin(),lhs_items.end(),rhs_items.begin());
}

bool ribi::foam::operator!=(const OwnerFile& lhs,const OwnerFile& rhs)
{
  return !(lhs == rhs);
}

std::istream& ribi::foam::operator>>(std::istream& is, OwnerFile& f)
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
    OwnerFileItem item;
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

std::ostream& ribi::foam::operator<<(std::ostream& os, const OwnerFile& f)
{
  os
    << f.GetHeader() << '\n'
    << "" << '\n'
    << f.m_items.size() << '\n'
    << "(" << '\n'
  ;

  for(const OwnerFileItem item: f.m_items)
  {
    os << item << '\n';
  }

  os
    << ")" << '\n'
  ;
  return os;
}

