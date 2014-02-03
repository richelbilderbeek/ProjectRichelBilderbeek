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
#include "qttesttictactoemaindialog.h"

#include <cassert>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/lexical_cast.hpp>
#include <boost/lambda/lambda.hpp>
#include <boost/numeric/conversion/cast.hpp>

#include <QDesktopWidget>
#include <QTimer>

#include "qtaboutdialog.h"
#include "qtcanvas.h"
#include "qttictactoewidget.h"
#include "textcanvas.h"
#include "tictactoe.h"
#include "trace.h"
#include "ui_qttesttictactoemaindialog.h"
#pragma GCC diagnostic pop

ribi::QtTestTicTacToeMainDialog::QtTestTicTacToeMainDialog(QWidget *parent)
  : QtHideAndShowDialog(parent),
    ui(new Ui::QtTestTicTacToeMainDialog),
    m_canvas{},
    m_tictactoewidget(new QtTicTacToeWidget),
    m_timer(new QTimer(this))
{
  #ifndef NDEBUG
  Test();
  #endif

  ui->setupUi(this);

  {
    assert(ui->verticalLayout);
    ui->verticalLayout->addWidget(m_tictactoewidget);
  }
  {
    assert(ui->verticalLayout);
    assert(!m_canvas);
    m_canvas = new QtCanvas(m_tictactoewidget->GetTicTacToe()->ToTextCanvas());
    ui->verticalLayout->addWidget(m_canvas);
  }

  m_tictactoewidget->m_signal_changed.connect(
    boost::bind(&ribi::QtTestTicTacToeMainDialog::OnStateChange,this,boost::lambda::_1)
  );
  m_tictactoewidget->m_signal_has_winner.connect(
    boost::bind(&ribi::QtTestTicTacToeMainDialog::OnStateChange,this,boost::lambda::_1)
  );

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

void ribi::QtTestTicTacToeMainDialog::OnTick()
{
  if (m_tictactoewidget->GetTicTacToe()->GetWinner() != TicTacToe::no_winner)
  {
    on_button_restart_clicked();
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

void ribi::QtTestTicTacToeMainDialog::OnStateChange(QtTicTacToeWidget*)
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

  m_canvas->SetCanvas(m_tictactoewidget->GetTicTacToe()->ToTextCanvas());
}

#ifndef NDEBUG
void ribi::QtTestTicTacToeMainDialog::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting ribi::QtTestTicTacToeMainDialog::Test");
  QtTestTicTacToeMainDialog d;
  assert(!d.GetVersion().empty());
  TRACE("Finished ribi::QtTestTicTacToeMainDialog::Test successfully");
}
#endif

void ribi::QtTestTicTacToeMainDialog::on_button_restart_clicked()
{
  m_tictactoewidget->Restart();
}

void ribi::QtTestTicTacToeMainDialog::on_button_auto_play_clicked()
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
