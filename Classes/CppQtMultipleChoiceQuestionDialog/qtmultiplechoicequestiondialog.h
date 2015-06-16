//---------------------------------------------------------------------------
/*
QtMultipleChoiceQuestionDialog, Qt dialog for MultipleChoiceQuestion
Copyright (C) 2011-2015 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/QtMultipleChoiceQuestionDialog.htm
//---------------------------------------------------------------------------
#ifndef QTMULTIPLECHOICEQUESTIONDIALOG_H
#define QTMULTIPLECHOICEQUESTIONDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/scoped_ptr.hpp>
#include <boost/shared_ptr.hpp>

#include "qthideandshowdialog.h"

#include "questiondialog.h"
#include "qtquestiondialog.h"
#pragma GCC diagnostic pop


namespace Ui {
  class QtMultipleChoiceQuestionDialog;
}

namespace ribi {

struct Question;
struct MultipleChoiceQuestion;
struct MultipleChoiceQuestionDialog;

class QtMultipleChoiceQuestionDialog : public QtQuestionDialog
{
  Q_OBJECT

public:
  explicit QtMultipleChoiceQuestionDialog(
    QWidget *parent = 0);

  QtMultipleChoiceQuestionDialog(
    const boost::shared_ptr<MultipleChoiceQuestionDialog>& dialog,
    QWidget *parent = 0);
  QtMultipleChoiceQuestionDialog(const QtMultipleChoiceQuestionDialog&) = delete;
  QtMultipleChoiceQuestionDialog& operator=(const QtMultipleChoiceQuestionDialog&) = delete;

  ~QtMultipleChoiceQuestionDialog() noexcept;

  boost::shared_ptr<const QuestionDialog> GetDialog() const;

  ///Obtain the version of this class
  static std::string GetVersion() noexcept;

  ///Obtain the version history of this class
  static std::vector<std::string> GetVersionHistory() noexcept;

  void SetDialog(const boost::shared_ptr<QuestionDialog>& dialog);

private slots:
  void on_button_submit_clicked() noexcept;

private:
  Ui::QtMultipleChoiceQuestionDialog *ui;
  boost::shared_ptr<MultipleChoiceQuestionDialog> m_dialog;

  ///Set the Question
  //void SetQuestion(const boost::shared_ptr<const MultipleChoiceQuestion>& question) noexcept;

  void OnMultipleChoiceQuestionDialogChanged(MultipleChoiceQuestionDialog * const mc_question_dialog) noexcept;
  void OnMultipleChoiceQuestionChanged(const boost::shared_ptr<MultipleChoiceQuestionDialog>& mc_question) noexcept;

};

} //~namespace ribi

#endif // QTMULTIPLECHOICEQUESTIONDIALOG_H
