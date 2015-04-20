#include "beaststatefile.h"

#include <cassert>
#include <sstream>
#include <stdexcept>

#include "fileio.h"

BeastStateFile::BeastStateFile(const std::string& filename)
  : m_tree{FindTree(filename)}
{
  #ifndef NDEBUG
  Test();
  #endif
  if (!ribi::fileio::FileIo().IsRegularFile(filename))
  {
    std::stringstream s;
    s << "BeastStateFile::BeastStateFile: file '" << filename << "' not found";
    throw std::logic_error(s.str().c_str());
  }
}

std::string BeastStateFile::FindTree(const std::string& filename) const
{
  if (!ribi::fileio::FileIo().IsRegularFile(filename))
  {
    std::stringstream s;
    s << "BeastStateFile::FindTree: file '" << filename << "' not found";
    throw std::logic_error(s.str().c_str());
  }
  const std::string s{FindTreeLine(filename)};

  // <statenode id='Tree.t:birthdeath_birthdeath'>[NEWICK]</statenode>
  // Remove leading XML opening tag
  const std::string t{s.substr(s.find('>') + 1,s.size() - s.find('>') - 1)};
  // Remove trailing XML closing tag
  const std::string to_remove{"</statenode>"};
  const std::string u{t.substr(0,t.size() - to_remove.size())};
  return u;
}

std::string BeastStateFile::FindTreeLine(const std::string& filename) const
{
  assert(ribi::fileio::FileIo().IsRegularFile(filename));
  const std::vector<std::string> v{
    ribi::fileio::FileIo().FileToVector(filename)
  };
  // <statenode id='Tree.t:birthdeath_birthdeath'>[NEWICK]</statenode>
  for (const std::string& s: v)
  {
    const std::string begins_with{"<statenode id='Tree.t:"};
    if (s.substr(0,begins_with.size()) == begins_with) { return s; }
  }
  throw std::logic_error("Could not find tree line");
}

