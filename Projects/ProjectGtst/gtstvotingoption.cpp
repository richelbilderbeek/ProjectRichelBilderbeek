//---------------------------------------------------------------------------
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
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/ProjectGtst.htm
//---------------------------------------------------------------------------
#include <cassert>
#include <iostream>

#include "gtstvotingoption.h"

ribi::gtst::VotingOption::VotingOption(
  const double chance,
  const double cost,
  const std::string& description)
  : m_chance{},
    m_cost{},
    m_description{}
{
  SetChance(chance);
  SetCost(cost);
  SetDescription(description);
}

///Get the chance of getting caught by a supervisor when not contributing
double ribi::gtst::VotingOption::GetChance() const
{
  return m_chance;
}

///Get the cost of this supervisor/option
double ribi::gtst::VotingOption::GetCost() const
{
  return m_cost;
}

///Get the description of this voting option
const std::string& ribi::gtst::VotingOption::GetDescription() const
{
  return m_description;
}

///Set the chance of getting caught by a supervisor when not contributing
void ribi::gtst::VotingOption::SetChance(const double p)
{
  assert(p>=0.0 && "A chance must be zero at least");
  assert(p<=1.0 && "A chance must be one (that is: 100%) at most");
  m_chance = p;
}

///Set the cost of this supervisor/option
void ribi::gtst::VotingOption::SetCost(const double cost)
{
  assert(cost >= 0.0 && "Costs typically are positive values");
  m_cost = cost;
}

///Set the description of this voting option
void ribi::gtst::VotingOption::SetDescription(const std::string& description)
{
  assert(!description.empty() && "A description must contain text");
  m_description = description;
}

std::ostream& ribi::gtst::operator<<(std::ostream& os,const VotingOption& v)
{
  os
    << "<chance>"
    << v.GetChance()
    << "</chance>"
    << "<cost>"
    << v.GetCost()
    << "</cost>"
    << "<description>"
    << v.GetDescription()
    << "</description>";
  return os;
}





