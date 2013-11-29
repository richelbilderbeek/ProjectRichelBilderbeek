#include "openfoamboundaryfile.h"

#include <cassert>
#include <ostream>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"

#include <boost/algorithm/string/trim.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/lexical_cast.hpp>

#include "filename.h"
#include "openfoamheader.h"
#pragma GCC diagnostic pop

ribi::foam::BoundaryFile::BoundaryFile(const std::vector<BoundaryFileItem>& items)
  : m_items(items)
{

}

const std::vector<ribi::foam::BoundaryFile::BoundaryFileItem> ribi::foam::BoundaryFile::Parse(
  const fileio::Filename& filename)
{
  assert(fileio::IsRegularFile(filename));
  const std::vector<std::string> lines { fileio::FileToVector(filename) };
  std::vector<BoundaryFileItem> items;


  enum class State { name, bracket_open, type, n_faces, start_face, bracket_close };
  State cur_state;
  BoundaryFileItem cur_item;


  for (const std::string& line_raw: lines)
  {
    const std::string line { boost::algorithm::trim_copy(line_raw) };
    if (line.empty()) continue; //Skip empty lines
    std::vector<std::string> words { SplitLine(line) };
    assert(!words.empty());

    switch (cur_state)
    {
      case State::name:
        assert(words.size() == 1);
        cur_item.m_name = words[0];
        break;
      case State::bracket_open:
        assert(words.size() == 1);
        assert(words[0] == std::string("{"));
        break;
      case State::type:
        assert(words.size() == 2);
        assert(words[0] == std::string("type"));
        cur_item.m_type = words[1];
        break;
      case State::n_faces:
        assert(words.size() == 2);
        assert(words[0] == std::string("nFaces"));
        cur_item.m_n_faces = boost::lexical_cast<int>(words[1]);
        break;
      case State::start_face:
        assert(words.size() == 2);
        assert(words[1] == std::string("startFaces"));
        cur_item.m_start_face = boost::lexical_cast<int>(words[1]);
        break;
      case State::bracket_close:
        assert(words.size() == 1);
        assert(words[0] == std::string("}"));
        break;
    }
    if (cur_state == State::bracket_close)
    {
      items.push_back(cur_item);
      cur_state = State::name;
    }
    else
    {
      cur_state = static_cast<State>(static_cast<int>(cur_state) + 1);
    }
  }
  assert(cur_state == State::name);
  return items;
}

const std::vector<std::string> ribi::foam::BoundaryFile::SplitLine(
  const std::string& s)
{
  std::vector<std::string> v;
  boost::algorithm::split(
    v,
    s,
    boost::is_any_of(" \t")
  );
  return v;
}

std::ostream& ribi::foam::operator<<(std::ostream& os, const BoundaryFile& f)
{
  const Header h("polyBoundaryMesh","constant/polyMesh","boundary");
  os
    << h << '\n'
    << "" << '\n'
    << f.m_items.size() << '\n'
    << "(" << '\n'
  ;

  for(const BoundaryFile::BoundaryFileItem item: f.m_items)
  {
    os
      << "  " << item.m_name << '\n'
      << "  {" << '\n'
      << "    type " << item.m_type << '\n'
      << "    nFaces " << item.m_n_faces << '\n'
      << "    startFace " << item.m_start_face << '\n'
      << "  }" << '\n'
    ;
  }

  os
    << ")" << '\n'
  ;
  return os;
}
