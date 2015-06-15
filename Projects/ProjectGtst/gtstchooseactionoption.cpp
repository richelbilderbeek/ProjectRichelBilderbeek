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

#include "gtstchooseactionoption.h"

ribi::gtst::ChooseActionOption::ChooseActionOption(
  const double contribution,
  const double cost,
  const std::string& description,
  const std::string& message)
  : m_contribution{},
    m_cost{},
    m_description{},
    m_message_choice{}
{
  SetContribution(contribution);
  SetCost(cost);
  SetDescription(description);
  SetMessageChoice(message);
}

///Get the chance of getting caught by a supervisor when not contributing
double ribi::gtst::ChooseActionOption::GetContribution() const
{
  return m_contribution;
}

///Get the cost of this supervisor/option
double ribi::gtst::ChooseActionOption::GetCost() const
{
  return m_cost;
}

const std::string& ribi::gtst::ChooseActionOption::GetDescription() const
{
  return m_description;
}

const std::string& ribi::gtst::ChooseActionOption::GetMessageChoice() const
{
  return m_message_choice;
}

void ribi::gtst::ChooseActionOption::SetContribution(const double contribution)
{
  m_contribution = contribution;
}

///Set the cost of this supervisor/option
void ribi::gtst::ChooseActionOption::SetCost(const double cost)
{
  assert(cost >= 0.0 && "Costs typically are positive values");
  m_cost = cost;
}

void ribi::gtst::ChooseActionOption::SetDescription(const std::string& description)
{
  assert(!description.empty() && "A description must contain text");
  m_description = description;
}

void ribi::gtst::ChooseActionOption::SetMessageChoice(const std::string& message_choice)
{
  m_message_choice = message_choice;
}

std::ostream& ribi::gtst::operator<<(std::ostream& os,const ChooseActionOption& v)
{
  os
    << "<contribution>"
    << v.GetContribution()
    << "</contribution>"
    << "<cost>"
    << v.GetCost()
    << "</cost>"
    << "<description>"
    << v.GetDescription()
    << "</description>";
  return os;
}





