#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "qtsketchwidget.h"

#include <cassert>

#include <QMouseEvent>
#include <QPainter>
#include <QSysInfo>
#pragma GCC diagnostic pop


QtSketchWidget::QtSketchWidget(QWidget *parent)
  : QWidget(parent)
{
  this->setMouseTracking(true);
}

void QtSketchWidget::clear()
{
  m_points.clear();
  this->repaint();
}

void QtSketchWidget::mouseMoveEvent(QMouseEvent * e)
{
  if (e->buttons() & Qt::LeftButton)
  {
    m_points.back().push_back(e->pos());
    this->repaint();
  }
}

void QtSketchWidget::mousePressEvent(QMouseEvent * e)
{
  if (e->buttons() & Qt::LeftButton)
  {
    m_points.push_back(std::vector<QPoint>());
    m_points.back().push_back(e->pos());
  }
}

void QtSketchWidget::paintEvent(QPaintEvent *)
{
  QPainter painter(this);
  {
    QPen pen = painter.pen();
    pen.setCapStyle(Qt::RoundCap);
    pen.setColor(Qt::gray);
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

