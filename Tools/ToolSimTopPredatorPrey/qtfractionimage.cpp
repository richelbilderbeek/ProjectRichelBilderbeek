#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "qtfractionimage.h"

#include <cassert>

#include <QImage>
#include <QPainter>
#pragma GCC diagnostic pop

QtFractionImage::QtFractionImage(QWidget *parent) :
    QWidget(parent),
    m_image{}
{
  m_image = QImage(m_width,m_height,QImage::Format::Format_RGB32);
}

void QtFractionImage::paintEvent(QPaintEvent *)
{
  QPainter painter(this);
  //painter.drawPixmap(0,0,m_width,m_height,QPixmap::fromImage(m_image));
  painter.drawPixmap(0,0,this->width(),this->height(),QPixmap::fromImage(m_image));
}

void QtFractionImage::Set(const Grid& grid)
{
  assert(static_cast<int>(grid.size()) == m_height);
  assert(static_cast<int>(grid[0].size()) == m_width);
  for (int y{0}; y!=m_height; ++y)
  {
    for (int x{0}; x!=m_width; ++x)
    {
      assert(grid[y][x] >= 0.0);
      assert(grid[y][x] <= 1.0);
      const double color_angle{grid[y][x] * 270.0};
      QColor color;
      color.setHsv(color_angle,254,254);
      int r,g,b;
      color.getRgb(&r,&g,&b);
      m_image.setPixel(x,y,qRgb(r,g,b));
    }
  }
  repaint();
}
