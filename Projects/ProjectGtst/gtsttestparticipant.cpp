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
#include <functional>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/shared_ptr.hpp>

#include "gtstall_groups.h"
#include "gtstall_parameters.h"
#include "gtstall_serverstates.h"
#include "gtstchatmessage.h"
#include "gtstgroups.h"
#include "gtstgroupassigner.h"
#include "ipaddress.h"
#include "gtstlogfile.h"
#include "gtstparticipant.h"
#include "gtstrepeatassigner.h"
#include "gtststate.h"
#include "stopwatch.h"
#include "gtsttest.h"
#include "gtstserver.h"
#include "shape.h"
#include "shapewidget.h"
#include "gtstvotingoption.h"
#include "wtshapewidget.h"
#pragma GCC diagnostic pop

void ribi::gtst::Test::TestParticipant()
{
  //Create a GroupAssigner
  const int expected_group = 1 + (std::rand() % 256);
  boost::shared_ptr<GroupAssigner> group_assigner(
    new GroupAssignerPredetermined(expected_group));
  {
    //Test the GroupAssigner
    /*
    for (int i=0; i!=10; ++i)
    {
      const int dummy_id = std::rand();
      assert(group_assigner->Assign(dummy_id) == expected_group
        && "Assume GroupAssignerPredetermined always produces the same integer");
    }
    */
  }


  boost::shared_ptr<Participant> p(
    new Participant(
      //chat_tag,
      group_assigner,m_server));
  {
    //assert(!p->CanGetGroup());
    assert(!p->CanGetId());
    assert(p->GetActions().empty());
    assert(p->GetVotes().empty());
    assert(!p->CanGetIpAddress());
  }
  //Assign an ID
  {
    const int id = 1 + (std::rand() % 256);
    p->AssignId(id);
    assert(p->CanGetId());
    assert(p->GetId() == id);
  }
  //Assign an IP address
  {
    boost::shared_ptr<SafeIpAddress> ip_address(
      new SafeIpAddress("123.123.123.123"));
    p->SetIpAddress(ip_address);
    assert(p->CanGetIpAddress());
    assert(p->GetIpAddress()->Get()  == ip_address.get()->Get());
  }
  //Assign a group
  {
    //p->AssignGroup();
    //assert(p->CanGetGroup());
    //assert(p->GetGroup() == expected_group);
  }
  //Chat #1
  {
    boost::shared_ptr<ChatMessage> chat_message(
      new ChatMessage(
        p,
        std::string("chat") + std::to_string(std::rand())));
    assert(p->GetChatLog().empty());
    //std::clog << "p has not yet chatted, not even close\n";
    //assert(!p->HasChatted());
    p->StartChat();
    assert(!p->GetChatLog().empty());
    assert(p->GetChatLog().back().empty());
    //assert(!p->CanGetLastChat());
    //std::clog << "p has not yet chatted\n";
    //assert(!p->HasChatted());
    p->AppendChat(chat_message);
    //assert(p->CanGetLastChat());
    //std::clog << "p has chatted\n";
    assert(!p->GetChatLog().empty());
    assert(!p->GetChatLog().back().empty());
    //assert(p->HasChatted());
    //std::clog << "p should not have an empty chat log\n";
    //assert(!p->GetLastChat().empty());
    //std::clog << "p should not have a chat log with one message\n";
    assert(p->GetChatLog().back().size() == 1);
    //std::clog << "p should not have a chat log with the one message chatted\n";
    assert(p->GetChatLog().back()[0] == chat_message);
  }
  //Voting #1
  {
    //const int vote = std::rand();
    //assert(!p->CanGetLastVote());
    //std::clog << "p has not yet voted, not even close\n";
    //assert(p->HasVoted());
    //p->StartVoting();
    //assert(!p->CanGetLastVote());
    //assert(!p->HasVoted());
    assert(p->GetVotes().empty());
    p->Vote(boost::shared_ptr<VotingOption>(
      new VotingOption(0.5,0.1,"Test")));
    assert(!p->GetVotes().empty());
    //assert(p->CanGetLastVote());
    //assert(p->HasVoted());
    //assert(p->GetLastVote() == vote);
  }
  //Choose action #1
  /*
  {
    const int action = std::rand();
    //assert(!p->CanGetLastAction());
    //assert(p->HasChosenAction());
    //p->StartChooseAction();
    //assert(!p->CanGetLastAction());
    //assert(!p->HasChosenAction());
    assert(p->GetActions().empty());
    p->ChooseAction(action);
    assert(!p->GetActions().empty());
    //assert(p->CanGetLastAction());
    //assert(p->HasChosenAction());
    //assert(p->GetLastChosenAction() == action);
  }
  */
  //Voting #2
  {
    //const int vote = std::rand();
    //assert(p->CanGetLastVote());
    //assert(p->HasVoted());
    //p->StartVoting();
    //assert(p->CanGetLastVote());
    //assert(!p->HasVoted());
    p->Vote(boost::shared_ptr<VotingOption>(
      new VotingOption(0.5,0.1,"Test2")));
    assert(p->GetVotes().size() == 2);
    //assert(p->CanGetLastVote());
    //assert(p->HasVoted());
    //assert(p->GetLastVote() == vote);
  }
  //Choose action #2
  /*
  {
    const int action = std::rand();
    //assert(p->CanGetLastAction());
    //assert(p->HasChosenAction());
    //p->StartChooseAction();
    //assert(p->CanGetLastAction());
    //assert(!p->HasChosenAction());
    p->ChooseAction(action);
    assert(p->GetActions().size() == 2);
    //assert(p->CanGetLastAction());
    //assert(p->HasChosenAction());
    //assert(p->GetLastChosenAction() == action);
  }
  */
  //Chat #2
  {
    boost::shared_ptr<ChatMessage> chat_message(
      new ChatMessage(
        p,
        std::string("chat") + std::to_string(std::rand())));
    //assert(p->CanGetLastChat());
    //assert(p->HasChatted());
    assert(p->GetChatLog().size() == 1);
    p->StartChat();
    assert(p->GetChatLog().size() == 2);
    assert(p->GetChatLog().back().empty());
    //assert(!p->CanGetLastChat());
    //assert(!p->HasChatted());
    p->AppendChat(chat_message);
    assert(!p->GetChatLog().back().empty());
    //assert(p->CanGetLastChat());
    //assert(p->HasChatted());
    //assert(!p->GetLastChat().empty());
    //assert(p->GetLastChat().size() == 1);
    assert(p->GetChatLog().back()[0] == chat_message);
  }
  ///Check the default Participant creation
  {
    boost::shared_ptr<Parameters> parameters(
      new Parameters(m_server));
    boost::shared_ptr<Participant> p1
      = parameters->CreateDefaultParticipant();
    boost::shared_ptr<Participant> p2
      = parameters->CreateDefaultParticipant();
    assert(p1->GetChatShape() != p2->GetChatShape());

  }
}


