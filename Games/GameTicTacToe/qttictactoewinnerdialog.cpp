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
#include "qttictactoewinnerdialog.h"

#include <cassert>

#include "trace.h"
#include "ui_qttictactoewinnerdialog.h"
#pragma GCC diagnostic pop

ribi::tictactoe::QtTicTacToeWinnerDialog::QtTicTacToeWinnerDialog(QWidget *parent) :
    QtHideAndShowDialog(parent),
    ui(new Ui::QtTicTacToeWinnerDialog)
{
  #ifndef NDEBUG
  Test();
  #endif

  ui->setupUi(this);
}

ribi::tictactoe::QtTicTacToeWinnerDialog::~QtTicTacToeWinnerDialog() noexcept
{
  delete ui;
}

void ribi::tictactoe::QtTicTacToeWinnerDialog::SetDraw()
{
  ui->label_title->setText("Draw");
  this->setWindowTitle("Draw");
  ui->label_winner->setText(" ");
}

void ribi::tictactoe::QtTicTacToeWinnerDialog::SetWinnerCross()
{
  ui->label_winner->setPixmap(QPixmap(":/images/X.png"));
}

void ribi::tictactoe::QtTicTacToeWinnerDialog::SetWinnerCircle()
{
  ui->label_winner->setPixmap(QPixmap(":/images/O.png"));
}

#ifndef NDEBUG
void ribi::tictactoe::QtTicTacToeWinnerDialog::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting ribi::tictactoe::QtTicTacToeWinnerDialog::Test");
  TRACE("Finished ribi::tictactoe::QtTicTacToeWinnerDialog::Test successfully");
}
#endif
