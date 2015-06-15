//---------------------------------------------------------------------------
/*
TimePoll, time polling server
Copyright (C) 2011-2015 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/ToolTimePoll.htm
//---------------------------------------------------------------------------
#ifndef TIMEPOLLDATA_H
#define TIMEPOLLDATA_H

#include <mutex>
#include <vector>

#include <boost/shared_ptr.hpp>


namespace ribi {

struct Stopwatch;

namespace ToolTimePoll {

///\brief
///The data used by the WtBroadcastServer
///
///Data is a Singleton
struct Data
{
  ///Get the fractions of the times spent in each option
  const std::vector<double> GetFractions() const;

  ///Get the currently selected index
  int GetIndex() const { return m_index; }

  ///Get the Data its only instance
  static Data * GetInstance();

  ///Get the times spent in each option
  const std::vector<double> GetTimes() const;

  ///Set the currently selected option
  void SetIndex(const int index);

  private:
  ///Data contructor is private, as it suits a Singleton best
  Data(const int n_options = 3);

  ///The currently selected index
  int m_index;

  ///The only instance of Data
  static Data * m_instance;

  ///The mutex
  static std::recursive_mutex m_mutex;

  ///The accumulated times
  std::vector<double> m_times;

  ///The stopwatch keeping track of the times
  boost::shared_ptr<Stopwatch> m_stopwatch;

};

} //~namespace ToolTimePoll
} //~namespace ribi

#endif // TIMEPOLLDATA_H
