
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

#ifndef PROJECTGTSTFORWARD_DECLARATIONS_H
#define PROJECTGTSTFORWARD_DECLARATIONS_H

///\brief
///Forward decalarations, for faster compiling
///
///Reference: Herb Sutter. Exceptional C++. ISBN: 0-201-61562-2.
///Item 26: 'Never #include a header when a forward declaration will suffice'

namespace Wt
{
  struct WAnchor;
  struct WApplication;
  struct WButtonGroup;
  struct WFileUpload;
  struct WLabel;
  struct WLineEdit;
  struct WText;
  struct WTextArea;
}

namespace ribi {
namespace gtst {

struct Administrator;
struct AdministratorDialog;
struct AdministratorDialogState;
struct AdministratorDialogStateLoggedIn;
struct AdministratorDialogStateNotLoggedIn;
struct Administrators;
struct ChatMessage;
struct ChooseActionOption;
struct Group;
struct GroupAssigner;
struct GroupFinished;
struct GroupLoggedIn;
struct GroupNotLoggedIn;
struct GroupParticipating;
struct Groups;
struct LogFile;
struct MenuDialog;
struct Parameters;
struct ParametersAssignPayoff;
struct ParametersChat;
struct ParametersChooseAction;
struct ParametersFinished;
struct ParametersGroupAssign;
struct ParametersGroupReAssign;
struct ParametersQuiz;
struct ParametersViewResultsGroup;
struct ParametersViewResultsVoting;
struct ParametersVoting;
struct Participant;
struct ParticipantDialog;
struct ParticipantDialogState;
struct ParticipantDialogStateAssignPayoff;
struct ParticipantDialogStateChat;
struct ParticipantDialogStateChooseAction;
struct ParticipantDialogStateFinished;
struct ParticipantDialogStateGroupAssign;
struct ParticipantDialogStateGroupReAssign;
struct ParticipantDialogStateLoggedIn;
struct ParticipantDialogStateNotLoggedIn;
struct ParticipantDialogStateQuiz;
struct ParticipantDialogStates;
struct ParticipantDialogStateViewResultsGroup;
struct ParticipantDialogStateViewResultsVoting;
struct ParticipantDialogStateVoting;
struct ParticipantState;
struct ParticipantState;
struct ParticipantStateAssignPayoff;
struct ParticipantStateChat;
struct ParticipantStateChooseAction;
struct ParticipantStateFinished;
struct ParticipantStateGroupAssign;
struct ParticipantStateGroupReAssign;
struct ParticipantStateLoggedIn;
struct ParticipantStateNotLoggedIn;
struct ParticipantStateQuiz;
struct ParticipantStateViewResultsGroup;
struct ParticipantStateViewResultsVoting;
struct ParticipantStateVoting;
struct Payoff;
struct Payoffs;
struct RepeatAssigner;
struct RepeatAssignerFixed;
struct RepeatAssignerRandomUniform;
struct Server;
struct ServerState;
struct ServerStateAssignPayoff;
struct ServerStateChat;
struct ServerStateChooseAction;
struct ServerStateFinished;
struct ServerStateGroupAssign;
struct ServerStateGroupReAssign;
struct ServerStateQuiz;
struct ServerStates;
struct ServerStateViewResultsGroup;
struct ServerStateViewResultsVoting;
struct ServerStateVoting;
struct ServerStateWaiting;
struct State;
struct Vote;
struct VotingOption;

} //~namespace gtst

struct Counter;
struct SafeIpAddress;
struct Shape;
struct ShapeWidget;
struct Stopwatch;
struct WtAboutDialog;
struct WtMultipleChoiceQuestionDialog;
struct WtSelectFileDialog;
struct WtShapeGroupWidget;
struct WtShapeWidget;
struct WtLedWidget;

} //~namespace ribi

#endif // FORWARD_DECLARATIONS_H
