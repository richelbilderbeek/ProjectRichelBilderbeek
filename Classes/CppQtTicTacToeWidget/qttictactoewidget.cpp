//---------------------------------------------------------------------------
/*
QtTicTacToeWidget, widget for TicTacToe class
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
//From http://www.richelbilderbeek.nl/CppQtTicTacToeWidget.htm
//---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "qttictactoewidget.h"

#include <cassert>
#include <iostream>

#include <boost/lambda/lambda.hpp>

#include <QMouseEvent>
#include <QPainter>
#include <QTimer>

#include "tictactoeai.h"
#include "tictactoeais.h"
#include "tictactoeboard.h"
#include "tictactoegame.h"
#include "tictactoewidget.h"
#include "trace.h"

#pragma GCC diagnostic pop

ribi::tictactoe::QtTicTacToeWidget::QtTicTacToeWidget(
  const boost::shared_ptr<Ai>& player1,
  const boost::shared_ptr<Ai>& player2,
  QWidget *parent)
  : QWidget(parent),
    m_signal_changed{},
    m_signal_has_winner{},
    m_player1{player1},
    m_player2{player2},
    m_widget(new Widget)
{
  #ifndef NDEBUG
  Test();
  #endif

  assert(m_widget);
  this->setMinimumHeight(64);
  this->setMinimumWidth(64);

  {
    QTimer * const timer = new QTimer(this);
    QObject::connect(timer,&QTimer::timeout,this,&ribi::tictactoe::QtTicTacToeWidget::OnTimer);
    timer->setInterval(1000);
    timer->start();
  }

  m_widget->m_signal_changed.connect(
    boost::bind(&QtTicTacToeWidget::OnChanged,this)
  );


}

std::string ribi::tictactoe::QtTicTacToeWidget::GetVersion() noexcept
{
  return "1.3";
}

std::vector<std::string> ribi::tictactoe::QtTicTacToeWidget::GetVersionHistory() noexcept
{
  return {
    "20xx-xx-xx: version 1.0: initial version",
    "2014-02-03: version 1.1: improved interface",
    "2014-03-17: version 1.2: use Widget as a member variable"
    "2014-03-21: version 1.3: added computer AI"
  };

}

void ribi::tictactoe::QtTicTacToeWidget::mousePressEvent(QMouseEvent * e)
{
  if (m_widget->GetGame()->GetWinner() != Winner::no_winner) return;
  const int x = 3 * e->x() / this->width();
  if (x < 0 || x > 2) return;
  const int y = 3 * e->y() / this->height();
  if (y < 0 || y > 2) return;
  if (m_widget->CanSelect(x,y))
  {
    m_widget->Select(x,y);
    m_widget->DoMove();
  }
  if (m_widget->GetGame()->GetWinner() != Winner::no_winner)
  {
    m_signal_has_winner(this);
  }
  repaint();
}

void ribi::tictactoe::QtTicTacToeWidget::OnChanged()
{
  repaint();
  m_signal_changed(this);
}

void ribi::tictactoe::QtTicTacToeWidget::OnTimer() noexcept
{
  if (m_widget->GetWinner() != Winner::no_winner) return;
  const boost::shared_ptr<const Ai> ai(m_widget->GetCurrentPlayer() == Player::player1 ? m_player1: m_player2);
  if (!ai) return;
  const auto move(ai->SuggestMove(*m_widget->GetGame()));
  m_widget->Select(move.first,move.second);
  m_widget->DoMove();
}

void ribi::tictactoe::QtTicTacToeWidget::paintEvent(QPaintEvent *) noexcept
{
  const int width  = this->width();
  const int height = this->height();
  //std::clog << "TicTacToeWidget::paintEvent\n";
  QPainter painter(this);
  //Set black pen
  QPen pen = painter.pen();
  pen.setCapStyle(Qt::RoundCap);
  pen.setColor(QColor::fromRgb(255,255,255));
  painter.setPen(pen);
  painter.setBrush(QBrush(QColor::fromRgb(255,255,255)));
  painter.drawRect(this->rect());
  //Set thick white pen
  pen.setColor(QColor::fromRgb(0,0,0));
  const int line_width = std::min(width,height) / 15;
  pen.setWidth(line_width);
  painter.setPen(pen);
  //Vertical lines
  painter.drawLine(
    ((1*width)/3)+4,     0+(line_width/2),
    ((1*width)/3)-4,height-(line_width/2));
  painter.drawLine(
    ((2*width)/3)-4,     0+(line_width/2),
    ((2*width)/3)+8,height-(line_width/2));
  //Horizontal lines
  painter.drawLine(
        0+(line_width/2),((1*height)/3)+4,
    width-(line_width/2),((1*height)/3)-4);
  painter.drawLine(
        0+(line_width/2),((2*height)/3)-4,
    width-(line_width/2),((2*height)/3)+8);

  for (int row=0; row!=3; ++row)
  {
    const int x1 = ((row + 0) * (width / 3)) + (line_width/1) + 4;
    const int x2 = ((row + 1) * (width / 3)) - (line_width/1) - 4;
    for (int col=0; col!=3; ++col)
    {
      const int y1 = ((col + 0) * (height / 3)) + (line_width/1) + 4;
      const int y2 = ((col + 1) * (height / 3)) - (line_width/1) - 4;
      const auto state(m_widget->GetGame()->GetBoard()->GetSquare(row,col));
      if (state == Square::player1)
      {
        //player1 = cross
        painter.drawLine(x1,y1,x2,y2);
        painter.drawLine(x1,y2,x2,y1);
      }
      else if (state == Square::player2)
      {
        //player1 = circle
        painter.drawEllipse(x1,y1,x2-x1,y2-y1);
      }
    }
  }
}


void ribi::tictactoe::QtTicTacToeWidget::resizeEvent(QResizeEvent *) noexcept
{
  repaint();
}

void ribi::tictactoe::QtTicTacToeWidget::Restart() noexcept
{
  m_widget->Restart();
}

#ifndef NDEBUG
void ribi::tictactoe::QtTicTacToeWidget::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting ribi::tictactoe::QtTicTacToeWidget::Test");
  for (auto ai: Ais().GetAll())
  {
    QtTicTacToeWidget w(ai,nullptr);
    assert(w.GetWidget());
  }
  {
    Widget w;
    assert(!w.GetVersion().empty());
  }
  TRACE("Finished ribi::tictactoe::QtTicTacToeWidget::Test successfully");
}
#endif
