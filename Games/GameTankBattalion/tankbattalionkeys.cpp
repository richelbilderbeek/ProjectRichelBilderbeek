#include "tankbattalionkeys.h"

#include <cassert>

#include "trace.h"

boost::bimap<ribi::taba::Key,std::string> ribi::taba::Keys::m_map;

ribi::taba::Keys::Keys() noexcept
{
  #ifndef NDEBUG
  Test();
  #endif
}

boost::bimap<ribi::taba::Key,std::string> ribi::taba::Keys::CreateMap() noexcept
{
  #ifndef NDEBUG
  Test();
  #endif

  boost::bimap<Key,std::string> m;
  m.insert(boost::bimap<Key,std::string>::value_type(Key::up,"up"));
  m.insert(boost::bimap<Key,std::string>::value_type(Key::right,"right"));
  m.insert(boost::bimap<Key,std::string>::value_type(Key::down,"down"));
  m.insert(boost::bimap<Key,std::string>::value_type(Key::left,"left"));
  m.insert(boost::bimap<Key,std::string>::value_type(Key::fire,"fire"));
  assert(static_cast<int>(m.left.size()) == static_cast<int>(Key::n_keys));
  return m;
}

std::vector<ribi::taba::Key> ribi::taba::Keys::GetAll() const noexcept
{
  std::vector<ribi::taba::Key> v
    = { Key::up, Key::right, Key::down, Key::left, Key::fire };
  #ifndef NDEBUG
  const int n_expected = static_cast<int>(Key::n_keys);
  const int n = static_cast<int>(v.size());
  assert(n == n_expected);
  #endif
  return v;

}

ribi::taba::Key ribi::taba::Keys::GetOpposite(const Key k) const noexcept
{
  assert(IsMovement(k));
  switch (k)
  {
    case Key::up: return Key::down;
    case Key::right: return Key::left;
    case Key::down: return Key::up;
    case Key::left: return Key::right;
    default:
      assert(!"Should not be used");
  }
  assert(!"Should not get here");
  throw std::logic_error("ribi::taba::Keys::GetOpposite: cannot get opposite of key");
}

bool ribi::taba::Keys::IsMovement(const Key k) const noexcept
{
  switch (k)
  {
    case Key::up:
    case Key::right:
    case Key::down:
    case Key::left:
      return true;
    default:
      return false;
  }
  assert(!"Should not get here");
}

bool ribi::taba::Keys::IsOpposite(const Key a, const Key b) const noexcept
{
  assert(IsMovement(a));
  assert(IsMovement(b));
  return a == GetOpposite(b);
}

#ifndef NDEBUG
void ribi::taba::Keys::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting ribi::TankBattalionMenuDialog::Test");
  const Keys keys;
  {
    assert(!keys.GetAll().empty());
  }
  {
    //GetOpposite
    assert(keys.GetOpposite(Key::up   ) == Key::down );
    assert(keys.GetOpposite(Key::right) == Key::left );
    assert(keys.GetOpposite(Key::down ) == Key::up   );
    assert(keys.GetOpposite(Key::left ) == Key::right);
  }
  {
    //IsOpposite
    assert( keys.IsOpposite(Key::left,Key::right));
    assert( keys.IsOpposite(Key::right,Key::left));
    assert(!keys.IsOpposite(Key::left,Key::up));
    assert( keys.IsOpposite(Key::up,Key::down));
    assert(!keys.IsOpposite(Key::up,Key::right));
  }
  //ToStr and ToType
  for (const auto t: keys.GetAll())
  {
    const std::string s = keys.ToStr(t);
    assert(!s.empty()
      && "Every type can be converted to a non-empty string");
    const auto u = keys.ToKey(s);
    assert(u == t
      && "When converting back the string, it should result in the original type");
  }

  TRACE("Finished ribi::TankBattalionMenuDialog::Test successfully");
}
#endif

ribi::taba::Key ribi::taba::Keys::ToKey(const std::string& s) const noexcept
{
  if (m_map.right.empty()) { m_map = CreateMap(); }
  assert(!m_map.right.empty());
  assert(m_map.right.count(s) == 1);
  const auto t = m_map.right.find(s)->second;
  return t;
}

std::string ribi::taba::Keys::ToStr(const Key key) const noexcept
{
  if (m_map.left.empty()) { m_map = CreateMap(); }
  assert(!m_map.left.empty());
  assert(m_map.left.count(key) == 1);
  const auto s = m_map.left.find(key)->second;
  return s;
}

