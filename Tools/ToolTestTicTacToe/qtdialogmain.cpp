//---------------------------------------------------------------------------
/*
TestTicTacToe, tool to test the TicTacToe class
Copyright (C) 2010 Richel Bilderbeek

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
#include <cassert>
//---------------------------------------------------------------------------
#include <boost/lexical_cast.hpp>
#include <boost/numeric/conversion/cast.hpp>
//---------------------------------------------------------------------------
#include <QDesktopWidget>
#include <QTimer>
//---------------------------------------------------------------------------
#include "qtdialogabout.h"
#include "qtdialogmain.h"
#include "../../Classes/CppQtTicTacToeWidget/qttictactoewidget.h"
#include "../../Classes/CppTicTacToe/tictactoe.h"
#include "ui_qtdialogmain.h"
//---------------------------------------------------------------------------
DialogMain::DialogMain(QWidget *parent) :
    QDialog(parent, Qt::Window),
    ui(new Ui::DialogMain),
    m_tictactoewidget(new QtTicTacToeWidget),
    m_timer(new QTimer( this))
{
  ui->setupUi(this);
  ui->layout_top->addWidget(m_tictactoewidget);

  QObject::connect(ui->button_about,SIGNAL(clicked()),
    this,SLOT(OnAbout()));
  QObject::connect(ui->button_auto_play,SIGNAL(clicked()),
    this,SLOT(OnPlay()));
  QObject::connect(ui->button_restart,SIGNAL(clicked()),
    this,SLOT(OnRestart()));

  QObject::connect(m_tictactoewidget,SIGNAL(stateChanged()),
    this,SLOT(OnStateChange()));
  QObject::connect(m_tictactoewidget,SIGNAL(hasWinner()),
    this,SLOT(OnStateChange()));

  QObject::connect(this->m_timer,SIGNAL(timeout()),
    this,SLOT(OnTick()));

  m_timer->setInterval(50);

  //Put the dialog in the screen center
  const QRect screen = QApplication::desktop()->screenGeometry();
  this->move( screen.center() - this->rect().center() );


  //Perform tests
  {
    //Check empty board state
    {
      TicTacToe t;
      const int s = t.GetSummarizedState();
      TicTacToe u(s);
      assert(u == s);
    }
    //Check one-move states
    for (int i=0; i!=9; ++i)
    {
      TicTacToe t;
      t.DoMove(i/3,i%3);
      const int s = t.GetSummarizedState();
      TicTacToe u(s);
      assert(u == s);
    }
    //Check two-move states
    for (int i=0; i!=8; ++i)
    {
      TicTacToe t;
      t.DoMove(i/3,i%3);
      t.DoMove(i/3,(i+1)%3);
      const int s = t.GetSummarizedState();
      TicTacToe u(s);
      assert(u == s);
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
//---------------------------------------------------------------------------
DialogMain::~DialogMain()
{
  delete ui;
  m_timer->stop();
}
//---------------------------------------------------------------------------
void DialogMain::changeEvent(QEvent *e)
{
  QDialog::changeEvent(e);
  switch (e->type()) {
  case QEvent::LanguageChange:
    ui->retranslateUi(this);
    break;
  default:
    break;
  }
}
//---------------------------------------------------------------------------
const std::string DialogMain::GetVersion()
{
  return "1.2";
}
//---------------------------------------------------------------------------
const std::vector<std::string> DialogMain::GetVersionHistory()
{
  std::vector<std::string> v;
  v.push_back("YYYY-MM-DD: version X.Y: [description]");
  v.push_back("2010-09-17: version 1.0: initial version, use of QTable as board");
  v.push_back("2010-09-22: version 1.1: use of TicTacToeWidget");
  v.push_back("2011-01-06: version 1.2: merge with Wt application");
  v.push_back("2011-01-06: version 1.3: moved TicTacToe and QtTicTacToeWidget to different folders");
  return v;
}
//---------------------------------------------------------------------------
void DialogMain::OnAbout()
{
  DialogAbout d;
  d.exec();
}
//---------------------------------------------------------------------------
void DialogMain::OnPlay()
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
//---------------------------------------------------------------------------
void DialogMain::OnRestart()
{
  this->m_tictactoewidget->Restart();
}
//---------------------------------------------------------------------------
void DialogMain::OnTick()
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
//---------------------------------------------------------------------------
void DialogMain::OnStateChange()
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
//---------------------------------------------------------------------------
