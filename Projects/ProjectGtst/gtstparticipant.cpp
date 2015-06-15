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
#include <iostream>
#include <numeric>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/numeric/conversion/cast.hpp>

#include "gtstchatshapefactory.h"
#include "gtstgroupassigner.h"
#include "ipaddress.h"
#include "gtstparticipant.h"
#include "gtstparticipantstate.h"
#include "gtstparticipantstateassignpayoff.h"
#include "gtstparticipantstatechat.h"
#include "gtstparticipantstatechooseaction.h"
#include "gtstparticipantstatefinished.h"
#include "gtstparticipantstategroupassign.h"
#include "gtstparticipantstategroupreassign.h"
#include "gtstparticipantstateloggedin.h"
#include "gtstparticipantstatenotloggedin.h"
#include "gtstparticipantstatequiz.h"
#include "gtstparticipantstateviewresultsgroup.h"
#include "gtstparticipantstateviewresultsvoting.h"
#include "gtstparticipantstatevoting.h"
#include "gtstpayoffs.h"
#include "shape.h"
#include "shapewidget.h"
#include "gtststate.h"
#include "wtshapewidget.h"
#pragma GCC diagnostic pop

ribi::gtst::Participant::Participant(
  boost::shared_ptr<GroupAssigner> group_assigner,
  Server * const server)
  : m_actions{},
    m_chat{},
    m_chat_shape(
      new WtShapeWidget(
        ChatShapeFactory::Get()->GetNextWidget())),
    m_group_assigner(group_assigner),
    m_id(0),
    m_ip_address{},
    m_payoffs(new Payoffs),
    m_state(new ParticipantStateNotLoggedIn(this,server)),
    m_state_assign_payoff(new ParticipantStateAssignPayoff(this,server)),
    m_state_chat(new ParticipantStateChat(this,server)),
    m_state_choose_action(new ParticipantStateChooseAction(this,server)),
    m_state_finished(new ParticipantStateFinished(this,server)),
    m_state_group_assign(new ParticipantStateGroupAssign(this,server)),
    m_state_group_reassign(new ParticipantStateGroupReAssign(this,server)),
    m_state_logged_in(new ParticipantStateLoggedIn(this,server)),
    m_state_not_logged_in(new ParticipantStateNotLoggedIn(this,server)),
    m_state_quiz(new ParticipantStateQuiz(this,server)),
    m_state_view_resuls_group(new ParticipantStateViewResultsGroup(this,server)),
    m_state_view_results_voting(new ParticipantStateViewResultsVoting(this,server)),
    m_state_voting(new ParticipantStateVoting(this,server)),
    m_votes{}
{
  assert(m_id == 0 && "Assume ID is unassigned");
  assert(m_group_assigner);
  assert(m_state);

  assert(!CanGetId());
}

ribi::gtst::Participant::~Participant()
{
  //std::clog << "ribi::gtst::Participant::~Participant() for #" << GetId() << '\n' ;
}

void ribi::gtst::Participant::AppendChat(const boost::shared_ptr<ChatMessage>& message)
{
  assert(message);
  assert(!m_chat.empty());

  m_chat.back().push_back(message);
}

///Assign the Participant an ID
void ribi::gtst::Participant::AssignId(const int id)
{
  assert(id > 0 && "ID\'s must be positive non-zero values");
  m_id = id;
}

///Assign the payoff the Participant receives from the chosen action
//void ribi::gtst::Participant::AssignPayoff(const double payoff)
//{
//  m_payoffs.push_back(payoff);
//}

///Check if the Participant is assigned an ID already
///if m_id equals zero, the Participant is not assigned an ID yet
bool ribi::gtst::Participant::CanGetId() const
{
  assert(m_id >= 0);
  return m_id != 0;
}

bool ribi::gtst::Participant::CanGetIpAddress() const
{
  return m_ip_address.get();
}

///Lets the Participant choose an action
void ribi::gtst::Participant::ChooseAction(const ChooseActionOption * const option)
{
  assert(option);

  m_actions.push_back(option);
}

///Get the Participant his/her unique ID
int ribi::gtst::Participant::GetId() const
{
  assert(m_id > 0 && "ID\'s must be positive non-zero values");
  return m_id;
}

///Get the Participant's IP address
const boost::shared_ptr<const ribi::SafeIpAddress> ribi::gtst::Participant::GetIpAddress() const
{
  return m_ip_address;
}

///Avoiding duplication in const and non-const member functions.
//Scott Meyers. Effective C++ (3rd edition). ISBN: 0-321-33487-6. Item 3,
//paragraph 'Avoid duplication in const and non-const member functions'
ribi::gtst::ParticipantState * ribi::gtst::Participant::GetState()
{
  return const_cast<ParticipantState*>(
    const_cast<const Participant&>(*this).GetState());
}

const ribi::gtst::ParticipantState * ribi::gtst::Participant::GetState() const
{
  assert(m_state);
  return m_state;
}

void ribi::gtst::Participant::SetIpAddress(const boost::shared_ptr<const SafeIpAddress>& ip_address)
{
  assert(!CanGetIpAddress() && "Cannot change the IP address of a participant if it is valid already");

  m_ip_address = ip_address;
}

///SetState sets the ParticipantState of the Participant
void ribi::gtst::Participant::SetState(const State * const state)
{
  if (dynamic_cast<const StateAssignPayoff*>(state))
  {
    m_state = m_state_assign_payoff.get();
  }
  else if (dynamic_cast<const StateChat*>(state))
  {
    m_state = m_state_chat.get();
  }
  else if (dynamic_cast<const StateChooseAction*>(state))
  {
    m_state = m_state_choose_action.get();
  }
  else if (dynamic_cast<const StateFinished*>(state))
  {
    m_state = m_state_finished.get();
  }
  else if (dynamic_cast<const StateGroupAssign*>(state))
  {
    m_state = m_state_group_assign.get();
  }
  else if (dynamic_cast<const StateGroupReAssign*>(state))
  {
    m_state = m_state_group_reassign.get();
  }
  else if (dynamic_cast<const StateLoggedIn*>(state))
  {
    m_state = m_state_logged_in.get();
  }
  else if (dynamic_cast<const StateNotLoggedIn*>(state))
  {
    m_state = m_state_not_logged_in.get();
  }
  else if (dynamic_cast<const StateQuiz*>(state))
  {
    m_state = m_state_quiz.get();
  }
  else if (dynamic_cast<const StateViewResultsGroup*>(state))
  {
    m_state = m_state_view_resuls_group.get();
  }
  else if (dynamic_cast<const StateViewResultsVoting*>(state))
  {
    m_state = m_state_view_results_voting.get();
  }
  else if (dynamic_cast<const StateVoting*>(state))
  {
    m_state = m_state_voting.get();
  }
  else
  {
    assert(!"Should not get here: unimplemented state for Participant");
  }
}

///StartChat lets the Participant know that he/she starts a new chat phase
void ribi::gtst::Participant::StartChat()
{
  m_chat.push_back(std::vector<boost::shared_ptr<ChatMessage> >());
}

///ToStr creates a one-line string viewed by an Administrator
const std::string ribi::gtst::Participant::ToAdminStr() const
{
  return this->GetState()->ToAdminStr();
}

void ribi::gtst::Participant::Vote(const boost::shared_ptr<VotingOption>& vote)
{
  m_votes.push_back(vote);
}

std::ostream& ribi::gtst::operator<<(std::ostream& os,const Participant& p)
{
  os
    << "<participant>"
    << "<id>"
    << (p.CanGetId()
      ? std::to_string(p.GetId())
      : std::string("N/A"))
    << "</id>"
    << "<ip_address>"
    << (p.CanGetIpAddress()
      ? p.GetIpAddress()->Get()
      : std::string("*"))
    << "</ip_address>"
    << "<state>"
    << (p.GetState()->ToStr())
    << "</state>"
    << "</participant>";
  return os;
  }

std::ostream& ribi::gtst::operator<<(std::ostream& os,const boost::shared_ptr<Participant>& p)
{
  assert(p);
  os << (*(p.get()));
  return os;
}

bool ribi::gtst::operator<(const Participant& lhs,const Participant& rhs)
{
  assert(lhs.GetId() != rhs.GetId() && "Assume each participant has a unique ID");
  return lhs.GetId() < rhs.GetId();
}


