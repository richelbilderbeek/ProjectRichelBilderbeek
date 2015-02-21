//---------------------------------------------------------------------------
/*
TestOpenQuestion, tool to test the OpenQuestion and OpenQuestionDialog classes
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
//From http://www.richelbilderbeek.nl/ToolTestOpenQuestion.htm
//---------------------------------------------------------------------------
#ifndef QTTESTOPENQUESTIONMAINDIALOG_H
#define QTTESTOPENQUESTIONMAINDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/scoped_ptr.hpp>
#include <boost/shared_ptr.hpp>

#include "qthideandshowdialog.h"
#pragma GCC diagnostic pop

namespace Ui {
  class QtTestOpenQuestionMainDialog;
}

namespace ribi {

struct TestOpenQuestionMainDialog;
struct QtOpenQuestionDialog;
struct OpenQuestionDialog;

class QtTestOpenQuestionMainDialog : public QtHideAndShowDialog
{
  Q_OBJECT

public:
  explicit QtTestOpenQuestionMainDialog(QWidget *parent = 0);
  QtTestOpenQuestionMainDialog(const QtTestOpenQuestionMainDialog&) = delete;
  QtTestOpenQuestionMainDialog& operator=(const QtTestOpenQuestionMainDialog&) = delete;
  ~QtTestOpenQuestionMainDialog() noexcept;
  const boost::shared_ptr<const QtOpenQuestionDialog> GetDialog() const { return m_dialog_1; }
  void SetQuestion(const std::string& s);

protected:
  void keyPressEvent(QKeyEvent* event);

private slots:
  void on_edit_question_textChanged(const QString &arg1);

private:
  Ui::QtTestOpenQuestionMainDialog *ui;
  boost::shared_ptr<QtOpenQuestionDialog> m_dialog_1;
  boost::shared_ptr<QtOpenQuestionDialog> m_dialog_2;

  static boost::shared_ptr<OpenQuestionDialog> CreateOpenQuestionDialog(const std::string& s);

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace ribi

#endif // QTTESTOPENQUESTIONMAINDIALOG_H
