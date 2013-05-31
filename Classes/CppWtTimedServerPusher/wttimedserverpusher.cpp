//---------------------------------------------------------------------------
/*
WtTimedServerPusher, server to broadcast to all its WtTimedServerPusherClients
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
//From http://www.richelbilderbeek.nl/CppWtTimedServerPusher.htm
//---------------------------------------------------------------------------
#include <algorithm>
#include <chrono>
#include <numeric>
//---------------------------------------------------------------------------
#include <boost/bind.hpp>
//---------------------------------------------------------------------------
#include <Wt/WApplication>
#include <Wt/WServer>
//---------------------------------------------------------------------------
#include "wttimedserverpusher.h"
//---------------------------------------------------------------------------
boost::scoped_ptr<WtTimedServerPusher> WtTimedServerPusher::m_instance;
//---------------------------------------------------------------------------
WtTimedServerPusher::WtTimedServerPusher()
  : m_running(true),
    m_thread(boost::bind(&WtTimedServerPusher::Run, this)),
    m_time(1000)
{

}
//---------------------------------------------------------------------------
WtTimedServerPusher::~WtTimedServerPusher()
{
  m_running = false;
  m_thread.join();
}
//---------------------------------------------------------------------------
 void WtTimedServerPusher::Connect(
   WtTimedServerPusherClient * const client,
   const boost::function<void()>& function)
{
  std::lock_guard<std::mutex> lock(m_mutex);

  m_connections.push_back(
    Connection(
      Wt::WApplication::instance()->sessionId(),
      client,
      function));
}
//---------------------------------------------------------------------------
void WtTimedServerPusher::Disconnect(const WtTimedServerPusherClient* const client)
{
  std::lock_guard<std::mutex> lock(m_mutex);
  m_connections.erase(
    std::remove_if(m_connections.begin(),m_connections.end(),
      [client](const Connection& c) { return c.m_client == client; } ));
}
//---------------------------------------------------------------------------
WtTimedServerPusher * WtTimedServerPusher::GetInstance()
{
  if (!m_instance) m_instance.reset(new WtTimedServerPusher);
  return m_instance.get();
}
//---------------------------------------------------------------------------
const std::string WtTimedServerPusher::GetVersion()
{
  return "1.0";
}
//---------------------------------------------------------------------------
const std::vector<std::string> WtTimedServerPusher::GetVersionHistory()
{
  std::vector<std::string> v;
  v.push_back("2011-08-05: version 1.0: initial version");
  return v;
}
//---------------------------------------------------------------------------
void WtTimedServerPusher::Run()
{
  while (m_running)
  {
    std::this_thread::sleep_for(std::chrono::milliseconds(m_time));
    {
      std::lock_guard<std::mutex> lock(m_mutex);
      std::for_each(m_connections.begin(),m_connections.end(),
        [](const Connection& i) { Wt::WServer::instance()->post(i.m_session_id, i.m_function); });
    }
  }
}
//---------------------------------------------------------------------------
void WtTimedServerPusher::SetTime(const int time)
{
  std::lock_guard<std::mutex> lock(m_mutex);
  if (m_running)
  {
    if (time <= 0)
    {
      //stop WtTimedServerPusher, although thread needs to finish first
      m_time = 0;
      m_running = false;
    }
    else
    {
      //Change time, although thread needs to finish first
      m_time = time;
    }
  }
  else
  {
    if (time <= 0)
    {
      //stop stopped WtTimedServerPusher
      m_time = 0;
    }
    else
    {
      //Start stopped WtTimedServerPusher
      m_running = true;
      m_time = time;
      m_thread = std::thread(boost::bind(&WtTimedServerPusher::Run, this));
    }
  }
}
//---------------------------------------------------------------------------
