//---------------------------------------------------------------------------
/*
GTST, Game Theory Server
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
//From http://www.richelbilderbeek.nl/ProjectGtst.htm
//---------------------------------------------------------------------------
#include <cstdio>
#include <ctime>
#include <fstream>
#include <iostream>
#include <string>
//---------------------------------------------------------------------------
#include <boost/filesystem.hpp>
#include <boost/numeric/conversion/cast.hpp>
//#include <boost/property_tree/ptree.hpp>
//#include <boost/property_tree/xml_parser.hpp>
//---------------------------------------------------------------------------
#include "administrators.h"
#include "all_parameters.h"
#include "all_serverstates.h"
#include "group.h"
#include "groupfinished.h"
#include "grouploggedin.h"
#include "groupnotloggedin.h"
#include "groupparticipating.h"
#include "groups.h"
#include "state.h"
#include "logfile.h"
#include "participant.h"
#include "repeatassigner.h"
#include "resources.h"
#include "stopwatch.h"
#include "test.h"
#include "server.h"
#include "trace.h"
#include "wtserverpusher.h"
//---------------------------------------------------------------------------
///The Server Singleton its only instance
boost::scoped_ptr<Server> Server::m_instance;
//---------------------------------------------------------------------------
///Mutex when writing to Server
std::recursive_mutex Server::m_mutex;
//---------------------------------------------------------------------------
Server::Server()
  : m_administrators(new Administrators),
    m_groups(new Groups(this)),
    m_log(new LogFile),
    m_parameters(new Parameters(this))
{
  std::lock_guard<std::recursive_mutex> lock(m_mutex);

  //Create resources
  {
    boost::scoped_ptr<Resources>(new Resources);
  }

  m_states.reset(new ServerStates(this,m_parameters,m_log.get()));
  //SetParameters(m_parameters);
}
//---------------------------------------------------------------------------
///Assignment operator
/*
Server& Server::operator=(const Server& rhs)
{
  if (this == &rhs) return *this;

  std::lock_guard<std::mutex> lock(m_mutex);

  this->m_administrators = rhs.m_administrators;
  this->m_groups = rhs.m_groups;
  this->m_last_id_administrator = rhs.m_last_id_administrator;
  this->m_log = rhs.m_log;
  this->m_parameters = rhs.m_parameters;
  this->m_state = rhs.m_state;
  this->m_state_assign_payoff = rhs.m_state_assign_payoff;
  this->m_state_chat = rhs.m_state_chat;
  this->m_state_choose_action = rhs.m_state_choose_action;
  this->m_state_finished = rhs.m_state_finished;
  this->m_state_group_assign = rhs.m_state_group_assign;
  this->m_state_group_reassign = rhs.m_state_group_reassign;
  this->m_state_quiz = rhs.m_state_quiz;
  this->m_state_view_results_group = rhs.m_state_view_results_group;
  this->m_state_view_results_voting = rhs.m_state_view_results_voting;
  this->m_state_voting = rhs.m_state_voting;
  this->m_state_waiting = rhs.m_state_waiting;

  return *this;
}
*/
//---------------------------------------------------------------------------
///Deletes all Participant instances
void Server::DeleteParticipants()
{
  std::lock_guard<std::recursive_mutex> lock(m_mutex);

  m_groups->MoveAllToFinished();
  //m_groups.reset(new Groups(this));
  assert(m_parameters);
  m_parameters->DeleteParticipants();
}
//---------------------------------------------------------------------------
Server * Server::Get()
{
  if (!m_instance)
  {
    //Double-checked lock
    std::lock_guard<std::recursive_mutex> lock(Server::m_mutex);
    if (!m_instance) m_instance.reset(new Server);
  }
  assert(m_instance);
  return m_instance.get();
}
//---------------------------------------------------------------------------
///Obtain a read-only pointer to Groups
const Groups * Server::GetGroups() const
{
  std::lock_guard<std::recursive_mutex> lock(m_mutex);

  assert(m_groups);
  return m_groups.get();
}
//---------------------------------------------------------------------------
///Obtain a read-and-write pointer to Groups
//Avoiding duplication in const and non-const member functions.
//Scott Meyers. Effective C++ (3rd edition). ISBN: 0-321-33487-6. Item 3,
//paragraph 'Avoid duplication in const and non-const member functions'
Groups * Server::GetGroups()
{
  return const_cast<Groups*>(
    const_cast<const Server&>(*this).GetGroups());
}
//---------------------------------------------------------------------------
const LogFile * Server::GetLog() const
{
  std::lock_guard<std::recursive_mutex> lock(m_mutex);

  assert(m_log);
  return m_log.get();
}
//---------------------------------------------------------------------------
LogFile * Server::GetLog()
{
  std::lock_guard<std::recursive_mutex> lock(m_mutex);

  assert(m_log);
  return m_log.get();
}
//---------------------------------------------------------------------------
const Parameters * Server::GetParameters() const
{
  std::lock_guard<std::recursive_mutex> lock(m_mutex);

  assert(m_parameters);
  return m_parameters.get();
}
//---------------------------------------------------------------------------
const ServerStates * Server::GetStates() const
{
  std::lock_guard<std::recursive_mutex> lock(m_mutex);

  assert(m_states);
  return m_states.get();
}
//---------------------------------------------------------------------------
ServerStates * Server::GetStates()
{
  std::lock_guard<std::recursive_mutex> lock(m_mutex);

  assert(m_states);
  return m_states.get();
}
//---------------------------------------------------------------------------
boost::weak_ptr<Administrator> Server::LoginAdministrator()
{
  std::lock_guard<std::recursive_mutex> lock(m_mutex);

  return m_administrators->CreateNewAdministrator();
}
//---------------------------------------------------------------------------
const boost::shared_ptr<const Participant> Server::LetLogin(const boost::shared_ptr<const SafeIpAddress>& ip_address)
{
  std::lock_guard<std::recursive_mutex> lock(m_mutex);

  //Check for participants that reloaded the page by pressing F5
  if (GetGroups()->CanGetParticipantWithIpAddress(ip_address))
  {
    return GetGroups()->GetParticipantWithIpAddress(ip_address);
  }

  assert(GetGroups()->CanLetLogin(ip_address));

  const boost::shared_ptr<const Participant> new_participant
    = m_groups->LetLogin(ip_address);
  assert(new_participant);

  //Logging this event
  m_log->Login(new_participant);

  //New participants try to log in
  return new_participant;
}
//---------------------------------------------------------------------------
void Server::Reset()
{
  std::lock_guard<std::recursive_mutex> lock(m_mutex);

  m_administrators.reset(new Administrators);
  m_parameters.reset(new Parameters(this));
  this->SetParameters(m_parameters);
}
//---------------------------------------------------------------------------
void Server::NotifyLogout(const boost::shared_ptr<const Participant>& participant)
{
  std::lock_guard<std::recursive_mutex> lock(m_mutex);

  assert(participant);

  //Logging this eventServerState
  m_log->Logout(participant);

  //Do not erase the Participant: it is used again when he/she
  //refreshed his/her browser, so he/she can log in easily
}
//---------------------------------------------------------------------------
void Server::OnTimedServerPush()
{
  std::lock_guard<std::recursive_mutex> lock(m_mutex);
  //if (!m_states) return;
  assert(m_states);
  m_states->GetCurrentState()->OnTimer();
}
//---------------------------------------------------------------------------
void Server::SetParameters(boost::shared_ptr<Parameters> parameters)
{
  std::lock_guard<std::recursive_mutex> lock(m_mutex);

  assert(parameters);
  //m_groups.reset(new Groups(this));
  m_groups->MoveAllToFinished();
  GroupParticipating::Reset();
  m_log.reset(new LogFile);
  assert(m_log);
  m_parameters = parameters;
  m_log->LogParameters(m_parameters);
  m_states.reset(new ServerStates(this,m_parameters,m_log.get()));
  m_groups->SetParticipants(m_parameters->GetParticipants());
}
//---------------------------------------------------------------------------
void Server::TestMe()
{
  std::lock_guard<std::recursive_mutex> lock(m_mutex);

  ///Only test server for the first person that logs in
  static bool has_tested = false;
  if (has_tested) return;
  boost::scoped_ptr<Test> test(new Test(this));
  has_tested = true;
}
//---------------------------------------------------------------------------
