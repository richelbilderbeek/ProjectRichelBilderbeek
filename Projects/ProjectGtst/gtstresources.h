
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

#ifndef PROJECTGTSTRESOURCES_H
#define PROJECTGTSTRESOURCES_H

#include <string>
#include <vector>

#include <boost/checked_delete.hpp>



namespace ribi {
namespace gtst {

///Resources ensures all resources will be present
struct Resources
{
  ///Create the Resources
  Resources();
  Resources(const Resources&) = delete;
  Resources& operator=(const Resources&) = delete;

  ///Get the filename of the background image
  static std::string GetImageFilenameBackground() { return "Background.png"; }

  ///Get the filename of the experiment cycle image
  static std::string GetImageFilenameCycle() { return "Cycle_100.png"; }

  ///Get the filename of the participant dialog 'Assign Payoff' and the parameter file possibilities
  static std::string GetImageFilenameParticipantDialogAssignPayoff() { return "ProjectGtstParticipantDialogAssignPayoffParameters.png"; }

  ///Get the filename of the participant dialog 'Chat' and the parameter file possibilities
  static std::string GetImageFilenameParticipantDialogChat() { return "ProjectGtstParticipantDialogChatParameters.png"; }

  ///Get the filename of the participant dialog 'Choose Action' and the parameter file possibilities
  static std::string GetImageFilenameParticipantDialogChooseAction() { return "ProjectGtstParticipantDialogChooseActionParameters.png"; }

  ///Get the filename of the participant dialog 'Finished' and the parameter file possibilities
  static std::string GetImageFilenameParticipantDialogFinished() { return "ProjectGtstParticipantDialogFinishedParameters.png"; }

  ///Get the filename of the participant dialog 'Group Assign' and the parameter file possibilities
  static std::string GetImageFilenameParticipantDialogGroupAssign() { return "ProjectGtstParticipantDialogGroupAssign2Parameters.png"; }

  ///Get the filename of the participant dialog 'Group Re-assign' and the parameter file possibilities
  static std::string GetImageFilenameParticipantDialogGroupReAssign() { return "ProjectGtstParticipantDialogGroupReAssignParameters.png"; }

  ///Get the filename of the participant dialog 'Logged-in' and the parameter file possibilities
  static std::string GetImageFilenameParticipantDialogLoggedIn() { return "ProjectGtstParticipantDialogLoggedInParameters.png"; }

  ///Get the filename of the participant dialog 'Not logged-in' and the parameter file possibilities
  static std::string GetImageFilenameParticipantDialogNotLoggedIn() { return "ProjectGtstParticipantDialogNotLoggedInParameters.png"; }

  ///Get the filename of the participant dialog 'View results group' and the parameter file possibilities
  static std::string GetImageFilenameParticipantDialogViewResultsGroup() { return "ProjectGtstParticipantDialogViewResultsGroupParameters.png"; }

  ///Get the filename of the participant dialog 'View results voting' and the parameter file possibilities
  static std::string GetImageFilenameParticipantDialogViewResultsVoting() { return "ProjectGtstParticipantDialogViewResultsVotingParameters.png"; }

  ///Get the filename of the participant dialog 'Voting' and the parameter file possibilities
  static std::string GetImageFilenameParticipantDialogVoting() { return "ProjectGtstParticipantDialogVotingParameters.png"; }

  ///Get the filename of the total experiment flow
  static std::string GetImageFilenameExperiment() { return "Experiment_100.png"; }

  ///Get the filename of the groups image
  static std::string GetImageFilenameGroups() { return "Groups.png"; }

  ///Get the filename of the experiment period image
  static std::string GetImageFilenamePeriod() { return "Period_100_58.png"; }

  private:
  ///Create the CSS for this application
  const std::vector<std::string> CreateStylesheet() const;

  ///Save the stylesheet for this application to file
  void SaveStylesheet() const;

  private:
  ~Resources() {}
  friend void boost::checked_delete<>(Resources*);

};

} //~namespace gtst
} //~namespace ribi

#endif // RESOURCES_H
