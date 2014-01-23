#include "rubiksclockpegs.h"

#include <cassert>

#include "rubiksclockside.h"
#include "togglebutton.h"
#include "togglebuttonwidget.h"
#include "trace.h"

ribi::ruco::Pegs::Pegs() noexcept
{
  for (int y=0; y!=2; ++y)
  {
    for (int x=0; x!=2; ++x)
    {
      m_pegs[x][y].reset(new ToggleButtonWidget(false,255,255,0));
    }
  }
}

const boost::shared_ptr<const ribi::ToggleButtonWidget> ribi::ruco::Pegs::GetPeg(const Side side) const noexcept
{
  switch (side)
  {
    case Side::topLeft    : return m_pegs[0][0];
    case Side::bottomLeft : return m_pegs[1][0];
    case Side::topRight   : return m_pegs[0][1];
    case Side::bottomRight: return m_pegs[1][1];
  }
  assert(!"Should not get here");
  throw std::logic_error("ribi::ruco::Pegs::GetPeg");
}

bool operator==(const ribi::ruco::Pegs& lhs, const ribi::ruco::Pegs& rhs) noexcept
{
  for (int y=0; y!=2; ++y)
  {
    for (int x=0; x!=2; ++x)
    {
      if (lhs.m_pegs[x][y] != rhs.m_pegs[x][y]) return false;
    }
  }
  return true;
}


std::ostream& ribi::ruco::operator<<(std::ostream& os, const ribi::ruco::Pegs& p) noexcept
{
  os
    << "<rubiks_clock_pegs>";
  for (int x=0; x!=2; ++x)
  {
    for (int y=0; y!=2; ++y)
    {
      os
        << "<rubiks_clock_pegs>"
        << "<x>"
        << x
        << "</x>"
        << "<y>"
        << y
        << "</y>"
        << p.m_pegs[x][y].get()
        << "</rubiks_clock_dial>";
    }
  }
  os
    << "</rubiks_clock_pegs>";
  return os;
}
