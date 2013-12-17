
#include <cstdlib>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <QMouseEvent>
#include <QPainter>

#include "reversi.h"
#include "reversiwidget.h"
#pragma GCC diagnostic pop

ribi::ReversiWidget::ReversiWidget(QWidget *parent) :
  QWidget(parent),
  m_reversi(new Reversi(4)),
  m_color_player1(    QColor(255,  0,  0)),
  m_color_player2(    QColor(  0,  0,255)),
  m_color_square_even(QColor( 32, 32, 32)),
  m_color_square_odd( QColor( 64, 64, 64))
{
  //Allows this widget to respond to mouse moving over it
  //this->setMouseTracking(true);
  //Test the Reversi
  {
    const int sz = 4;
    Reversi r(sz);
    assert(r.GetSize() == sz);
    assert(r.Get(1,1) == Reversi::player1);
    assert(r.Get(1,2) == Reversi::player2);
    assert(r.Get(2,1) == Reversi::player2);
    assert(r.Get(2,2) == Reversi::player1);
    assert(r.CanDoMove(2,0));
    assert(r.CanDoMove(3,1));
    assert(r.CanDoMove(0,2));
    assert(r.CanDoMove(1,3));

    //r.
  }
}

void ribi::ReversiWidget::mousePressEvent(QMouseEvent * e)
{
  const int x = (e->x() * m_reversi->GetSize()) / this->width();
  const int y = (e->y() * m_reversi->GetSize()) / this->height();
  if ( x >=  0 && x < m_reversi->GetSize()
    && y >=  0 && y < m_reversi->GetSize()
    && m_reversi->CanDoMove(x,y))
  {
     m_reversi->DoMove(x,y);
     repaint();
  }
}

void ribi::ReversiWidget::paintEvent(QPaintEvent *)
{
  QPainter painter(this);
  const int width  = this->width();
  const int height = this->height();
  const int sz = m_reversi->GetSize();
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
      switch (m_reversi->Get(col,row))
      {
        case Reversi::player1: brush.setColor(m_color_player1); break;
        case Reversi::player2: brush.setColor(m_color_player2); break;
        default: brush.setColor((col + row) % 2 ? m_color_square_odd : m_color_square_even); break;
      }
      painter.setBrush(brush);
      painter.drawRect(x1,y1,x2-x1,y2-y1);
    }
  }
}

