#include "rubiksclocktimes.h"

#include <cassert>

#include "dial.h"
#include "rubiksclock.h"
#include "rubiksclockwidget.h"
#include "rubiksclockdial.h"
#include "rubiksclockdialwidget.h"

ribi::ruco::Times::Times(const bool is_front) noexcept
{
  for (int y=0; y!=3; ++y)
  {
    for (int x=0; x!=3; ++x)
    {
      times[x][y].reset(new ClockDialWidget(0,0,0,32,32,
        is_front ? 196 : 128,
        is_front ? 196 : 128,
        is_front ? 255 : 255));
    }
  }
}

bool ribi::ruco::operator==(const ribi::ruco::Times& lhs, const ribi::ruco::Times& rhs) noexcept
{
  for (int y=0; y!=3; ++y)
  {
    for (int x=0; x!=3; ++x)
    {
      if (lhs.times[x][y]->GetRubiksClockDial()->GetTime()
        != rhs.times[x][y]->GetRubiksClockDial()->GetTime()) return false;
    }
  }
  return true;
}

std::ostream& ribi::ruco::operator<<(std::ostream& os, const ribi::ruco::Times& t) noexcept
{
  os
    << "<rubiks_clock_times>";
  for (int x=0; x!=3; ++x)
  {
    for (int y=0; y!=3; ++y)
    {
      os
        << "<rubiks_clock_dial>"
        << "<x>"
        << x
        << "</x>"
        << "<y>"
        << y
        << "</y>"
        << t.times[x][y].get()
        << "</rubiks_clock_dial>";
    }
  }
  os
    << "</rubiks_clock_times>";
  return os;
}
