//---------------------------------------------------------------------------
/*
TicTacToe, tic-tac-toe game
Copyright (C) 2010-2014 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/GameTicTacToe.htm
//---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "qttictactoemenudialog.h"

#include <cassert>

#include "qtaboutdialog.h"
#include "qttictactoegamedialog.h"
#include "qttictactoewidget.h"
#include "tictactoemenudialog.h"
#include "trace.h"
#include "ui_qttictactoemenudialog.h"
#pragma GCC diagnostic pop

ribi::QtTicTacToeMenuDialog::QtTicTacToeMenuDialog(QWidget *parent) :
    QtHideAndShowDialog(parent),
    ui(new Ui::QtTicTacToeMenuDialog)
{
  #ifndef NDEBUG
  Test();
  #endif

  ui->setupUi(this);
}

ribi::QtTicTacToeMenuDialog::~QtTicTacToeMenuDialog() noexcept
{
  delete ui;
}

void ribi::QtTicTacToeMenuDialog::on_button_start_clicked()
{
  QtTicTacToeGameDialog d;
  this->ShowChild(&d);
}

void ribi::QtTicTacToeMenuDialog::on_button_about_clicked()
{
  About a = TicTacToeMenuDialog().GetAbout();
  a.AddLibrary("QtTicTacToeWidget version: " + QtTicTacToeWidget::GetVersion());
  QtAboutDialog d(a);
  this->ShowChild(&d);
}

void ribi::QtTicTacToeMenuDialog::on_button_quit_clicked()
{
  close();
}

#ifndef NDEBUG
void ribi::QtTicTacToeMenuDialog::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting ribi::QtTicTacToeMenuDialog::Test");
  TRACE("Finished ribi::QtTicTacToeMenuDialog::Test successfully");
}
#endif
