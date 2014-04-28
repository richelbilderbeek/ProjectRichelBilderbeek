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

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-variable"
#include <boost/bind.hpp>

#include <Wt/WApplication>
#include <Wt/WServer>

#include "wttimedserverpusher.h"
#pragma GCC diagnostic pop

boost::scoped_ptr<ribi::WtTimedServerPusher> ribi::WtTimedServerPusher::m_instance;

ribi::WtTimedServerPusher::WtTimedServerPusher()
  : m_connections{},
    m_data{},
    m_mutex{},
    m_running(true),
    m_thread(boost::bind(&ribi::WtTimedServerPusher::Run, this)),
    m_time(1000)
{

}

ribi::WtTimedServerPusher::~WtTimedServerPusher()
{
  m_running = false;
  m_thread.join();
}

 void ribi::WtTimedServerPusher::Connect(
   WtTimedServerPusherClient * const client,
   const boost::function<void()>& function)
{
  std::lock_guard<std::mutex> lock(m_mutex);

  const boost::shared_ptr<Connection> connection {
    new Connection(
      Wt::WApplication::instance()->sessionId(),
      client,
      function
    )
  };

  m_connections.push_back(connection);

}

void ribi::WtTimedServerPusher::Disconnect(const WtTimedServerPusherClient* const client)
{
  std::lock_guard<std::mutex> lock(m_mutex);
  m_connections.erase(
    std::remove_if(m_connections.begin(),m_connections.end(),
      [client](const boost::shared_ptr<Connection>  c) { return c->m_client == client; } ));
}

ribi::WtTimedServerPusher * ribi::WtTimedServerPusher::GetInstance()
{
  if (!m_instance) m_instance.reset(new WtTimedServerPusher);
  return m_instance.get();
}

const std::string ribi::WtTimedServerPusher::GetVersion()
{
  return "1.0";
}

const std::vector<std::string> ribi::WtTimedServerPusher::GetVersionHistory()
{
  return {
    "2011-08-05: version 1.0: initial version"
  };
}

void ribi::WtTimedServerPusher::Run()
{
  while (m_running)
  {
    std::this_thread::sleep_for(std::chrono::milliseconds(m_time));
    {
      std::lock_guard<std::mutex> lock(m_mutex);
      std::for_each(m_connections.begin(),m_connections.end(),
        [](const boost::shared_ptr<Connection> i) { Wt::WServer::instance()->post(i->m_session_id, i->m_function); });
    }
  }
}

void ribi::WtTimedServerPusher::SetTime(const int time)
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
      m_thread = std::thread(boost::bind(&ribi::WtTimedServerPusher::Run, this));
    }
  }
}

