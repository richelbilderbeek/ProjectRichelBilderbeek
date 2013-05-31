#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif

//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#include "kalmanfiltertypes.h"

boost::bimap<KalmanFilterType,std::string> KalmanFilterTypes::m_map;

const boost::bimap<KalmanFilterType,std::string> KalmanFilterTypes::CreateMap()
{
  #ifndef NDEBUG
  Test();
  #endif

  boost::bimap<KalmanFilterType,std::string> m;
  m.insert(boost::bimap<KalmanFilterType,std::string>::value_type(
    KalmanFilterType::fixed_lag_smoother,std::string("fixed lag smoother")));
  m.insert(boost::bimap<KalmanFilterType,std::string>::value_type(
    KalmanFilterType::standard,std::string("discrete")));
  m.insert(boost::bimap<KalmanFilterType,std::string>::value_type(
    KalmanFilterType::steady_state,std::string("steady state")));
  return m;
}

const std::vector<KalmanFilterType> KalmanFilterTypes::GetAllTypes()
{
  const std::vector<KalmanFilterType> v
  =
  {
    KalmanFilterType::fixed_lag_smoother,
    KalmanFilterType::standard,
    KalmanFilterType::steady_state
  };
  assert(static_cast<int>(v.size()) == static_cast<int>(KalmanFilterType::n_types));
  return v;
}

#ifndef NDEBUG
void KalmanFilterTypes::Test()
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  const std::vector<KalmanFilterType> v = GetAllTypes();
  const std::size_t sz = v.size();
  for (std::size_t i=0; i!=sz; ++i)
  {
    assert(i < v.size());
    const KalmanFilterType t = v[i];
    const std::string s = ToStr(t);
    assert(!s.empty());
    const KalmanFilterType u = ToType(s);
    assert(u == t);
  }
}
#endif

const std::string KalmanFilterTypes::ToStr(const KalmanFilterType type)
{
  if (m_map.left.empty()) m_map = CreateMap();
  assert(!m_map.left.empty());
  assert(m_map.left.count(type));
  const std::string s = m_map.left.find(type)->second;
  return s;
}

KalmanFilterType KalmanFilterTypes::ToType(const std::string& s)
{
  if (m_map.right.empty()) m_map = CreateMap();
  assert(!m_map.right.empty());
  assert(m_map.right.count(s) == 1);
  const KalmanFilterType t = m_map.right.find(s)->second;
  return t;
}
