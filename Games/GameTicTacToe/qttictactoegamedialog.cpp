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
#include "qttictactoegamedialog.h"

#include <cassert>
#include <stdexcept>

#include <QDesktopWidget>

#include "tictactoegame.h"
#include "tictactoewidget.h"
#include "qttictactoewidget.h"
#include "qttictactoewinnerdialog.h"
#include "trace.h"
#include "ui_qttictactoegamedialog.h"

#pragma GCC diagnostic pop

ribi::tictactoe::QtTicTacToeGameDialog::QtTicTacToeGameDialog(
  const boost::shared_ptr<Ai>& player1,
  const boost::shared_ptr<Ai>& player2,
  QWidget *parent
) : QtHideAndShowDialog(parent),
    ui(new Ui::QtTicTacToeGameDialog),
    m_tictactoe(new QtTicTacToeWidget(player1,player2))
{
  #ifndef NDEBUG
  Test();
  #endif

  ui->setupUi(this);
  ui->layout->addWidget(m_tictactoe.get());
  QObject::connect(m_tictactoe.get(),SIGNAL(hasWinner()),
    this,SLOT(HasWinner()));

  //Put the dialog in the screen center
  const QRect screen = QApplication::desktop()->screenGeometry();
  this->setGeometry(0,0,3 * screen.width() / 4,3 * screen.height() / 4);
  this->move( screen.center() - this->rect().center() );
}

ribi::tictactoe::QtTicTacToeGameDialog::~QtTicTacToeGameDialog() noexcept
{
  delete ui;
}

void ribi::tictactoe::QtTicTacToeGameDialog::HasWinner()
{

  QtTicTacToeWinnerDialog d;
  switch (m_tictactoe->GetWidget()->GetWinner())
  {
    case Winner::player1: d.SetWinnerCross(); break;
    case Winner::player2: d.SetWinnerCircle(); break;
    case Winner::draw: d.SetDraw(); break;
    case Winner::no_winner:
      assert(!"QtTicTacToeGameDialog::HasWinner: should not respond to no winner");
      throw std::logic_error("QtTicTacToeGameDialog::HasWinner: should not respond to no winner");
  }
  d.exec();
  m_tictactoe->Restart();
}

#ifndef NDEBUG
void ribi::tictactoe::QtTicTacToeGameDialog::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting ribi::tictactoe::QtTicTacToeGameDialog::Test");
  TRACE("Finished ribi::tictactoe::QtTicTacToeGameDialog::Test successfully");
}
#endif
