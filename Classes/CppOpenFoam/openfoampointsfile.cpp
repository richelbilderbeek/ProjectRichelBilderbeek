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

#include "fileio.h"

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

ribi::foam::Header ribi::foam::PointsFile::GetDefaultHeader() noexcept
{
  return Header("vectorField","constant/polyMesh","","points");
}

ribi::foam::PointsFile ribi::foam::PointsFile::Parse(std::istream& is)
{
  PointsFile b;
  is >> b;
  assert(is);
  return b;
}

ribi::foam::PointsFile ribi::foam::PointsFile::Parse(const std::string& filename)
{
  const std::string tmp_filename { fileio::FileIo().GetTempFileName() };
  fileio::FileIo().CopyFile(filename,tmp_filename);
  Header::CleanFile(tmp_filename);
  std::ifstream f(tmp_filename.c_str());
  ribi::foam::PointsFile file { Parse(f) };
  f.close();
  fileio::FileIo().DeleteFile(tmp_filename);
  return file;
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
  typedef boost::geometry::model::point<double,3,boost::geometry::cs::cartesian> Coordinat3D;

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
      PointsFile b(filename);
      if (b.GetItems().empty())
      {
        TRACE("ERROR");
      }
      assert(!b.GetItems().empty());
    }
  }
  TRACE("Finished ribi::foam::Header::PointsFile successfully");
}
#endif

bool ribi::foam::operator==(const PointsFile& lhs,const PointsFile& rhs) noexcept
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

bool ribi::foam::operator!=(const PointsFile& lhs,const PointsFile& rhs) noexcept
{
  return !(lhs == rhs);
}

std::istream& ribi::foam::operator>>(std::istream& is, PointsFile& f)
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
      PointsFileItem item;
      is >> item;
      assert(is);
      f.m_items.push_back(item);
    }
  }
  else
  {
    assert(opening_bracket == '{');
    //Read once, push n_items times
    PointsFileItem item;
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

std::ostream& ribi::foam::operator<<(std::ostream& os, const PointsFile& f) noexcept
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
