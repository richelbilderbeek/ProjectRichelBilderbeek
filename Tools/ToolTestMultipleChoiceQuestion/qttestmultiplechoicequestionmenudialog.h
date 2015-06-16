//---------------------------------------------------------------------------
/*
TestMultipleChoiceQuestion, tests multiple choice question classes
Copyright (C) 2013-2015 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/ToolTestMultipleChoiceQuestion.htm
//---------------------------------------------------------------------------
#ifndef QTTESTMULTIPLECHOICEQUESTIONMENUDIALOG_H
#define QTTESTMULTIPLECHOICEQUESTIONMENUDIALOG_H

#include <boost/scoped_ptr.hpp>

#include "qthideandshowdialog.h"

namespace Ui {
  class QtTestMultipleChoiceQuestionMenuDialog;
}

namespace ribi {

struct TestMultipleChoiceQuestionMenuDialog;

class QtTestMultipleChoiceQuestionMenuDialog : public QtHideAndShowDialog
{
  Q_OBJECT

public:
  explicit QtTestMultipleChoiceQuestionMenuDialog(QWidget *parent = 0);
  QtTestMultipleChoiceQuestionMenuDialog(const QtTestMultipleChoiceQuestionMenuDialog&) = delete;
  QtTestMultipleChoiceQuestionMenuDialog& operator=(const QtTestMultipleChoiceQuestionMenuDialog&) = delete;
  ~QtTestMultipleChoiceQuestionMenuDialog() noexcept;

protected:
  void keyPressEvent(QKeyEvent* event);

private slots:
  void on_button_start_clicked();
  void on_button_about_clicked();
  void on_button_quit_clicked();

private:
  Ui::QtTestMultipleChoiceQuestionMenuDialog *ui;
  boost::scoped_ptr<TestMultipleChoiceQuestionMenuDialog> m_dialog;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace ribi

#endif // QTTESTMULTIPLECHOICEQUESTIONMENUDIALOG_H
