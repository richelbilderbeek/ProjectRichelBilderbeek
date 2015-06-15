
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

#ifndef PROJECTGTSTCHOOSEACTIONOPTION_H
#define PROJECTGTSTCHOOSEACTIONOPTION_H

#include <iosfwd>
#include <string>
#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/checked_delete.hpp>
//#include <boost/scoped_ptr.hpp>

#include "gtstforward_declarations.h"
#pragma GCC diagnostic pop

namespace ribi {
namespace gtst {

///\brief
///An option of an action that can be chosen for
///
///A ChooseActionOption has a description and if this description denotes
///a contribution or not
struct ChooseActionOption
{
  ///A ChooseActionOption has a description and a chance of getting caught
  ///by a supervisor.
  ChooseActionOption(
    const double contribution,
    const double cost,
    const std::string& description,
    const std::string& message);
  ChooseActionOption(const ChooseActionOption&) = delete;
  ChooseActionOption& operator=(const ChooseActionOption&) = delete;

  ///Get the Participant his/her contribution to the group by this option
  double GetContribution() const;

  ///Get the cost the individual makes by this action
  double GetCost() const;

  ///\brief
  ///Get the description of this choose action option
  ///
  ///For example: Do not contribute, Contribute
  const std::string& GetDescription() const;

  ///\brief
  ///Get the message given from this choice
  ///
  ///Examples:
  ///- You have chosen to contribute in this round
  ///- You have chosen not to contribute in this round
  const std::string& GetMessageChoice() const;

  ///Set the Participant his/her contribution to the group by this option
  void SetContribution(const double contribution);

  ///Set the cost the individual makes by this action
  void SetCost(const double cost);

  ///Set the description of this choose action option
  void SetDescription(const std::string& description);

  ///\brief
  ///Set the message given from this choice
  ///
  ///Examples:
  ///- You have chosen to contribute in this round
  ///- You have chosen not to contribute in this round
  void SetMessageChoice(const std::string& message);

  private:
  ~ChooseActionOption() {}
  friend void boost::checked_delete<>(ChooseActionOption*);

  ///The Participant his/her contribution to the group by this option
  double m_contribution;

  ///The individual cost the Participant makes by this option
  double m_cost;

  ///\brief
  ///The description of this option
  ///
  ///For example: Do not contribute, Contribute
  std::string m_description;

  ///\brief
  ///The message given from this choice
  ///
  ///Examples:
  ///- You have chosen to contribute in this round
  ///- You have chosen not to contribute in this round
  std::string m_message_choice;
};

std::ostream& operator<<(std::ostream& os,const ChooseActionOption& v);

} //~namespace gtst
} //~namespace ribi

#endif // CHOOSEACTIONOPTION_H
