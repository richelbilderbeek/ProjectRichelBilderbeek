#include "canvascoordinatsystems.h"

#include <cassert>

#include "trace.h"

boost::bimap<ribi::CanvasCoordinatSystem,std::string> ribi::CanvasCoordinatSystems::m_map;

const boost::bimap<ribi::CanvasCoordinatSystem,std::string> ribi::CanvasCoordinatSystems::CreateMap()
{
  #ifndef NDEBUG
  Test();
  #endif
  boost::bimap<CanvasCoordinatSystem,std::string> m;
  m.insert(boost::bimap<CanvasCoordinatSystem,std::string>::value_type(
    CanvasCoordinatSystem::graph,"graph"));
  m.insert(boost::bimap<CanvasCoordinatSystem,std::string>::value_type(
    CanvasCoordinatSystem::screen,"screen"));
  return m;
}

const std::vector<ribi::CanvasCoordinatSystem> ribi::CanvasCoordinatSystems::GetAll() noexcept
{
  const std::vector<CanvasCoordinatSystem> v {
    CanvasCoordinatSystem::graph,
    CanvasCoordinatSystem::screen
  };
  assert(static_cast<int>(v.size()) == static_cast<int>(CanvasCoordinatSystem::n_types));
  return v;
}

#ifndef NDEBUG
void ribi::CanvasCoordinatSystems::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting ribi::CanvasCoordinatSystems::Test");
  const std::vector<CanvasCoordinatSystem> v = GetAll();
  const std::size_t sz = v.size();
  for (std::size_t i=0; i!=sz; ++i)
  {
    assert(i < v.size());
    const CanvasCoordinatSystem t = v[i];
    const std::string s = ToStr(t);
    assert(!s.empty());
    const CanvasCoordinatSystem u = ToType(s);
    assert(u == t);
  }
  TRACE("Finished ribi::CanvasCoordinatSystems::Test successfully");
}
#endif


const std::string ribi::CanvasCoordinatSystems::ToStr(const CanvasCoordinatSystem type) noexcept
{
  if (m_map.left.empty()) m_map = CreateMap();
  assert(!m_map.left.empty());
  assert(m_map.left.count(type));
  const std::string s = m_map.left.find(type)->second;
  return s;
}

ribi::CanvasCoordinatSystem ribi::CanvasCoordinatSystems::ToType(const std::string& s)
{
  if (m_map.right.empty()) m_map = CreateMap();
  assert(!m_map.right.empty());
  assert(m_map.right.count(s) == 1);
  const CanvasCoordinatSystem t = m_map.right.find(s)->second;
  return t;
}
