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
#include <algorithm>
#include <cassert>
//#include <iostream>
#include <sstream>
#include <stdexcept>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/numeric/conversion/cast.hpp>

#include "gtstparametersvoting.h"
#include "gtstvotingoption.h"
#pragma GCC diagnostic pop

ribi::gtst::ParametersVoting::ParametersVoting()
  : m_duration(10),
    m_options(CreateDefaultOptions()),
    m_wait(true)
{

}

const std::vector<boost::shared_ptr<ribi::gtst::VotingOption> >
  ribi::gtst::ParametersVoting::CreateDefaultOptions()
{
  std::vector<boost::shared_ptr<VotingOption> > v;
  {
    boost::shared_ptr<VotingOption> p(new VotingOption(0.0,0.0,"No supervisor"));
    v.push_back(p);
  }
  {
    boost::shared_ptr<VotingOption> p(new VotingOption(0.5,1.0,"Lenient supervisor"));
    v.push_back(p);
  }
  {
    boost::shared_ptr<VotingOption> p(new VotingOption(1.0,2.0,"Rigorous supervisor"));
    v.push_back(p);
  }
  return v;
}

int ribi::gtst::ParametersVoting::GetDuration() const
{
  assert(m_duration >= 0);
  return m_duration;
}

///Get the descriptions of the options to vote for only
std::vector<std::string> ribi::gtst::ParametersVoting::GetVoteDescriptions() const
{
  std::vector<std::string> w;

  std::transform(
    m_options.begin(),
    m_options.end(),
    std::back_inserter(w),
    //boost::lambda::bind(&VotingOption::GetDescription, *boost::lambda::_1)
    [](const boost::shared_ptr<VotingOption>& i)
    {
      return i->GetDescription();
    }
    );
  return w;
}

///Parse a line
void ribi::gtst::ParametersVoting::Parse(const std::string& s)
{
  if (s.size() > 9 && s.substr(0,9) == "duration=")
  {
    const std::string t = s.substr(9,s.size()-9);
    try
    {
      std::stoi(t);
      //std::stoi(t);
    }
    catch (std::exception&)
    //catch (std::exception&)
    {
      throw std::runtime_error("voting_duration must be an integer");
    }
    const int time = std::stoi(t);
    //const int time = std::stoi(t);
    if (time < 0) throw std::runtime_error("voting_duration must be zero or posive");
    SetDuration(time);
    return;
  }


  if (s.size() > 5 && s.substr(0,5) == "wait=")
  {
    const std::string t = s.substr(5,s.size()-5);
    if (t=="y" || t=="Y" || t=="1" || t == "n" || t == "N" || t =="0")
    {
      if (t=="y" || t=="Y" || t=="1")
      {
        SetWait(true);
      }
      else
      {
        SetWait(false);
      }
    }
    else
    {
      throw std::runtime_error("vote_wait me be either \'y\' or \'n\'");
    }
    return;
  }

  //Participants
  if (s.size() > 7 && s.substr(0,7) == "option=")
  {
    const std::string t = s.substr(7,s.size() - 7);
    const std::vector<std::string> v = SeperateString(t,',');
    if (v.size() != 3)
    {
      throw std::runtime_error(
        std::string("Incorrectly formed vote_option line: ")
        +  s
        + std::string(": must consist of [description][chance][cost],")
        + std::string("for example \'Lenient supervisor,0.5,1.0\'"));
    }
    assert(v.size() == 3 && "vote_options must have two elements");

    const std::string description = v[0];
    const std::string chance_str = v[1];
    const std::string cost_str = v[2];

    try
    {
      std::stod(chance_str);
      //std::stod(chance_str);
    }
    catch (std::exception&)
    //catch (std::logic_error&)
    {
      throw std::runtime_error(
        std::string("Incorrectly formed chance: ")
        + chance_str);
    }
    try
    {
      std::stod(cost_str);
      //std::stod(cost_str);
    }
    catch (std::exception&)
    //catch (std::logic_error&)
    {
      throw std::runtime_error(
        "Incorrectly formed cost: "
        + cost_str);
    }

    const double chance = std::stod(chance_str);
    //const double chance = std::stod(chance_str);
    const double cost = std::stod(cost_str);
    //const double cost = std::stod(cost_str);
    boost::shared_ptr<VotingOption> p(
      new VotingOption(chance,cost,description));
    m_options.push_back(p);
    return;
  }

}

///SeperateString splits a std::string
//From http://www.richelbilderbeek.nl/CppSeperateString.htm
const std::vector<std::string> ribi::gtst::ParametersVoting::SeperateString(
  const std::string& input,
  const char seperator)
{
  std::istringstream is(input);
  std::vector<std::string> v;
  for (
    std::string sub;
    std::getline(is, sub, seperator);
    v.push_back(sub))
  {
    //Empty for loop
  }
  return v;
}

void ribi::gtst::ParametersVoting::SetDuration(const int time)
{
  m_duration = time;
  assert(m_duration >= 0);
}

void ribi::gtst::ParametersVoting::SetOptions(
  const std::vector<boost::shared_ptr<VotingOption> >& options)
{
  assert(options.size() >= 2
    && "A participant must vote between at least two options");
  m_options = options;
}

///Set if there is waited for all before going on
void ribi::gtst::ParametersVoting::SetWait(const bool wait)
{
  m_wait = wait;
}

std::ostream& ribi::gtst::operator<<(std::ostream& os,const ParametersVoting& parameters)
{
  os
    << "<parametersvoting>"
    << "<time>"
    << parameters.GetDuration()
    << "</time>";
  const int n_actions = boost::numeric_cast<int>(
    parameters.GetOptions().size());
  for (int i=0; i!=n_actions;++i)
  {
    os
      << "<option" << i << ">"
      << (*(parameters.GetOptions()[i]))
      << "</option" << i << ">";
  }
  os
    << "</parametersvoting>";

  return os;
}



