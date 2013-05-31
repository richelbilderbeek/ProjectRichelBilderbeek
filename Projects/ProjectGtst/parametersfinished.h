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
#ifndef PROJECTGTSTPARAMETERSFINISHED_H
#define PROJECTGTSTPARAMETERSFINISHED_H
//---------------------------------------------------------------------------
#include <iosfwd>
#include <string>
//---------------------------------------------------------------------------
#include <boost/checked_delete.hpp>
#include <boost/noncopyable.hpp>
//---------------------------------------------------------------------------
#include "forward_declarations.h"
//---------------------------------------------------------------------------
///\brief
///Parameters for the finished state
struct ParametersFinished
{
  ParametersFinished();

  ///Calculate the earnings of a Participant for participating,
  ///from the amount of payoff he/she has gathered
  double CalculateEarnings(const double payoff) const;

  ///Get the function that is used to calculate the earnings of
  ///a Participant for participating, from the amount of payoff
  ///he/she has gathered
  const std::string& GetEarningsFunction() const { return m_earnings_function; }

  ///Get the message shown to the Participant when the experiment has finished
  const std::string& GetMessage() const { return m_message; }

  ///Parse a line
  void Parse(const std::string& s);

  ///Set the function that is used to calculate the earnings of
  ///a Participant for participating, from the amount of payoff
  ///he/she has gathered
  void SetEarningsFunction(const std::string& earnings_function);

  ///Set the message shown to the Participant when the experiment has finished
  void SetMessage(const std::string& message);

  private:
  ///Only allow a Boost smart pointer to delete ParametersFinished
  //to prevent the following trouble,
  //cited from http://www.boost.org/libs/utility/checked_delete.html:
  //The C++ Standard allows, in 5.3.5/5, pointers to incomplete
  //class types to be deleted with a delete-expression.
  //When the class has a non-trivial destructor, or a class-specific operator
  //delete, the behavior is undefined. Some compilers issue a warning when an
  //incomplete type is deleted, but unfortunately, not all do, and programmers
  //sometimes ignore or disable warnings.
  ~ParametersFinished() {}
  ///Only let smart pointers delete ParametersFinished
  //Template syntax from Herb Sutter. Exceptional C++ style. 2005. ISBN: 0-201-76042-8. Item 8: 'Befriending templates'.
  friend void boost::checked_delete<>(ParametersFinished*);

  ///\brief
  ///The function that is used to calculate the earnings of
  ///a Participant for participating, from the amount of payoff
  ///he/she has gathered
  ///
  ///For example 'sqrt(p)+10'
  std::string m_earnings_function;

  ///\brief
  ///The message a Particapants get when finished
  ///
  ///For example: 'Thanks for participating in this experiment'
  std::string m_message;

};
//---------------------------------------------------------------------------
std::ostream& operator<<(std::ostream& os,const ParametersFinished& parameters);
//---------------------------------------------------------------------------
#endif // PARAMETERSFINISHED_H
