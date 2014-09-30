#include "qtsimtoppredatorpreywidget.h"

#include <cassert>

#include <QImage>
#include <QPainter>

SimTopPredatorPreyWidget::SimTopPredatorPreyWidget(QWidget *parent) :
    QWidget(parent),
    m_image{}
{
  m_image = QImage(m_width,m_height,QImage::Format::Format_RGB32);
}

void SimTopPredatorPreyWidget::paintEvent(QPaintEvent *)
{
  QPainter painter(this);
  painter.drawPixmap(0,0,m_width,m_height,QPixmap::fromImage(m_image));
}

void SimTopPredatorPreyWidget::Set(const Grid& grid)
{
  assert(static_cast<int>(grid.size()) == m_height);
  assert(static_cast<int>(grid[0].size()) == m_width);
  for (int y{0}; y!=m_height; ++y)
  {
    for (int x{0}; x!=m_width; ++x)
    {
      const int color{static_cast<int>(grid[y][x] * 255.0)};
      m_image.setPixel(x,y,qRgb(color,color,color));
    }
  }
  repaint();
}
