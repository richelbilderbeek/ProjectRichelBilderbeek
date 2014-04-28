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
#ifndef WTBROADCASTSERVER_H
#define WTBROADCASTSERVER_H

#include <mutex>
#include <thread>
#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/any.hpp>
#include <boost/function.hpp>
#include <boost/scoped_ptr.hpp>
#pragma GCC diagnostic pop

struct WtBroadcastServerClient;

///A Server that broadcasts its messages
struct WtBroadcastServer
{
  ///Let a WtBroadcastServerClient have its supplied function called by WtBroadcastServer::Run
  void Connect(WtBroadcastServerClient * const client, const boost::function<void()>& function);

  ///Stop a WtBroadcastServerClient have its supplied function called by TimePollServer::Run
  void Disconnect(const WtBroadcastServerClient* const client);

  //private:
  ///\brief
  ///Get a _copy_ of the data by reference
  ///
  ///GetData is implemented by references, so that obtaining the data
  ///can also be done thread-safe, that is, locked by a mutex
  void GetData(boost::any& data) const;

  public:
  ///Obtain the only instace to WtBroadcastServer
  static WtBroadcastServer * GetInstance();

  ///Get the version of this class
  static const std::string GetVersion();

  ///Get the version history of this class
  static const std::vector<std::string> GetVersionHistory();

  ///Post calls all WtBroadcastServerClients' supplied functions
  void Post();

  //private:
  ///Set the data
  void SetData(const boost::any& data);
  public:

  ///\brief
  ///Set the time (in milliseconds) WtBroadcastServerClient::UpdatePage is to be called
  ///
  ///Use a time of zero to only let WtBroadcastServerClient::UpdatePage be
  ///called upon Post
  void SetTime(const int time);

private:
  //Connection is a POD
  struct Connection
  {
    Connection(
      const std::string& session_id,
      WtBroadcastServerClient * client,
      const boost::function<void()>& function)
      : m_session_id(session_id),m_client(client),m_function(function)
    {

    }
    std::string m_session_id;
    WtBroadcastServerClient * m_client;
    boost::function<void()> m_function;
  };

  ///WtBroadcastServer constructor, which is private, because WtBroadcastServer follows
  ///the Singleton design pattern
  WtBroadcastServer();

  ///WtBroadcastServer destructor
  ~WtBroadcastServer();

  ///Only let a smart pointer (that is, m_instance) delete WtBroadcastServer
  friend void boost::checked_delete<>(WtBroadcastServer*);

  ///All connections to the WtBroadcastServerClients
  std::vector<Connection> m_connections;

  ///The WtBroadcastServer its only instance
  static boost::scoped_ptr<WtBroadcastServer> m_instance;

  ///The data, can be anything
  boost::any m_data;

  ///A mutex
  mutable std::mutex m_mutex;

  ///If the Server is running
  bool m_running;

  ///The thread for WtBroadcastServer::Run
  std::thread m_thread;

  ///The number of milliseconds before Run triggers Post
  int m_time;

  ///The method that is called every 100 msecs
  void Run();
};

#endif // WTBROADCASTSERVER_H
