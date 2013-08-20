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
#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif

//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#include "qttestopenquestionmenudialog.h"

#include <QKeyEvent>

#include "about.h"
#include "qtaboutdialog.h"
#include "qthideandshowdialog.h"
#include "qtopenquestiondialog.h"
#include "qtquestiondialog.h"
#include "qttestopenquestionmaindialog.h"
#include "questiondialog.h"
#include "testopenquestionmenudialog.h"
#include "trace.h"
#include "ui_qttestopenquestionmenudialog.h"

QtTestOpenQuestionMenuDialog::QtTestOpenQuestionMenuDialog(QWidget *parent) :
  QtHideAndShowDialog(parent),
  ui(new Ui::QtTestOpenQuestionMenuDialog),
  m_dialog(new TestOpenQuestionMenuDialog)
{
  #ifndef NDEBUG
  Test();
  #endif
  ui->setupUi(this);
}

QtTestOpenQuestionMenuDialog::~QtTestOpenQuestionMenuDialog()
{
  delete ui;
}

void QtTestOpenQuestionMenuDialog::keyPressEvent(QKeyEvent* event)
{
  if (event->key() == Qt::Key_Escape) close();
}

void QtTestOpenQuestionMenuDialog::on_button_start_clicked()
{
  QtTestOpenQuestionMainDialog d;
  d.setStyleSheet(this->styleSheet());
  ShowChild(&d);
}

void QtTestOpenQuestionMenuDialog::on_button_about_clicked()
{
  hide();
  About a = m_dialog->GetAbout();
  a.AddLibrary("QtHideAndShowDialog version: " + QtHideAndShowDialog::GetVersion());
  a.AddLibrary("QtOpenQuestionDialog version: " + QtOpenQuestionDialog::GetVersion());
  a.AddLibrary("QtQuestionDialog version: " + QtQuestionDialog::GetVersion());
  QtAboutDialog d(a);
  d.setStyleSheet(this->styleSheet());
  d.exec();
  show();
}

void QtTestOpenQuestionMenuDialog::on_button_quit_clicked()
{
  close();
}

#ifndef NDEBUG
void QtTestOpenQuestionMenuDialog::Test()
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting QtTestOpenQuestionMenuDialog::Test");
  QtTestOpenQuestionMainDialog();
  TRACE("Finished QtTestOpenQuestionMenuDialog::Test successfully");
}
#endif

