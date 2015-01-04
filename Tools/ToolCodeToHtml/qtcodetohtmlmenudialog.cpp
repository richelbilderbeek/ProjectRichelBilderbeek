//---------------------------------------------------------------------------
/*
CodeToHtml, converts C++ code to HTML
Copyright (C) 2010-2015 Richel Bilderbeek

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program.If not, see <http://www.gnu.org/licenses/>.
*/
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/ToolCodeToHtml.htm
//---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "qtcodetohtmlmenudialog.h"

#include <QDesktopWidget>
#include <QKeyEvent>

#include "codetohtmlinfo.h"
#include "codetohtmlmenudialog.h"
#include "qtaboutdialog.h"
#include "qtcodetohtmlmaindialog.h"
#include "testtimer.h"
#include "qthideandshowdialog.h"
#include "trace.h"
#include "ui_qtcodetohtmlmenudialog.h"
#pragma GCC diagnostic pop

ribi::c2h::QtCodeToHtmlMenuDialog::QtCodeToHtmlMenuDialog(QWidget *parent) noexcept :
    QtHideAndShowDialog(parent),
    ui(new Ui::QtCodeToHtmlMenuDialog)
{
  #ifndef NDEBUG
  Test();
  #endif
  ui->setupUi(this);
}

ribi::c2h::QtCodeToHtmlMenuDialog::~QtCodeToHtmlMenuDialog() noexcept
{
  delete ui;
}

void ribi::c2h::QtCodeToHtmlMenuDialog::keyPressEvent(QKeyEvent * event) noexcept
{
  if (event->key() == Qt::Key_Escape) { close(); return; }
}

void ribi::c2h::QtCodeToHtmlMenuDialog::on_button_about_clicked() noexcept
{
  ribi::About a = CodeToHtmlMenuDialog().GetAbout();
  a.AddLibrary("QtHideAndShowDialog version: " + QtHideAndShowDialog::GetVersion());
  ribi::QtAboutDialog d(a);
  d.setWindowIcon(this->windowIcon());
  d.setStyleSheet(this->styleSheet());
  this->ShowChild(&d);
}

void ribi::c2h::QtCodeToHtmlMenuDialog::on_button_quit_clicked() noexcept
{
  close();
}

void ribi::c2h::QtCodeToHtmlMenuDialog::on_button_start_clicked() noexcept
{
  QtCodeToHtmlMainDialog d;
  ShowChild(&d);
}

#ifndef NDEBUG
void ribi::c2h::QtCodeToHtmlMenuDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  CodeToHtmlMenuDialog();
  QtCodeToHtmlMainDialog();
  const TestTimer test_timer(__func__,__FILE__,1.0);
}
#endif

void ribi::c2h::QtCodeToHtmlMenuDialog::on_button_test_1_clicked()
{
  Info::TestIfAllCreatedPagesAreValid();
  ui->button_test_1->setText("PASSED!");
  ui->button_test_1->setEnabled(false);
}

void ribi::c2h::QtCodeToHtmlMenuDialog::on_button_test_2_clicked()
{
  ribi::c2h::CodeToHtmlMenuDialog::TestAllProgramsHaveInfo();
  ui->button_test_2->setText("PASSED!");
  ui->button_test_2->setEnabled(false);
}

void ribi::c2h::QtCodeToHtmlMenuDialog::on_button_test_3_clicked()
{
  ui->button_test_3->setText("PASSED!");
  ui->button_test_3->setEnabled(false);
}
