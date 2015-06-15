
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

//From http://www.richelbilderbeek.nl/ProjectGtst.htm

#ifndef PROJECTGTSTPARTICIPANT_H
#define PROJECTGTSTPARTICIPANT_H

#include <iosfwd>
#include <string>
#include <vector>

#include <boost/checked_delete.hpp>

#include <boost/scoped_ptr.hpp>
#include <boost/shared_ptr.hpp>

#include "gtstforward_declarations.h"


namespace ribi {
namespace gtst {

///\brief
///Participant is a participant.
///
///During a session there are zero, one or more instances of Participant.
struct Participant
{
  ///A Participant is constructed by a chat tag and his/her GroupAssigner
  Participant(
    boost::shared_ptr<GroupAssigner> group_assigner,
    Server * const server);
  Participant(const Participant&) = delete;
  Participant& operator=(const Participant&) = delete;

  ///Append the last chat message (from someone in Participants's group)
  ///to this Participant's chat log
  void AppendChat(const boost::shared_ptr<ChatMessage>& message);

  ///Assign the Participant an ID
  void AssignId(const int id);

  ///Assign the payoff the Participant receives from the chosen action
  //void AssignPayoff(const double payoff);

  ///Check if the Participant is assigned an ID already
  bool CanGetId() const;

  ///Check if the Participant already has an IP address assigned
  bool CanGetIpAddress() const;

  ///Lets the Participant choose an action
  void ChooseAction(const ChooseActionOption * const option);

  ///Get the Actions taken by the Participant
  const std::vector<const ChooseActionOption *>& GetActions() const { return m_actions; }

  ///Get the Chat log of all chat messages in group
  const std::vector<std::vector<boost::shared_ptr<ChatMessage> > >& GetChatLog() const { return m_chat; }

  ///Get the Participant's chat tag
  boost::shared_ptr<const WtShapeWidget> GetChatShape() const { return m_chat_shape; }

  ///Get the Participant his/her unique ID
  int GetId() const;

  ///Get the Participant's IP address
  const boost::shared_ptr<const SafeIpAddress> GetIpAddress() const;

  ///Get the Participant his/her GroupAssigner as a read-only pointer
  const GroupAssigner * GetGroupAssigner() const { return m_group_assigner.get(); }

  ///Get the Participant his/her payoffs received in the total experiment
  const boost::shared_ptr<const Payoffs> GetPayoffs() const { return m_payoffs; }

  ///Get the Participant his/her payoffs received in the total experiment
  boost::shared_ptr<Payoffs> GetPayoffs() { return m_payoffs; }

  ///Get the Participant last assigned payoff
  //double GetPayoffLast() const;

  ///Get the Participant his/her total payoff
  //double GetPayoffTotal() const;

  ///Get the ExperimentState in which the Participant is
  ///in as a read-only pointer
  const ParticipantState * GetState() const;

  ///Get the ExperimentState in which the Participant is
  ///in as a read-and-write pointer
  ParticipantState * GetState();

  ///Get all votes of this Participant
  const std::vector<boost::shared_ptr<VotingOption> >& GetVotes() const { return m_votes; }

  ///Assign an IP address to the Participant
  void SetIpAddress(const boost::shared_ptr<const SafeIpAddress>& ip_address);

  ///SetState sets the ParticipantState of the Participant
  void SetState(const State * const state);

  ///StartChat lets the Participant know that he/she starts a new chat phase
  void StartChat();

  ///ToStr creates a one-line string viewed by an Administrator
  const std::string ToAdminStr() const;

  ///Lets the Participant vote
  void Vote(const boost::shared_ptr<VotingOption>& vote);

  private:
  ~Participant();
  friend void boost::checked_delete<>(Participant*);

  ///m_actions is a log of all actions taken by the participant
  std::vector<const ChooseActionOption *> m_actions;

  ///m_chat is the participants' chat log, obtained from all participants
  std::vector<std::vector<boost::shared_ptr<ChatMessage> > > m_chat;

  ///The chat tag is the character that is assigned to a participant at chatting
  const boost::shared_ptr<WtShapeWidget> m_chat_shape;

  ///m_group_assigner is a Strategy that determines the group number
  ///of a Participant.
  boost::shared_ptr<GroupAssigner> m_group_assigner;

  ///Every Participant has a unique ID.
  ///This ID is uncorrelated with Administrator::m_id
  int m_id;

  ///The IP address this participant is allowed to be assigned to.
  ///if m_ip_address is null, the participant can log in from any IP address.
  ///When the participant logs in, his/her IP address is stored here
  boost::shared_ptr<const SafeIpAddress> m_ip_address;

  ///m_payoffs is a log of all payoffs recieved by the participant
  boost::shared_ptr<Payoffs> m_payoffs;

  //Server * const m_server;

  ///The current ParticipantState the Participant is in
  ParticipantState * m_state;
  ///The Participant his/her ParticipantStateAssignPayoff ParticipantState
  boost::scoped_ptr<ParticipantStateAssignPayoff> m_state_assign_payoff;
  ///The Participant his/her ParticipantStateChat ParticipantState
  boost::scoped_ptr<ParticipantStateChat> m_state_chat;
  ///The Participant his/her ParticipantStateChooseAction ParticipantState
  boost::scoped_ptr<ParticipantStateChooseAction> m_state_choose_action;
  ///The Participant his/her ParticipantStateFinished ParticipantState
  boost::scoped_ptr<ParticipantStateFinished> m_state_finished;
  ///The Participant his/her ParticipantStateGroupAssign ParticipantState
  boost::scoped_ptr<ParticipantStateGroupAssign> m_state_group_assign;
  ///The Participant his/her ParticipantStateGroupReAssign ParticipantState
  boost::scoped_ptr<ParticipantStateGroupReAssign> m_state_group_reassign;
  ///The Participant his/her ParticipantStateLoggedIn ParticipantState
  boost::scoped_ptr<ParticipantStateLoggedIn> m_state_logged_in;
  ///The Participant his/her ParticipantStateNotLoggedIn ParticipantState
  boost::scoped_ptr<ParticipantStateNotLoggedIn> m_state_not_logged_in;
  ///The Participant his/her ParticipantStateQuiz ParticipantState
  boost::scoped_ptr<ParticipantStateQuiz> m_state_quiz;
  ///The Participant his/her ParticipantStateViewResultsGroup ParticipantState
  boost::scoped_ptr<ParticipantStateViewResultsGroup> m_state_view_resuls_group;
  ///The Participant his/her ParticipantStateViewResultsVoting ParticipantState
  boost::scoped_ptr<ParticipantStateViewResultsVoting> m_state_view_results_voting;
  ///The Participant his/her ParticipantStateVoting ParticipantState
  boost::scoped_ptr<ParticipantStateVoting> m_state_voting;

  ///m_votes is a log of all votes by the participant
  std::vector<boost::shared_ptr<VotingOption> > m_votes;
};

//Forward declarations.
//Herb Sutter. Exceptional C++. ISBN: 0-201-61562-2. Item 26: 'Never #include a header when a forward declaration will suffice'
std::ostream& operator<<(std::ostream& os,const Participant& p);
std::ostream& operator<<(std::ostream& os,const boost::shared_ptr<Participant>& p);
bool operator<(const Participant& lhs,const Participant& rhs);

} //~namespace gtst
} //~namespace ribi

#endif // PARTICIPANT_H
