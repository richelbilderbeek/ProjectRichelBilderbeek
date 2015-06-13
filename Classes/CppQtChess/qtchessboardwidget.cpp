//---------------------------------------------------------------------------
/*
QtChessBoardWidget, Qt widget for displaying the Chess::Board class
Copyright (C) 2011-2014 Richel Bilderbeek

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
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "qtchessboardwidget.h"

#ifdef MXE_SUPPORTS_THREADS
#include <future>
#endif

#include <iostream>
#include <boost/bind.hpp>
#include <boost/numeric/conversion/cast.hpp>

#include <QBitmap>
#include <QMouseEvent>
#include <QPainter>

#include "chessboard.h"
#include "chessboardwidget.h"
#include "chessmove.h"
#include "chessresources.h"
#include "chesssquare.h"
#include "chesssquarefactory.h"
#include "chesssquareselector.h"
#include "chesswidget.h"
#include "fileio.h"
#include "chessboardfactory.h"
#include "qtchessresources.h"
#include "trace.h"
#include "widget.h"
#pragma GCC diagnostic pop

ribi::Chess::QtChessBoardWidget::QtChessBoardWidget(QWidget *parent)
  : QWidget(parent),
    m_signal_changed{},
    m_resources(new Chess::QtResources),
    m_widget(new BoardWidget(BoardFactory().Create(),Widget::CreateRect(0,0,400,400)))
{
  #ifndef NDEBUG
  Test();
  #endif
  assert(m_widget);

  m_widget->m_signal_geometry_changed.connect(
    boost::bind(
      &ribi::Chess::QtChessBoardWidget::DoRepaint,
      this));

  m_widget->m_signal_graphic_changed.connect(
    boost::bind(
      &ribi::Chess::QtChessBoardWidget::DoRepaint,
      this));

  resize(200,200);
}

ribi::Chess::QtChessBoardWidget::QtChessBoardWidget(
  const int width, const int height,
  QWidget *parent)
  : QWidget(parent),
    m_signal_changed{},
    m_resources(new Chess::QtResources),
    m_widget(new Chess::BoardWidget(
      BoardFactory().Create(),Widget::CreateRect(0,0,width,height)))
{
  assert(m_widget);

  //m_widget->GetMachine()->GetDialBack()->GetDial()->m_signal_position_changed.connect(boost::bind(
  //  &ribi::Chess::QtChessBoardWidget::DoRepaint,this));
  //m_widget->GetMachine()->GetDialFront()->GetDial()->m_signal_position_changed.connect(boost::bind(
  //  &ribi::Chess::QtChessBoardWidget::DoRepaint,this));
  //m_widget->GetMachine()->GetToggleButton()->GetToggleButton()->m_signal_toggled.connect(boost::bind(
  //  &ribi::Chess::QtChessBoardWidget::DoRepaint,this));
  m_widget->m_signal_geometry_changed.connect(
    boost::bind(
      &ribi::Chess::QtChessBoardWidget::DoRepaint,
      this));

  resize(width,height);
}

void ribi::Chess::QtChessBoardWidget::DoRepaint()
{
  this->repaint();
}

void ribi::Chess::QtChessBoardWidget::DrawChessBoard(
  QPainter& painter,
  const Chess::BoardWidget * const widget)
{
  const int w = widget->GetWidth();
  const int h = widget->GetHeight();

  //Draw the plain chessboard
  DrawChessBoard(
    painter,
    widget->GetLeft(),
    widget->GetTop(),
    w,
    h,
    widget->GetBoard().get());
  //Draw the selected square
  static const Chess::QtResources r;
  const int square_w = w / 8;
  const int square_h = h / 8;


  const boost::shared_ptr<const Chess::Square> selected = widget->GetSelector()->GetSelected();
  if (selected)
  {
    TRACE_FUNC();
    const int x_co = selected->GetFile().ToInt() * square_w;
    const int y_co = selected->GetRank().ToInt() * square_h;
    if (widget->GetBoard()->GetPiece(selected))
    {
      const std::string filename = Chess::Resources::Find(
        widget->GetBoard()->GetPiece(selected),
        Chess::SquareSelector::m_selected_color,
        true);
      TRACE(filename);
      assert(fileio::FileIo().IsRegularFile(filename));
      const QPixmap p(filename.c_str());
      painter.drawPixmap(x_co,y_co,square_w,square_h,p);
    }
    else
    {
      assert(!"Should not get here");
    }

    //Draw the possible moves

    const std::vector<boost::shared_ptr<Move> > moves = widget->GetBoard()->GetMoves(selected);
    for(const boost::shared_ptr<Move> move: moves)
    {
      if (move->To())
      {
        const int x_co = move->To()->GetFile().ToInt() * square_w;
        const int y_co = move->To()->GetRank().ToInt() * square_h;
        if (widget->GetBoard()->GetPiece(move->To()))
        {
          const std::string filename = Chess::Resources::Find(
            widget->GetBoard()->GetPiece(move->To()),
            Chess::SquareSelector::m_moves_color);
          assert(fileio::FileIo().IsRegularFile(filename));
          const QPixmap p(filename.c_str());
          painter.drawPixmap(x_co,y_co,square_w,square_h,p);
        }
        else
        {
          const boost::shared_ptr<Square> square {
            SquareFactory().Create(move->To()->GetFile(),move->To()->GetRank())
          };
          const std::string filename
            = Chess::Resources::Find(
              square,
              Chess::SquareSelector::m_moves_color);
          assert(fileio::FileIo().IsRegularFile(filename));
          const QPixmap p(filename.c_str());
          painter.drawPixmap(x_co,y_co,square_w,square_h,p);
        }
      }
    }
  }
  //Draw cursor
  const boost::shared_ptr<const Chess::Square> cursor = widget->GetSelector()->GetCursor();
  assert(cursor);
  {
    const int x_co = cursor->GetFile().ToInt() * square_w;
    const int y_co = cursor->GetRank().ToInt() * square_h;
    if (widget->GetBoard()->GetPiece(cursor))
    {
      const std::string filename = Chess::Resources::Find(widget->GetBoard()->GetPiece(cursor),
        Chess::SquareSelector::m_cursor_color,
        selected && *selected == *cursor );
      assert(fileio::FileIo().IsRegularFile(filename));
      const QPixmap p(filename.c_str());
      painter.drawPixmap(x_co,y_co,square_w,square_h,p);
    }
    else
    {
      const std::string filename
        = Chess::Resources::Find(
          cursor,
          Chess::SquareSelector::m_cursor_color);
      assert(fileio::FileIo().IsRegularFile(filename));
      const QPixmap p(filename.c_str());
      painter.drawPixmap(x_co,y_co,square_w,square_h,p);
    }
  }
}

void ribi::Chess::QtChessBoardWidget::DrawChessBoard(
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
      const boost::shared_ptr<Square> square {
        SquareFactory().Create(File(x),Rank(y))
      };
      if (board->GetPiece(square))
      {
        const QPixmap p(r.Find(board->GetPiece(square)).c_str());
        painter.drawPixmap(left + x_co,top + y_co,square_w,square_h,p);
      }
      else
      {
        const QPixmap p(r.Find(square).c_str());
        painter.drawPixmap(left + x_co,top + y_co,square_w,square_h,p);
      }
    }
  }
}

std::string ribi::Chess::QtChessBoardWidget::GetVersion()
{
  return "1.0";
}

std::vector<std::string> ribi::Chess::QtChessBoardWidget::GetVersionHistory()
{
  return {
    "2012-01-26: version 1.0: initial version"
  };
}

void ribi::Chess::QtChessBoardWidget::keyPressEvent(QKeyEvent * e)
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

void ribi::Chess::QtChessBoardWidget::mousePressEvent(QMouseEvent * e)
{
  m_widget->ClickPixel(e->x(),e->y());
  //m_widget->Click(e->x(),e->y());
}

void ribi::Chess::QtChessBoardWidget::paintEvent(QPaintEvent *)
{
  QPainter painter(this);
  DrawChessBoard( painter,this->m_widget.get());
}

void ribi::Chess::QtChessBoardWidget::resizeEvent(QResizeEvent *)
{
  m_widget->SetGeometry(0,0,width(),height());
}


void ribi::Chess::QtChessBoardWidget::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  #ifdef MXE_SUPPORTS_THREADS
  std::thread t(
    []
  #endif
    {
      QtChessBoardWidget();
    }
  #ifdef MXE_SUPPORTS_THREADS
  );
  t.join();
  #endif
}
