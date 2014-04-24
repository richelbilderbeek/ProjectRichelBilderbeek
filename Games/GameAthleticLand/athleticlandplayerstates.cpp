#include "athleticlandplayerstates.h"

#include <cassert>

#include "trace.h"

boost::bimap<ribi::athl::PlayerState,std::string> ribi::athl::PlayerStates::m_map;

ribi::athl::PlayerStates::PlayerStates()
{
  #ifndef NDEBUG
  Test();
  #endif
}

boost::bimap<ribi::athl::PlayerState,std::string> ribi::athl::PlayerStates::CreateMap()
{
  boost::bimap<PlayerState,std::string> m;
  m.insert(boost::bimap<PlayerState,std::string>::value_type(PlayerState::stand_left ,"stand_left"));
  m.insert(boost::bimap<PlayerState,std::string>::value_type(PlayerState::stand_right,"stand_right"));
  return m;
}

std::vector<ribi::athl::PlayerState> ribi::athl::PlayerStates::GetAll() noexcept
{
  const std::vector<PlayerState> v {
    PlayerState::stand_left,
    PlayerState::stand_right
  };
  assert(static_cast<int>(v.size()) == static_cast<int>(PlayerState::n_types));
  return v;
}

#ifndef NDEBUG
void ribi::athl::PlayerStates::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting ribi::athl::PlayerStates::Test");
  const std::vector<PlayerState> v = GetAll();
  const std::size_t sz = v.size();
  for (std::size_t i=0; i!=sz; ++i)
  {
    assert(i < v.size());
    const PlayerState t = v[i];
    const std::string s = ToStr(t);
    assert(!s.empty());
    const PlayerState u = ToType(s);
    assert(u == t);
  }
  TRACE("Finished ribi::athl::PlayerStates::Test successfully");
}
#endif

std::string ribi::athl::PlayerStates::ToStr(const PlayerState type) noexcept
{
  if (m_map.left.empty()) m_map = CreateMap();
  assert(!m_map.left.empty());
  assert(m_map.left.count(type));
  const std::string s = m_map.left.find(type)->second;
  return s;
}

ribi::athl::PlayerState ribi::athl::PlayerStates::ToType(const std::string& s)
{
  if (m_map.right.empty()) m_map = CreateMap();
  assert(!m_map.right.empty());
  assert(m_map.right.count(s) == 1);
  const PlayerState t = m_map.right.find(s)->second;
  return t;
}
