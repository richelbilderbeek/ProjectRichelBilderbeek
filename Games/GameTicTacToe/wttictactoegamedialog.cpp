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
#include "wttictactoegamedialog.h"

#include <cassert>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-variable"
#include <Wt/WBreak>
#include <Wt/WPushButton>

#include "wttictactoewidget.h"

#pragma GCC diagnostic pop

ribi::WtTicTacToeGameDialog::WtTicTacToeGameDialog(
  const bool display_close_button)
  : m_signal_close{},
    m_button_restart{},
    m_tictactoe(new WtTicTacToeWidget)
{
  this->setContentAlignment(Wt::AlignCenter);
  //TicTacToeWidget
  {
    this->addWidget(m_tictactoe);
    m_tictactoe->m_signal_state_changed.connect(
      boost::bind(
        &ribi::WtTicTacToeGameDialog::OnStateChanged,
        this));
  }
  this->addWidget(new Wt::WBreak);
  //Restart button
  {
    m_button_restart
      = new Wt::WPushButton("Restart",this);
    this->addWidget(m_button_restart);
    m_button_restart->clicked().connect(
      this,&ribi::WtTicTacToeGameDialog::OnRestart);
  }
  //Close button
  if (display_close_button)
  {
    Wt::WPushButton * const button
      = new Wt::WPushButton("Close",this);
    button->clicked().connect(
      this,&ribi::WtTicTacToeGameDialog::OnClose);
  }
}

void ribi::WtTicTacToeGameDialog::OnClose()
{
  //emit that this dialog closes
  m_signal_close();
}

void ribi::WtTicTacToeGameDialog::OnRestart()
{
  m_tictactoe->Restart();
  m_button_restart->setText("Restart");
}

void ribi::WtTicTacToeGameDialog::OnStateChanged()
{
  switch (m_tictactoe->GetWinner())
  {
    case tictactoe::Winner::player1:
      m_button_restart->setText("Player 1 has won. Click to restart");
      break;
    case tictactoe::Winner::player2:
      m_button_restart->setText("Player 2 has won. Click to restart");
      break;
    case tictactoe::Winner::draw:
      m_button_restart->setText("Draw. Click to restart");
      break;
    case tictactoe::Winner::no_winner:
      m_button_restart->setText("Restart");
      break;
    default:
      assert(!"Should not get here");
      break;
  }
}



