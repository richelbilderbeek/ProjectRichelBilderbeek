//---------------------------------------------------------------------------
/*
TestTicTacToe, tool to test the TicTacToe class
Copyright (C) 2011-2015 Richel Bilderbeek

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
#include "testtimer.h"
#include "textcanvas.h"
#include "tictactoeais.h"
#include "tictactoewidget.h"
#include "trace.h"
#include "ui_qttesttictactoemaindialog.h"
#pragma GCC diagnostic pop

ribi::tictactoe::QtTestTicTacToeMainDialog::QtTestTicTacToeMainDialog(
  const boost::shared_ptr<Ai>& player1,
  const boost::shared_ptr<Ai>& player2,
  QWidget *parent
) : QtHideAndShowDialog(parent),
    ui(new Ui::QtTestTicTacToeMainDialog),
    m_canvas{},
    m_tictactoewidget(new QtTicTacToeWidget(player1,player2)),
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
    m_canvas = new ::ribi::QtCanvas(m_tictactoewidget->GetWidget()->ToTextCanvas());
    ui->verticalLayout->addWidget(m_canvas);
  }

  m_tictactoewidget->m_signal_changed.connect(
    boost::bind(&ribi::tictactoe::QtTestTicTacToeMainDialog::OnStateChange,this,boost::lambda::_1)
  );
  m_tictactoewidget->m_signal_has_winner.connect(
    boost::bind(&ribi::tictactoe::QtTestTicTacToeMainDialog::OnStateChange,this,boost::lambda::_1)
  );

  QObject::connect(this->m_timer,&QTimer::timeout,
    this,&ribi::tictactoe::QtTestTicTacToeMainDialog::OnTick);

  m_timer->setInterval(50);

  //Put the dialog in the screen center
  const QRect screen = QApplication::desktop()->screenGeometry();
  this->move( screen.center() - this->rect().center() );



}

ribi::tictactoe::QtTestTicTacToeMainDialog::~QtTestTicTacToeMainDialog()
{
  delete ui;
  m_timer->stop();
}

void ribi::tictactoe::QtTestTicTacToeMainDialog::OnTick()
{
  if (m_tictactoewidget->GetWidget()->GetWinner() != Winner::no_winner)
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

void ribi::tictactoe::QtTestTicTacToeMainDialog::OnStateChange(QtTicTacToeWidget*)
{
  //Give feedback
  ui->text->clear();
  //Determine game state
  {
    std::string s = "Winner: ";
    switch (m_tictactoewidget->GetWidget()->GetWinner())
    {
      case Winner::no_winner:
        s+="none";
        break;
      case Winner::player1: s+="player 1 ('X')";
        break;
      case Winner::player2:
        s+="player 2 ('O')";
        break;
      case Winner::draw:
        s+="draw";
        break;
      default: assert(!"Should not get here");
    }
    ui->text->appendPlainText(s.c_str());
  }
  {
    std::string s = "Current active player: ";
    switch (m_tictactoewidget->GetWidget()->GetCurrentPlayer())
    {
      case Player::player1: s+="player 1 ('X')"; break;
      case Player::player2: s+="player 2 ('O')"; break;
      default: assert(!"Should not get here");
    }
    ui->text->appendPlainText(s.c_str());
  }
  ui->text->appendPlainText("Summarized state: "
    + QString::number(m_tictactoewidget->GetWidget()->GetSummarizedState()));

  m_canvas->SetCanvas(m_tictactoewidget->GetWidget()->ToTextCanvas());
}

#ifndef NDEBUG
void ribi::tictactoe::QtTestTicTacToeMainDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
  for (const auto& ai: Ais().GetAll())
  {
    QtTestTicTacToeMainDialog d(ai,nullptr);
    assert(!d.GetVersion().empty());
  }
  for (const auto& ai: Ais().GetAll())
  {
    QtTicTacToeWidget w(nullptr,ai);
    assert(!w.GetVersion().empty());
  }
}
#endif

void ribi::tictactoe::QtTestTicTacToeMainDialog::on_button_restart_clicked()
{
  m_tictactoewidget->Restart();
}

void ribi::tictactoe::QtTestTicTacToeMainDialog::on_button_auto_play_clicked()
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
