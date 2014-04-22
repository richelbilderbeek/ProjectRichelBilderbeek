//---------------------------------------------------------------------------
/*
WtOpenQuestionDialog, Wt dialog for OpenQuestionDialog
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
//From http://www.richelbilderbeek.nl/CppWtOpenQuestionDialog.htm
//---------------------------------------------------------------------------
#ifndef WTOPENQUESTIONDIALOG_H
#define WTOPENQUESTIONDIALOG_H

#include <boost/scoped_ptr.hpp>
#include <boost/shared_ptr.hpp>

#include "wtquestiondialog.h"

namespace Wt
{
  struct WLineEdit;
  struct WStackedWidget;
}


namespace ribi {

struct Question;
struct OpenQuestion;
struct OpenQuestionDialog;

struct WtOpenQuestionDialog : public WtQuestionDialog
{
  explicit WtOpenQuestionDialog(const std::string& question);

  explicit WtOpenQuestionDialog(const boost::shared_ptr<QuestionDialog>& dialog);

  const boost::shared_ptr<const QuestionDialog> GetDialog() const noexcept;
  const boost::shared_ptr<const OpenQuestionDialog> GetOpenQuestionDialog() const noexcept;

  static const std::string GetVersion();
  static const std::vector<std::string> GetVersionHistory();

private:

  struct Ui
  {
    Ui();
    Wt::WPushButton * const m_button_submit;
    Wt::WLineEdit * const m_edit_answer;
    Wt::WStackedWidget * const m_stacked_widget;
  } m_ui;

  boost::shared_ptr<OpenQuestionDialog> m_dialog;

  ///Set the Question
  void SetQuestion(const boost::shared_ptr<const Question> question);

  void OnButtonSubmitClicked();
};

} //~namespace ribi

#endif // WTOPENQUESTIONDIALOG_H
