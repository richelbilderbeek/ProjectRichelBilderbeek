//---------------------------------------------------------------------------
/*
WtSafeTimer, forward-declaration-safe Wt::WTimer
Copyright (C) 2011 Richel Bilderbeek

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program. If not, see <http://www.gnu.org/licenses/>.
*/
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/CppWtSafeTimer.htm
//---------------------------------------------------------------------------
#include <iostream>
//---------------------------------------------------------------------------
#include <Wt/WTimer>
#include <Wt/WEvent>
//---------------------------------------------------------------------------
#include "wtsafetimer.h"
//---------------------------------------------------------------------------
WtSafeTimer::WtSafeTimer(const int time_msec)
  : m_timer(new Wt::WTimer)
{
  m_timer->setInterval(time_msec);
  m_timer->start();
}
//---------------------------------------------------------------------------
WtSafeTimer::~WtSafeTimer()
{

}
//---------------------------------------------------------------------------
const std::string WtSafeTimer::GetVersion()
{
  return "1.0";
}
//---------------------------------------------------------------------------
const std::vector<std::string> WtSafeTimer::GetVersionHistory()
{
  std::vector<std::string> v;
  v.push_back("YYYY-MM-DD: version X.Y: [description]");
  v.push_back("2011-06-22: version 1.0: initial version");
  return v;
}
//---------------------------------------------------------------------------
void WtSafeTimer::OnTimer()
{
  std::clog << __func__ << '\n';
  timeout().emit(Wt::WMouseEvent());
}
//---------------------------------------------------------------------------
Wt::EventSignal<Wt::WMouseEvent>& WtSafeTimer::timeout()
{
  assert(m_timer);
  return m_timer->timeout();
}
//---------------------------------------------------------------------------
