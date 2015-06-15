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
#include <iostream>
#include <iterator>

 

#include "gtstall_groups.h"
#include "gtstall_parameters.h"
#include "gtstall_serverstates.h"
#include "gtstchatshapefactory.h"
#include "gtstgroups.h"
#include "gtstgroupassigner.h"
#include "gtstlogfile.h"
#include "gtstparticipant.h"
#include "gtstrepeatassigner.h"
#include "gtststate.h"
#include "stopwatch.h"
#include "gtsttest.h"
#include "gtstserver.h"
#include "gtstvotingoption.h"
#include "trace.h"

void ribi::gtst::Test::CreateParameterFile1()
{
  std::vector<std::string> v;
  v.push_back("///////////////////////////////////////////////////////////////////////////////");
  v.push_back("//Default parameters file                                                    //");
  v.push_back("///////////////////////////////////////////////////////////////////////////////");
  v.push_back("");
  v.push_back("///////////////////////////////////////////////////////////////////////////////");
  v.push_back("//Parameters for participants                                                //");
  v.push_back("///////////////////////////////////////////////////////////////////////////////");
  v.push_back("//A participant has the following parameters");
  v.push_back("//- Initial group assigned to. Possible values:");
  v.push_back("//  - a positive value: the ID will assigned to group x");
  v.push_back("//- Chat tag");
  v.push_back("//  - a non-asterisk character: that character");
  v.push_back("//- IP address");
  v.push_back("//  - a valid IP address: this IP address is assigned to this ID");
  v.push_back("//  - *: any IP address is allowed");
  v.push_back("participant=1,*"); //0
  v.push_back("participant=1,*"); //1
  v.push_back("participant=1,*"); //2
  v.push_back("participant=2,*"); //3
  v.push_back("participant=2,*"); //4
  v.push_back("participant=2,*"); //5
  v.push_back("");
  v.push_back("///////////////////////////////////////////////////////////////////////////////");
  v.push_back("//Parameters for the group assignment phase (experiment cycle)               //");
  v.push_back("///////////////////////////////////////////////////////////////////////////////");
  v.push_back("");
  v.push_back("//group_assign_message_assigned is the message displayed to an assigned participant");
  v.push_back("group_assign_message_assigned=U bent ingedeeld in groep #");
  v.push_back("");
  v.push_back("//group_assign_message_assigned is the message displayed to an assigned participant");
  v.push_back("group_assign_message_unassigned=U bent nog niet ingedeeld");
  v.push_back("");
  v.push_back("//The function that determines how much payoff the waiting participant is rewarded");
  v.push_back("//for simply waiting, where p is the average payoff gathered by the active");
  v.push_back("//participants in the last period.");
  v.push_back("//Examples:");
  v.push_back("//- 1.0");
  v.push_back("//- 1.0 + (0.01 * p)");
  v.push_back("//- 1.0 + (0.1 * p * p)");
  v.push_back("group_assign_waiting_payoff_function=0.5 + (0.5 * p)");
  v.push_back("");
  v.push_back("///////////////////////////////////////////////////////////////////////////////");
  v.push_back("//Parameters for the chat phase (experiment cycle)                           //");
  v.push_back("///////////////////////////////////////////////////////////////////////////////");
  v.push_back("");
  v.push_back("//How long does the chat state take in seconds?");
  v.push_back("chat_duration=60");
  v.push_back("");
  v.push_back("///////////////////////////////////////////////////////////////////////////////");
  v.push_back("//Parameters for the majority voting phase (experiment cycle)                //");
  v.push_back("///////////////////////////////////////////////////////////////////////////////");
  v.push_back("");
  v.push_back("//How long does the (majority) voting state take in seconds?");
  v.push_back("voting_duration=60");
  v.push_back("");
  v.push_back("//What can be voted for?");
  v.push_back("//Must be in the form of [description],[chance],[cost]");
  v.push_back("//For example:");
  v.push_back("//- voting_option=Lenient supervisor,0.5,1.0");
  v.push_back("//- voting_option=Rigorous supervisor,1.0,2.0");
  v.push_back("voting_option=Mijn vriendin,1.0,2.0");
  v.push_back("voting_option=Mijn moeder,0.5,1.0");
  v.push_back("voting_option=Mijn oma,0.0,0.0");
  v.push_back("");
  v.push_back("//Wait for all participants to vote?");
  v.push_back("//- y : yes");
  v.push_back("//- n : no, after vote_duration a random vote is chosen");
  v.push_back("voting_wait=n");
  v.push_back("");
  v.push_back("///////////////////////////////////////////////////////////////////////////////");
  v.push_back("//Parameters for the majority voting results phase (experiment cycle)        //");
  v.push_back("///////////////////////////////////////////////////////////////////////////////");
  v.push_back("");
  v.push_back("");
  v.push_back("//How long does the majority voting results state take in seconds?");
  v.push_back("view_results_voting_duration=30");
  v.push_back("");
  v.push_back("///////////////////////////////////////////////////////////////////////////////");
  v.push_back("//Parameters for the choose action screen (IPGG cycle)                       //");
  v.push_back("///////////////////////////////////////////////////////////////////////////////");
  v.push_back("");
  v.push_back("//choose_action_options are the option of the actions to be chosen");
  v.push_back("//and have the form [description],[benefit to group],[individual cost]");
  v.push_back("//for example:");
  v.push_back("//- choose_action_option=I want to contribute,2.0,1.0,You have chosen not to contribute");
  v.push_back("//- choose_action_option=I do not want to contribute,0.0,0.0,You have chosen not to contribute");
  v.push_back("choose_action_option=Ik zet mijn beste beentje voor,2.0,1.0,U heeft ervoor gekozen om bij te dragen");
  v.push_back("choose_action_option=De ander kan de tering krijgen,0.0,0.0,U heeft ervoor gekozen om niet bij te dragen");
  v.push_back("");
  v.push_back("//Wait for all participants to choos an action?");
  v.push_back("//- y : yes");
  v.push_back("//- n : no, after choose_action_duration a random action is chosen");
  v.push_back("choose_action_wait=n");
  v.push_back("");
  v.push_back("//How long does the choose action state take in seconds?");
  v.push_back("//- any non-zero positive value: this time in seconsd");
  v.push_back("choose_action_duration=30");
  v.push_back("");
  v.push_back("///////////////////////////////////////////////////////////////////////////////");
  v.push_back("//Parameters for the individual payoff (IPGG cycle)                          //");
  v.push_back("///////////////////////////////////////////////////////////////////////////////");
  v.push_back("");
  v.push_back("//The message displayed to the participant");
  v.push_back("assign_payoff_message=Ik ken nu de payoffs toe");
  v.push_back("");
  v.push_back("///////////////////////////////////////////////////////////////////////////////");
  v.push_back("//Parameters for the view in-group results screen (period cycle)             //");
  v.push_back("///////////////////////////////////////////////////////////////////////////////");
  v.push_back("");
  v.push_back("//How long does the choose action state take in seconds?");
  v.push_back("view_results_group_duration=30");
  v.push_back("");
  v.push_back("//How many IPGG cycles are there?");
  v.push_back("//- x     : x cycles, for example '1'");
  v.push_back("//- ?w    : after every action there is a chance of w for another cycle,");
  v.push_back("//-         for example '0.8'");
  v.push_back("//- [a,b> : there are from a to (not including) b cycles, following a ");
  v.push_back("//-         uniform distribution, for example '[1,4>'");
  v.push_back("view_results_group_cycles=7");
  v.push_back("");
  v.push_back("///////////////////////////////////////////////////////////////////////////////");
  v.push_back("//Parameters for the view all-group results screen (experiment cycle)        //");
  v.push_back("///////////////////////////////////////////////////////////////////////////////");
  v.push_back("");
  v.push_back("//How long does the choose action state take in seconds?");
  v.push_back("group_reassign_duration=30");
  v.push_back("");
  v.push_back("//How much experimental cycles/periods are played?");
  v.push_back("group_reassign_number_of_periods=4");
  v.push_back("");
  v.push_back("//How much payoff is an active participant given for reaching the next period?");
  v.push_back("//This is a function of p, where p stands for his/her total accumulated payoff");
  v.push_back("//Examples:");
  v.push_back("//- 1.0");
  v.push_back("//- 1.0 + (0.01 * p)");
  v.push_back("//- 1.0 + (0.1 * p * p)");
  v.push_back("group_reassign_next_period_payoff_function=1.0 + (0.0 * p)");
  v.push_back("");
  v.push_back("//How much payoff is an active participant given for reaching the next period?");
  v.push_back("//This is a function of p, where p stands for his/her total accumulated payoff");
  v.push_back("//Examples:");
  v.push_back("//- 1.0");
  v.push_back("//- 1.0 + (0.01 * p)");
  v.push_back("//- 1.0 + (0.1 * p * p)");
  v.push_back("group_reassign_next_period_payoff_function=1.0 + (0.0 * p)");
  v.push_back("");
  v.push_back("///////////////////////////////////////////////////////////////////////////////");
  v.push_back("//Parameters for the finished experimenty screen (experiment cycle)          //");
  v.push_back("///////////////////////////////////////////////////////////////////////////////");
  v.push_back("");
  v.push_back("//The goodbye message on the finished screen");
  v.push_back("finished_message=Klaar!");
  v.push_back("");
  v.push_back("//How much money does the participant earn from his/her payoff?");
  v.push_back("//This is a function of p, where p stands for payoff");
  v.push_back("//Examples:");
  v.push_back("//- 1.0 + (0.01 * p)");
  v.push_back("//- 1.0 + (0.1 * p * p)");
  v.push_back("finished_earnings_function=1.0 + (0.001 * p)");
  v.push_back("");
  std::ofstream file("parameters1.txt");
  std::copy(v.begin(),v.end(),std::ostream_iterator<std::string>(file,"\n"));
}

void ribi::gtst::Test::CreateParameterFile2()
{
  std::vector<std::string> v;
  v.push_back("///////////////////////////////////////////////////////////////////////////////");
  v.push_back("//Default parameters file                                                    //");
  v.push_back("///////////////////////////////////////////////////////////////////////////////");
  v.push_back("");
  v.push_back("///////////////////////////////////////////////////////////////////////////////");
  v.push_back("//Parameters for participants                                                //");
  v.push_back("///////////////////////////////////////////////////////////////////////////////");
  v.push_back("//A participant has the following parameters");
  v.push_back("//- Initial group assigned to. Possible values:");
  v.push_back("//  - a positive value: the ID will assigned to group x");
  v.push_back("//- Chat tag");
  v.push_back("//  - a non-asterisk character: that character");
  v.push_back("//- IP address");
  v.push_back("//  - a valid IP address: this IP address is assigned to this ID");
  v.push_back("//  - *: any IP address is allowed");
  v.push_back("participant=1,*"); //0
  v.push_back("participant=2,*"); //1
  v.push_back("participant=1,*"); //2
  v.push_back("participant=2,*"); //3
  v.push_back("participant=1,*"); //4
  v.push_back("participant=2,*"); //5
  v.push_back("");
  v.push_back("///////////////////////////////////////////////////////////////////////////////");
  v.push_back("//Parameters for the group assignment phase (experiment cycle)               //");
  v.push_back("///////////////////////////////////////////////////////////////////////////////");
  v.push_back("");
  v.push_back("//group_assign_message_assigned is the message displayed to an assigned participant");
  v.push_back("group_assign_message_assigned=You have been assigned to group #");
  v.push_back("");
  v.push_back("//group_assign_message_assigned is the message displayed to an assigned participant");
  v.push_back("group_assign_message_unassigned=You have not been assigned to a group yet");
  v.push_back("");
  v.push_back("//The function that determines how much payoff the waiting participant is rewarded");
  v.push_back("//for simply waiting, where p is the average payoff gathered by the active");
  v.push_back("//participants in the last period.");
  v.push_back("//Examples:");
  v.push_back("//- 1.0");
  v.push_back("//- 1.0 + (0.01 * p)");
  v.push_back("//- 1.0 + (0.1 * p * p)");
  v.push_back("group_assign_waiting_payoff_function=0.5 + (0.5 * p)");
  v.push_back("");
  v.push_back("///////////////////////////////////////////////////////////////////////////////");
  v.push_back("//Parameters for the chat phase (experiment cycle)                           //");
  v.push_back("///////////////////////////////////////////////////////////////////////////////");
  v.push_back("");
  v.push_back("//How long does the chat state take in seconds?");
  v.push_back("chat_duration=120");
  v.push_back("");
  v.push_back("///////////////////////////////////////////////////////////////////////////////");
  v.push_back("//Parameters for the majority voting phase (experiment cycle)                //");
  v.push_back("///////////////////////////////////////////////////////////////////////////////");
  v.push_back("");
  v.push_back("//How long does the (majority) voting state take in seconds?");
  v.push_back("voting_duration=30");
  v.push_back("");
  v.push_back("//What can be voted for?");
  v.push_back("//Must be in the form of [description],[chance],[cost]");
  v.push_back("//For example:");
  v.push_back("//- voting_option=Lenient supervisor,0.5,1.0");
  v.push_back("//- voting_option=Rigorous supervisor,1.0,2.0");
  v.push_back("voting_option=rigorous supervisor,1.0,2.0");
  v.push_back("voting_option=lenient supervisor,0.5,1.0");
  v.push_back("voting_option=no supervisor,0.0,0.0");
  v.push_back("");
  v.push_back("//Wait for all participants to vote?");
  v.push_back("//- y : yes");
  v.push_back("//- n : no, after vote_duration a random vote is chosen");
  v.push_back("voting_wait=y");
  v.push_back("");
  v.push_back("///////////////////////////////////////////////////////////////////////////////");
  v.push_back("//Parameters for the majority voting results phase (experiment cycle)        //");
  v.push_back("///////////////////////////////////////////////////////////////////////////////");
  v.push_back("");
  v.push_back("");
  v.push_back("//How long does the majority voting results state take in seconds?");
  v.push_back("view_results_voting_duration=60");
  v.push_back("");
  v.push_back("///////////////////////////////////////////////////////////////////////////////");
  v.push_back("//Parameters for the choose action screen (IPGG cycle)                       //");
  v.push_back("///////////////////////////////////////////////////////////////////////////////");
  v.push_back("");
  v.push_back("//choose_action_options are the option of the actions to be chosen");
  v.push_back("//and have the form [description],[benefit to group],[individual cost]");
  v.push_back("//for example:");
  v.push_back("//- choose_action_option=I want to contribute,2.0,1.0");
  v.push_back("//- choose_action_option=I do not want to contribute,0.0,0.0");
  v.push_back("choose_action_option=Contribute,2.0,1.0,You have chosen to contribute");
  v.push_back("choose_action_option=Do not contribute,0.0,0.0,You have chosen not to contribute");
  v.push_back("");
  v.push_back("//Wait for all participants to choose an action?");
  v.push_back("//- y : yes");
  v.push_back("//- n : no, after choose_action_duration a random action is chosen");
  v.push_back("choose_action_wait=y");
  v.push_back("");
  v.push_back("//How long does the choose action state take in seconds?");
  v.push_back("//- any non-zero positive value: this time in seconsd");
  v.push_back("choose_action_duration=60");
  v.push_back("");
  v.push_back("///////////////////////////////////////////////////////////////////////////////");
  v.push_back("//Parameters for the individual payoff (IPGG cycle)                          //");
  v.push_back("///////////////////////////////////////////////////////////////////////////////");
  v.push_back("");
  v.push_back("//The message displayed to the participant");
  v.push_back("assign_payoff_message=Assigning payoffs");
  v.push_back("");
  v.push_back("///////////////////////////////////////////////////////////////////////////////");
  v.push_back("//Parameters for the view in-group results screen (period cycle)             //");
  v.push_back("///////////////////////////////////////////////////////////////////////////////");
  v.push_back("");
  v.push_back("//How long does the choose action state take in seconds?");
  v.push_back("view_results_group_duration=60");
  v.push_back("");
  v.push_back("//How many IPGG cycles are there?");
  v.push_back("//- x     : x cycles, for example '1'");
  v.push_back("//- ?w    : after every action there is a chance of w for another cycle,");
  v.push_back("//-         for example '0.8'");
  v.push_back("//- [a,b> : there are from a to (not including) b cycles, following a ");
  v.push_back("//-         uniform distribution, for example '[1,4>'");
  v.push_back("view_results_group_cycles=3");
  v.push_back("");
  v.push_back("///////////////////////////////////////////////////////////////////////////////");
  v.push_back("//Parameters for the view all-group results screen (experiment cycle)        //");
  v.push_back("///////////////////////////////////////////////////////////////////////////////");
  v.push_back("");
  v.push_back("//How long does the choose action state take in seconds?");
  v.push_back("group_reassign_duration=90");
  v.push_back("");
  v.push_back("//How much experimental cycles/periods are played?");
  v.push_back("group_reassign_number_of_periods=3");
  v.push_back("");
  v.push_back("//How much payoff is an active participant given for reaching the next period?");
  v.push_back("//This is a function of p, where p stands for his/her total accumulated payoff");
  v.push_back("//Examples:");
  v.push_back("//- 1.0");
  v.push_back("//- 1.0 + (0.01 * p)");
  v.push_back("//- 1.0 + (0.1 * p * p)");
  v.push_back("group_reassign_next_period_payoff_function=1.0 + (0.0 * p)");
  v.push_back("");
  v.push_back("///////////////////////////////////////////////////////////////////////////////");
  v.push_back("//Parameters for the finished experimenty screen (experiment cycle)          //");
  v.push_back("///////////////////////////////////////////////////////////////////////////////");
  v.push_back("");
  v.push_back("//The goodbye message on the finished screen");
  v.push_back("finished_message=The experiment has finished");
  v.push_back("");
  v.push_back("//How much money does the participant earn from his/her payoff?");
  v.push_back("//This is a function of p, where p stands for payoff");
  v.push_back("//Examples:");
  v.push_back("//- 1.0 + (0.01 * p)");
  v.push_back("//- 1.0 + (0.1 * p * p)");
  v.push_back("finished_earnings_function=1.0 + (0.01 * p)");
  v.push_back("");
  std::ofstream file("parameters2.txt");
  std::copy(v.begin(),v.end(),std::ostream_iterator<std::string>(file,"\n"));
}

void ribi::gtst::Test::CreateParameterFile3()
{
  std::vector<std::string> v;
  v.push_back("///////////////////////////////////////////////////////////////////////////////");
  v.push_back("//Default parameters file                                                    //");
  v.push_back("///////////////////////////////////////////////////////////////////////////////");
  v.push_back("");
  v.push_back("///////////////////////////////////////////////////////////////////////////////");
  v.push_back("//Parameters for participants                                                //");
  v.push_back("///////////////////////////////////////////////////////////////////////////////");
  v.push_back("//A participant has the following parameters");
  v.push_back("//- Initial group assigned to. Possible values:");
  v.push_back("//  - a positive value: the ID will assigned to group x");
  v.push_back("//- Chat tag");
  v.push_back("//  - a non-asterisk character: that character");
  v.push_back("//- IP address");
  v.push_back("//  - a valid IP address: this IP address is assigned to this ID");
  v.push_back("//  - *: any IP address is allowed");
  v.push_back("participant=1,*"); //0
  v.push_back("participant=2,*"); //1
  v.push_back("participant=1,*"); //2
  v.push_back("participant=2,*"); //3
  v.push_back("participant=1,*"); //4
  v.push_back("participant=2,*"); //5
  v.push_back("");
  v.push_back("///////////////////////////////////////////////////////////////////////////////");
  v.push_back("//Parameters for the group assignment phase (experiment cycle)               //");
  v.push_back("///////////////////////////////////////////////////////////////////////////////");
  v.push_back("");
  v.push_back("//group_assign_message_assigned is the message displayed to an assigned participant");
  v.push_back("group_assign_message_assigned=You have been assigned to group #");
  v.push_back("");
  v.push_back("//group_assign_message_assigned is the message displayed to an assigned participant");
  v.push_back("group_assign_message_unassigned=You have not been assigned to a group yet");
  v.push_back("");
  v.push_back("//The function that determines how much payoff the waiting participant is rewarded");
  v.push_back("//for simply waiting, where p is the average payoff gathered by the active");
  v.push_back("//participants in the last period.");
  v.push_back("//Examples:");
  v.push_back("//- 1.0");
  v.push_back("//- 1.0 + (0.01 * p)");
  v.push_back("//- 1.0 + (0.1 * p * p)");
  v.push_back("group_assign_waiting_payoff_function=0.5 + (0.5 * p)");
  v.push_back("");
  v.push_back("///////////////////////////////////////////////////////////////////////////////");
  v.push_back("//Parameters for the chat phase (experiment cycle)                           //");
  v.push_back("///////////////////////////////////////////////////////////////////////////////");
  v.push_back("");
  v.push_back("");
  v.push_back("//How long does the chat state take in seconds?");
  v.push_back("chat_duration=120");
  v.push_back("");
  v.push_back("///////////////////////////////////////////////////////////////////////////////");
  v.push_back("//Parameters for the majority voting phase (experiment cycle)                //");
  v.push_back("///////////////////////////////////////////////////////////////////////////////");
  v.push_back("");
  v.push_back("//How long does the (majority) voting state take in seconds?");
  v.push_back("voting_duration=30");
  v.push_back("");
  v.push_back("//What can be voted for?");
  v.push_back("//Must be in the form of [description],[chance],[cost]");
  v.push_back("//For example:");
  v.push_back("//- voting_option=Lenient supervisor,0.5,1.0");
  v.push_back("//- voting_option=Rigorous supervisor,1.0,2.0");
  v.push_back("voting_option=rigorous supervisor,1.0,2.0");
  v.push_back("voting_option=lenient supervisor,0.5,1.0");
  v.push_back("voting_option=no supervisor,0.0,0.0");
  v.push_back("");
  v.push_back("//Wait for all participants to vote?");
  v.push_back("//- y : yes");
  v.push_back("//- n : no, after vote_duration a random vote is chosen");
  v.push_back("voting_wait=y");
  v.push_back("");
  v.push_back("///////////////////////////////////////////////////////////////////////////////");
  v.push_back("//Parameters for the majority voting results phase (experiment cycle)        //");
  v.push_back("///////////////////////////////////////////////////////////////////////////////");
  v.push_back("");
  v.push_back("");
  v.push_back("//How long does the majority voting results state take in seconds?");
  v.push_back("view_results_voting_duration=60");
  v.push_back("");
  v.push_back("///////////////////////////////////////////////////////////////////////////////");
  v.push_back("//Parameters for the choose action screen (IPGG cycle)                       //");
  v.push_back("///////////////////////////////////////////////////////////////////////////////");
  v.push_back("");
  v.push_back("//choose_action_options are the option of the actions to be chosen");
  v.push_back("//and have the form [description],[benefit to group],[individual cost]");
  v.push_back("//for example:");
  v.push_back("//- choose_action_option=I want to contribute,2.0,1.0,You have chosen to contribute");
  v.push_back("//- choose_action_option=I do not want to contribute,0.0,0.0,You have chosen not to contribute");
  v.push_back("choose_action_option=Contribute,2.0,1.0,You have chosen to contribute");
  v.push_back("choose_action_option=Do not contribute,0.0,0.0,You have chosen not to contribute");
  v.push_back("");
  v.push_back("//Wait for all participants to choose an action?");
  v.push_back("//- y : yes");
  v.push_back("//- n : no, after choose_action_duration a random action is chosen");
  v.push_back("choose_action_wait=y");
  v.push_back("");
  v.push_back("//How long does the choose action state take in seconds?");
  v.push_back("//- any non-zero positive value: this time in seconsd");
  v.push_back("choose_action_duration=60");
  v.push_back("");
  v.push_back("///////////////////////////////////////////////////////////////////////////////");
  v.push_back("//Parameters for the individual payoff (IPGG cycle)                          //");
  v.push_back("///////////////////////////////////////////////////////////////////////////////");
  v.push_back("");
  v.push_back("//The message displayed to the participant");
  v.push_back("assign_payoff_message=Assigning payoffs");
  v.push_back("");
  v.push_back("///////////////////////////////////////////////////////////////////////////////");
  v.push_back("//Parameters for the view in-group results screen (period cycle)             //");
  v.push_back("///////////////////////////////////////////////////////////////////////////////");
  v.push_back("");
  v.push_back("//How long does the view results group state take in seconds?");
  v.push_back("view_results_group_duration=60");
  v.push_back("");
  v.push_back("//How many IPGG cycles are there?");
  v.push_back("//- x     : x cycles, for example '1'");
  v.push_back("//- ?w    : after every action there is a chance of w for another cycle,");
  v.push_back("//-         for example '0.8'");
  v.push_back("//- [a,b> : there are from a to (not including) b cycles, following a ");
  v.push_back("//-         uniform distribution, for example '[1,4>'");
  v.push_back("view_results_group_cycles=[1,4>");
  v.push_back("");
  v.push_back("///////////////////////////////////////////////////////////////////////////////");
  v.push_back("//Parameters for the view all-group results screen (experiment cycle)        //");
  v.push_back("///////////////////////////////////////////////////////////////////////////////");
  v.push_back("");
  v.push_back("//How long does the view results group take in seconds?");
  v.push_back("group_reassign_duration=90");
  v.push_back("");
  v.push_back("//How much experimental cycles/periods are played?");
  v.push_back("group_reassign_number_of_periods=3");
  v.push_back("");
  v.push_back("//How much payoff is an active participant given for reaching the next period?");
  v.push_back("//This is a function of p, where p stands for his/her total accumulated payoff");
  v.push_back("//Examples:");
  v.push_back("//- 1.0");
  v.push_back("//- 1.0 + (0.01 * p)");
  v.push_back("//- 1.0 + (0.1 * p * p)");
  v.push_back("group_reassign_next_period_payoff_function=1.0 + (0.0 * p)");
  v.push_back("");
  v.push_back("///////////////////////////////////////////////////////////////////////////////");
  v.push_back("//Parameters for the finished experimenty screen (experiment cycle)          //");
  v.push_back("///////////////////////////////////////////////////////////////////////////////");
  v.push_back("");
  v.push_back("//The goodbye message on the finished screen");
  v.push_back("finished_message=The experiment has finished");
  v.push_back("");
  v.push_back("//How much money does the participant earn from his/her payoff?");
  v.push_back("//This is a function of p, where p stands for payoff");
  v.push_back("//Examples:");
  v.push_back("//- 1.0 + (0.01 * p)");
  v.push_back("//- 1.0 + (0.1 * p * p)");
  v.push_back("finished_earnings_function=1.0 + (0.01 * p)");
  v.push_back("");
  std::ofstream file("parameters3.txt");
  std::copy(v.begin(),v.end(),std::ostream_iterator<std::string>(file,"\n"));
}

void ribi::gtst::Test::CreateParameterFile4()
{
  std::vector<std::string> v;
  v.push_back("///////////////////////////////////////////////////////////////////////////////");
  v.push_back("//Default parameters file                                                    //");
  v.push_back("///////////////////////////////////////////////////////////////////////////////");
  v.push_back("");
  v.push_back("///////////////////////////////////////////////////////////////////////////////");
  v.push_back("//Parameters for participants                                                //");
  v.push_back("///////////////////////////////////////////////////////////////////////////////");
  v.push_back("//A participant has the following parameters");
  v.push_back("//- Initial group assigned to. Possible values:");
  v.push_back("//  - a positive value: the ID will assigned to group x");
  v.push_back("//- Chat tag");
  v.push_back("//  - a non-asterisk character: that character");
  v.push_back("//- IP address");
  v.push_back("//  - a valid IP address: this IP address is assigned to this ID");
  v.push_back("//  - *: any IP address is allowed");
  v.push_back("participant=1,*"); //0
  v.push_back("participant=2,*"); //1
  v.push_back("participant=1,*"); //2
  v.push_back("participant=2,*"); //3
  v.push_back("participant=1,*"); //4
  v.push_back("participant=2,*"); //5
  v.push_back("");
  v.push_back("///////////////////////////////////////////////////////////////////////////////");
  v.push_back("//Parameters for the group assignment phase (experiment cycle)               //");
  v.push_back("///////////////////////////////////////////////////////////////////////////////");
  v.push_back("");
  v.push_back("");
  v.push_back("//group_assign_message_assigned is the message displayed to an assigned participant");
  v.push_back("group_assign_message_assigned=You have been assigned to group #");
  v.push_back("");
  v.push_back("//group_assign_message_assigned is the message displayed to an assigned participant");
  v.push_back("group_assign_message_unassigned=You have not been assigned to a group yet");
  v.push_back("");
  v.push_back("//The function that determines how much payoff the waiting participant is rewarded");
  v.push_back("//for simply waiting, where p is the average payoff gathered by the active");
  v.push_back("//participants in the last period.");
  v.push_back("//Examples:");
  v.push_back("//- 1.0");
  v.push_back("//- 1.0 + (0.01 * p)");
  v.push_back("//- 1.0 + (0.1 * p * p)");
  v.push_back("group_assign_waiting_payoff_function=0.5 + (0.5 * p)");
  v.push_back("");
  v.push_back("///////////////////////////////////////////////////////////////////////////////");
  v.push_back("//Parameters for the chat phase (experiment cycle)                           //");
  v.push_back("///////////////////////////////////////////////////////////////////////////////");
  v.push_back("");
  v.push_back("");
  v.push_back("//How long does the chat state take in seconds?");
  v.push_back("chat_duration=120");
  v.push_back("");
  v.push_back("///////////////////////////////////////////////////////////////////////////////");
  v.push_back("//Parameters for the majority voting phase (experiment cycle)                //");
  v.push_back("///////////////////////////////////////////////////////////////////////////////");
  v.push_back("");
  v.push_back("//How long does the (majority) voting state take in seconds?");
  v.push_back("voting_duration=30");
  v.push_back("");
  v.push_back("//What can be voted for?");
  v.push_back("//Must be in the form of [description],[chance],[cost]");
  v.push_back("//For example:");
  v.push_back("//- voting_option=Lenient supervisor,0.5,1.0");
  v.push_back("//- voting_option=Rigorous supervisor,1.0,2.0");
  v.push_back("voting_option=rigorous supervisor,1.0,2.0");
  v.push_back("voting_option=lenient supervisor,0.5,1.0");
  v.push_back("voting_option=no supervisor,0.0,0.0");
  v.push_back("");
  v.push_back("//Wait for all participants to vote?");
  v.push_back("//- y : yes");
  v.push_back("//- n : no, after vote_duration a random vote is chosen");
  v.push_back("voting_wait=y");
  v.push_back("");
  v.push_back("///////////////////////////////////////////////////////////////////////////////");
  v.push_back("//Parameters for the majority voting results phase (experiment cycle)        //");
  v.push_back("///////////////////////////////////////////////////////////////////////////////");
  v.push_back("");
  v.push_back("");
  v.push_back("//How long does the majority voting results state take in seconds?");
  v.push_back("view_results_voting_duration=60");
  v.push_back("");
  v.push_back("///////////////////////////////////////////////////////////////////////////////");
  v.push_back("//Parameters for the choose action screen (IPGG cycle)                       //");
  v.push_back("///////////////////////////////////////////////////////////////////////////////");
  v.push_back("");
  v.push_back("//choose_action_options are the option of the actions to be chosen");
  v.push_back("//and have the form [description],[benefit to group],[individual cost]");
  v.push_back("//for example:");
  v.push_back("//- choose_action_option=I want to contribute,2.0,1.0,You have chosen not to contribute");
  v.push_back("//- choose_action_option=I do not want to contribute,0.0,0.0,You have chosen not to contribute");
  v.push_back("choose_action_option=Contribute,2.0,1.0,You have chosen to contribute");
  v.push_back("choose_action_option=Do not contribute,0.0,0.0,You have chosen not to contribute");
  v.push_back("");
  v.push_back("//Wait for all participants to choose an action?");
  v.push_back("//- y : yes");
  v.push_back("//- n : no, after choose_action_duration a random action is chosen");
  v.push_back("choose_action_wait=y");
  v.push_back("");
  v.push_back("//How long does the choose action state take in seconds?");
  v.push_back("//- any non-zero positive value: this time in seconsd");
  v.push_back("choose_action_duration=60");
  v.push_back("");
  v.push_back("///////////////////////////////////////////////////////////////////////////////");
  v.push_back("//Parameters for the individual payoff (IPGG cycle)                          //");
  v.push_back("///////////////////////////////////////////////////////////////////////////////");
  v.push_back("");
  v.push_back("//The message displayed to the participant");
  v.push_back("assign_payoff_message=Assigning payoffs");
  v.push_back("");
  v.push_back("///////////////////////////////////////////////////////////////////////////////");
  v.push_back("//Parameters for the view in-group results screen (period cycle)             //");
  v.push_back("///////////////////////////////////////////////////////////////////////////////");
  v.push_back("");
  v.push_back("//How long does the view results group state take in seconds?");
  v.push_back("view_results_group_duration=60");
  v.push_back("");
  v.push_back("//How many IPGG cycles are there?");
  v.push_back("//- x     : x cycles, for example '1'");
  v.push_back("//- ?w    : after every action there is a chance of w for another cycle,");
  v.push_back("//-         for example '0.8'");
  v.push_back("//- [a,b> : there are from a to (not including) b cycles, following a ");
  v.push_back("//-         uniform distribution, for example '[1,4>'");
  v.push_back("view_results_group_cycles=?0.5");
  v.push_back("");
  v.push_back("///////////////////////////////////////////////////////////////////////////////");
  v.push_back("//Parameters for the view all-group results screen (experiment cycle)        //");
  v.push_back("///////////////////////////////////////////////////////////////////////////////");
  v.push_back("");
  v.push_back("//How long does the view results group take in seconds?");
  v.push_back("group_reassign_duration=90");
  v.push_back("");
  v.push_back("//How much experimental cycles/periods are played?");
  v.push_back("group_reassign_number_of_periods=3");
  v.push_back("");
  v.push_back("//How much payoff is an active participant given for reaching the next period?");
  v.push_back("//This is a function of p, where p stands for his/her total accumulated payoff");
  v.push_back("//Examples:");
  v.push_back("//- 1.0");
  v.push_back("//- 1.0 + (0.01 * p)");
  v.push_back("//- 1.0 + (0.1 * p * p)");
  v.push_back("group_reassign_next_period_payoff_function=1.0 + (0.0 * p)");
  v.push_back("");
  v.push_back("///////////////////////////////////////////////////////////////////////////////");
  v.push_back("//Parameters for the finished experimenty screen (experiment cycle)          //");
  v.push_back("///////////////////////////////////////////////////////////////////////////////");
  v.push_back("");
  v.push_back("//The goodbye message on the finished screen");
  v.push_back("finished_message=The experiment has finished");
  v.push_back("");
  v.push_back("//How much money does the participant earn from his/her payoff?");
  v.push_back("//This is a function of p, where p stands for payoff");
  v.push_back("//Examples:");
  v.push_back("//- 1.0 + (0.01 * p)");
  v.push_back("//- 1.0 + (0.1 * p * p)");
  v.push_back("finished_earnings_function=1.0 + (0.01 * p)");
  v.push_back("");
  std::ofstream file("parameters4.txt");
  std::copy(v.begin(),v.end(),std::ostream_iterator<std::string>(file,"\n"));
}

void ribi::gtst::Test::CreateParameterFile5()
{
  std::vector<std::string> v;
  v.push_back("///////////////////////////////////////////////////////////////////////////////");
  v.push_back("//Default parameters file                                                    //");
  v.push_back("///////////////////////////////////////////////////////////////////////////////");
  v.push_back("");
  v.push_back("///////////////////////////////////////////////////////////////////////////////");
  v.push_back("//Parameters for participants                                                //");
  v.push_back("///////////////////////////////////////////////////////////////////////////////");
  v.push_back("//A participant has the following parameters");
  v.push_back("//- Initial group assigned to. Possible values:");
  v.push_back("//  - a positive value: the ID will assigned to group x");
  v.push_back("//- Chat tag");
  v.push_back("//  - a non-asterisk character: that character");
  v.push_back("//- IP address");
  v.push_back("//  - a valid IP address: this IP address is assigned to this ID");
  v.push_back("//  - *: any IP address is allowed");
  v.push_back("participant=1,*"); //0
  v.push_back("participant=1,*"); //1
  v.push_back("participant=1,*"); //2
  v.push_back("participant=2,*"); //3
  v.push_back("participant=2,*"); //4
  v.push_back("participant=2,*"); //5
  v.push_back("participant=?,*"); //6
  v.push_back("participant=?,*"); //7
  v.push_back("participant=?,*"); //8
  v.push_back("participant=?,*"); //9
  v.push_back("participant=?,*"); //10
  v.push_back("participant=?,*"); //11
  v.push_back("");
  v.push_back("///////////////////////////////////////////////////////////////////////////////");
  v.push_back("//Parameters for the group assignment phase (experiment cycle)               //");
  v.push_back("///////////////////////////////////////////////////////////////////////////////");
  v.push_back("");
  v.push_back("");
  v.push_back("//group_assign_message_assigned is the message displayed to an assigned participant");
  v.push_back("group_assign_message_assigned=You have been assigned to group #");
  v.push_back("");
  v.push_back("//group_assign_message_assigned is the message displayed to an assigned participant");
  v.push_back("group_assign_message_unassigned=You have not been assigned to a group yet");
  v.push_back("");
  v.push_back("//The function that determines how much payoff the waiting participant is rewarded");
  v.push_back("//for simply waiting, where p is the average payoff gathered by the active");
  v.push_back("//participants in the last period.");
  v.push_back("//Examples:");
  v.push_back("//- 1.0");
  v.push_back("//- 1.0 + (0.01 * p)");
  v.push_back("//- 1.0 + (0.1 * p * p)");
  v.push_back("group_assign_waiting_payoff_function=0.5 + (0.5 * p)");
  v.push_back("");
  v.push_back("///////////////////////////////////////////////////////////////////////////////");
  v.push_back("//Parameters for the chat phase (experiment cycle)                           //");
  v.push_back("///////////////////////////////////////////////////////////////////////////////");
  v.push_back("");
  v.push_back("");
  v.push_back("//How long does the chat state take in seconds?");
  v.push_back("chat_duration=5");
  v.push_back("");
  v.push_back("///////////////////////////////////////////////////////////////////////////////");
  v.push_back("//Parameters for the majority voting phase (experiment cycle)                //");
  v.push_back("///////////////////////////////////////////////////////////////////////////////");
  v.push_back("");
  v.push_back("//How long does the (majority) voting state take in seconds?");
  v.push_back("voting_duration=5");
  v.push_back("");
  v.push_back("//What can be voted for?");
  v.push_back("//Must be in the form of [description],[chance],[cost]");
  v.push_back("//For example:");
  v.push_back("//- voting_option=Lenient supervisor,0.5,1.0");
  v.push_back("//- voting_option=Rigorous supervisor,1.0,2.0");
  v.push_back("voting_option=rigorous supervisor,1.0,2.0");
  v.push_back("voting_option=lenient supervisor,0.5,1.0");
  v.push_back("voting_option=no supervisor,0.0,0.0");
  v.push_back("");
  v.push_back("//Wait for all participants to vote?");
  v.push_back("//- y : yes");
  v.push_back("//- n : no, after vote_duration a random vote is chosen");
  v.push_back("voting_wait=y");
  v.push_back("");
  v.push_back("///////////////////////////////////////////////////////////////////////////////");
  v.push_back("//Parameters for the majority voting results phase (experiment cycle)        //");
  v.push_back("///////////////////////////////////////////////////////////////////////////////");
  v.push_back("");
  v.push_back("");
  v.push_back("//How long does the majority voting results state take in seconds?");
  v.push_back("view_results_voting_duration=5");
  v.push_back("");
  v.push_back("///////////////////////////////////////////////////////////////////////////////");
  v.push_back("//Parameters for the choose action screen (IPGG cycle)                       //");
  v.push_back("///////////////////////////////////////////////////////////////////////////////");
  v.push_back("");
  v.push_back("//choose_action_options are the option of the actions to be chosen");
  v.push_back("//and have the form [description],[benefit to group],[individual cost]");
  v.push_back("//for example:");
  v.push_back("//- choose_action_option=I want to contribute,2.0,1.0");
  v.push_back("//- choose_action_option=I do not want to contribute,0.0,0.0");
  v.push_back("choose_action_option=Contribute,2.0,1.0,You have chosen to contribute");
  v.push_back("choose_action_option=Do not contribute,0.0,0.0,You have chosen not to contribute");
  v.push_back("");
  v.push_back("//Wait for all participants to choose an action?");
  v.push_back("//- y : yes");
  v.push_back("//- n : no, after choose_action_duration a random action is chosen");
  v.push_back("choose_action_wait=y");
  v.push_back("");
  v.push_back("//How long does the choose action state take in seconds?");
  v.push_back("//- any non-zero positive value: this time in seconsd");
  v.push_back("choose_action_duration=5");
  v.push_back("");
  v.push_back("///////////////////////////////////////////////////////////////////////////////");
  v.push_back("//Parameters for the individual payoff (IPGG cycle)                          //");
  v.push_back("///////////////////////////////////////////////////////////////////////////////");
  v.push_back("");
  v.push_back("//The message displayed to the participant");
  v.push_back("assign_payoff_message=Assigning payoffs");
  v.push_back("");
  v.push_back("///////////////////////////////////////////////////////////////////////////////");
  v.push_back("//Parameters for the view in-group results screen (period cycle)             //");
  v.push_back("///////////////////////////////////////////////////////////////////////////////");
  v.push_back("");
  v.push_back("//How long does the view results group state take in seconds?");
  v.push_back("view_results_group_duration=5");
  v.push_back("");
  v.push_back("//How many IPGG cycles are there?");
  v.push_back("//- x     : x cycles, for example '1'");
  v.push_back("//- ?w    : after every action there is a chance of w for another cycle,");
  v.push_back("//-         for example '0.8'");
  v.push_back("//- [a,b> : there are from a to (not including) b cycles, following a ");
  v.push_back("//-         uniform distribution, for example '[1,4>'");
  v.push_back("view_results_group_cycles=?0.1");
  v.push_back("");
  v.push_back("///////////////////////////////////////////////////////////////////////////////");
  v.push_back("//Parameters for the view all-group results screen (experiment cycle)        //");
  v.push_back("///////////////////////////////////////////////////////////////////////////////");
  v.push_back("");
  v.push_back("//How long does the view results group take in seconds?");
  v.push_back("group_reassign_duration=5");
  v.push_back("");
  v.push_back("//How much experimental cycles/periods are played?");
  v.push_back("group_reassign_number_of_periods=3");
  v.push_back("");
  v.push_back("//How much payoff is an active participant given for reaching the next period?");
  v.push_back("//This is a function of p, where p stands for his/her total accumulated payoff");
  v.push_back("//Examples:");
  v.push_back("//- 1.0");
  v.push_back("//- 1.0 + (0.01 * p)");
  v.push_back("//- 1.0 + (0.1 * p * p)");
  v.push_back("group_reassign_next_period_payoff_function=1.0 + (0.0 * p)");
  v.push_back("");
  v.push_back("///////////////////////////////////////////////////////////////////////////////");
  v.push_back("//Parameters for the finished experimenty screen (experiment cycle)          //");
  v.push_back("///////////////////////////////////////////////////////////////////////////////");
  v.push_back("");
  v.push_back("//The goodbye message on the finished screen");
  v.push_back("finished_message=The experiment has finished");
  v.push_back("");
  v.push_back("//How much money does the participant earn from his/her payoff?");
  v.push_back("//This is a function of p, where p stands for payoff");
  v.push_back("//Examples:");
  v.push_back("//- 1.0 + (0.01 * p)");
  v.push_back("//- 1.0 + (0.1 * p * p)");
  v.push_back("finished_earnings_function=1.0 + (0.01 * p)");
  v.push_back("");
  std::ofstream file("parameters5.txt");
  std::copy(v.begin(),v.end(),std::ostream_iterator<std::string>(file,"\n"));
}

void ribi::gtst::Test::CreateParameterFile6()
{
  std::vector<std::string> v;
  v.push_back("///////////////////////////////////////////////////////////////////////////////");
  v.push_back("//Default parameters file                                                    //");
  v.push_back("///////////////////////////////////////////////////////////////////////////////");
  v.push_back("");
  v.push_back("///////////////////////////////////////////////////////////////////////////////");
  v.push_back("//Parameters for participants                                                //");
  v.push_back("///////////////////////////////////////////////////////////////////////////////");
  v.push_back("//A participant has the following parameters");
  v.push_back("//- Initial group assigned to. Possible values:");
  v.push_back("//  - a positive value: the ID will assigned to group x");
  v.push_back("//- Chat tag");
  v.push_back("//  - a non-asterisk character: that character");
  v.push_back("//- IP address");
  v.push_back("//  - a valid IP address: this IP address is assigned to this ID");
  v.push_back("//  - *: any IP address is allowed");
  v.push_back("participant=1,*"); //0
  v.push_back("participant=2,*"); //1
  v.push_back("participant=1,*"); //2
  v.push_back("participant=2,*"); //3
  v.push_back("participant=1,*"); //4
  v.push_back("participant=2,*"); //5
  v.push_back("");
  v.push_back("///////////////////////////////////////////////////////////////////////////////");
  v.push_back("//Parameters for the group assignment phase (experiment cycle)               //");
  v.push_back("///////////////////////////////////////////////////////////////////////////////");
  v.push_back("");
  v.push_back("");
  v.push_back("//group_assign_message_assigned is the message displayed to an assigned participant");
  v.push_back("group_assign_message_assigned=You have been assigned to group #");
  v.push_back("");
  v.push_back("//group_assign_message_assigned is the message displayed to an assigned participant");
  v.push_back("group_assign_message_unassigned=You have not been assigned to a group yet");
  v.push_back("");
  v.push_back("//The function that determines how much payoff the waiting participant is rewarded");
  v.push_back("//for simply waiting, where p is the average payoff gathered by the active");
  v.push_back("//participants in the last period.");
  v.push_back("//Examples:");
  v.push_back("//- 1.0");
  v.push_back("//- 1.0 + (0.01 * p)");
  v.push_back("//- 1.0 + (0.1 * p * p)");
  v.push_back("group_assign_waiting_payoff_function=0.5 + (0.5 * p)");
  v.push_back("");
  v.push_back("///////////////////////////////////////////////////////////////////////////////");
  v.push_back("//Parameters for the chat phase (experiment cycle)                           //");
  v.push_back("///////////////////////////////////////////////////////////////////////////////");
  v.push_back("");
  v.push_back("");
  v.push_back("//How long does the chat state take in seconds?");
  v.push_back("chat_duration=5");
  v.push_back("");
  v.push_back("///////////////////////////////////////////////////////////////////////////////");
  v.push_back("//Parameters for the majority voting phase (experiment cycle)                //");
  v.push_back("///////////////////////////////////////////////////////////////////////////////");
  v.push_back("");
  v.push_back("//How long does the (majority) voting state take in seconds?");
  v.push_back("voting_duration=5");
  v.push_back("");
  v.push_back("//What can be voted for?");
  v.push_back("//What can be voted for?");
  v.push_back("//Must be in the form of [description],[chance],[cost]");
  v.push_back("//For example:");
  v.push_back("//- voting_option=Lenient supervisor,0.5,1.0");
  v.push_back("//- voting_option=Rigorous supervisor,1.0,2.0");
  v.push_back("voting_option=rigorous supervisor,1.0,2.0");
  v.push_back("voting_option=lenient supervisor,0.5,1.0");
  v.push_back("voting_option=no supervisor,0.0,0.0");
  v.push_back("");
  v.push_back("//Wait for all participants to vote?");
  v.push_back("//- y : yes");
  v.push_back("//- n : no, after vote_duration a random vote is chosen");
  v.push_back("voting_wait=y");
  v.push_back("");
  v.push_back("///////////////////////////////////////////////////////////////////////////////");
  v.push_back("//Parameters for the majority voting results phase (experiment cycle)        //");
  v.push_back("///////////////////////////////////////////////////////////////////////////////");
  v.push_back("");
  v.push_back("");
  v.push_back("//How long does the majority voting results state take in seconds?");
  v.push_back("view_results_voting_duration=5");
  v.push_back("");
  v.push_back("///////////////////////////////////////////////////////////////////////////////");
  v.push_back("//Parameters for the choose action screen (IPGG cycle)                       //");
  v.push_back("///////////////////////////////////////////////////////////////////////////////");
  v.push_back("");
  v.push_back("//choose_action_options are the option of the actions to be chosen");
  v.push_back("//and have the form [description],[benefit to group],[individual cost]");
  v.push_back("//for example:");
  v.push_back("//- choose_action_option=I want to contribute,2.0,1.0,You have chosen not to contribute");
  v.push_back("//- choose_action_option=I do not want to contribute,0.0,0.0,You have chosen not to contribute");
  v.push_back("choose_action_option=Contribute,2.0,1.0,You have chosen not to contribute");
  v.push_back("choose_action_option=Do not contribute,0.0,0.0,You have chosen not to contribute");
  v.push_back("");
  v.push_back("//Wait for all participants to choose an action?");
  v.push_back("//- y : yes");
  v.push_back("//- n : no, after choose_action_duration a random action is chosen");
  v.push_back("choose_action_wait=y");
  v.push_back("");
  v.push_back("//How long does the choose action state take in seconds?");
  v.push_back("//- any non-zero positive value: this time in seconsd");
  v.push_back("choose_action_duration=5");
  v.push_back("");
  v.push_back("///////////////////////////////////////////////////////////////////////////////");
  v.push_back("//Parameters for the individual payoff (IPGG cycle)                          //");
  v.push_back("///////////////////////////////////////////////////////////////////////////////");
  v.push_back("");
  v.push_back("//The message displayed to the participant");
  v.push_back("assign_payoff_message=Assigning payoffs");
  v.push_back("");
  v.push_back("///////////////////////////////////////////////////////////////////////////////");
  v.push_back("//Parameters for the view in-group results screen (period cycle)             //");
  v.push_back("///////////////////////////////////////////////////////////////////////////////");
  v.push_back("");
  v.push_back("//How long does the view results group state take in seconds?");
  v.push_back("view_results_group_duration=5");
  v.push_back("");
  v.push_back("//How many IPGG cycles are there?");
  v.push_back("//- x     : x cycles, for example '1'");
  v.push_back("//- ?w    : after every action there is a chance of w for another cycle,");
  v.push_back("//-         for example '0.8'");
  v.push_back("//- [a,b> : there are from a to (not including) b cycles, following a ");
  v.push_back("//-         uniform distribution, for example '[1,4>'");
  v.push_back("view_results_group_cycles=?0.8");
  v.push_back("");
  v.push_back("///////////////////////////////////////////////////////////////////////////////");
  v.push_back("//Parameters for the view all-group results screen (experiment cycle)        //");
  v.push_back("///////////////////////////////////////////////////////////////////////////////");
  v.push_back("");
  v.push_back("//How long does the view results group take in seconds?");
  v.push_back("group_reassign_duration=5");
  v.push_back("");
  v.push_back("//How much experimental cycles/periods are played?");
  v.push_back("group_reassign_number_of_periods=2");
  v.push_back("");
  v.push_back("//How much payoff is an active participant given for reaching the next period?");
  v.push_back("//This is a function of p, where p stands for his/her total accumulated payoff");
  v.push_back("//Examples:");
  v.push_back("//- 1.0");
  v.push_back("//- 1.0 + (0.01 * p)");
  v.push_back("//- 1.0 + (0.1 * p * p)");
  v.push_back("group_reassign_next_period_payoff_function=1.0 + (0.0 * p)");
  v.push_back("");
  v.push_back("///////////////////////////////////////////////////////////////////////////////");
  v.push_back("//Parameters for the finished experimenty screen (experiment cycle)          //");
  v.push_back("///////////////////////////////////////////////////////////////////////////////");
  v.push_back("");
  v.push_back("//The goodbye message on the finished screen");
  v.push_back("finished_message=The experiment has finished");
  v.push_back("");
  v.push_back("//How much money does the participant earn from his/her payoff?");
  v.push_back("//This is a function of p, where p stands for payoff");
  v.push_back("//Examples:");
  v.push_back("//- 1.0 + (0.01 * p)");
  v.push_back("//- 1.0 + (0.1 * p * p)");
  v.push_back("finished_earnings_function=1.0 + (0.01 * p)");
  v.push_back("");
  std::ofstream file("parameters6.txt");
  std::copy(v.begin(),v.end(),std::ostream_iterator<std::string>(file,"\n"));
}

void ribi::gtst::Test::CreateParameterFile7()
{
  std::vector<std::string> v;
  v.push_back("///////////////////////////////////////////////////////////////////////////////");
  v.push_back("//Default parameters file                                                    //");
  v.push_back("///////////////////////////////////////////////////////////////////////////////");
  v.push_back("");
  v.push_back("///////////////////////////////////////////////////////////////////////////////");
  v.push_back("//Parameters for participants                                                //");
  v.push_back("///////////////////////////////////////////////////////////////////////////////");
  v.push_back("//A participant has the following parameters");
  v.push_back("//- Initial group assigned to. Possible values:");
  v.push_back("//  - a positive value: the ID will assigned to group x");
  v.push_back("//- Chat tag");
  v.push_back("//  - a non-asterisk character: that character");
  v.push_back("//- IP address");
  v.push_back("//  - a valid IP address: this IP address is assigned to this ID");
  v.push_back("//  - *: any IP address is allowed");
  v.push_back("participant=1,*"); //0
  v.push_back("participant=1,*"); //1
  v.push_back("participant=1,*"); //2
  v.push_back("participant=2,*"); //3
  v.push_back("participant=2,*"); //4
  v.push_back("participant=2,*"); //5
  v.push_back("participant=3,*"); //6
  v.push_back("participant=3,*"); //7
  v.push_back("participant=3,*"); //8
  v.push_back("participant=4,*"); //9
  v.push_back("participant=4,*"); //10
  v.push_back("participant=4,*"); //11
  v.push_back("participant=?,*");
  v.push_back("participant=?,*");
  v.push_back("participant=?,*");
  v.push_back("participant=?,*");
  v.push_back("participant=?,*");
  v.push_back("participant=?,*");
  v.push_back("participant=?,*");
  v.push_back("participant=?,*");
  v.push_back("participant=?,*");
  v.push_back("participant=?,*");
  v.push_back("participant=?,*");
  v.push_back("participant=?,*");
  v.push_back("participant=?,*");
  v.push_back("participant=?,*");
  v.push_back("participant=?,*");
  v.push_back("participant=?,*");
  v.push_back("participant=?,*");
  v.push_back("participant=?,*");
  v.push_back("participant=?,*");
  v.push_back("participant=?,*");
  v.push_back("participant=?,*");
  v.push_back("participant=?,*");
  v.push_back("participant=?,*");
  v.push_back("participant=?,*");
  v.push_back("participant=?,*");
  v.push_back("participant=?,*");
  v.push_back("participant=?,*");
  v.push_back("participant=?,*");
  v.push_back("participant=?,*");
  v.push_back("participant=?,*");
  v.push_back("participant=?,*");
  v.push_back("participant=?,*");
  v.push_back("participant=?,*");
  v.push_back("participant=?,*");
  v.push_back("participant=?,*");
  v.push_back("participant=?,*");
  v.push_back("");
  v.push_back("///////////////////////////////////////////////////////////////////////////////");
  v.push_back("//Parameters for the group assignment phase (experiment cycle)               //");
  v.push_back("///////////////////////////////////////////////////////////////////////////////");
  v.push_back("");
  v.push_back("");
  v.push_back("//group_assign_message_assigned is the message displayed to an assigned participant");
  v.push_back("group_assign_message_assigned=You have been assigned to group #");
  v.push_back("");
  v.push_back("//group_assign_message_assigned is the message displayed to an assigned participant");
  v.push_back("group_assign_message_unassigned=You have not been assigned to a group yet");
  v.push_back("");
  v.push_back("//The function that determines how much payoff the waiting participant is rewarded");
  v.push_back("//for simply waiting, where p is the average payoff gathered by the active");
  v.push_back("//participants in the last period.");
  v.push_back("//Examples:");
  v.push_back("//- 1.0");
  v.push_back("//- 1.0 + (0.01 * p)");
  v.push_back("//- 1.0 + (0.1 * p * p)");
  v.push_back("group_assign_waiting_payoff_function=0.5 + (0.5 * p)");
  v.push_back("");
  v.push_back("///////////////////////////////////////////////////////////////////////////////");
  v.push_back("//Parameters for the chat phase (experiment cycle)                           //");
  v.push_back("///////////////////////////////////////////////////////////////////////////////");
  v.push_back("");
  v.push_back("");
  v.push_back("//How long does the chat state take in seconds?");
  v.push_back("chat_duration=10");
  v.push_back("");
  v.push_back("///////////////////////////////////////////////////////////////////////////////");
  v.push_back("//Parameters for the majority voting phase (experiment cycle)                //");
  v.push_back("///////////////////////////////////////////////////////////////////////////////");
  v.push_back("");
  v.push_back("//How long does the (majority) voting state take in seconds?");
  v.push_back("voting_duration=10");
  v.push_back("");
  v.push_back("//What can be voted for?");
  v.push_back("//Must be in the form of [description],[chance],[cost]");
  v.push_back("//For example:");
  v.push_back("//- voting_option=Lenient supervisor,0.5,1.0");
  v.push_back("//- voting_option=Rigorous supervisor,1.0,2.0");
  v.push_back("voting_option=rigorous supervisor,1.0,2.0");
  v.push_back("voting_option=lenient supervisor,0.5,1.0");
  v.push_back("voting_option=no supervisor,0.0,0.0");
  v.push_back("");
  v.push_back("//Wait for all participants to vote?");
  v.push_back("//- y : yes");
  v.push_back("//- n : no, after vote_duration a random vote is chosen");
  v.push_back("voting_wait=y");
  v.push_back("");
  v.push_back("///////////////////////////////////////////////////////////////////////////////");
  v.push_back("//Parameters for the majority voting results phase (experiment cycle)        //");
  v.push_back("///////////////////////////////////////////////////////////////////////////////");
  v.push_back("");
  v.push_back("");
  v.push_back("//How long does the majority voting results state take in seconds?");
  v.push_back("view_results_voting_duration=10");
  v.push_back("");
  v.push_back("///////////////////////////////////////////////////////////////////////////////");
  v.push_back("//Parameters for the choose action screen (IPGG cycle)                       //");
  v.push_back("///////////////////////////////////////////////////////////////////////////////");
  v.push_back("");
  v.push_back("//choose_action_options are the option of the actions to be chosen");
  v.push_back("//and have the form [description],[benefit to group],[individual cost]");
  v.push_back("//for example:");
  v.push_back("//- choose_action_option=I want to contribute,2.0,1.0,You have chosen not to contribute");
  v.push_back("//- choose_action_option=I do not want to contribute,0.0,0.0,You have chosen not to contribute");
  v.push_back("choose_action_option=Contribute,2.0,1.0,You have chosen not to contribute");
  v.push_back("choose_action_option=Do not contribute,0.0,0.0,You have chosen not to contribute");
  v.push_back("");
  v.push_back("//Wait for all participants to choose an action?");
  v.push_back("//- y : yes");
  v.push_back("//- n : no, after choose_action_duration a random action is chosen");
  v.push_back("choose_action_wait=y");
  v.push_back("");
  v.push_back("//How long does the choose action state take in seconds?");
  v.push_back("//- any non-zero positive value: this time in seconsd");
  v.push_back("choose_action_duration=10");
  v.push_back("");
  v.push_back("///////////////////////////////////////////////////////////////////////////////");
  v.push_back("//Parameters for the individual payoff (IPGG cycle)                          //");
  v.push_back("///////////////////////////////////////////////////////////////////////////////");
  v.push_back("");
  v.push_back("//The message displayed to the participant");
  v.push_back("assign_payoff_message=Assigning payoffs");
  v.push_back("");
  v.push_back("///////////////////////////////////////////////////////////////////////////////");
  v.push_back("//Parameters for the view in-group results screen (period cycle)             //");
  v.push_back("///////////////////////////////////////////////////////////////////////////////");
  v.push_back("");
  v.push_back("//How long does the view results group state take in seconds?");
  v.push_back("view_results_group_duration=10");
  v.push_back("");
  v.push_back("//How many IPGG cycles are there?");
  v.push_back("//- x     : x cycles, for example '1'");
  v.push_back("//- ?w    : after every action there is a chance of w for another cycle,");
  v.push_back("//-         for example '0.8'");
  v.push_back("//- [a,b> : there are from a to (not including) b cycles, following a ");
  v.push_back("//-         uniform distribution, for example '[1,4>'");
  v.push_back("view_results_group_cycles=?0.1");
  v.push_back("");
  v.push_back("///////////////////////////////////////////////////////////////////////////////");
  v.push_back("//Parameters for the view all-group results screen (experiment cycle)        //");
  v.push_back("///////////////////////////////////////////////////////////////////////////////");
  v.push_back("");
  v.push_back("//How long does the view results group take in seconds?");
  v.push_back("group_reassign_duration=10");
  v.push_back("");
  v.push_back("//How much experimental cycles/periods are played?");
  v.push_back("group_reassign_number_of_periods=10");
  v.push_back("");
  v.push_back("//How much payoff is an active participant given for reaching the next period?");
  v.push_back("//This is a function of p, where p stands for his/her total accumulated payoff");
  v.push_back("//Examples:");
  v.push_back("//- 1.0");
  v.push_back("//- 1.0 + (0.01 * p)");
  v.push_back("//- 1.0 + (0.1 * p * p)");
  v.push_back("group_reassign_next_period_payoff_function=1.0 + (0.0 * p)");
  v.push_back("");
  v.push_back("///////////////////////////////////////////////////////////////////////////////");
  v.push_back("//Parameters for the finished experimenty screen (experiment cycle)          //");
  v.push_back("///////////////////////////////////////////////////////////////////////////////");
  v.push_back("");
  v.push_back("//The goodbye message on the finished screen");
  v.push_back("finished_message=The experiment has finished");
  v.push_back("");
  v.push_back("//How much money does the participant earn from his/her payoff?");
  v.push_back("//This is a function of p, where p stands for payoff");
  v.push_back("//Examples:");
  v.push_back("//- 1.0 + (0.01 * p)");
  v.push_back("//- 1.0 + (0.1 * p * p)");
  v.push_back("finished_earnings_function=1.0 + (0.01 * p)");
  v.push_back("");
  std::ofstream file("parameters7.txt");
  std::copy(v.begin(),v.end(),std::ostream_iterator<std::string>(file,"\n"));
}

///Tests the parsing of the parameter files
void ribi::gtst::Test::TestParameterParsing()
{
  {
    CreateParameterFile1();
    boost::shared_ptr<Parameters> parameters(new Parameters(m_server));
    parameters->ReadFromFile("parameters1.txt");
    assert(parameters->GetParticipants().size() == 6);
    assert(parameters->GetAssignPayoff()->GetMessage() == "Ik ken nu de payoffs toe");
    assert(parameters->GetChat()->GetDuration() == 60);
    assert(parameters->GetChooseAction()->GetDuration() == 30);
    assert(parameters->GetChooseAction()->GetOptions().size() == 2);
    assert(parameters->GetChooseAction()->GetWait() == false);
    assert(parameters->GetFinished()->GetMessage() == "Klaar!");
    assert(parameters->GetFinished()->GetEarningsFunction() == "1.0 + (0.001 * p)");
    assert(parameters->GetGroupAssign()->GetMessageAssigned() == "U bent ingedeeld in groep #");
    assert(parameters->GetGroupAssign()->GetMessageUnassigned() == "U bent nog niet ingedeeld");
    assert(parameters->GetGroupAssign()->GetWaitingPayoffFunction() == "0.5 + (0.5 * p)");
    assert(parameters->GetGroupReAssign()->GetNextPeriodPayoffFunction() == "1.0 + (0.0 * p)");

    assert(parameters->GetViewResultsGroup()->GetDuration() == 30);
    assert(parameters->GetViewResultsGroup()->GetRepeatAssigner()->Assign() == 7);
    assert(parameters->GetViewResultsVoting()->GetDuration() == 30);
    assert(parameters->GetVoting()->GetDuration() == 60);
    #ifndef NDEBUG
    if(parameters->GetVoting()->GetOptions().size() != 3)
    {
      TRACE("ERROR");
      const auto sz = parameters->GetVoting()->GetOptions().size();
      for (const auto& v: parameters->GetVoting()->GetOptions())
      {
        TRACE(v->GetDescription());
      }
      TRACE(sz);
      TRACE("BREAK");
    }
    #endif //NDEBUG
    assert(parameters->GetVoting()->GetOptions().size() == 3);
    {
      std::vector<std::string> v;
      v.push_back("Mijn vriendin");
      v.push_back("Mijn moeder");
      v.push_back("Mijn oma");
      assert(parameters->GetVoting()->GetVoteDescriptions() == v);
    }
    assert(parameters->GetVoting()->GetWait() == false);
  }
  {
    CreateParameterFile2();
    boost::shared_ptr<Parameters> parameters(new Parameters(m_server));
    parameters->ReadFromFile("parameters2.txt");
    assert(parameters->GetParticipants().size() == 6);
    assert(parameters->GetAssignPayoff()->GetMessage() == "Assigning payoffs");
    assert(parameters->GetChat()->GetDuration() == 120);
    assert(parameters->GetChooseAction()->GetDuration() == 60);
    assert(parameters->GetChooseAction()->GetOptions().size() == 2);
    assert(parameters->GetChooseAction()->GetWait() == true);
    assert(parameters->GetFinished()->GetMessage() == "The experiment has finished");
    assert(parameters->GetGroupAssign()->GetMessageAssigned() == "You have been assigned to group #");
    assert(parameters->GetGroupAssign()->GetMessageUnassigned() == "You have not been assigned to a group yet");
    assert(parameters->GetGroupAssign()->GetWaitingPayoffFunction() == "0.5 + (0.5 * p)");
    assert(parameters->GetGroupReAssign()->GetNextPeriodPayoffFunction() == "1.0 + (0.0 * p)");
    assert(parameters->GetViewResultsGroup()->GetDuration() == 60);
    assert(parameters->GetViewResultsGroup()->GetRepeatAssigner()->Assign() == 3);
    assert(parameters->GetViewResultsVoting()->GetDuration() == 60);
    assert(parameters->GetVoting()->GetDuration() == 30);
    assert(parameters->GetVoting()->GetOptions().size() == 3);
    {
      std::vector<std::string> v;
      v.push_back("rigorous supervisor");
      v.push_back("lenient supervisor");
      v.push_back("no supervisor");
      assert(parameters->GetVoting()->GetVoteDescriptions() == v);
    }
    assert(parameters->GetVoting()->GetWait() == true);
  }
  {
    CreateParameterFile3();
    boost::shared_ptr<Parameters> parameters(new Parameters(m_server));
    parameters->ReadFromFile("parameters3.txt");
    std::vector<int> score(4,0);
    while (score[1] == 0 || score[2] == 0 || score[3] == 0)
    {
      const int n_repeats = parameters->GetViewResultsGroup()->GetRepeatAssigner()->Assign();
      assert(n_repeats != 0);
      assert(n_repeats <  4);
      ++score[n_repeats];
    }
    assert(parameters->GetChooseAction()->GetOptions().size() == 2);
    assert(parameters->GetGroupAssign()->GetWaitingPayoffFunction() == "0.5 + (0.5 * p)");
    assert(parameters->GetGroupReAssign()->GetNextPeriodPayoffFunction() == "1.0 + (0.0 * p)");
    assert(parameters->GetVoting()->GetOptions().size() == 3);
  }
  {
    CreateParameterFile4();
    boost::shared_ptr<Parameters> parameters(new Parameters(m_server));
    parameters->ReadFromFile("parameters4.txt");
    std::vector<int> score(5,0);
    while (score[1] == 0 || score[2] == 0 || score[3] == 0 || score[4] == 0)
    {
      const int n_repeats = parameters->GetViewResultsGroup()->GetRepeatAssigner()->Assign();
      assert(n_repeats != 0);
      if (n_repeats < 5) ++score[n_repeats];
    }
    assert(parameters->GetChooseAction()->GetOptions().size() == 2);
    assert(parameters->GetGroupAssign()->GetWaitingPayoffFunction() == "0.5 + (0.5 * p)");
    assert(parameters->GetGroupReAssign()->GetNextPeriodPayoffFunction() == "1.0 + (0.0 * p)");
    assert(parameters->GetVoting()->GetOptions().size() == 3);
  }

  {
    CreateParameterFile5();
    boost::shared_ptr<Parameters> parameters(new Parameters(m_server));
    parameters->ReadFromFile("parameters5.txt");
    assert(parameters->GetGroupAssign()->GetWaitingPayoffFunction() == "0.5 + (0.5 * p)");
    assert(parameters->GetGroupReAssign()->GetNextPeriodPayoffFunction() == "1.0 + (0.0 * p)");
    assert(parameters->GetVoting()->GetOptions().size() == 3);
  }

  {
    CreateParameterFile6();
    boost::shared_ptr<Parameters> parameters(new Parameters(m_server));
    parameters->ReadFromFile("parameters6.txt");
    assert(parameters->GetChooseAction()->GetOptions().size() == 2);
    assert(parameters->GetGroupAssign()->GetWaitingPayoffFunction() == "0.5 + (0.5 * p)");
    assert(parameters->GetGroupReAssign()->GetNextPeriodPayoffFunction() == "1.0 + (0.0 * p)");
    assert(parameters->GetVoting()->GetOptions().size() == 3);
  }
  {
    CreateParameterFile7();
    boost::shared_ptr<Parameters> parameters(new Parameters(m_server));
    parameters->ReadFromFile("parameters7.txt");
    assert(parameters->GetChooseAction()->GetOptions().size() == 2);
    assert(parameters->GetGroupAssign()->GetWaitingPayoffFunction() == "0.5 + (0.5 * p)");
    assert(parameters->GetGroupReAssign()->GetNextPeriodPayoffFunction() == "1.0 + (0.0 * p)");
    assert(parameters->GetVoting()->GetOptions().size() == 3);
  }
  ChatShapeFactory::Get()->Reset();
}

