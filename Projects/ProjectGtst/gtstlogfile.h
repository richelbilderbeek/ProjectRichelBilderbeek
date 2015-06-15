
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

#ifndef PROJECTGTSTLOGFILE_H
#define PROJECTGTSTLOGFILE_H

#include <ctime>
#include <iosfwd>
#include <string>
#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/shared_ptr.hpp>

#include "gtstforward_declarations.h"
#pragma GCC diagnostic pop

namespace ribi {
namespace gtst {

///\brief
///LogFile is the log file.
///
///A crashed session should be able to be restored it.
struct LogFile
{
  LogFile();
  LogFile(const LogFile&) = delete;
  LogFile& operator=(const LogFile&) = delete;

  //Clear the LogFile NEVER DO SO!
  //static void ClearLogFile();

  ///Log a Participant his/her last action
  void LogAction(const boost::shared_ptr<const Participant>& participant);

  ///Log a Participant being assigned to a group
  void LogAssignGroup(
    const Group * const group,
    const boost::shared_ptr<const Participant>& participant);

  ///Log a Participant having assigned his/her Payoff
  void LogAssignPayoff(const boost::shared_ptr<const Participant>& participant);

  ///Log a ChatMessage from a Participant
  void LogChatMessage(
    const boost::shared_ptr<const Participant>& participant,
    const boost::shared_ptr<ChatMessage>& message);

  ///Log that the experiment its state/phase has been changed
  void LogExperimentStateChanged(const ServerState* const new_state);

  ///Log that a Participant has logged in
  void Login(const boost::shared_ptr<const Participant>& participant);

  ///Log a Participant has logged out (although he/she will remain in memory)
  void Logout(const boost::shared_ptr<const Participant>& participant);

  ///Log the parameters
  void LogParameters(boost::shared_ptr<Parameters> parameters);

  ///Log that a ParticipantDialog has its ParticipantDialogState changed
  void LogParticipantDialogStateChanged(const ParticipantDialogState* const new_state);

  ///Log a Participant having survived a period
  void LogReAssignPayoff(const boost::shared_ptr<const Participant>& participant);

  ///Log a Participant being removed from a group
  void LogRemoveParticipant(
    const Group * const group,
    const boost::shared_ptr<const Participant>& participant);

  ///Log a Participant his/her vote
  void LogVote(const boost::shared_ptr<const Participant>& participant);

  ///The filename of the log file where all logged operations are written to
  const std::string m_log_filename;

  private:
  ~LogFile();
  friend void boost::checked_delete<>(LogFile*);

  ///Befriend operator<<
  friend std::ostream& operator<<(std::ostream& os,const LogFile& logfile);

  ///Returns date in YYYY-MM-DD format
  //From http://www.richelbilderbeek.nl/CppGetDateIso8601.htm
  static std::string GetDateIso8601();

  ///Get the current time
  //From http://www.richelbilderbeek.nl/CppGetTime.htm
  static std::string GetTime();

  ///Returns the current date and time as a YYYY_MM_DD_HH_MM_SS std::string,
  ///for example '2011_07_01_11_35_38'
  //From http://www.richelbilderbeek.nl/CppGetTimestamp.htm
  static std::string GetTimestamp();
};

std::ostream& operator<<(std::ostream& os,const LogFile& logfile);

} //~namespace gtst
} //~namespace ribi

#endif // LOGFILE_H
