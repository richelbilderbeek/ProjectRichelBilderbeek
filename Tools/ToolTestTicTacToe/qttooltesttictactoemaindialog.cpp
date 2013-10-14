//---------------------------------------------------------------------------
/*
TestTicTacToe, tool to test the TicTacToe class
Copyright (C) 2011-2013 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/ToolTestTicTacToe.htm
//---------------------------------------------------------------------------
#include "qttooltesttictactoemaindialog.h"

#include <cassert>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/lexical_cast.hpp>
#include <boost/numeric/conversion/cast.hpp>

#include <QDesktopWidget>
#include <QTimer>

#include "qtaboutdialog.h"
#include "qttictactoewidget.h"
#include "tictactoe.h"
#include "ui_qttooltesttictactoemaindialog.h"
#pragma GCC diagnostic pop

ribi::QtTestTicTacToeMainDialog::QtTestTicTacToeMainDialog(QWidget *parent)
  : QtHideAndShowDialog(parent),
    ui(new Ui::QtTestTicTacToeMainDialog),
    m_tictactoewidget(new QtTicTacToeWidget),
    m_timer(new QTimer(this))
{
  #ifndef NDEBUG
  Test();
  #endif

  ui->setupUi(this);
  ui->layout_top->addWidget(m_tictactoewidget);

  QObject::connect(ui->button_auto_play,&QPushButton::clicked,
    this,&ribi::QtTestTicTacToeMainDialog::OnPlay);
  QObject::connect(ui->button_restart,&QPushButton::clicked,
    this,&ribi::QtTestTicTacToeMainDialog::OnRestart);
  QObject::connect(m_tictactoewidget,&QtTicTacToeWidget::stateChanged,
    this,&ribi::QtTestTicTacToeMainDialog::OnStateChange);
  QObject::connect(m_tictactoewidget,&QtTicTacToeWidget::hasWinner,
    this,&ribi::QtTestTicTacToeMainDialog::OnStateChange);
  QObject::connect(this->m_timer,&QTimer::timeout,
    this,&ribi::QtTestTicTacToeMainDialog::OnTick);

  m_timer->setInterval(50);

  //Put the dialog in the screen center
  const QRect screen = QApplication::desktop()->screenGeometry();
  this->move( screen.center() - this->rect().center() );



}

ribi::QtTestTicTacToeMainDialog::~QtTestTicTacToeMainDialog()
{
  delete ui;
  m_timer->stop();
}


void ribi::QtTestTicTacToeMainDialog::OnPlay()
{
  if (m_timer->isActive())
  {
    m_timer->stop();
    ui->button_auto_play->setText("&Start auto-play");
  }
  else
  {
    m_timer->start();
    ui->button_auto_play->setText("&Stop auto-play");
  }
}

void ribi::QtTestTicTacToeMainDialog::OnRestart()
{
  this->m_tictactoewidget->Restart();
}

void ribi::QtTestTicTacToeMainDialog::OnTick()
{
  if (m_tictactoewidget->GetTicTacToe()->GetWinner() != TicTacToe::no_winner)
  {
    this->OnRestart();
    return;
  }
  const QRect r = m_tictactoewidget->geometry();
  const int x = r.left() + (std::rand() % r.width());
  const int y = r.top()  + (std::rand() % r.height());
  QPoint pos(x,y);
  boost::shared_ptr<QMouseEvent> e(
    new QMouseEvent(
      QEvent::MouseButtonPress,
      pos,
      Qt::LeftButton,
      Qt::LeftButton,
      Qt::NoModifier));
  m_tictactoewidget->mousePressEvent(e.get());
}

void ribi::QtTestTicTacToeMainDialog::OnStateChange()
{
  //Give feedback
  ui->text->clear();
  //Determine game state
  {
    std::string s = "Winner: ";
    switch (m_tictactoewidget->GetTicTacToe()->GetWinner())
    {
      case TicTacToe::no_winner:
        s+="none";
        break;
      case TicTacToe::player1: s+="player 1 ('X')";
        break;
      case TicTacToe::player2:
        s+="player 2 ('O')";
        break;
      case TicTacToe::draw:
        s+="draw";
        break;
      default: assert(!"Should not get here");
    }
    ui->text->appendPlainText(s.c_str());
  }
  {
    std::string s = "Current active player: ";
    switch (m_tictactoewidget->GetTicTacToe()->GetCurrentPlayer())
    {
      case TicTacToe::player1: s+="player 1 ('X')"; break;
      case TicTacToe::player2: s+="player 2 ('O')"; break;
      default: assert(!"Should not get here");
    }
    ui->text->appendPlainText(s.c_str());
  }
  ui->text->appendPlainText("Summarized state: "
    + QString::number(m_tictactoewidget->GetTicTacToe()->GetSummarizedState()));
}

#ifndef NDEBUG
void ribi::QtTestTicTacToeMainDialog::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  //Perform tests
  {
    //Check empty board state
    {
      TicTacToe t;
      const int s = t.GetSummarizedState();
      TicTacToe u(s);
      assert(u == t);
    }
    //Check one-move states
    for (int i=0; i!=9; ++i)
    {
      TicTacToe t;
      t.DoMove(i/3,i%3);
      const int s = t.GetSummarizedState();
      TicTacToe u(s);
      assert(u == t);
    }
    //Check two-move states
    for (int i=0; i!=8; ++i)
    {
      TicTacToe t;
      t.DoMove(i/3,i%3);
      t.DoMove(i/3,(i+1)%3);
      const int s = t.GetSummarizedState();
      TicTacToe u(s);
      assert(u == t);
    }
    //Check draw detection
    {
      TicTacToe t;
      assert(t.GetCurrentPlayer() == TicTacToe::player1);
      assert(t.GetCurrentTurn()   == 0);
      t.DoMove(1,1);
      assert(t.GetCurrentPlayer() == TicTacToe::player2);
      assert(t.GetCurrentTurn()   == 1);
      t.DoMove(0,0);
      assert(t.GetCurrentPlayer() == TicTacToe::player1);
      assert(t.GetCurrentTurn()   == 2);
      t.DoMove(1,2);
      assert(t.GetCurrentPlayer() == TicTacToe::player2);
      assert(t.GetCurrentTurn()   == 3);
      t.DoMove(1,0);
      assert(t.GetCurrentPlayer() == TicTacToe::player1);
      assert(t.GetCurrentTurn()   == 4);
      t.DoMove(2,0);
      assert(t.GetCurrentPlayer() == TicTacToe::player2);
      assert(t.GetCurrentTurn()   == 5);
      t.DoMove(0,2);
      assert(t.GetCurrentPlayer() == TicTacToe::player1);
      assert(t.GetCurrentTurn()   == 6);
      t.DoMove(0,1);
      assert(t.GetCurrentPlayer() == TicTacToe::player2);
      assert(t.GetCurrentTurn()   == 7);
      t.DoMove(2,1);
      assert(t.GetCurrentPlayer() == TicTacToe::player1);
      assert(t.GetCurrentTurn()   == 8);
      t.DoMove(2,2);
      assert(t.GetCurrentPlayer() == TicTacToe::player2);
      assert(t.GetCurrentTurn()   == 9);
      assert(t.GetWinner() == TicTacToe::draw);
    }
    //Check player1 wins horizontally detection
    {
      TicTacToe t;
      assert(t.GetWinner() == TicTacToe::no_winner);
      t.DoMove(0,0);
      assert(t.GetWinner() == TicTacToe::no_winner);
      t.DoMove(1,0);
      assert(t.GetWinner() == TicTacToe::no_winner);
      t.DoMove(0,1);
      assert(t.GetWinner() == TicTacToe::no_winner);
      t.DoMove(1,1);
      assert(t.GetWinner() == TicTacToe::no_winner);
      t.DoMove(0,2);
      assert(t.GetWinner() == TicTacToe::player1);
    }
    //Check player2 wins vertically detection
    {
      TicTacToe t;
      assert(t.GetWinner() == TicTacToe::no_winner);
      t.DoMove(0,0);
      assert(t.GetWinner() == TicTacToe::no_winner);
      t.DoMove(1,0);
      assert(t.GetWinner() == TicTacToe::no_winner);
      t.DoMove(0,1);
      assert(t.GetWinner() == TicTacToe::no_winner);
      t.DoMove(1,1);
      assert(t.GetWinner() == TicTacToe::no_winner);
      t.DoMove(2,2);
      assert(t.GetWinner() == TicTacToe::no_winner);
      t.DoMove(1,2);
      assert(t.GetWinner() == TicTacToe::player2);
    }
    //Check player1 wins diagonally detection
    {
      TicTacToe t;
      assert(t.GetWinner() == TicTacToe::no_winner);
      t.DoMove(0,0);
      assert(t.GetWinner() == TicTacToe::no_winner);
      t.DoMove(1,0);
      assert(t.GetWinner() == TicTacToe::no_winner);
      t.DoMove(1,1);
      assert(t.GetWinner() == TicTacToe::no_winner);
      t.DoMove(1,2);
      assert(t.GetWinner() == TicTacToe::no_winner);
      t.DoMove(2,2);
      assert(t.GetWinner() == TicTacToe::player1);
    }
    //Check no-winner detection
    {
      TicTacToe t;
      t.DoMove(1,1);
      t.DoMove(0,0);
      t.DoMove(1,2);
      t.DoMove(1,0);
      t.DoMove(2,0);
      t.DoMove(0,2);
      t.DoMove(0,1);
      t.DoMove(2,1);
      //t.DoMove(2,2); //Final move to make a draw
      assert(t.GetWinner() == TicTacToe::no_winner);
    }
    //Check CanDoMove
    for (int i=0; i!=9; ++i)
    {
      TicTacToe t;
      t.DoMove(i/3,i%3);
      assert(t.CanDoMove(i/3,i%3)==false);
    }
    //Check all states
    //59049 = 3^10
    for (int i=0; i!=59049; ++i)
    {
      try
      {
        TicTacToe t(i);
        assert(t.GetSummarizedState() == i);
      }
      catch (std::exception&)
      {
        //No problem
      }
    }
  }
}
#endif
