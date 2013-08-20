//---------------------------------------------------------------------------
/*
TestQuestion, tool to test the Question and QuestionDialog classes
Copyright (C) 2011-2013 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/ToolTestQuestion.htm
//---------------------------------------------------------------------------
#ifndef QTTESTQUESTIONMENUDIALOG_H
#define QTTESTQUESTIONMENUDIALOG_H

#include <boost/scoped_ptr.hpp>

#include "qthideandshowdialog.h"

namespace Ui {
class QtTestQuestionMenuDialog;
}
struct TestQuestionMenuDialog;

class QtTestQuestionMenuDialog : public QtHideAndShowDialog
{
  Q_OBJECT

public:
  explicit QtTestQuestionMenuDialog(QWidget *parent = 0);
  ~QtTestQuestionMenuDialog();

protected:
  void keyPressEvent(QKeyEvent* event);

private slots:
  void on_button_start_clicked();
  void on_button_about_clicked();
  void on_button_quit_clicked();

private:
  Ui::QtTestQuestionMenuDialog *ui;
  boost::scoped_ptr<TestQuestionMenuDialog> m_dialog;

  #ifndef NDEBUG
  static void Test();
  #endif
};

#endif // QTTESTQUESTIONMENUDIALOG_H
