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
#ifndef QTTESTMULTIPLECHOICEQUESTIONMAINDIALOG_H
#define QTTESTMULTIPLECHOICEQUESTIONMAINDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/scoped_ptr.hpp>
#include <boost/shared_ptr.hpp>

#include "qthideandshowdialog.h"
#pragma GCC diagnostic pop

namespace Ui {
  class QtTestMultipleChoiceQuestionMainDialog;
}

namespace ribi {

struct TestMultipleChoiceQuestionMainDialog;
struct QtMultipleChoiceQuestionDialog;

class QtTestMultipleChoiceQuestionMainDialog : public QtHideAndShowDialog
{
  Q_OBJECT

public:
  explicit QtTestMultipleChoiceQuestionMainDialog(QWidget *parent = 0);
  QtTestMultipleChoiceQuestionMainDialog(const QtTestMultipleChoiceQuestionMainDialog&) = delete;
  QtTestMultipleChoiceQuestionMainDialog& operator=(const QtTestMultipleChoiceQuestionMainDialog&) = delete;
  ~QtTestMultipleChoiceQuestionMainDialog() noexcept;
  const boost::shared_ptr<const QtMultipleChoiceQuestionDialog> GetDialog() const { return m_dialog; }
  void SetQuestion(const std::string& s);

protected:
  void keyPressEvent(QKeyEvent* event);

private slots:
  void on_edit_question_textChanged(const QString &arg1);

private:
  Ui::QtTestMultipleChoiceQuestionMainDialog *ui;
  boost::shared_ptr<QtMultipleChoiceQuestionDialog> m_dialog;

  static boost::shared_ptr<QtMultipleChoiceQuestionDialog> CreateQtMultipleChoiceQuestionDialog(const std::string& s);

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace ribi

#endif // QTTESTMULTIPLECHOICEQUESTIONMAINDIALOG_H
