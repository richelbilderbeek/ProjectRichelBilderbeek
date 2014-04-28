//---------------------------------------------------------------------------
/*
WtBroadcastServer, server to broadcast to all its WtBroadcastServerClients
Copyright (C) 2011-2014 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/CppWtBroadcastServer.htm
//---------------------------------------------------------------------------
#include "wtbroadcastserver.h"

#include <algorithm>
#include <chrono>
#include <numeric>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/bind.hpp>

#include <Wt/WApplication>
#include <Wt/WServer>

#pragma GCC diagnostic pop

boost::scoped_ptr<WtBroadcastServer> WtBroadcastServer::m_instance;

WtBroadcastServer::WtBroadcastServer()
  : m_running(true),
    m_thread(boost::bind(&WtBroadcastServer::Run, this)),
    m_time(1000)
{

}

WtBroadcastServer::~WtBroadcastServer()
{
  m_running = false;
  m_thread.join();
}

 void WtBroadcastServer::Connect(
   WtBroadcastServerClient * const client,
   const boost::function<void()>& function)
{
  std::lock_guard<std::mutex> lock(m_mutex);

  m_connections.push_back(
    Connection(
      Wt::WApplication::instance()->sessionId(),
      client,
      function));
}

void WtBroadcastServer::Disconnect(const WtBroadcastServerClient* const client)
{
  std::lock_guard<std::mutex> lock(m_mutex);
  m_connections.erase(
    std::remove_if(m_connections.begin(),m_connections.end(),
      [client](const Connection& c) { return c.m_client == client; } ));
}

void WtBroadcastServer::GetData(boost::any& data) const
{
  //Let this thread sleep, to give the other thread a chance
  std::this_thread::sleep_for(std::chrono::milliseconds(1));
  std::lock_guard<std::mutex> lock(m_mutex);
  data = m_data;
}

WtBroadcastServer * WtBroadcastServer::GetInstance()
{
  if (!m_instance) m_instance.reset(new WtBroadcastServer);
  return m_instance.get();
}

const std::string WtBroadcastServer::GetVersion()
{
  return "3.0";
}

const std::vector<std::string> WtBroadcastServer::GetVersionHistory()
{
  std::vector<std::string> v;
  v.push_back("2011-07-27: version 1.0: initial version");
  v.push_back("2011-07-29: version 2.0: added Post method");
  v.push_back("2011-07-29: version 2.1: fixed bug in timed updates");
  v.push_back("2011-08-01: version 3.0: made reading data thread-safe");
  return v;
}

void WtBroadcastServer::Post()
{
  ///Let this thread sleep, to give the other thread a chance
  //std::this_thread::sleep_for(std::chrono::milliseconds(10));
  std::lock_guard<std::mutex> lock(m_mutex);

  std::for_each(m_connections.begin(),m_connections.end(),
    [](const Connection& i) { Wt::WServer::instance()->post(i.m_session_id, i.m_function); });
}

void WtBroadcastServer::Run()
{
  while (m_running)
  {
    std::this_thread::sleep_for(std::chrono::milliseconds(m_time));
    {
      std::lock_guard<std::mutex> lock(m_mutex);
      //Do not call Post here!
      std::for_each(m_connections.begin(),m_connections.end(),
        [](const Connection& i) { Wt::WServer::instance()->post(i.m_session_id, i.m_function); });
    }
  }
}

void WtBroadcastServer::SetData(const boost::any& data)
{
  ///Let this thread sleep, to give the other thread a chance
  //std::this_thread::sleep_for(std::chrono::milliseconds(1));

  std::lock_guard<std::mutex> lock(m_mutex);
  m_data = data;
  //Notify the WtBroadcastServerClients
  //Do not call Post here!
  std::for_each(m_connections.begin(),m_connections.end(),
    [](const Connection& i) { Wt::WServer::instance()->post(i.m_session_id, i.m_function); });
}

void WtBroadcastServer::SetTime(const int time)
{
  std::lock_guard<std::mutex> lock(m_mutex);
  m_running = time > 0;
  m_time = time;
}

