//---------------------------------------------------------------------------
/*
QtChessBoardWidget, Qt widget for displaying the Chess::Board class
Copyright (C) 2011 Richel Bilderbeek

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program. If not, see <http://www.gnu.org/licenses/>.
*/
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/CppQtChessBoardWidget.htm
//---------------------------------------------------------------------------
#include "qtchessboardwidget.h"

#include <future>
#include <iostream>
#include <boost/bind.hpp>
#include <boost/filesystem.hpp>
#include <boost/numeric/conversion/cast.hpp>

#include <QBitmap>
#include <QMouseEvent>
#include <QPainter>

#include "chessboard.h"
#include "chessboardwidget.h"
#include "chessmove.h"
#include "chessresources.h"
#include "chesssquare.h"
#include "chesssquareselector.h"
#include "chesswidget.h"
#include "qtchessresources.h"
#include "trace.h"
#include "widget.h"

QtChessBoardWidget::QtChessBoardWidget(QWidget *parent)
  : QWidget(parent),
    m_resources(new Chess::QtResources),
    m_widget(new Chess::BoardWidget(
      boost::shared_ptr<Chess::Board>(new Chess::Board(Chess::Board::GetInitialSetup())),
      Rect(0,0,400,400)))
{
  #ifndef NDEBUG
  Test();
  #endif
  assert(m_widget);

  m_widget->m_signal_geometry_changed.connect(
    boost::bind(
      &QtChessBoardWidget::DoRepaint,
      this));

  m_widget->m_signal_graphic_changed.connect(
    boost::bind(
      &QtChessBoardWidget::DoRepaint,
      this));

  resize(200,200);
}

QtChessBoardWidget::QtChessBoardWidget(
  const int width, const int height,
  QWidget *parent)
  : QWidget(parent),
    m_resources(new Chess::QtResources),
    m_widget(new Chess::BoardWidget(
      boost::shared_ptr<Chess::Board>(new Chess::Board(Chess::Board::GetInitialSetup())),
      Rect(0,0,width,height)))
{
  assert(m_widget);

  //m_widget->GetMachine()->GetDialBack()->GetDial()->m_signal_position_changed.connect(boost::bind(
  //  &QtChessBoardWidget::DoRepaint,this));
  //m_widget->GetMachine()->GetDialFront()->GetDial()->m_signal_position_changed.connect(boost::bind(
  //  &QtChessBoardWidget::DoRepaint,this));
  //m_widget->GetMachine()->GetToggleButton()->GetToggleButton()->m_signal_toggled.connect(boost::bind(
  //  &QtChessBoardWidget::DoRepaint,this));
  m_widget->m_signal_geometry_changed.connect(
    boost::bind(
      &QtChessBoardWidget::DoRepaint,
      this));

  resize(width,height);
}

void QtChessBoardWidget::DoRepaint()
{
  this->repaint();
}

void QtChessBoardWidget::DrawChessBoard(
  QPainter& painter,
  const Chess::BoardWidget * const widget)
{
  const int w = widget->GetGeometry().GetWidth();
  const int h = widget->GetGeometry().GetHeight();

  //Draw the plain chessboard
  DrawChessBoard(
    painter,
    widget->GetGeometry().GetX(),
    widget->GetGeometry().GetY(),
    w,
    h,
    widget->GetBoard().get());
  //Draw the selected square
  static const Chess::QtResources r;
  const int square_w = w / 8;
  const int square_h = h / 8;


  const boost::scoped_ptr<Chess::Square>& selected = widget->GetSelector()->GetSelected();
  if (selected)
  {
    TRACE_FUNC();
    const int x_co = selected->GetFile().ToInt() * square_w;
    const int y_co = selected->GetRank().ToInt() * square_h;
    if (widget->GetBoard()->GetPiece(*selected.get()))
    {
      const std::string filename = Chess::Resources::Find(
        widget->GetBoard()->GetPiece(*selected.get()),
        Chess::SquareSelector::m_selected_color,
        true);
      TRACE(filename);
      assert(boost::filesystem::exists(filename));
      const QPixmap p(filename.c_str());
      painter.drawPixmap(x_co,y_co,square_w,square_h,p);
    }
    else
    {
      assert(!"Should not get here");
    }

    //Draw the possible moves

    const std::vector<Chess::Move> moves = widget->GetBoard()->GetMoves(*selected.get());
    std::for_each(moves.begin(),moves.end(),
      [&painter,square_w,square_h,widget](const Chess::Move& move)
      {
        if (move.To())
        {
          const int x_co = move.To()->GetFile().ToInt() * square_w;
          const int y_co = move.To()->GetRank().ToInt() * square_h;
          if (widget->GetBoard()->GetPiece(*move.To().get()))
          {
            const std::string filename = Chess::Resources::Find(
              widget->GetBoard()->GetPiece(*move.To().get()),
              Chess::SquareSelector::m_moves_color);
            assert(boost::filesystem::exists(filename));
            const QPixmap p(filename.c_str());
            painter.drawPixmap(x_co,y_co,square_w,square_h,p);
          }
          else
          {
            const std::string filename
              = Chess::Resources::Find(
                Chess::Square(move.To()->GetFile().ToInt(),move.To()->GetRank().ToInt()),
                Chess::SquareSelector::m_moves_color);
            assert(boost::filesystem::exists(filename));
            const QPixmap p(filename.c_str());
            painter.drawPixmap(x_co,y_co,square_w,square_h,p);
          }
        }
      }
    );
  }
  //Draw cursor
  const boost::scoped_ptr<const Chess::Square>& cursor = widget->GetSelector()->GetCursor();
  assert(cursor);
  {
    const int x_co = cursor->GetFile().ToInt() * square_w;
    const int y_co = cursor->GetRank().ToInt() * square_h;
    if (widget->GetBoard()->GetPiece(*cursor.get()))
    {
      const std::string filename = Chess::Resources::Find(widget->GetBoard()->GetPiece(*cursor.get()),
        Chess::SquareSelector::m_cursor_color,
        selected && *selected == *cursor );
      assert(boost::filesystem::exists(filename));
      const QPixmap p(filename.c_str());
      painter.drawPixmap(x_co,y_co,square_w,square_h,p);
    }
    else
    {
      const std::string filename
        = Chess::Resources::Find(
          *cursor,
          Chess::SquareSelector::m_cursor_color);
      assert(boost::filesystem::exists(filename));
      const QPixmap p(filename.c_str());
      painter.drawPixmap(x_co,y_co,square_w,square_h,p);
    }
  }
}

void QtChessBoardWidget::DrawChessBoard(
  QPainter& painter,
  const int left, const int top,
  const int width, const int height,
  const Chess::Board * const board)
{
  static const Chess::QtResources r;
  const int square_w = width  / 8;
  const int square_h = height / 8;
  for (int y=0; y!=8; ++y)
  {
    for (int x=0; x!=8; ++x)
    {
      const int x_co = x * square_w;
      const int y_co = y * square_h;
      if (board->GetPiece(Chess::Square(x,y)))
      {
        const QPixmap p(r.Find(board->GetPiece(Chess::Square(x,y))).c_str());
        painter.drawPixmap(left + x_co,top + y_co,square_w,square_h,p);
      }
      else
      {
        const QPixmap p(r.Find(Chess::Square(x,y)).c_str());
        painter.drawPixmap(left + x_co,top + y_co,square_w,square_h,p);
      }
    }
  }
}

const std::string QtChessBoardWidget::GetVersion()
{
  return "1.0";
}

const std::vector<std::string> QtChessBoardWidget::GetVersionHistory()
{
  std::vector<std::string> v;
  v.push_back("2012-01-26: version 1.0: initial version");
  return v;
}

void QtChessBoardWidget::keyPressEvent(QKeyEvent * e)
{
  TRACE_FUNC();
  switch (e->key())
  {
    case Qt::Key_Up: this->m_widget->GetSelector()->MoveUp(); break;
    case Qt::Key_Right: this->m_widget->GetSelector()->MoveRight(); break;
    case Qt::Key_Down: this->m_widget->GetSelector()->MoveDown(); break;
    case Qt::Key_Left: this->m_widget->GetSelector()->MoveLeft(); break;
    case Qt::Key_Space: this->m_widget->GetSelector()->DoSelect(); break;
  }
}

void QtChessBoardWidget::mousePressEvent(QMouseEvent * e)
{
  m_widget->ClickPixel(e->x(),e->y());
  //m_widget->Click(e->x(),e->y());
}

void QtChessBoardWidget::paintEvent(QPaintEvent *)
{
  QPainter painter(this);
  DrawChessBoard( painter,this->m_widget.get());
}

void QtChessBoardWidget::resizeEvent(QResizeEvent *)
{
  m_widget->SetGeometry(Rect(0,0,width(),height()));
}


void QtChessBoardWidget::Test()
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  std::thread t(
    []
    {
      QtChessBoardWidget();
    }
  );
  t.join();
}
