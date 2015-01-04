//---------------------------------------------------------------------------
/*
RubiksClock. Rubik's Clock game.
Copyright (C) 2007-2015 Richel Bilderbeek

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/GameRubiksClock.htm
//---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "qtrubiksclockmenudialog.h"

#include <QKeyEvent>

#include "qtaboutdialog.h"
#include "qtdialwidget.h"
#include "qthideandshowdialog.h"
#include "qtrubiksclockmaindialog.h"
#include "qtrubiksclockwidget.h"
#include "qttogglebuttonwidget.h"
#include "rubiksclockmenudialog.h"
#include "testtimer.h"
#include "trace.h"
#include "ui_qtrubiksclockmenudialog.h"
#pragma GCC diagnostic pop

ribi::ruco::QtRubiksClockMenuDialog::QtRubiksClockMenuDialog(QWidget *parent) :
    QtHideAndShowDialog(parent),
    ui(new Ui::QtRubiksClockMenuDialog)
{
  #ifndef NDEBUG
  Test();
  #endif
  ui->setupUi(this);
}

ribi::ruco::QtRubiksClockMenuDialog::~QtRubiksClockMenuDialog() noexcept
{
  delete ui;
}

void ribi::ruco::QtRubiksClockMenuDialog::keyPressEvent(QKeyEvent * e)
{
  if (e->key()  == Qt::Key_Escape) close();
}

void ribi::ruco::QtRubiksClockMenuDialog::on_button_about_clicked()
{
  About a = MenuDialog().GetAbout();
  a.AddLibrary("QtDialWidget version: " + QtDialWidget::GetVersion());
  a.AddLibrary("QtHideAndShowDialog version: " + QtHideAndShowDialog::GetVersion());
  a.AddLibrary("QtRubiksClockWidget version: " + QtRubiksClockWidget::GetVersion());
  a.AddLibrary("QtToggleButtonWidget version: " + QtToggleButtonWidget::GetVersion());
  QtAboutDialog d(a);
  d.setWindowIcon(this->windowIcon());
  d.setStyleSheet(this->styleSheet());
  this->ShowChild(&d);
}

void ribi::ruco::QtRubiksClockMenuDialog::on_button_quit_clicked()
{
  close();
}

void ribi::ruco::QtRubiksClockMenuDialog::on_button_start_clicked()
{
  QtRubiksClockMainDialog d;
  ShowChild(&d);
}

#ifndef NDEBUG
void ribi::ruco::QtRubiksClockMenuDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
}
#endif
