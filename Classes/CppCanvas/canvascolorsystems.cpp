#include "canvascolorsystems.h"

boost::bimap<ribi::CanvasColorSystem,std::string> ribi::CanvasColorSystems::m_map;

const boost::bimap<ribi::CanvasColorSystem,std::string> ribi::CanvasColorSystems::CreateMap()
{
  #ifndef NDEBUG
  Test();
  #endif
  boost::bimap<CanvasColorSystem,std::string> m;
  m.insert(boost::bimap<CanvasColorSystem,std::string>::value_type(
    CanvasColorSystem::invert,std::string("invert")));
  m.insert(boost::bimap<CanvasColorSystem,std::string>::value_type(
    CanvasColorSystem::normal,std::string("normal")));
  return m;
}

const std::vector<ribi::CanvasColorSystem> ribi::CanvasColorSystems::GetAll() noexcept
{
  const std::vector<CanvasColorSystem> v {
    CanvasColorSystem::invert,
    CanvasColorSystem::normal
  };
  assert(static_cast<int>(v.size()) == static_cast<int>(CanvasColorSystem::n_types));
  return v;
}

#ifndef NDEBUG
void ribi::CanvasColorSystems::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  const std::vector<CanvasColorSystem> v = GetAll();
  const std::size_t sz = v.size();
  for (std::size_t i=0; i!=sz; ++i)
  {
    assert(i < v.size());
    const CanvasColorSystem t = v[i];
    const std::string s = ToStr(t);
    assert(!s.empty());
    const CanvasColorSystem u = ToType(s);
    assert(u == t);
  }
}
#endif

const std::string ribi::CanvasColorSystems::ToStr(const CanvasColorSystem type) noexcept
{
  if (m_map.left.empty()) m_map = CreateMap();
  assert(!m_map.left.empty());
  assert(m_map.left.count(type));
  const std::string s = m_map.left.find(type)->second;
  return s;
}

ribi::CanvasColorSystem ribi::CanvasColorSystems::ToType(const std::string& s)
{
  if (m_map.right.empty()) m_map = CreateMap();
  assert(!m_map.right.empty());
  assert(m_map.right.count(s) == 1);
  const CanvasColorSystem t = m_map.right.find(s)->second;
  return t;
}
