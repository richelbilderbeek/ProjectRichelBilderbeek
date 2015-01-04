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
#ifndef QTTESTOPENQUESTIONMENUDIALOG_H
#define QTTESTOPENQUESTIONMENUDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/scoped_ptr.hpp>

#include "qthideandshowdialog.h"
#pragma GCC diagnostic pop

namespace Ui {
  class QtTestOpenQuestionMenuDialog;
}

namespace ribi {

struct TestOpenQuestionMenuDialog;

class QtTestOpenQuestionMenuDialog : public QtHideAndShowDialog
{
  Q_OBJECT

public:
  explicit QtTestOpenQuestionMenuDialog(QWidget *parent = 0);
  QtTestOpenQuestionMenuDialog(const QtTestOpenQuestionMenuDialog&) = delete;
  QtTestOpenQuestionMenuDialog& operator=(const QtTestOpenQuestionMenuDialog&) = delete;
  ~QtTestOpenQuestionMenuDialog() noexcept;

protected:
  void keyPressEvent(QKeyEvent* event);

private slots:
  void on_button_start_clicked();
  void on_button_about_clicked();
  void on_button_quit_clicked();

private:
  Ui::QtTestOpenQuestionMenuDialog *ui;
  boost::scoped_ptr<TestOpenQuestionMenuDialog> m_dialog;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace ribi

#endif // QTTESTOPENQUESTIONMENUDIALOG_H
