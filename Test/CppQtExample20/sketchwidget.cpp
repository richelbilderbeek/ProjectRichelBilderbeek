#include "sketchwidget.h"

#include <cassert>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <QMouseEvent>
#include <QPainter>
#pragma GCC diagnostic pop

SketchWidget::SketchWidget(QWidget *parent)
  : QWidget(parent),
    m_points{}
{
  this->setMouseTracking(true);
}

void SketchWidget::clear()
{
  m_points.clear();
  this->repaint();
}

void SketchWidget::mouseMoveEvent(QMouseEvent * e)
{
  if (e->buttons() & Qt::LeftButton)
  {
    m_points.back().push_back(e->pos());
    this->repaint();
  }
}

void SketchWidget::mousePressEvent(QMouseEvent * e)
{
  if (e->buttons() & Qt::LeftButton)
  {
    m_points.push_back(std::vector<QPoint>());
    m_points.back().push_back(e->pos());
  }
}

void SketchWidget::paintEvent(QPaintEvent *)
{
  QPainter painter(this);
  {
    QPen pen = painter.pen();
    pen.setCapStyle(Qt::RoundCap);
    pen.setWidth(10);
    painter.setPen(pen);
  }

  const int n_lines = static_cast<int>(m_points.size());
  for (int line=0; line!=n_lines; ++line)
  {
    const std::vector<QPoint>& points = m_points[line];
    const int n_points = static_cast<int>(points.size());
    for (int point=1; point!=n_points; ++point)
    {
      painter.drawLine(points[point-1],points[point]);
    }
  }
}


