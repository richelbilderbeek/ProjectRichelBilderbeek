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
#include <cassert>
//#include <iostream>
//---------------------------------------------------------------------------
//#include <boost/bind.hpp>
#include <boost/foreach.hpp>
#include <boost/lambda/bind.hpp>
#include <boost/lambda/lambda.hpp>
//---------------------------------------------------------------------------
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
#include "stopwatch.h"
#include "server.h"
//#include "trace.h"
//---------------------------------------------------------------------------
ServerStateQuiz::ServerStateQuiz(
  Server * const server, const int period, const int cycle,
  const boost::shared_ptr<const ParametersQuiz>& parameters)
  : ServerState(server,period,cycle),
    m_parameters(parameters)
{
  assert(m_parameters);
}
//---------------------------------------------------------------------------
///ServerStateQuiz goes to the next state if
/// - all Participants are logged in
/// - all Participants have voted
bool ServerStateQuiz::CanGoToNextState() const
{
  typedef std::pair<boost::shared_ptr<const Participant>,bool> Pair;
  BOOST_FOREACH(const Pair& p,m_has_voted)
  {
    if (p.second == false) return false;
  }
  return true;

  /*
  //If there is no 'false' in m_has_voted::second
  return std::find_if(
    m_has_voted.begin(),
    m_has_voted.end(),
      boost::lambda::bind(
        &std::pair<const Participant*,bool>::second,
        boost::lambda::_1) == false)
    == m_has_voted.end();
  */
}
//---------------------------------------------------------------------------
///Obtain the duration of the state in seconds
int ServerStateQuiz::GetStateDuration() const
{
  //return m_parameters->GetDuration();
  return 123456;
}
//---------------------------------------------------------------------------
///ParticipantDialog notifies the Server of the
///Participant his/her vote
void ServerStateQuiz::NotifyVote(
  const boost::shared_ptr<const Participant>& participant,
  const boost::shared_ptr<VotingOption>& vote)
{
  FindParticipant(participant)->Vote(vote);

  m_has_voted[participant] = true;

  //Log the vote
  m_server->GetLog()->LogVote(participant);
  //WtBroadcastServer::GetInstance()->Post();
}
//---------------------------------------------------------------------------
void ServerStateQuiz::OnTimer()
{
  if (CanGoToNextState()) GoToNextState();
}
//---------------------------------------------------------------------------
/*
void ServerStateQuiz::SetParameters(const ParametersQuiz* const parameters)
{
  assert(parameters);
  m_parameters = parameters;

  ResetTimeLeft();
  assert(this->GetTimeLeft() >= 0);
}
*/
//---------------------------------------------------------------------------
void ServerStateQuiz::Start()
{
  ///Keeps track of Participants having voted
  m_has_voted.clear();
  assert(m_has_voted.empty());

  BOOST_FOREACH(const boost::shared_ptr<const Participant>& p,
    GetServer()->GetGroups()->CollectParticipants(false,false,true,false))
  {
    assert(p);
    m_has_voted[p] = false;
    StateQuiz * const state = dynamic_cast<const StateQuiz*>(this);
    assert(state);
    FindParticipant(p)->SetState(state);
  }
  assert(!CanGoToNextState());
}
//---------------------------------------------------------------------------
std::ostream& operator<<(std::ostream& os,const ServerStateQuiz& s)
{
  os
    << "<state_" << s.ToStr() << ">"
    << s.m_parameters
    << "</state_" << s.ToStr() << ">";
  return os;
}
//---------------------------------------------------------------------------
