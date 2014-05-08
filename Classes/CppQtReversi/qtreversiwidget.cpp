#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "qtreversiwidget.h"

#include <cstdlib>

#include <QMouseEvent>
#include <QPainter>

#include "reversiboard.h"
#include "reversiwidget.h"
#include "reversimove.h"
#include "trace.h"
#pragma GCC diagnostic pop

ribi::reversi::QtWidget::QtWidget(QWidget* parent, Qt::WindowFlags f)
  : QWidget(parent,f),
    m_reversi(new Widget(4)),
    m_color_player1(    QColor(255,  0,  0)),
    m_color_player2(    QColor(  0,  0,255)),
    m_color_square_even(QColor( 32, 32, 32)),
    m_color_square_odd( QColor( 64, 64, 64))
{
  #ifndef NDEBUG
  Test();
  #endif
  //Allows this widget to respond to mouse moving over it
  this->setMouseTracking(true);
}

void ribi::reversi::QtWidget::mousePressEvent(QMouseEvent * e)
{
  const int x = (e->x() * m_reversi->GetBoard()->GetSize()) / this->width();
  const int y = (e->y() * m_reversi->GetBoard()->GetSize()) / this->height();

  const boost::shared_ptr<MovePlacePiece> move {
    new MovePlacePiece(x,y)
  };

  if (m_reversi->CanDoMove(move))
  {
     m_reversi->DoMove(move);
     repaint();
  }
}

void ribi::reversi::QtWidget::paintEvent(QPaintEvent *)
{

  QPainter painter(this);
  const int width  = this->width();
  const int height = this->height();
  const int sz = m_reversi->GetBoard()->GetSize();
  QBrush brush = painter.brush();
  brush.setStyle(Qt::SolidPattern);
  for (int row=0; row!=sz; ++row)
  {
    const int y1 = (height * (row + 0)) / sz;
    const int y2 = (height * (row + 1)) / sz;
    for (int col=0; col!=sz; ++col)
    {
      const int x1 = (width * (col + 0)) / sz;
      const int x2 = (width * (col + 1)) / sz;
      switch (m_reversi->GetBoard()->Get(col,row))
      {
        case Square::player1: brush.setColor(m_color_player1); break;
        case Square::player2: brush.setColor(m_color_player2); break;
        case Square::empty  : brush.setColor((col + row) % 2 ? m_color_square_odd : m_color_square_even); break;

      }
      painter.setBrush(brush);
      painter.drawRect(x1,y1,x2-x1,y2-y1);
    }
  }
}

#ifndef NDEBUG
void ribi::reversi::QtWidget::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting ribi::reversi::QtWidget::Test()");
  TRACE("Finished ribi::reversi::QtWidget::Test()");
}
#endif
