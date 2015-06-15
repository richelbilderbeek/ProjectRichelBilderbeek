//---------------------------------------------------------------------------
/*
WtMultipleChoiceQuestionDialog, Wt dialog for MultipleChoiceQuestion
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
//From http://www.richelbilderbeek.nl/CppWtMultipleChoiceQuestionDialog.htm
//---------------------------------------------------------------------------
#ifndef WTMULTIPLECHOICEQUESTIONDIALOG_H
#define WTMULTIPLECHOICEQUESTIONDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-variable"
#include <boost/scoped_ptr.hpp>
#include <boost/shared_ptr.hpp>

#include "wtquestiondialog.h"
#pragma GCC diagnostic pop

namespace ribi {

struct Question;
struct MultipleChoiceQuestion;
struct MultipleChoiceQuestionDialog;

struct WtMultipleChoiceQuestionDialog : public WtQuestionDialog
{
  explicit WtMultipleChoiceQuestionDialog(const std::string& question);

  explicit WtMultipleChoiceQuestionDialog(const boost::shared_ptr<MultipleChoiceQuestionDialog>& dialog);

  boost::shared_ptr<const QuestionDialog> GetDialog() const noexcept;
  boost::shared_ptr<const MultipleChoiceQuestionDialog> GetMultipleChoiceQuestionDialog() const noexcept;


  ///Obtain the version of this class
  static std::string GetVersion();

  ///Obtain the version history of this class
  static std::vector<std::string> GetVersionHistory();

  ///Sets the selected radio button index
  void SetSelectedRadioButton(const int index);

private:
  struct Ui
  {
    Ui();
    Ui(const Ui&) = delete;
    Ui& operator=(const Ui&) = delete;

    Wt::WPushButton * const m_button_submit;
    std::vector<Wt::WRadioButton*> m_radio_buttons;
    Wt::WStackedWidget * const m_stacked_widget;
  } m_ui;

  boost::shared_ptr<MultipleChoiceQuestionDialog> m_dialog;

  ///Respond to a click on the Submit button
  void OnButtonSubmitClicked();

  ///Create the page
  void Show();
};

} //~namespace ribi

#endif // WTMULTIPLECHOICEQUESTIONDIALOG_H
