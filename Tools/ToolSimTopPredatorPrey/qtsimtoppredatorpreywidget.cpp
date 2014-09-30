#include "qtsimtoppredatorpreywidget.h"

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

void SimTopPredatorPreyWidget::Set(const int z)
{
  for (int y{0}; y!=m_height; ++y)
  {
    for (int x{0}; x!=m_width; ++x)
    {
      m_image.setPixel(
        x,
        y,
        qRgb((x+z)%256,(y+z)%256,(x+y+z)%256));
    }
  }
  repaint();
}
