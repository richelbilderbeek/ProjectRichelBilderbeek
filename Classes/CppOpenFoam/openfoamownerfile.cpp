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

#include <QFile>

#include "filename.h"
#include "fileio.h"
#include "openfoamheader.h"
#include "openfoamfaceindex.h"
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

const ribi::foam::CellIndex ribi::foam::OwnerFile::CountNumberOfCells() const noexcept
{
  assert(!m_items.empty());

  CellIndex i = (*std::max_element(
    m_items.begin(),
    m_items.end(),
    [](const OwnerFileItem& lhs, const OwnerFileItem& rhs)
    {
      return lhs.GetCellIndex() < rhs.GetCellIndex();
    }
  )).GetCellIndex();

  // +1, because if the highest cell index found is x, there are x+1 cells
  return ++i;
}

const ribi::foam::Header ribi::foam::OwnerFile::GetDefaultHeader() noexcept
{
  return Header("labelList","constant/polyMesh","","owner");
}

const ribi::foam::OwnerFileItem& ribi::foam::OwnerFile::GetItem(
  const ribi::foam::FaceIndex& face_index) const noexcept
{
  const int i = face_index.Get();
  assert(i < static_cast<int>(m_items.size()));
  return m_items[i];
}

const ribi::foam::OwnerFile ribi::foam::OwnerFile::Parse(std::istream& is)
{
  OwnerFile b;
  is >> b;
  assert(is);
  return b;
}

const ribi::foam::OwnerFile ribi::foam::OwnerFile::Parse(const std::string& filename)
{
  const std::string tmp_filename { fileio::GetTempFileName() };
  fileio::CopyFile(filename,tmp_filename);
  Header::CleanFile(tmp_filename);
  std::ifstream f(tmp_filename.c_str());
  const OwnerFile file { Parse(f) };
  f.close();
  fileio::DeleteFile(tmp_filename);
  return file;
}

void ribi::foam::OwnerFile::SetItem(const FaceIndex& face_index, const OwnerFileItem& item) noexcept
{
  const int i = face_index.Get();
  assert(i < static_cast<int>(m_items.size()));
  m_items[i] = item;
  assert(m_items[i] == item);
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
    OwnerFileItem item(CellIndex(i * i));
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
      OwnerFileItem item(CellIndex(2 * i * i));
      other_items.push_back(item);
    }
    const OwnerFile c(header,other_items);
    assert(b != c);
  }
  //operator!=
  {
    const OwnerFile b(header,items);
    OwnerFile c(header,items);
    assert(b == c);
    const FaceIndex i(1);
    const CellIndex j { c.GetItem(i).GetCellIndex() };
    const OwnerFileItem new_item(CellIndex(j.Get() + 1));
    assert(c.GetItem(i) != new_item);
    c.SetItem(i,new_item);
    assert(c.GetItem(i) == new_item);
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
      OwnerFile b(filename);
      if (b.GetItems().empty())
      {
        TRACE("ERROR");
      }
      assert(!b.GetItems().empty());
    }
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
      OwnerFileItem item;
      is >> item;
      assert(is);
      f.m_items.push_back(item);
    }
  }
  else
  {
    assert(opening_bracket == '{');
    //Read once, push n_items times
    OwnerFileItem item;
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

