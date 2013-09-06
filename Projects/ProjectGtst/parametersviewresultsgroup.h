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
#ifndef PROJECTGTSTPARAMETERSVIEWRESULTSGROUP_H
#define PROJECTGTSTPARAMETERSVIEWRESULTSGROUP_H
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
///Parameters in the view-results group state (in the smaller/IPGG cycle)
struct ParametersViewResultsGroup : public boost::noncopyable
{
  ///Default-construct a ParametersViewResultsGroup
  ParametersViewResultsGroup();

  ///Get the ParametersViewResultsGroup its RepeatAssigner
  boost::shared_ptr<RepeatAssigner> GetRepeatAssigner() const { return m_repeat_assigner; }

  ///Get the duration of the ServerState (in seconds)
  int GetDuration() const;

  ///Parse a line
  void Parse(const std::string& s);

  ///Set the ParametersViewResultsGroup its RepeatAssigner
  void SetRepeatAssigner(boost::shared_ptr<RepeatAssigner> assigner);

  ///Set the duration of the ServerState (in seconds)
  void SetDuration(const int time);


  private:
  ///Only allow a Boost smart pointer to delete ParametersViewResultsGroup
  //to prevent the following trouble,
  //cited from http://www.boost.org/libs/utility/checked_delete.html:
  //The C++ Standard allows, in 5.3.5/5, pointers to incomplete
  //class types to be deleted with a delete-expression.
  //When the class has a non-trivial destructor, or a class-specific operator
  //delete, the behavior is undefined. Some compilers issue a warning when an
  //incomplete type is deleted, but unfortunately, not all do, and programmers
  //sometimes ignore or disable warnings.
  ~ParametersViewResultsGroup() {}
  ///Only let smart pointers delete ParametersViewResultsGroup
  //Template syntax from Herb Sutter. Exceptional C++ style. 2005. ISBN: 0-201-76042-8. Item 8: 'Befriending templates'.
  friend void boost::checked_delete<>(ParametersViewResultsGroup*);

  ///The assigner of how much repeats this state must have
  boost::shared_ptr<RepeatAssigner> m_repeat_assigner;

  ///Time that is allowed in this phase
  int m_duration;

  ///Parse a line starting with cycles=
  void ParseCycles(const std::string& s);

  ///Seperates a std::string
  static const std::vector<std::string> SeperateString(
    const std::string& input,
    const char seperator);

};
//---------------------------------------------------------------------------
std::ostream& operator<<(std::ostream& os,const ParametersViewResultsGroup& parameters);

} //~namespace gtst
} //~namespace ribi

#endif // PARAMETERSVIEWRESULTSGROUP_H
