#include "whitenoisesystemtypes.h"

boost::bimap<ribi::kalman::WhiteNoiseSystemType,std::string> ribi::kalman::WhiteNoiseSystemTypes::m_map;

boost::bimap<ribi::kalman::WhiteNoiseSystemType,std::string> ribi::kalman::WhiteNoiseSystemTypes::CreateMap() noexcept
{
  #ifndef NDEBUG
  Test();
  #endif

  boost::bimap<WhiteNoiseSystemType,std::string> m;
  m.insert(boost::bimap<WhiteNoiseSystemType,std::string>::value_type(
    WhiteNoiseSystemType::gaps_filled,"gaps_filled"));
  m.insert(boost::bimap<WhiteNoiseSystemType,std::string>::value_type(
    WhiteNoiseSystemType::lagged,"lagged"));
  m.insert(boost::bimap<WhiteNoiseSystemType,std::string>::value_type(
    WhiteNoiseSystemType::standard,"standard"));
  return m;
}

std::vector<ribi::kalman::WhiteNoiseSystemType> ribi::kalman::WhiteNoiseSystemTypes::GetAllTypes() noexcept
{
  const std::vector<WhiteNoiseSystemType> v {
    WhiteNoiseSystemType::gaps_filled,
    WhiteNoiseSystemType::lagged,
    WhiteNoiseSystemType::standard
  };
  assert(static_cast<int>(v.size()) == static_cast<int>(WhiteNoiseSystemType::n_types));
  return v;
}

#ifndef NDEBUG
void ribi::kalman::WhiteNoiseSystemTypes::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  for (const auto t: GetAllTypes())
  {
    const std::string s = ToStr(t);
    assert(!s.empty());
    const auto u = ToType(s);
    assert(u == t);
  }
}
#endif

std::string ribi::kalman::WhiteNoiseSystemTypes::ToStr(const WhiteNoiseSystemType type) noexcept
{
  if (m_map.left.empty()) { m_map = CreateMap(); }
  assert(!m_map.left.empty());
  assert(m_map.left.count(type) == 1);
  const std::string s = m_map.left.find(type)->second;
  return s;
}

ribi::kalman::WhiteNoiseSystemType ribi::kalman::WhiteNoiseSystemTypes::ToType(const std::string& s)
{
  if (m_map.right.empty()) { m_map = CreateMap(); }
  assert(!m_map.right.empty());
  assert(m_map.right.count(s) == 1);
  const auto t = m_map.right.find(s)->second;
  return t;
}
