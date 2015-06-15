//---------------------------------------------------------------------------
/*
TestTimedServerPusher, tool to test WtTimedServerPusher
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
//From http://www.richelbilderbeek.nl/ToolTestTimedServerPusher.htm
//---------------------------------------------------------------------------
#ifndef TOOLTESTTIMEDSERVERPUSHERDATA_H
#define TOOLTESTTIMEDSERVERPUSHERDATA_H

#include <chrono>
#include <mutex>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/checked_delete.hpp>
#pragma GCC diagnostic pop

namespace ribi {
namespace ToolTestTimedServerPusher {

///Data is a Singleton
struct Data
{
  ///Get the Data single instance
  static Data * GetInstance();

  ///Get the data
  std::string GetData() const;

  private:
  ///Data constructor
  Data();

  ///Data destructor
  ~Data();

  ///Only let a smart pointer (that is, m_instance) delete Data
  friend void boost::checked_delete<>(Data*);

  static Data * m_instance;

  static std::mutex m_mutex;

  ///The program its starting time
  const std::time_t m_time_start;
  //std::chrono::system_clock::time_point m_s;

  ///The number of times the data has been requested
  mutable int m_requested;
};


} //~namespace ToolTestTimedServerPusher
} //~namespace ribi

#endif // TOOLTESTTIMEDSERVERPUSHERDATA_H
