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
#include "testserverpusherdata.h"



ribi::ToolTestServerPusher::Data * ribi::ToolTestServerPusher::Data::m_instance = 0;

std::mutex ribi::ToolTestServerPusher::Data::m_mutex;

ribi::ToolTestServerPusher::Data::Data()
  : m_s("TestServerPusher")
{

}

ribi::ToolTestServerPusher::Data::~Data()
{

}

void ribi::ToolTestServerPusher::Data::SetData(const std::string& s)
{
  if (s != m_s)
  {
    //Double-lock idiom
    std::lock_guard<std::mutex> lock(m_mutex);
    if (s != m_s)
    {
      m_s = s;
    }
  }
}

ribi::ToolTestServerPusher::Data * ribi::ToolTestServerPusher::Data::GetInstance()
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

std::string ribi::ToolTestServerPusher::Data::GetData() const
{
  std::lock_guard<std::mutex> lock(m_mutex);
  return m_s;
}

