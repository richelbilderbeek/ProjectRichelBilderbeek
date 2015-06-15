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
#include <fstream>
#include <iostream>
#include <map>
#include <stdexcept>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/numeric/conversion/cast.hpp>
#include <boost/algorithm/string/trim.hpp>

#include "fileio.h"
#include "gtstall_parameters.h"
#include "gtstchatshapefactory.h"
#include "gtstgroupassigner.h"
#include "ipaddress.h"
#include "gtstparameters.h"
#include "gtstparticipant.h"
#include "shape.h"
#include "shapewidget.h"
//#include "trace.h"
#include "wtshapewidget.h"
#pragma GCC diagnostic pop

ribi::gtst::Parameters::Parameters(Server * const server)
  : m_assign_payoff(new ParametersAssignPayoff),
    m_chat(new ParametersChat),
    m_choose_action(new ParametersChooseAction),
    m_finished(new ParametersFinished),
    m_group_assign(new ParametersGroupAssign),
    m_group_reassign(new ParametersGroupReAssign),
    m_participants{},
    m_quiz(new ParametersQuiz),
    m_server(server),
    m_view_results_group(new ParametersViewResultsGroup),
    m_view_results_voting(new ParametersViewResultsVoting),
    m_voting(new ParametersVoting)
{
  assert(m_server);
  assert(m_participants.empty()
    && "Do not create Participants by default as this will start a default experiment");
}

///Add Participants to Parameters
void ribi::gtst::Parameters::AddParticipant(boost::shared_ptr<Participant> participant)
{
  std::clog << "Added participant " << participant << '\n';
  assert(participant);
  m_participants.push_back(participant);
}

///Create a default non-logged in Partipant
boost::shared_ptr<ribi::gtst::Participant> ribi::gtst::Parameters::CreateDefaultParticipant()
{
  static int already_created = 0;
  //Create chat tag
  boost::shared_ptr<WtShapeWidget> chat_shape(
    new WtShapeWidget(
      ChatShapeFactory::Get()->GetNextWidget()));
  //Create GroupAssigner
  boost::shared_ptr<GroupAssigner> group_assigner(
    new GroupAssignerPredetermined(
      1 + (already_created%2)));
  //Set wild-card IP address
  const std::string ip_address="*";
  //Create the Participant

  boost::shared_ptr<Participant> p(
    new Participant(
      //boost::shared_ptr<WtShapeWidget>(
      //  new WtShapeWidget(
      //    ChatShapeFactory::Get()->GetNextWidget()
      //    )
      //  ),
      group_assigner,m_server));

  assert(p);
  //Check if the Participant is really created from scratch
  assert(!p->CanGetId()
    && "ID must be assigned by Server");

  assert(!p->CanGetIpAddress() && "IP address must be assigned by Server");

  ++already_created;

  return p;
}

///Deletes all Participant instances
void ribi::gtst::Parameters::DeleteParticipants()
{
  this->m_participants.clear();
  assert(m_participants.empty());
}

void ribi::gtst::Parameters::ReadFromFile(const std::string& filename)
{

  if (!fileio::FileIo().IsRegularFile(filename))
  {
    const std::string error
      = std::string("File ")
      + filename
      + std::string(" not found");
    throw std::runtime_error(error);
  }
  assert(fileio::FileIo().IsRegularFile(filename));

  const std::vector<std::string> v = fileio::FileIo().FileToVector(filename);
  std::for_each(v.begin(),v.end(),
    [this](const std::string& s)
    {
      //Trim_copy s to remove Microsoft Windows line endings
      this->Parse(boost::algorithm::trim_copy(s));
    }
  );

  ///Check if at least initial group 1 and 2 are present
  std::map<int,int> tally;
  std::for_each(m_participants.begin(),m_participants.end(),
    [&tally](const boost::shared_ptr<Participant>& p)
  {
      const GroupAssigner * const a = p->GetGroupAssigner();
      assert(a);
      if (dynamic_cast<const GroupAssignerPredetermined*>(a))
      {
        ++tally[dynamic_cast<const GroupAssignerPredetermined*>(a)->GetGroup()];
      }
    }
  );
  if (tally[1]==0)
  {
    throw std::runtime_error("Group #1 must exist and contain either 3 or 5 participants");
  }
  if (tally[1]!=3 && tally[1]!=5)
  {
    throw std::runtime_error("Group #1 must contain either 3 or 5 participants");
  }
  if (tally[2]==0)
  {
    throw std::runtime_error("Group #2 must exist and contain either 3 or 5 participants");
  }
  if (tally[2]!=3 && tally[2]!=5)
  {
    throw std::runtime_error("Group #2 must contain either 3 or 5 participants");
  }
  std::vector<int> ids;
  std::transform(
    tally.begin(),tally.end(),std::back_inserter(ids),
    [](const std::pair<const int,int>& p) { return p.first; } );
    //boost::lambda::bind(&std::pair<const int,int>::first, boost::lambda::_1));
  const int n_ids = boost::numeric_cast<int>(ids.size());
  for (int i=0; i!=n_ids; ++i)
  {
    //At index 0 there must be ID 1
    if (ids[i] != i+1)
    {
      const std::string s
        = std::string("Group #")
        + std::to_string(i+1)
        + std::string(" is missing") ;
      throw std::runtime_error(s.c_str());
    }
  }

  if (m_choose_action->GetOptions().size() < 2)
  {
    throw std::runtime_error("Please specify at least two choose_action_options");
  }
  if (this->m_voting->GetOptions().size() < 2)
  {
    throw std::runtime_error("Please specify at least two voting_options");
  }
}

///Parse a line in a Parameter file.
void ribi::gtst::Parameters::Parse(const std::string& s)
{
  if (s.empty()) return;
  if (s.size() > 0 && s.substr(0,1) == "#") return;
  if (s.size() > 1 && s.substr(0,2) == "//") return;

  ///Parameters starting with finished_ are parsed by ParametersFinished
  if (s.size() > 9 && s.substr(0,9) == "finished_")
  {
    const std::string t = s.substr(9,s.size()-9);
    this->GetFinished()->Parse(t);
    return;
  }

  ///Parameters starting with finished_ are parsed by ParametersGroupReAssign
  if (s.size() > 13 && s.substr(0,13) == "group_assign_")
  {
    const std::string t = s.substr(13,s.size()-13);
    this->GetGroupAssign()->Parse(t);
    return;
  }

  ///Parameters starting with finished_ are parsed by ParametersGroupReAssign
  if (s.size() > 15 && s.substr(0,15) == "group_reassign_")
  {
    const std::string t = s.substr(15,s.size()-15);
    this->GetGroupReAssign()->Parse(t);
    return;
  }

  ///Parameters starting with finished_ are parsed by ParametersGroupReAssign
  if (s.size() > 14 && s.substr(0,14) == "assign_payoff_")
  {
    const std::string t = s.substr(14,s.size()-14);
    this->GetAssignPayoff()->Parse(t);
    return;
  }

  ///Parameters starting with finished_ are parsed by ParametersViewResultsGroup
  if (s.size() > 20 && s.substr(0,20) == "view_results_voting_")
  {
    const std::string t = s.substr(20,s.size()-20);
    this->GetViewResultsVoting()->Parse(t);
    return;
  }

  ///Parameters starting with finished_ are parsed by ParametersViewResultsGroup
  if (s.size() > 19 && s.substr(0,19) == "view_results_group_")
  {
    const std::string t = s.substr(19,s.size()-19);
    this->GetViewResultsGroup()->Parse(t);
    return;
  }

  ///Parameters starting with finished_ are parsed by ParametersViewResultsGroup
  if (s.size() > 14 && s.substr(0,14) == "assign_payoff_")
  {
    const std::string t = s.substr(14,s.size()-14);
    this->GetAssignPayoff()->Parse(t);
    return;
  }

  if (s.size() > 14 && s.substr(0,14) == "choose_action_")
  {
    const std::string t = s.substr(14,s.size()-14);
    this->GetChooseAction()->Parse(t);
    return;
  }

  if (s.size() > 5 && s.substr(0,5) == "chat_")
  {
    const std::string t = s.substr(5,s.size()-5);
    this->GetChat()->Parse(t);
    return;
  }

  if (s.size() > 7 && s.substr(0,7) == "voting_")
  {
    const std::string t = s.substr(7,s.size()-7);
    this->GetVoting()->Parse(t);
    return;
  }

  //Participants
  if (s.size() > 12 && s.substr(0,12) == "participant=")
  {
    const std::string t = s.substr(12,s.size() - 12);
    const std::vector<std::string> v = SeperateString(t,',');
    if (v.size() != 2)
    {
      throw std::runtime_error((std::string("Incorrectly formed participant line: ") + s).c_str());;
    }
    assert(v.size() == 2 && "Participant must have two elements");

    boost::shared_ptr<GroupAssigner> group_assigner
      = GroupAssigner::CreateAssigner(v[0]);

    const std::string ip_address_str = v[1];


    boost::shared_ptr<Participant> participant(
     new Participant(group_assigner,m_server)
      );
    if (ip_address_str!="*")
    {
      try
      {
        boost::shared_ptr<SafeIpAddress> ip_address(new SafeIpAddress(ip_address_str));
        participant->SetIpAddress(ip_address);
      }
      catch (std::logic_error&)
      {
        throw std::runtime_error((std::string("Incorrectly formed IP address: ") + ip_address_str).c_str());
      }
    }

    m_participants.push_back(participant);
    return;
  }
  throw std::runtime_error((std::string("Unparsable parameter file line: ") + s).c_str());
}

//From http://www.richelbilderbeek.nl/CppSeperateString.htm
const std::vector<std::string> ribi::gtst::Parameters::SeperateString(
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

std::ostream& ribi::gtst::operator<<(std::ostream& os,const Parameters& parameters)
{
  os
    << "<parameters>"
    << "<participants>";
  {
    const std::vector<boost::shared_ptr<Participant> >& participants
      = parameters.GetParticipants();
    std::for_each(participants.begin(),participants.end(),
      [&os](const boost::shared_ptr<Participant>& p) { os << (*p); }
    );
  }
  os
    << "</participants>"
    << (*parameters.GetAssignPayoff())
    << (*parameters.GetChat())
    << (*parameters.GetChooseAction())
    << (*parameters.GetGroupAssign())
    << (*parameters.GetGroupReAssign())
    << (*parameters.GetFinished())
    //<< (*parameters.GetViewResultsAll())
    << (*parameters.GetViewResultsGroup())
    << (*parameters.GetViewResultsVoting())
    << (*parameters.GetVoting())
    << "</parameters>";

  return os;
}

