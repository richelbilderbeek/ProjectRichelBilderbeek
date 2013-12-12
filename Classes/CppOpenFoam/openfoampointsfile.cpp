#include "openfoampointsfile.h"

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
#include "openfoampointsfileitem.h"
#include "trace.h"
#pragma GCC diagnostic pop


ribi::foam::PointsFile::PointsFile(
  const Header header,
  const std::vector<PointsFileItem>& items)
  : m_header{header},
    m_items(items)
{
  #ifndef NDEBUG
  Test();
  #endif
}

const ribi::foam::Header ribi::foam::PointsFile::GetDefaultHeader() noexcept
{
  return Header("vectorField","constant/polyMesh","","points");
}

const ribi::foam::PointsFile ribi::foam::PointsFile::Parse(std::istream& is)
{
  PointsFile b;
  is >> b;
  return b;
}

#ifndef NDEBUG
void ribi::foam::PointsFile::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting ribi::foam::PointsFile::Test");
  //Some initial data
  const Header header("some_name","some_location","some_object");
  std::vector<PointsFileItem> items;
  for (int i=1; i!=4; ++i)
  {
    PointsFileItem item(
      Coordinat3D(
        static_cast<double>(i) * 1.1,
        static_cast<double>(i) * 2.2,
        static_cast<double>(i) * 3.3
      )
    );
    items.push_back(item);
  }
  //operator==
  {
    const PointsFile b(header,items);
    const PointsFile c(header,items);
    assert(header == header);
    assert(b == c);
  }
  //operator!=
  {
    const PointsFile b(header,items);
    const Header other_header("some_other_name","some_other_location","some_other_object");
    assert(header != other_header);
    const PointsFile c(other_header,items);
    assert(b != c);
  }
  //operator!=
  {
    const PointsFile b(header,items);
    std::vector<PointsFileItem> other_items;
    for (int i=1; i!=3; ++i)
    {
      PointsFileItem item(
        Coordinat3D(
          static_cast<double>(i) * 4.4,
          static_cast<double>(i) * 5.5,
          static_cast<double>(i) * 6.6
        )
      );
      other_items.push_back(item);
    }
    const PointsFile c(header,other_items);
    assert(b != c);
  }
  //Stream conversion
  {
    const PointsFile b(header,items);
    std::stringstream s;
    s << b;
    PointsFile c;
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
      PointsFile b(f);
      assert(!b.GetItems().empty());
    }
  }
  TRACE("Finished ribi::foam::Header::PointsFile successfully");
}
#endif

bool ribi::foam::operator==(const PointsFile& lhs,const PointsFile& rhs)
{
  if (lhs.GetHeader() != rhs.GetHeader())
  {
    return false;
  }
  const std::vector<PointsFileItem>& lhs_items = lhs.GetItems();
  const std::vector<PointsFileItem>& rhs_items = rhs.GetItems();
  if (lhs_items.size() != rhs_items.size())
  {
    return false;
  }
  return std::equal(lhs_items.begin(),lhs_items.end(),rhs_items.begin());
}

bool ribi::foam::operator!=(const PointsFile& lhs,const PointsFile& rhs)
{
  return !(lhs == rhs);
}

std::istream& ribi::foam::operator>>(std::istream& is, PointsFile& f)
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
    PointsFileItem item;
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

std::ostream& ribi::foam::operator<<(std::ostream& os, const PointsFile& f)
{
  os
    << f.GetHeader() << '\n'
    << "" << '\n'
    << f.m_items.size() << '\n'
    << "(" << '\n'
  ;

  for(const PointsFileItem item: f.m_items)
  {
    os << item << '\n';
  }

  os
    << ")" << '\n'
  ;
  return os;
}
