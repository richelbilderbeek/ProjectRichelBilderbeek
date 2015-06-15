
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

#ifndef PROJECTGTSTPARAMETERSQUIZ_H
#define PROJECTGTSTPARAMETERSQUIZ_H

#include <iosfwd>
#include <string>
#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/checked_delete.hpp>

#include <boost/shared_ptr.hpp>

#include "gtstforward_declarations.h"
#pragma GCC diagnostic pop

namespace ribi {
namespace gtst {

///\brief
///Parameters for the voting state
struct ParametersQuiz
{
  ParametersQuiz();

  ///Get the duration of the ServerState (in seconds)
  int GetDuration() const;

  ///GetNumberOfOptions returns the number of options to vote for
  //int GetNumberOfOptions() const;

  ///Get all options to vote for
  //const std::vector<boost::shared_ptr<QuizOption> >& GetOptions() const { return m_options; }

  ///Get the descriptions of the options to vote for only
  std::vector<std::string> GetVoteDescriptions() const;

  ///Does the ServerState and ParticipantDialog wait for all?
  bool GetWait() const { return m_wait; }

  ///Parse a line
  void Parse(const std::string& s);

  ///Set the duration of the ServerState (in seconds)
  void SetDuration(const int time);

  ///Set the descriptions of the voting options
  //void SetOptions(const std::vector<boost::shared_ptr<QuizOption> >& options);

  ///Set if there is waited for all before going on
  void SetWait(const bool wait);

  private:
  ~ParametersQuiz() {}
  friend void boost::checked_delete<>(ParametersQuiz*);

  ///Time that is allowed in this phase, or that is indicated to be enough
  int m_duration;

  ///The descriptions of the voting options
  //std::vector<boost::shared_ptr<QuizOption> > m_options;

  ///Wait for all before going on?
  ///-true: After voting, Participant has to wait until all have
  ///-false: after m_time seconds, an automatic random vote is made for the Participant
  bool m_wait;

  //static const std::vector<boost::shared_ptr<QuizOption> > CreateDefaultOptions();

  ///SeperateString splits a std::string
  const std::vector<std::string> SeperateString(
    const std::string& input,
    const char seperator);

};

std::ostream& operator<<(std::ostream& os,const ParametersQuiz& parameters);

} //~namespace gtst
} //~namespace ribi

#endif // PARAMETERSQUIZ_H
