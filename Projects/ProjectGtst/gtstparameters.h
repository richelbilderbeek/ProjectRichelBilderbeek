
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

#ifndef PROJECTGTSTPARAMETERS_H
#define PROJECTGTSTPARAMETERS_H

#include <string>
#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/scoped_ptr.hpp>
#include <boost/shared_ptr.hpp>

#include "gtstforward_declarations.h"
#pragma GCC diagnostic pop

namespace ribi {
namespace gtst {

///\brief
///Parameters for an experiment
struct Parameters
{
  ///Create a default-constructed Parameters
  Parameters(Server * const server);
  Parameters(const Parameters&) = delete;
  Parameters& operator=(const Parameters&) = delete;

  ///Create a default non-logged in Participant
  boost::shared_ptr<Participant> CreateDefaultParticipant();

  ///Deletes all Participant instances
  void DeleteParticipants();

  ///Set a Parameter from file
  void ReadFromFile(const std::string& filename);

  ///Get the ParametersAssignPayoff as a read-and-write pointer
  boost::shared_ptr<ParametersAssignPayoff> GetAssignPayoff() { return m_assign_payoff; }
  ///Get the ParametersAssignPayoff as a read-only pointer
  boost::shared_ptr<const ParametersAssignPayoff> GetAssignPayoff() const { return m_assign_payoff; }
  ///Get the ParametersChat as a read-and-write pointer
  boost::shared_ptr<ParametersChat> GetChat() { return m_chat; }
  ///Get the ParametersChat as a read-only pointer
  boost::shared_ptr<const ParametersChat> GetChat() const { return m_chat; }
  ///Get the ParametersChooseAction as a read-and-write pointer
  boost::shared_ptr<ParametersChooseAction> GetChooseAction() { return m_choose_action; }
  ///Get the ParametersChooseAction as a read-only pointer
  boost::shared_ptr<const ParametersChooseAction> GetChooseAction() const { return m_choose_action; }
  ///Get the ParametersFinished as a read-and-write pointer
  boost::shared_ptr<ParametersFinished> GetFinished() { return m_finished; }
  ///Get the ParametersFinished as a read-only pointer
  boost::shared_ptr<const ParametersFinished> GetFinished() const { return m_finished; }
  ///Get the ParametersGroupAssign as a read-and-write pointer
  boost::shared_ptr<ParametersGroupAssign> GetGroupAssign() { return m_group_assign; }
  ///Get the ParametersGroupAssign as a read-only pointer
  boost::shared_ptr<const ParametersGroupAssign> GetGroupAssign() const { return m_group_assign; }
  ///Get the ParametersGroupReAssign as a read-and-write pointer
  boost::shared_ptr<ParametersGroupReAssign> GetGroupReAssign() { return m_group_reassign; }
  ///Get the ParametersGroupReAssign as a read-only pointer
  boost::shared_ptr<const ParametersGroupReAssign> GetGroupReAssign() const { return m_group_reassign; }
  ///Get the ParametersQuiz as a read-and-write pointer
  boost::shared_ptr<ParametersQuiz> GetQuiz() { return m_quiz; }
  ///Get the ParametersQuiz as a read-only pointer
  boost::shared_ptr<const ParametersQuiz> GetQuiz() const { return m_quiz; }
  ///Get the ParametersViewResultsAll as a read-and-write pointer
  //ParametersViewResultsAll * GetViewResultsAll();
  ///Get the ParametersViewResultsAll as a read-only pointer
  //const ParametersViewResultsAll * GetViewResultsAll() const;
  ///Get the ParametersViewResultsGroup as a read-and-write pointer
  boost::shared_ptr<ParametersViewResultsGroup> GetViewResultsGroup() { return m_view_results_group; }
  ///Get the ParametersViewResultsGroup as a read-only pointer
  boost::shared_ptr<const ParametersViewResultsGroup> GetViewResultsGroup() const { return m_view_results_group; }
  ///Get the ParametersViewResultsVoting as a read-and-write pointer
  boost::shared_ptr<ParametersViewResultsVoting> GetViewResultsVoting() { return m_view_results_voting; }
  ///Get the ParametersViewResultsVoting as a read-only pointer
  boost::shared_ptr<const ParametersViewResultsVoting> GetViewResultsVoting() const { return m_view_results_voting; }
  ///Get the ParametersVoting as a read-and-write pointer
  boost::shared_ptr<ParametersVoting> GetVoting() { return m_voting; }
  ///Get the ParametersVoting as a read-only pointer
  boost::shared_ptr<const ParametersVoting> GetVoting() const { return m_voting; }

  ///Get the Participants as a read-only reference
  const std::vector<boost::shared_ptr<Participant> >& GetParticipants() const { return m_participants; }
  ///Get the Participants as a reference
  std::vector<boost::shared_ptr<Participant> >& GetParticipants() { return m_participants; }

  ///Add Participants to Parameters
  void AddParticipant(boost::shared_ptr<Participant> participant);

  private:
  ~Parameters() {}
  friend void boost::checked_delete<>(Parameters*);

  ///The ParametersAssignPayoff
  boost::shared_ptr<ParametersAssignPayoff> m_assign_payoff;

  ///The ParametersChat
  boost::shared_ptr<ParametersChat> m_chat;

  ///The ParametersChooseAction
  boost::shared_ptr<ParametersChooseAction> m_choose_action;

  ///The ParametersFinished
  boost::shared_ptr<ParametersFinished> m_finished;

  ///The ParametersGroupAssign
  boost::shared_ptr<ParametersGroupAssign> m_group_assign;

  ///The ParametersGroupReAssign
  boost::shared_ptr<ParametersGroupReAssign> m_group_reassign;

  ///Unassigned Participant colection
  std::vector<boost::shared_ptr<Participant> > m_participants;

  ///The ParametersQuiz
  boost::shared_ptr<ParametersQuiz> m_quiz;

  Server * const m_server;

  ///The ParametersViewResultsGroup
  boost::shared_ptr<ParametersViewResultsGroup> m_view_results_group;

  ///The ParametersViewResultsVoting
  boost::shared_ptr<ParametersViewResultsVoting> m_view_results_voting;

  ///The ParametersVoting
  boost::shared_ptr<ParametersVoting> m_voting;

  ///Parse a line in a Parameter file
  void Parse(const std::string& s);

  ///Split a std::string
  ///From http://www.richelbilderbeek.nl/CppSeperateString.htm
  static const std::vector<std::string> SeperateString(
    const std::string& input,const char seperator);
};

std::ostream& operator<<(std::ostream& os,const Parameters& parameters);

} //~namespace gtst
} //~namespace ribi

#endif // PARAMETERS_H
