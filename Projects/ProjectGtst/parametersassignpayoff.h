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
#ifndef PROJECTGTSTPARAMETERSASSIGNPAYOFF_H
#define PROJECTGTSTPARAMETERSASSIGNPAYOFF_H
//---------------------------------------------------------------------------
#include <iosfwd>
#include <string>
//---------------------------------------------------------------------------
#include <boost/checked_delete.hpp>

//---------------------------------------------------------------------------
#include "forward_declarations.h"
//---------------------------------------------------------------------------

namespace ribi {
namespace gtst {

///\brief
///Parameters in the assign-payoff state (in the smaller/IPGG cycle)
struct ParametersAssignPayoff
{
  ParametersAssignPayoff();

  ///Get the message displayed in the ParticipantDialogStateAssignPayoff
  const std::string& GetMessage() const { return m_message; }

  ///Parse a line
  void Parse(const std::string& s);

  ///Set the message displayed in the ParticipantDialogStateAssignPayoff
  void SetMessage(const std::string& message);

  private:
  ~ParametersAssignPayoff() {}
  friend void boost::checked_delete<>(ParametersAssignPayoff*);

  ///The message displayed in the ParticipantDialogStateAssignPayoff
  std::string m_message;
};
//---------------------------------------------------------------------------
std::ostream& operator<<(std::ostream& os,const ParametersAssignPayoff& parameters);

} //~namespace gtst
} //~namespace ribi

#endif // PARAMETERSASSIGNPAYOFF_H
