

#include "whitenoisesystemtypes.h"

boost::bimap<ribi::kalman::WhiteNoiseSystemType,std::string> ribi::kalman::WhiteNoiseSystemTypes::m_map;

const boost::bimap<ribi::kalman::WhiteNoiseSystemType,std::string> ribi::kalman::WhiteNoiseSystemTypes::CreateMap()
{
  #ifndef NDEBUG
  Test();
  #endif

  boost::bimap<WhiteNoiseSystemType,std::string> m;
  m.insert(boost::bimap<WhiteNoiseSystemType,std::string>::value_type(
    WhiteNoiseSystemType::gaps_filled,std::string("gaps_filled")));
  m.insert(boost::bimap<WhiteNoiseSystemType,std::string>::value_type(
    WhiteNoiseSystemType::lagged,std::string("lagged")));
  m.insert(boost::bimap<WhiteNoiseSystemType,std::string>::value_type(
    WhiteNoiseSystemType::standard,std::string("standard")));
  return m;
}

const std::vector<ribi::kalman::WhiteNoiseSystemType> ribi::kalman::WhiteNoiseSystemTypes::GetAllTypes()
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
void ribi::kalman::WhiteNoiseSystemTypes::Test()
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  const std::vector<WhiteNoiseSystemType> v = GetAllTypes();
  const std::size_t sz = v.size();
  for (std::size_t i=0; i!=sz; ++i)
  {
    assert(i < v.size());
    const WhiteNoiseSystemType t = v[i];
    const std::string s = ToStr(t);
    assert(!s.empty());
    const WhiteNoiseSystemType u = ToType(s);
    assert(u == t);
  }
}
#endif

const std::string ribi::kalman::WhiteNoiseSystemTypes::ToStr(const WhiteNoiseSystemType type)
{
  if (m_map.left.empty()) m_map = CreateMap();
  assert(!m_map.left.empty());
  assert(m_map.left.count(type) == 1);
  const std::string s = m_map.left.find(type)->second;
  return s;
}

ribi::kalman::WhiteNoiseSystemType ribi::kalman::WhiteNoiseSystemTypes::ToType(const std::string& s)
{
  if (m_map.right.empty()) m_map = CreateMap();
  assert(!m_map.right.empty());
  assert(m_map.right.count(s) == 1);
  const WhiteNoiseSystemType t = m_map.right.find(s)->second;
  return t;
}
