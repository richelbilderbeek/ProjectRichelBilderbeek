//---------------------------------------------------------------------------
/*
TestMultipleChoiceQuestion, tool to test the MultipleChoiceQuestion and MultipleChoiceQuestionDialog classes
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
//From http://www.richelbilderbeek.nl/ToolTestMultipleChoiceQuestion.htm
//---------------------------------------------------------------------------
#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif

//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
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

QtTestMultipleChoiceQuestionMenuDialog::QtTestMultipleChoiceQuestionMenuDialog(QWidget *parent) :
  QtHideAndShowDialog(parent),
  ui(new Ui::QtTestMultipleChoiceQuestionMenuDialog),
  m_dialog(new TestMultipleChoiceQuestionMenuDialog)
{
  #ifndef NDEBUG
  Test();
  #endif
  ui->setupUi(this);
}

QtTestMultipleChoiceQuestionMenuDialog::~QtTestMultipleChoiceQuestionMenuDialog()
{
  delete ui;
}

void QtTestMultipleChoiceQuestionMenuDialog::keyPressEvent(QKeyEvent* event)
{
  if (event->key() == Qt::Key_Escape) close();
}

void QtTestMultipleChoiceQuestionMenuDialog::on_button_start_clicked()
{
  QtTestMultipleChoiceQuestionMainDialog d;
  d.setStyleSheet(this->styleSheet());
  ShowChild(&d);
}

void QtTestMultipleChoiceQuestionMenuDialog::on_button_about_clicked()
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

void QtTestMultipleChoiceQuestionMenuDialog::on_button_quit_clicked()
{
  close();
}

#ifndef NDEBUG
void QtTestMultipleChoiceQuestionMenuDialog::Test()
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting QtTestMultipleChoiceQuestionMenuDialog::Test");
  QtTestMultipleChoiceQuestionMainDialog();
  TRACE("Finished QtTestMultipleChoiceQuestionMenuDialog::Test successfully");
}
#endif

