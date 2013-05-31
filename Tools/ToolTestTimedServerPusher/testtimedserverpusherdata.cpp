//---------------------------------------------------------------------------
/*
TestTimedServerPusher, tool to test WtTimedServerPusher
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
//From http://www.richelbilderbeek.nl/ToolTestTimedServerPusher.htm
//---------------------------------------------------------------------------
#include <boost/lexical_cast.hpp>
#include "testtimedserverpusherdata.h"
//---------------------------------------------------------------------------
namespace ToolTestTimedServerPusher {
//---------------------------------------------------------------------------
Data * Data::m_instance = 0;
//---------------------------------------------------------------------------
std::mutex Data::m_mutex;
//---------------------------------------------------------------------------
Data::Data()
  : m_time_start(std::time(0)),
  //m_s(std::chrono::system_clock::now()),
  m_requested(0)

{

}
//---------------------------------------------------------------------------
Data::~Data()
{

}
//---------------------------------------------------------------------------
Data * Data::GetInstance()
{
  if (!m_instance)
  {
    //Double-lock idiom
    std::lock_guard<std::mutex> lock(m_mutex);
    if (!m_instance)
    {
      m_instance = new Data;
    }
  }
  return m_instance;
}
//---------------------------------------------------------------------------
const std::string Data::GetData() const
{
  std::lock_guard<std::mutex> lock(m_mutex);
  //std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
  //std::chrono::duration<int,1> d = now - m_s;
  //const std::string s = std::lexical_cast<std::string>(d);
  ++m_requested;
  const std::string s = boost::lexical_cast<std::string>(
    std::difftime(std::time(0),m_time_start))
    + std::string(" seconds, ")
    + boost::lexical_cast<std::string>(m_requested)
    + std::string(" requests ");
  return s;
}
//---------------------------------------------------------------------------
} //~namespace ToolTestTimedServerPusher
//---------------------------------------------------------------------------
