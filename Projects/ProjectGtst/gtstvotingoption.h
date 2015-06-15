
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

#ifndef PROJECTGTSTVOTINGOPTION_H
#define PROJECTGTSTVOTINGOPTION_H

#include <iosfwd>
#include <string>
#include <vector>

#include <boost/checked_delete.hpp>
//#include <boost/scoped_ptr.hpp>

#include "gtstforward_declarations.h"


namespace ribi {
namespace gtst {

///\brief
///An option that can be voted for
///
///A VotingOption has a description and a chance of getting caught
///by a supervisor.
struct VotingOption
{
  ///A VotingOption has a description and a chance of getting caught
  ///by a supervisor.
  VotingOption(
    const double chance,
    const double cost,
    const std::string& description);
  VotingOption(const VotingOption&) = delete;
  VotingOption& operator=(const VotingOption&) = delete;

  ///Get the chance of getting caught by a supervisor when not contributing
  double GetChance() const;

  ///Get the cost of this supervisor/option
  double GetCost() const;

  ///Get the description of this voting option
  const std::string& GetDescription() const;

  ///Set the chance of getting caught by a supervisor when not contributing
  void SetChance(const double chance);

  ///Set the cost of this supervisor/option
  void SetCost(const double cost);

  ///Set the description of this voting option
  void SetDescription(const std::string& description);

  private:
  ~VotingOption() {}
  friend void boost::checked_delete<>(VotingOption*);

  ///The chance of getting caught by a supervisor when not contributing
  double m_chance;

  ///The cost of this supervisor/option
  double m_cost;

  ///The description of this voting option
  std::string m_description;

};

std::ostream& operator<<(std::ostream& os,const VotingOption& v);

} //~namespace gtst
} //~namespace ribi

#endif // VOTINGOPTION_H
