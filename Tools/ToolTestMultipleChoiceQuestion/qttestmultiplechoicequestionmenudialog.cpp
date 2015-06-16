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
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "qttestmultiplechoicequestionmenudialog.h"

#include <QKeyEvent>

#include "about.h"
#include "qtaboutdialog.h"
#include "qthideandshowdialog.h"
#include "qtmultiplechoicequestiondialog.h"
#include "qtquestiondialog.h"
#include "qttestmultiplechoicequestionmaindialog.h"
#include "questiondialog.h"
#include "testmultiplechoicequestionmenudialog.h"
#include "trace.h"
#include "ui_qttestmultiplechoicequestionmenudialog.h"
#pragma GCC diagnostic pop

ribi::QtTestMultipleChoiceQuestionMenuDialog::QtTestMultipleChoiceQuestionMenuDialog(QWidget *parent) :
  QtHideAndShowDialog(parent),
  ui(new Ui::QtTestMultipleChoiceQuestionMenuDialog),
  m_dialog(new TestMultipleChoiceQuestionMenuDialog)
{
  #ifndef NDEBUG
  Test();
  #endif
  ui->setupUi(this);
}

ribi::QtTestMultipleChoiceQuestionMenuDialog::~QtTestMultipleChoiceQuestionMenuDialog() noexcept
{
  delete ui;
}

void ribi::QtTestMultipleChoiceQuestionMenuDialog::keyPressEvent(QKeyEvent* event)
{
  if (event->key() == Qt::Key_Escape) close();
}

void ribi::QtTestMultipleChoiceQuestionMenuDialog::on_button_start_clicked()
{
  QtTestMultipleChoiceQuestionMainDialog d;
  d.setStyleSheet(this->styleSheet());
  ShowChild(&d);
}

void ribi::QtTestMultipleChoiceQuestionMenuDialog::on_button_about_clicked()
{
  hide();
  About a = m_dialog->GetAbout();
  a.AddLibrary("QtHideAndShowDialog version: " + QtHideAndShowDialog::GetVersion());
  a.AddLibrary("QtMultipleChoiceQuestionDialog version: " + QtMultipleChoiceQuestionDialog::GetVersion());
  a.AddLibrary("QtQuestionDialog version: " + QtQuestionDialog::GetVersion());
  QtAboutDialog d(a);
  d.setStyleSheet(this->styleSheet());
  d.exec();
  show();
}

void ribi::QtTestMultipleChoiceQuestionMenuDialog::on_button_quit_clicked()
{
  close();
}

#ifndef NDEBUG
void ribi::QtTestMultipleChoiceQuestionMenuDialog::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting ribi::QtTestMultipleChoiceQuestionMenuDialog::Test");
  QtTestMultipleChoiceQuestionMainDialog();
  TRACE("Finished ribi::QtTestMultipleChoiceQuestionMenuDialog::Test successfully");
}
#endif

