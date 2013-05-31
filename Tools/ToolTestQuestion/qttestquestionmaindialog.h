//---------------------------------------------------------------------------
/*
TestQuestion, tool to test the Question and QuestionDialog classes
Copyright (C) 2011-2012 Richel Bilderbeek

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
#ifndef QTTESTQUESTIONMAINDIALOG_H
#define QTTESTQUESTIONMAINDIALOG_H

#include <boost/scoped_ptr.hpp>
#include <boost/shared_ptr.hpp>

#include "qthideandshowdialog.h"

namespace Ui {
  class QtTestQuestionMainDialog;
}
struct TestQuestionMainDialog;
struct QtQuestionDialog;

class QtTestQuestionMainDialog : public QtHideAndShowDialog
{
  Q_OBJECT

public:
  explicit QtTestQuestionMainDialog(QWidget *parent = 0);
  ~QtTestQuestionMainDialog();

protected:
  void changeEvent(QEvent *e);
  void keyPressEvent(QKeyEvent* event);

private:
  Ui::QtTestQuestionMainDialog *ui;
  boost::scoped_ptr<TestQuestionMainDialog> m_dialog;
  std::vector<boost::shared_ptr<QtQuestionDialog> > m_dialogs;

  void OnSubmit();
};

#endif // QTTESTQUESTIONMAINDIALOG_H
