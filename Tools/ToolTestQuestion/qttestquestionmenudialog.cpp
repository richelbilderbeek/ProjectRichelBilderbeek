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
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "qttestquestionmenudialog.h"

#include <QKeyEvent>

#include "about.h"
#include "qtaboutdialog.h"
#include "qthideandshowdialog.h"
#include "qtmultiplechoicequestiondialog.h"
#include "qtopenquestiondialog.h"
#include "qtquestiondialog.h"
#include "qttestquestionmaindialog.h"
#include "questiondialog.h"
#include "testquestionmenudialog.h"
#include "trace.h"
#include "ui_qttestquestionmenudialog.h"
#pragma GCC diagnostic pop

ribi::QtTestQuestionMenuDialog::QtTestQuestionMenuDialog(QWidget *parent) :
  QtHideAndShowDialog(parent),
  ui(new Ui::QtTestQuestionMenuDialog),
  m_dialog(new TestQuestionMenuDialog)
{
  #ifndef NDEBUG
  Test();
  #endif
  ui->setupUi(this);
}

ribi::QtTestQuestionMenuDialog::~QtTestQuestionMenuDialog() noexcept
{
  delete ui;
}

void ribi::QtTestQuestionMenuDialog::keyPressEvent(QKeyEvent* event)
{
  if (event->key() == Qt::Key_Escape) close();
}

void ribi::QtTestQuestionMenuDialog::on_button_start_clicked()
{
  QtTestQuestionMainDialog d;
  d.setStyleSheet(this->styleSheet());
  ShowChild(&d);
}

void ribi::QtTestQuestionMenuDialog::on_button_about_clicked()
{
  About a = m_dialog->GetAbout();
  a.AddLibrary("QtHideAndShowDialog version: " + QtHideAndShowDialog::GetVersion());
  a.AddLibrary("QtOpenQuestionDialog version: " + QtOpenQuestionDialog::GetVersion());
  a.AddLibrary("QtMultipleChoiceQuestionDialog version: " + QtMultipleChoiceQuestionDialog::GetVersion());
  a.AddLibrary("QtQuestionDialog version: " + QtQuestionDialog::GetVersion());
  QtAboutDialog d(a);
  d.setStyleSheet(this->styleSheet());
  this->ShowChild(&d);
}

void ribi::QtTestQuestionMenuDialog::on_button_quit_clicked()
{
  close();
}

#ifndef NDEBUG
void ribi::QtTestQuestionMenuDialog::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting ribi::QtTestQuestionMenuDialog::Test");
  QtTestQuestionMainDialog();
  TRACE("Finished ribi::QtTestQuestionMenuDialog::Test successfully");
}
#endif

