//---------------------------------------------------------------------------
/*
GTST, Game Theory Server
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
//From http://www.richelbilderbeek.nl/ProjectGtst.htm
//---------------------------------------------------------------------------
#include <cassert>
#include <fstream>
#include <iomanip>
//#include <iostream>
#include <sstream>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/numeric/conversion/bounds.hpp>

#include "gtstadministrator.h"
#include "gtstall_parameters.h"
#include "gtstall_serverstates.h"
#include "gtstgroupfinished.h"
#include "gtstgrouploggedin.h"
#include "gtstgroupnotloggedin.h"
#include "gtstgroupparticipating.h"
#include "gtstgroups.h"
#include "gtstlogfile.h"
#include "gtstparticipant.h"
#include "gtstrepeatassigner.h"
#include "gtststate.h"
#include "stopwatch.h"
#include "gtstserver.h"
#include "gtstparticipantdialog.h"
#include "gtstparticipantdialogstate.h"
#pragma GCC diagnostic pop

ribi::gtst::ServerState::ServerState(
  Server * const server,
  const int period,
  const int cycle)
  : m_cycle(cycle),
    m_period(period),
    m_server(server),
    m_stopwatch(new Stopwatch),
    m_wait_time{}
{
  assert(m_server);
  assert(m_stopwatch);
}

const std::string ribi::gtst::ServerState::CurrencyToStr(const double value)
{
  std::stringstream s;
  s << std::setprecision(2) << std::fixed;
  s << value;
  return s.str();
}

///Find a read/write Group from a read-only Group
///
///\note
///This is the only method that const_casts a Group
ribi::gtst::Group * ribi::gtst::ServerState::FindGroup(const Group * const group) const
{
  return GetServer()->GetGroups()->FindGroup(group);
}

///Find a read/write Participant from a read-only Participant
///Just checks if the Participant really exists
///
///\note
///One of the most important const_casts
boost::shared_ptr<ribi::gtst::Participant> ribi::gtst::ServerState::FindParticipant(const boost::shared_ptr<const Participant>& participant) const
{
  assert(GetServer()->GetGroups()->FindMyGroup(participant));

  return boost::const_pointer_cast<Participant>(participant);
}

///Obtain all Participant's their states relevant for the current ServerState
std::vector<std::string> ribi::gtst::ServerState::GetParticipantStates() const
{
  assert(GetServer());
  assert(GetServer()->GetGroups());
  std::vector<std::string> v;
  if (GetServer()->GetGroups()->CollectParticipants().empty())
  {
    v.push_back("No participants logged in");
    return v;
  }

  {
    auto ps = GetServer()->GetGroups()->CollectParticipants();
    std::for_each(ps.begin(),ps.end(),
      [&v](const boost::shared_ptr<const Participant>& p)
      {
        assert(p);
        v.push_back(p->ToAdminStr());
      } );
  }

  return v;
}

///Obtain the State its parent
ribi::gtst::Server * ribi::gtst::ServerState::GetServer() const
{
  assert(m_server);
  return m_server;
}

int ribi::gtst::ServerState::GetTimeLeft() const
{
  assert(m_stopwatch);
  return m_wait_time - m_stopwatch->elapsed();
}

void ribi::gtst::ServerState::GoToNextState()
{
  GetServer()->GetStates()->GoToNextState();
}

void ribi::gtst::ServerState::ResetTimeLeft()
{
  const int state_duration = GetStateDuration();
  assert(state_duration >= 0);
  this->SetTimeLeft(state_duration);
  assert(GetTimeLeft() >= -1); //-1 because of a possible clock tick
}

void ribi::gtst::ServerState::SetTimeLeft(const int time)
{
  //m_stopwatch.reset(new Stopwatch);
  m_wait_time = m_stopwatch->elapsed() + time;
}

