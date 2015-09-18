//---------------------------------------------------------------------------
/*
TicTacToe, tic-tac-toe game
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
//From http://www.richelbilderbeek.nl/GameTicTacToe.htm
//---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "sfmltictactoemenudialog.h"

#include <cassert>
#include <boost/make_shared.hpp>

#include <QApplication>
#include <QDesktopWidget>

#include "testtimer.h"
#include "sfmltictactoegamedialog.h"
#include "tictactoemenudialog.h"
#include "tictactoeai.h"
#include "trace.h"
#pragma GCC diagnostic pop

ribi::tictactoe::SfmlMenuDialog::SfmlMenuDialog()
{
  #ifndef NDEBUG
  Test();
  #endif
}


void ribi::tictactoe::SfmlMenuDialog::on_button_start_clicked()
{
  const boost::shared_ptr<Ai> player1;
  const boost::shared_ptr<Ai> player2;
  SfmlGameDialog d(player1,player2);
  assert(!"TODO");
}

void ribi::tictactoe::SfmlMenuDialog::on_button_about_clicked()
{
  assert(!"TODO");
}

void ribi::tictactoe::SfmlMenuDialog::on_button_quit_clicked()
{
  assert(!"TODO");
}

#ifndef NDEBUG
void ribi::tictactoe::SfmlMenuDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  TicTacToeMenuDialog();
  {
    const boost::shared_ptr<Ai> player1;
    const boost::shared_ptr<Ai> player2;
    SfmlGameDialog d(player1,player2);
    assert(!d.GetVersion().empty());
  }
}
#endif
