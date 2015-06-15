//---------------------------------------------------------------------------
/*
TestServerPusher, tool to test WtServerPusher
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
//From http://www.richelbilderbeek.nl/ToolTestServerPusher.htm
//---------------------------------------------------------------------------
#ifndef TOOLTESTSERVERPUSHERDATA_H
#define TOOLTESTSERVERPUSHERDATA_H

#include <mutex>

#include <boost/checked_delete.hpp>

namespace ribi {
namespace ToolTestServerPusher {

///Data is a Singleton
struct Data
{
  ///Set the data
  void SetData(const std::string& s);

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

  ///The data
  std::string m_s;
};

} //~namespace ToolTestServerPusher
} //~namespace ribi

#endif // TOOLTESTSERVERPUSHERDATA_H
