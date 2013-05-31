//---------------------------------------------------------------------------
/*
QtTicTacToeWidget, widget for TicTacToe class
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
//From http://www.richelbilderbeek.nl/CppQtTicTacToeWidget.htm
//---------------------------------------------------------------------------
#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif

//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#include "qttictactoewidget.h"

#include <cassert>
#include <iostream>
//---------------------------------------------------------------------------
#include <QMouseEvent>
#include <QPainter>
//---------------------------------------------------------------------------
#include "tictactoe.h"
//---------------------------------------------------------------------------
QtTicTacToeWidget::QtTicTacToeWidget(QWidget *parent) :
  QWidget(parent),
  m_tictactoe(new TicTacToe)
{
  assert(m_tictactoe);
  this->setMinimumHeight(64);
  this->setMinimumWidth(64);
}
//---------------------------------------------------------------------------
void QtTicTacToeWidget::mousePressEvent(QMouseEvent * e)
{
  if (m_tictactoe->GetWinner() != TicTacToe::no_winner) return;
  const int x = 3 * e->x() / this->width();
  if (x < 0 || x > 2) return;
  const int y = 3 * e->y() / this->height();
  if (y < 0 || y > 2) return;
  if (m_tictactoe->CanDoMove(x,y))
  {
    m_tictactoe->DoMove(x,y);
    emit stateChanged();
  }
  if (m_tictactoe->GetWinner() != TicTacToe::no_winner)
  {
    emit hasWinner();
  }
  repaint();
}
//---------------------------------------------------------------------------
void QtTicTacToeWidget::paintEvent(QPaintEvent *)
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
      const int state = m_tictactoe->GetSquare(row,col);
      if (state == TicTacToe::player1)
      {
        //player1 = cross
        painter.drawLine(x1,y1,x2,y2);
        painter.drawLine(x1,y2,x2,y1);
      }
      else if (state == TicTacToe::player2)
      {
        //player1 = circle
        painter.drawEllipse(x1,y1,x2-x1,y2-y1);
      }
    }
  }
}
//---------------------------------------------------------------------------
void QtTicTacToeWidget::resizeEvent(QResizeEvent *)
{
  repaint();
}
//---------------------------------------------------------------------------
void QtTicTacToeWidget::Restart()
{
  m_tictactoe.reset(new TicTacToe);
  repaint();
}
//---------------------------------------------------------------------------
