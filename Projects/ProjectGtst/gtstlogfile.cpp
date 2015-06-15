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
#include <fstream>
#include <iostream>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/date_time/gregorian/gregorian.hpp>

#include "gtstall_parameters.h"
#include "gtstchatmessage.h"
#include "gtstchooseactionoption.h"
#include "gtstgroup.h"
#include "gtstlogfile.h"
#include "gtststate.h"
#include "gtstparticipant.h"
#include "gtstparticipantdialogstate.h"
#include "gtstpayoff.h"
#include "gtstpayoffs.h"
#include "stopwatch.h"
#include "gtstserverstate.h"
#include "gtstvotingoption.h"
#pragma GCC diagnostic pop

ribi::gtst::LogFile::LogFile()
  : m_log_filename("log" + GetTimestamp() + ".xml")
{
  //std::ofstream f(m_log_filename.c_str());
  //f
  //  << "‭<?xml version=\"1.0\" encoding=\"utf-8\"?>"
  //  << "‭<logfile name=\"gtst\" xml:lang=\"en\">";

}

ribi::gtst::LogFile::~LogFile()
{
  //std::ofstream f(m_log_filename.c_str(),std::ios::app);
  //f << "‎</logfile>";
}

/*
void ribi::gtst::LogFile::ClearLogFile()
{
  //Clear log file
  {
    std::ofstream f(m_log_filename.c_str());
    std::string t = GetTime();
    assert(!t.empty());
    //Pop back trailing newlines
    while (t[t.size() -1] == '\n')
    {
      assert(t.size() >= 1);
      t.resize(t.size() -1);
    }

    f << "<START>" << t << "</START>\n";
  }
}
*/

///Returns date in YYYY-MM-DD format
//From http://www.richelbilderbeek.nl/CppGetDateIso8601.htm
std::string ribi::gtst::LogFile::GetDateIso8601()
{
  const boost::gregorian::date today
    = boost::gregorian::day_clock::local_day();
  const std::string s
    = boost::gregorian::to_iso_extended_string(today);
  assert(s.size()==10);
  assert(s[4]=='-');
  assert(s[7]=='-');
  return s;
}

///Get the current time
//From http://www.richelbilderbeek.nl/CppGetTime.htm
std::string ribi::gtst::LogFile::GetTime()
{
  //Get the local time
  boost::posix_time::ptime now
    = boost::posix_time::second_clock::local_time();
  //Convert the time to std::stringstream
  std::stringstream s;
  s << now.time_of_day();
  //Return the std::string
  return s.str();
}

///Returns the current date and time as a YYYY_MM_DD_HH_MM_SS std::string,
///for example '2011_07_01_11_35_38'
//From http://www.richelbilderbeek.nl/CppGetTimestamp.htm
std::string ribi::gtst::LogFile::GetTimestamp()
{
  std::string s = GetDateIso8601() + '_' + GetTime();
  std::replace(s.begin(),s.end(),':','_');
  std::replace(s.begin(),s.end(),'-','_');
  return s;
}

void ribi::gtst::LogFile::LogAction(const boost::shared_ptr<const Participant>& participant)
{
  assert(participant->CanGetId());
  assert(!participant->GetActions().empty());
  std::ofstream f(m_log_filename.c_str(),std::ios::app);
  f << "<choose_action>"
    << "<time>"
    << GetTime()
    << "</time>"
    << "<id>"
    << participant->GetId()
    << "</id>"
    << "<action>"
    << *participant->GetActions().back()
    << "</action>"
    << "</choose_action>\n";
}

void ribi::gtst::LogFile::LogAssignGroup(
  const Group * const group,
  const boost::shared_ptr<const Participant>& participant)
{
  assert(group);
  assert(participant);


  std::ofstream f(m_log_filename.c_str(),std::ios::app);
  f << "<assign_group>"
    << "<time>"
    << GetTime()
    << "</time>"
    << "<id>"
    << (participant->CanGetId()
      ? std::to_string(participant->GetId())
      : std::string("unassigned"))
    << "</id>"
    << "<group>"
    << group->GetId()
    << "</group>"
    << "</assign_group>\n";
}

void ribi::gtst::LogFile::LogAssignPayoff(const boost::shared_ptr<const Participant>& participant)
{
  std::ofstream f(m_log_filename.c_str(),std::ios::app);
  f
    << "<assign_payoff>"
    << "<time>"
    << GetTime()
    << "</time>"
    << "<participant>"
    << "<id>"
    << participant->GetId() //Only log the Participant his/her ID
    << "</id>"
    << "</participant>"
    << *participant->GetPayoffs()->GetLast()
    << "</assign_payoff>\n";
}

void ribi::gtst::LogFile::LogExperimentStateChanged(const ServerState* new_state)
{
  std::ofstream f(m_log_filename.c_str(),std::ios::app);
  f
    << "<experimentstate_change>"
    << "<time>"
    << GetTime()
    << "</time>"
    << "<new_period>"
    << new_state->GetPeriod()
    << "</new_period>"
    << "<new_cycle>"
    << new_state->GetCycle()
    << "</new_cycle>"
    << "<new_state>"
    << new_state->ToStr()
    << "</new_state>"
    << "</experimentstate_change>\n";
}

void ribi::gtst::LogFile::Login(const boost::shared_ptr<const Participant>& participant)
{
  std::ofstream f(m_log_filename.c_str(),std::ios::app);
  f
    << "<login>"
    << "<time>"
    << GetTime()
    << "</time>"
    << (*participant)
    << "</login>\n";
}

void ribi::gtst::LogFile::Logout(const boost::shared_ptr<const Participant>& participant)
{
  std::ofstream f(m_log_filename.c_str(),std::ios::app);
  f
    << "<logout>"
    << "<time>"
    << GetTime()
    << "</time>"
    << (*participant)
    << "</logout>\n";
}

void ribi::gtst::LogFile::LogReAssignPayoff(const boost::shared_ptr<const Participant>& participant)
{
  std::ofstream f(m_log_filename.c_str(),std::ios::app);
  f
    << "<reassign_payoff>"
    << "<time>"
    << GetTime()
    << "</time>"
    << "<participant>"
    << "<id>"
    << participant->GetId() //Only log the Participant his/her ID
    << "</id>"
    << "</participant>"
    << *participant->GetPayoffs()->GetLast()
    << "</reassign_payoff>\n";
}

void ribi::gtst::LogFile::LogRemoveParticipant(
  const Group * const group,
  const boost::shared_ptr<const Participant>& participant)
{
  assert(group);
  assert(participant);
  assert(participant->CanGetId());

  std::ofstream f(m_log_filename.c_str(),std::ios::app);
  f << "<remove_participant>"
    << "<time>"
    << GetTime()
    << "</time>"
    << "<id>"
    << participant->GetId()
    << "</id>"
    << "<old_group>"
    << group->GetId()
    << "</old_group>"
    << "</remove_participant>\n";
}

void ribi::gtst::LogFile::LogVote(const boost::shared_ptr<const Participant>& participant)
{
  assert(participant->CanGetId());
  assert(!participant->GetVotes().empty());
  std::ofstream f(m_log_filename.c_str(),std::ios::app);
  f << "<vote>"
    << "<time>"
    << GetTime()
    << "</time>"
    << "<id>"
    << participant->GetId()
    << "</id>"
    << "<voting_option>"
    << *participant->GetVotes().back()
    << "</voting_option>"
    << "</vote>\n";
}

void ribi::gtst::LogFile::LogParameters(boost::shared_ptr<Parameters> parameters)
{
  std::ofstream f(m_log_filename.c_str(),std::ios::app);
  f
    << "<set_parameters>"
    << "<time>"
    << GetTime()
    << "</time>"
    << (*parameters.get())
    << "</set_parameters>\n";
}

void ribi::gtst::LogFile::LogParticipantDialogStateChanged(const ParticipantDialogState* const new_state)
{
  std::ofstream f(m_log_filename.c_str(),std::ios::app);

  f
    << "<participantdialogstate_change>"
    << "<time>"
    << GetTime()
    << "</time>"
    << new_state->ToStr()
    << "</participantdialogstate_change>\n";
}

void ribi::gtst::LogFile::LogChatMessage(
  const boost::shared_ptr<const Participant>& participant,
  const boost::shared_ptr<ChatMessage>& message)
{
  assert(participant);
  std::ofstream f(m_log_filename.c_str(),std::ios::app);
  f
    << "<chat>"
    << "<time>"
    << GetTime()
    << "</time>"
    << "<participant_id>"
    << participant->GetId()
    << "</participant_id>"
    << (*message)
    << "</chat>\n";
}

std::ostream& ribi::gtst::operator<<(std::ostream& os,const LogFile& logfile)
{
  os
    << "<logfile>"
    << "<log_filename>"
    << logfile.m_log_filename
    << "</log_filename>"
    << "</logfile>";
  return os;
}

