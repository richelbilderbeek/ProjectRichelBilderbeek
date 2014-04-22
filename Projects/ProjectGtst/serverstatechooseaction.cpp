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
#include <fstream>
#include <iostream>
//---------------------------------------------------------------------------
//#include <boost/bind.hpp>
#include <boost/foreach.hpp>
#include <boost/lambda/bind.hpp>
#include <boost/lambda/lambda.hpp>
//---------------------------------------------------------------------------
#include "administrator.h"
#include "all_parameters.h"
#include "all_serverstates.h"
#include "groupfinished.h"
#include "grouploggedin.h"
#include "groupnotloggedin.h"
#include "groupparticipating.h"
#include "groups.h"
#include "state.h"
#include "logfile.h"
#include "participant.h"
#include "repeatassigner.h"
#include "stopwatch.h"
#include "server.h"
#include "trace.h"
//#include "wtbroadcastserver.h"
//---------------------------------------------------------------------------
ribi::gtst::ServerStateChooseAction::ServerStateChooseAction(
  Server * const server, const int period, const int cycle,
  const boost::shared_ptr<const ParametersChooseAction> parameters)
  : ServerState(server,period,cycle),
    m_has_chosen_action{},
    m_parameters(parameters)
{

}
//---------------------------------------------------------------------------
///Check if this state can go to the next state.
bool ribi::gtst::ServerStateChooseAction::CanGoToNextState() const
{
  return std::find_if(
    m_has_chosen_action.begin(),
    m_has_chosen_action.end(),
    [](const std::pair<const boost::shared_ptr<const Participant>,bool>& i) { return !i.second; } )
    == m_has_chosen_action.end();
}
//---------------------------------------------------------------------------
///Obtain the duration of the state in seconds
int ribi::gtst::ServerStateChooseAction::GetStateDuration() const
{
  return m_parameters->GetDuration();
}
//---------------------------------------------------------------------------
///The Server is notified by ParticipantDialogChooseAction
///of the action taken by its Participant
void ribi::gtst::ServerStateChooseAction::NotifyChosenAction(
  const boost::shared_ptr<const Participant>& participant,
  const ChooseActionOption * const option)
{
  assert(option);
  this->FindParticipant(participant)->ChooseAction(option);

  m_has_chosen_action[participant] = true;

  m_server->GetLog()->LogAction(participant);
}
//---------------------------------------------------------------------------
void ribi::gtst::ServerStateChooseAction::OnTimer()
{
  if (CanGoToNextState())
  {
    GoToNextState();
  }
}
//---------------------------------------------------------------------------
/*
void ribi::gtst::ServerStateChooseAction::SetParameters(const boost::shared_ptr<const ParametersChooseAction>& parameters)
{
  assert(parameters);
  m_parameters = parameters;

  ResetTimeLeft();
  assert(this->GetTimeLeft() >= 0);
}
*/
//---------------------------------------------------------------------------
void ribi::gtst::ServerStateChooseAction::Start()
{
  ///Keeps track of Participants having voted
  m_has_chosen_action.clear();
  assert(m_has_chosen_action.empty());

  BOOST_FOREACH(
    const boost::shared_ptr<const Participant>& p,
    GetServer()->GetGroups()->CollectParticipants(false,false,true,false))
  {
    assert(!GetServer()->GetGroups()->CollectParticipants(false,false,true,false).empty());
    assert(p);
    m_has_chosen_action.insert(std::make_pair(p,false));
    StateChooseAction * const state = dynamic_cast<const StateChooseAction*>(this);
    assert(state);
    FindParticipant(p)->SetState(state);
  }
  assert(!CanGoToNextState());
}
//---------------------------------------------------------------------------
std::ostream& ribi::gtst::operator<<(std::ostream& os,const ServerStateChooseAction& s)
{
  os
    << "<state_" << s.ToStr() << ">"
    << "<has_chosen_action>";
  std::for_each(s.m_has_chosen_action.begin(),s.m_has_chosen_action.end(),
    [&os](const std::pair<const boost::shared_ptr<const Participant>,bool>& p)
    {
      os
        << (*(p.first))
        << "<yesno>"
        << p.second
        << "</yesno>";
    } );

  os
    << "</has_chosen_action>"
    << s.m_parameters
    << "</state_" << s.ToStr() << ">";
  return os;
}
//---------------------------------------------------------------------------
