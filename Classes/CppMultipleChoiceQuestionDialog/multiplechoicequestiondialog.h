//---------------------------------------------------------------------------
/*
MultipleChoiceQuestionDialog, dialog for MultipleChoiceQuestion
Copyright (C) 2011 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/CppMultipleChoiceQuestionDialog.htm
//---------------------------------------------------------------------------
#ifndef MULTIPLECHOICEQUESTIONDIALOG_H
#define MULTIPLECHOICEQUESTIONDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include <boost/shared_ptr.hpp>
#include "questiondialog.h"
#pragma GCC diagnostic pop

namespace ribi {

struct MultipleChoiceQuestion;

struct MultipleChoiceQuestionDialog : public QuestionDialog
{
  explicit MultipleChoiceQuestionDialog(
    const boost::shared_ptr<const MultipleChoiceQuestion>& question
    = CreateDefaultQuestion());

  explicit MultipleChoiceQuestionDialog(const std::string& question);

  ///Obtain the version
  static const std::string GetVersion() noexcept;

  ///Obtain the version history
  static const std::vector<std::string> GetVersionHistory() noexcept;

  private:
  friend void boost::checked_delete<>(MultipleChoiceQuestionDialog *);
  ~MultipleChoiceQuestionDialog() noexcept {}

  ///Create a default Question
  //static MultipleChoiceQuestion * CreateDefaultQuestion();
  static boost::shared_ptr<MultipleChoiceQuestion> CreateDefaultQuestion() noexcept;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace ribi

#endif // MULTIPLECHOICEQUESTIONDIALOG_H
