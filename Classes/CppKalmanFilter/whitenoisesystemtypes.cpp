#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorUnableToFindNumericLiteralOperatorOperatorQ.htm
#if !(__GNUC__ >= 4 && __GNUC_MINOR__ >= 8)
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif
#endif

//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#include "whitenoisesystemtypes.h"

boost::bimap<WhiteNoiseSystemType,std::string> WhiteNoiseSystemTypes::m_map;

const boost::bimap<WhiteNoiseSystemType,std::string> WhiteNoiseSystemTypes::CreateMap()
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

const std::vector<WhiteNoiseSystemType> WhiteNoiseSystemTypes::GetAllTypes()
{
  const std::vector<WhiteNoiseSystemType> v
  =
  {
    WhiteNoiseSystemType::gaps_filled,
    WhiteNoiseSystemType::lagged,
    WhiteNoiseSystemType::standard
  };
  assert(static_cast<int>(v.size()) == static_cast<int>(WhiteNoiseSystemType::n_types));
  return v;
}

#ifndef NDEBUG
void WhiteNoiseSystemTypes::Test()
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

const std::string WhiteNoiseSystemTypes::ToStr(const WhiteNoiseSystemType type)
{
  if (m_map.left.empty()) m_map = CreateMap();
  assert(!m_map.left.empty());
  assert(m_map.left.count(type) == 1);
  const std::string s = m_map.left.find(type)->second;
  return s;
}

WhiteNoiseSystemType WhiteNoiseSystemTypes::ToType(const std::string& s)
{
  if (m_map.right.empty()) m_map = CreateMap();
  assert(!m_map.right.empty());
  assert(m_map.right.count(s) == 1);
  const WhiteNoiseSystemType t = m_map.right.find(s)->second;
  return t;
}
