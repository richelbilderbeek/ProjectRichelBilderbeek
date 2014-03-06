//---------------------------------------------------------------------------
/*
OpenQuestionDialog, dialog for OpenQuestion
Copyright (C) 2011-2014 Richel Bilderbeek

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program.If not, see <http://www.gnu.org/licenses/>.
*/
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/CppOpenQuestionDialog.htm
//---------------------------------------------------------------------------
#ifndef OPENQUESTIONDIALOG_H
#define OPENQUESTIONDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include <boost/shared_ptr.hpp>
#include "questiondialog.h"
#pragma GCC diagnostic pop

namespace ribi {

struct Question;
struct OpenQuestion;

///Dialog for an OpenQuestion
struct OpenQuestionDialog : public QuestionDialog
{
  explicit OpenQuestionDialog(const std::string& question);
  explicit OpenQuestionDialog(const boost::shared_ptr<const OpenQuestion>& question);

  const boost::shared_ptr<const OpenQuestion> GetOpenQuestion() const { return m_question; }

  const boost::shared_ptr<const Question> GetQuestion() const;

  ///Obtain the version
  static const std::string GetVersion() noexcept;

  ///Obtain the version history
  static std::vector<std::string> GetVersionHistory() noexcept;

  ///Submit an answer
  ///For an open question, s will be the anwer
  void Submit(const std::string& s);

  private:
  friend void boost::checked_delete<>(OpenQuestionDialog*);
  ~OpenQuestionDialog() noexcept {}

  const boost::shared_ptr<const OpenQuestion> m_question;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace ribi

#endif // OPENQUESTIONDIALOG_H
