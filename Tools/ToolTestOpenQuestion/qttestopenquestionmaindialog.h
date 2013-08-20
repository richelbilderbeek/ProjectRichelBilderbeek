//---------------------------------------------------------------------------
/*
TestOpenQuestion, tool to test the OpenQuestion and OpenQuestionDialog classes
Copyright (C) 2013 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/ToolTestOpenQuestion.htm
//---------------------------------------------------------------------------
#ifndef QTTESTOPENQUESTIONMAINDIALOG_H
#define QTTESTOPENQUESTIONMAINDIALOG_H

#include <boost/scoped_ptr.hpp>
#include <boost/shared_ptr.hpp>

#include "qthideandshowdialog.h"

namespace Ui {
  class QtTestOpenQuestionMainDialog;
}
struct TestOpenQuestionMainDialog;
struct QtOpenQuestionDialog;

class QtTestOpenQuestionMainDialog : public QtHideAndShowDialog
{
  Q_OBJECT

public:
  explicit QtTestOpenQuestionMainDialog(QWidget *parent = 0);
  ~QtTestOpenQuestionMainDialog();
  const boost::shared_ptr<const QtOpenQuestionDialog> GetDialog() const { return m_dialog; }
  void SetQuestion(const std::string& s);

protected:
  void keyPressEvent(QKeyEvent* event);

private slots:
  void on_edit_question_textChanged(const QString &arg1);

private:
  Ui::QtTestOpenQuestionMainDialog *ui;
  boost::shared_ptr<QtOpenQuestionDialog> m_dialog;

  static boost::shared_ptr<QtOpenQuestionDialog> CreateQtOpenQuestionDialog(const std::string& s);

  #ifndef NDEBUG
  static void Test();
  #endif
};

#endif // QTTESTOPENQUESTIONMAINDIALOG_H
