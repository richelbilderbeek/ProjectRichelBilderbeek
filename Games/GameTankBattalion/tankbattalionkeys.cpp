#include "tankbattalionkeys.h"

#include <cassert>

#include "trace.h"

ribi::taba::Keys::Keys() noexcept
{
  #ifndef NDEBUG
  Test();
  #endif
}

ribi::taba::Key ribi::taba::Keys::GetOpposite(const Key k) const noexcept
{
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
}

bool ribi::taba::Keys::IsOpposite(const Key a, const Key b) const noexcept
{
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
  const Keys k;
  {
    //GetOpposite
    assert(k.GetOpposite(Key::up   ) == Key::down );
    assert(k.GetOpposite(Key::right) == Key::left );
    assert(k.GetOpposite(Key::down ) == Key::up   );
    assert(k.GetOpposite(Key::left ) == Key::right);
  }
  {
    //IsOpposite
    assert( k.IsOpposite(Key::left,Key::right));
    assert( k.IsOpposite(Key::right,Key::left));
    assert(!k.IsOpposite(Key::left,Key::up));
    assert( k.IsOpposite(Key::up,Key::down));
    assert(!k.IsOpposite(Key::up,Key::right));
  }
  TRACE("Finished ribi::TankBattalionMenuDialog::Test successfully");
}
#endif
