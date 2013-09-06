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
#ifndef PROJECTGTSTPARAMETERSCHOOSEACTION_H
#define PROJECTGTSTPARAMETERSCHOOSEACTION_H
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
///Parameters in the choose-action state (in the smaller/IPGG cycle)
struct ParametersChooseAction
{
  ParametersChooseAction();

  ///Get the descriptions of the actions that can be chosen
  const std::vector<boost::shared_ptr<ChooseActionOption> >& GetOptions() const { return m_options; }

  ///Get the duration of the ServerState (in seconds)
  int GetDuration() const;

  ///Does the ServerState and ParticipantDialog wait for all?
  bool GetWait() const { return m_wait; }

  ///Parse a line
  void Parse(const std::string& s);

  ///Set the options of the actions to be chosen by the Participant
  void SetOptions(const std::vector<boost::shared_ptr<ChooseActionOption> >& options);

  ///Set the duration of the ServerState (in seconds)
  void SetDuration(const int time);

  ///Set if the ServerState and ParticipantDialog wait for all other
  void SetWait(const bool wait) { m_wait = wait; }

  private:
  ///Only allow a Boost smart pointer to delete ParametersChooseAction
  //to prevent the following trouble,
  //cited from http://www.boost.org/libs/utility/checked_delete.html:
  //The C++ Standard allows, in 5.3.5/5, pointers to incomplete
  //class types to be deleted with a delete-expression.
  //When the class has a non-trivial destructor, or a class-specific operator
  //delete, the behavior is undefined. Some compilers issue a warning when an
  //incomplete type is deleted, but unfortunately, not all do, and programmers
  //sometimes ignore or disable warnings.
  ~ParametersChooseAction() {}
  ///Only let smart pointers delete ParametersChooseAction
  //Template syntax from Herb Sutter. Exceptional C++ style. 2005. ISBN: 0-201-76042-8. Item 8: 'Befriending templates'.
  friend void boost::checked_delete<>(ParametersChooseAction*);

  ///The options to choose from
  std::vector<boost::shared_ptr<ChooseActionOption> > m_options;

  ///Time that is allowed in this phase, where zero
  ///denotes to wait for all participants
  int m_duration;

  ///Wait for all before going on?
  ///-true: After voting, Participant has to wait until all have choosen an action
  ///-false: after m_time seconds, an automatic random action is chosen for the Participant
  bool m_wait;

  ///Seperates a std::string
  static const std::vector<std::string> SeperateString(
    const std::string& input,
    const char seperator);
};
//---------------------------------------------------------------------------
std::ostream& operator<<(std::ostream& os,const ParametersChooseAction& parameters);

} //~namespace gtst
} //~namespace ribi

#endif // PARAMETERSCHOOSEACTION_H
