//---------------------------------------------------------------------------
/*
TestQuestion, tool to test the Question and QuestionDialog classes
Copyright (C) 2011-2015 Richel Bilderbeek

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

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include <boost/scoped_ptr.hpp>
#include <boost/shared_ptr.hpp>
#include "qthideandshowdialog.h"
#pragma GCC diagnostic pop

namespace Ui {
  class QtTestQuestionMainDialog;
}

namespace ribi {

struct TestQuestionMainDialog;
struct QtQuestionDialog;

class QtTestQuestionMainDialog : public QtHideAndShowDialog
{
  Q_OBJECT

public:
  explicit QtTestQuestionMainDialog(QWidget *parent = 0);
  QtTestQuestionMainDialog(const QtTestQuestionMainDialog&) = delete;
  QtTestQuestionMainDialog& operator=(const QtTestQuestionMainDialog&) = delete;
  ~QtTestQuestionMainDialog() noexcept;

  const boost::shared_ptr<const QtQuestionDialog> GetDialog() const { return m_dialog; }
  void SetQuestion(const std::string& s);

protected:
  void keyPressEvent(QKeyEvent* event);

private slots:
  void on_edit_question_textChanged(const QString &arg1);

private:
  Ui::QtTestQuestionMainDialog *ui;
  boost::shared_ptr<QtQuestionDialog> m_dialog;

  static boost::shared_ptr<QtQuestionDialog> CreateQtQuestionDialog(const std::string& s);

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace ribi

#endif // QTTESTQUESTIONMAINDIALOG_H
