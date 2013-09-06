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
#ifndef PROJECTGTSTPARAMETERSVOTING_H
#define PROJECTGTSTPARAMETERSVOTING_H
//---------------------------------------------------------------------------
#include <iosfwd>
#include <string>
#include <vector>
//---------------------------------------------------------------------------
#include <boost/checked_delete.hpp>
#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>
//---------------------------------------------------------------------------
#include "forward_declarations.h"
//---------------------------------------------------------------------------

namespace ribi {
namespace gtst {

///\brief
///Parameters for the voting state
struct ParametersVoting
{
  ParametersVoting();

  /////Find a VotingOption from its description
  //const VotingOption * FindVotingOption(const std::string& description) const;

  ///Get the duration of the ServerState (in seconds)
  int GetDuration() const;

  ///GetNumberOfOptions returns the number of options to vote for
  //int GetNumberOfOptions() const;

  ///Get all options to vote for
  const std::vector<boost::shared_ptr<VotingOption> >& GetOptions() const { return m_options; }

  ///Get the descriptions of the options to vote for only
  const std::vector<std::string> GetVoteDescriptions() const;

  ///Does the ServerState and ParticipantDialog wait for all?
  bool GetWait() const { return m_wait; }

  ///Parse a line
  void Parse(const std::string& s);

  ///Set the duration of the ServerState (in seconds)
  void SetDuration(const int time);

  ///Set the descriptions of the voting options
  void SetOptions(const std::vector<boost::shared_ptr<VotingOption> >& options);

  ///Set if there is waited for all before going on
  void SetWait(const bool wait);

  private:
  ///Only allow a Boost smart pointer to delete ParametersVoting
  //to prevent the following trouble,
  //cited from http://www.boost.org/libs/utility/checked_delete.html:
  //The C++ Standard allows, in 5.3.5/5, pointers to incomplete
  //class types to be deleted with a delete-expression.
  //When the class has a non-trivial destructor, or a class-specific operator
  //delete, the behavior is undefined. Some compilers issue a warning when an
  //incomplete type is deleted, but unfortunately, not all do, and programmers
  //sometimes ignore or disable warnings.
  ~ParametersVoting() {}
  ///Only let smart pointers delete ParametersVoting
  //Template syntax from Herb Sutter. Exceptional C++ style. 2005. ISBN: 0-201-76042-8. Item 8: 'Befriending templates'.
  friend void boost::checked_delete<>(ParametersVoting*);

  ///Time that is allowed in this phase, or that is indicated to be enough
  int m_duration;

  ///The descriptions of the voting options
  std::vector<boost::shared_ptr<VotingOption> > m_options;

  ///Wait for all before going on?
  ///-true: After voting, Participant has to wait until all have
  ///-false: after m_time seconds, an automatic random vote is made for the Participant
  bool m_wait;

  static const std::vector<boost::shared_ptr<VotingOption> > CreateDefaultOptions();

  ///SeperateString splits a std::string
  const std::vector<std::string> SeperateString(
    const std::string& input,
    const char seperator);

};
//---------------------------------------------------------------------------
std::ostream& operator<<(std::ostream& os,const ParametersVoting& parameters);

} //~namespace gtst
} //~namespace ribi

#endif // PARAMETERSVOTING_H
