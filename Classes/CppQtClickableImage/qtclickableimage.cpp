#include "qtimage.h"

#include <iostream>
#include <QMouseEvent>

QtImage::QtImage(QWidget *parent)
  : QLabel(parent),
    m_v{}
{
  this->setMouseTracking(true);
}

void QtImage::AddClickableRegion(const QRect& region,const std::function<void()>& function_to_do)
{
  m_v.push_back(std::make_pair(region,function_to_do));
}

void QtImage::mouseMoveEvent(QMouseEvent *e)
{
  bool is_arrow = true;
  //std::clog << e->pos().x() << ',' << e->pos().y() << '\n';
  for (const auto p: m_v)
  {
    if (p.first.contains(e->pos()))
    {
      is_arrow = false;
      //std::clog << e->pos().x() << ',' << e->pos().y() << '\n';
    }
  }
  this->setCursor(QCursor(is_arrow ? Qt::ArrowCursor : Qt::PointingHandCursor));
}

void QtImage::mousePressEvent(QMouseEvent *e)
{
  //std::clog << e->pos().x() << ',' << e->pos().y() << '\n';
  for (const auto p: m_v)
  {
    if (p.first.contains(e->pos()))
    {
      const auto f = p.second;
      f();
    }
  }
}
