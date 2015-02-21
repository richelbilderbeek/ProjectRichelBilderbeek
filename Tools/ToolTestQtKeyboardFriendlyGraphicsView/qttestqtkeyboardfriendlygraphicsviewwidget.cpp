//---------------------------------------------------------------------------
/*
TestKeyboardFriendlyGraphicsView, tests QtKeyboardFriendlyGraphicsView
Copyright (C) 2012-2015 Richel Bilderbeek

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program.If not, see <http://www.gnu.org/licenses/>.
*/
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/ToolTestKeyboardFriendlyGraphicsView.htm
//---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "qttestqtkeyboardfriendlygraphicsviewwidget.h"

#include <boost/array.hpp>
#include <boost/lambda/lambda.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/math/constants/constants.hpp>

#include <QKeyEvent>

#include "qtarrowitem.h"
#include "qtdisplaypositem.h"
#include "qtleftrightrectitem.h"
#include "qtroundedrectitem.h"
#include "qtpatharrowitem.h"
#include "testtimer.h"
#include "qtroundededitrectitem.h"
#include "qtquadbezierarrowitem.h"
#include "trace.h"
#pragma GCC diagnostic pop

ribi::QtTestKeyboardFriendlyGraphicsViewWidget::QtTestKeyboardFriendlyGraphicsViewWidget()
  : m_signal_request_about{},
    m_signal_request_quit{}
{
  #ifndef NDEBUG
  Test();
  #endif
  const double pi = boost::math::constants::pi<double>();
  {
    //Legend
    const double midx = 0.0;
    const double midy = 0.0;
    const double ray = 100.0;
    QGraphicsEllipseItem * const circle = new QGraphicsEllipseItem(midx - ray, midy - ray,2.0 * ray,2.0 * ray);
    scene()->addItem(circle);
    {
      QGraphicsTextItem * const item = new QGraphicsTextItem("ESC: Quit");
      scene()->addItem(item);
      item->setPos(midx + 0.0 - item->boundingRect().center().x(),midy - 20.0 - item->boundingRect().center().y());
    }
    {
      QGraphicsTextItem * const item = new QGraphicsTextItem("a: about");
      scene()->addItem(item);
      item->setPos(midx + 0.0 - item->boundingRect().center().x(),midy + 20.0 - item->boundingRect().center().y());
    }

  }

  {
    //QGraphicsRectItems
    typedef QGraphicsRectItem Item;
    const double midx =    0.0;
    const double midy = -200.0;
    const int n = 3;
    const double ray = 100.0;
    QGraphicsTextItem * const text = new QGraphicsTextItem("QGraphicsRectItem");
    text->setPos(midx - text->boundingRect().center().x(),midy - text->boundingRect().center().y());
    scene()->addItem(text);
    QGraphicsEllipseItem * const circle = new QGraphicsEllipseItem(midx - ray, midy - ray,2.0 * ray,2.0 * ray);
    scene()->addItem(circle);

    for (int i=0; i!=n; ++i)
    {
      const double angle = 2.0 * pi * static_cast<double>(i) / static_cast<double>(n);
      const double x = midx + (std::sin(angle) * 0.5 * ray);
      const double y = midy - (std::cos(angle) * 0.5 * ray);
      Item * const item = new Item;
      item->setPos(x,y);
      item->setRect(-16.0,-16.0,32.0,32.0);
      item->setFlags(QGraphicsItem::ItemIsFocusable | QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable);
      scene()->addItem(item);
    }
  }
  {
    //QtRoundedRectItem
    typedef QtRoundedRectItem Item;
    const double midx =   0.0;
    const double midy = 200.0;
    const int n = 3;
    const double ray = 100.0;
    QGraphicsTextItem * const text = new QGraphicsTextItem("QtRoundedRectItem");
    text->setPos(midx - text->boundingRect().center().x(),midy - text->boundingRect().center().y());
    scene()->addItem(text);
    QGraphicsEllipseItem * const circle = new QGraphicsEllipseItem(midx - ray, midy - ray,2.0 * ray,2.0 * ray);
    scene()->addItem(circle);
    for (int i=0; i!=n; ++i)
    {
      const double angle = 2.0 * pi * static_cast<double>(i) / static_cast<double>(n);
      const double x = midx + (std::sin(angle) * 0.5 * ray);
      const double y = midy - (std::cos(angle) * 0.5 * ray);
      Item * const item = new Item;
      item->SetCenterPos(x,y);
      scene()->addItem(item);
    }
  }
  {
    //QtRoundedTextRectItem
    typedef QtRoundedEditRectItem Item;
    const double midx = 174.0;
    const double midy = 300.0;
    const int n = 3;
    const double ray = 100.0;
    QGraphicsTextItem * const text = new QGraphicsTextItem("QtRoundedEditRectItem");
    text->setPos(midx - text->boundingRect().center().x(),midy - text->boundingRect().center().y());
    scene()->addItem(text);
    QGraphicsEllipseItem * const circle = new QGraphicsEllipseItem(midx - ray, midy - ray,2.0 * ray,2.0 * ray);
    scene()->addItem(circle);
    for (int i=0; i!=n; ++i)
    {
      const double angle = 2.0 * pi * static_cast<double>(i) / static_cast<double>(n);
      const double x = midx + (std::sin(angle) * 0.5 * ray);
      const double y = midy - (std::cos(angle) * 0.5 * ray);
      Item * const item = new Item;
      item->SetCenterPos(x,y);
      //item->setRect(-16.0,-16.0,32.0,32.0);
      scene()->addItem(item);
    }
  }
  {
    //QtLeftRightRectItem
    typedef QtLeftRightRectItem Item;
    const double midx = 174.0;
    const double midy = 100.0;
    const int n = 3;
    const double ray = 100.0;
    QGraphicsTextItem * const text = new QGraphicsTextItem("QtLeftRightRectItem");
    text->setPos(midx - text->boundingRect().center().x(),midy - text->boundingRect().center().y());
    scene()->addItem(text);
    QGraphicsEllipseItem * const circle = new QGraphicsEllipseItem(midx - ray, midy - ray,2.0 * ray,2.0 * ray);
    scene()->addItem(circle);
    for (int i=0; i!=n; ++i)
    {
      const double angle = 2.0 * pi * static_cast<double>(i) / static_cast<double>(n);
      const double x = midx + (std::sin(angle) * 0.5 * ray);
      const double y = midy - (std::cos(angle) * 0.5 * ray);
      Item * const item = new Item;
      item->setPos(x,y);
      //item->setRect(-16.0,-16.0,32.0,32.0);
      scene()->addItem(item);
    }
  }
  {
    //QtDisplayPosItem
    typedef QtDisplayPosItem Item;
    const double midx =  174.0;
    const double midy = -100.0;
    const int n = 3;
    const double ray = 100.0;
    QGraphicsTextItem * const text = new QGraphicsTextItem("QtDisplayPosItem");
    text->setPos(midx - text->boundingRect().center().x(),midy - text->boundingRect().center().y());
    scene()->addItem(text);
    QGraphicsEllipseItem * const circle = new QGraphicsEllipseItem(midx - ray, midy - ray,2.0 * ray,2.0 * ray);
    scene()->addItem(circle);
    for (int i=0; i!=n; ++i)
    {
      const double angle = 2.0 * pi * static_cast<double>(i) / static_cast<double>(n);
      const double x = midx + (std::sin(angle) * 0.5 * ray);
      const double y = midy - (std::cos(angle) * 0.5 * ray);
      Item * const item = new Item;
      item->setPos(x - item->boundingRect().center().x(),y - item->boundingRect().center().y());
      //item->setPos(x,y);
      //item->setRect(-16.0,-16.0,32.0,32.0);
      scene()->addItem(item);
    }
  }
  {
    //QtQuadBezierArrow
    typedef QtQuadBezierArrowItem Item;
    const double midx = -174.0;
    const double midy =  100.0;
    const int n = 3;
    const double ray = 100.0;
    QGraphicsTextItem * const text = new QGraphicsTextItem("QtQuadBezierArrowItem");
    text->setPos(midx - text->boundingRect().center().x(),midy - text->boundingRect().center().y());
    scene()->addItem(text);
    QGraphicsEllipseItem * const circle = new QGraphicsEllipseItem(midx - ray, midy - ray,2.0 * ray,2.0 * ray);
    scene()->addItem(circle);

    for (int i=0; i!=n; ++i)
    {
      const double angle = 2.0 * pi * static_cast<double>(i) / static_cast<double>(n);
      boost::array<QGraphicsItem *,3> v;
      v.assign(nullptr); assert(v[0] == nullptr && v[1] == nullptr && v[2] == nullptr);
      for (int j=0; j!=3; ++j)
      {
        const double sub_ray = 90.0;
        const double sub_angle = angle + (2.0 * 2.0 * pi * static_cast<double>(j + 1) / static_cast<double>( (3 + 2) * n));
        const double x = midx + std::sin(sub_angle) * sub_ray;
        const double y = midy - std::cos(sub_angle) * sub_ray;
        QtRoundedRectItem * const item = new QtRoundedRectItem;
        item->SetOuterWidth(16.0);
        item->SetOuterHeight(8.0);
        //item->SetOuterRoundedRect(QRectF(-4.0,-4.0,8.0,8.0),1.0,1.0);
        item->SetCenterPos(x,y);
        scene()->addItem(item);
        v[j] = item;
      }
      {
        assert(v[0] && v[1] && v[2]);
        Item * const item = new Item(v[0],false,v[1],true,v[2]);
        scene()->addItem(item);
      }
    }
  }
  {
    //QtArrowItem
    typedef QtArrowItem Item;
    const double midx = -174.0;
    const double midy =  300.0;
    const int n = 3;
    const double ray = 100.0;
    QGraphicsTextItem * const text = new QGraphicsTextItem("QtArrowItem");
    text->setPos(midx - text->boundingRect().center().x(),midy - text->boundingRect().center().y());
    scene()->addItem(text);
    QGraphicsEllipseItem * const circle = new QGraphicsEllipseItem(midx - ray, midy - ray,2.0 * ray,2.0 * ray);
    scene()->addItem(circle);

    for (int i=0; i!=n; ++i)
    {
      const double angle = 2.0 * pi * static_cast<double>(i) / static_cast<double>(n);
      const double x1 = midx + std::sin(angle) * 0.5 * ray;
      const double y1 = midy - std::cos(angle) * 0.5 * ray;
      const double x2 = midx + std::sin(angle) * 0.9 * ray;
      const double y2 = midy - std::cos(angle) * 0.9 * ray;
      Item * const item = new Item(x1,y1,false,x2,y2,true);
      item->m_signal_item_requests_scene_update.connect(boost::bind(&This::DoUpdateScene,this));
      scene()->addItem(item);
    }
  }
  {
    //QtPathArrowItem
    typedef QtPathArrowItem Item;
    const double midx = -348.0;
    const double midy =  200.0;
    const int n = 3;
    const double ray = 100.0;
    QGraphicsTextItem * const text = new QGraphicsTextItem("QtPathArrowItem");
    text->setPos(midx - text->boundingRect().center().x(),midy - text->boundingRect().center().y());
    scene()->addItem(text);
    QGraphicsEllipseItem * const circle = new QGraphicsEllipseItem(midx - ray, midy - ray,2.0 * ray,2.0 * ray);
    scene()->addItem(circle);

    for (int i=0; i!=n; ++i)
    {
      const double angle = 2.0 * pi * static_cast<double>(i) / static_cast<double>(n);
      const double x1 = midx + std::sin(angle) * 0.5 * ray;
      const double y1 = midy - std::cos(angle) * 0.5 * ray;

      const double x_mid = midx + std::sin(angle + 0.1) * 0.7 * ray;
      const double y_mid = midy - std::cos(angle + 0.1) * 0.7 * ray;

      const double x2 = midx + std::sin(angle) * 0.9 * ray;
      const double y2 = midy - std::cos(angle) * 0.9 * ray;
      Item * const item = new Item(QPointF(x1,y1),false, { QPointF(x_mid,y_mid) },true,QPointF(x2,y2));
      item->m_signal_item_requests_scene_update.connect(boost::bind(&This::DoUpdateScene,this));
      scene()->addItem(item);
    }
  }

  {
    //QtRoundedEditRectItem
    typedef QtRoundedEditRectItem Item;
    const double midx = 2.0 * 174.0;
    const double midy = 0.0;
    const int n = 3;
    const double ray = 100.0;
    QGraphicsTextItem * const text = new QGraphicsTextItem("QtRoundedEditRectItem");
    text->setPos(midx - text->boundingRect().center().x(),midy - text->boundingRect().center().y());
    scene()->addItem(text);
    QGraphicsEllipseItem * const circle = new QGraphicsEllipseItem(midx - ray, midy - ray,2.0 * ray,2.0 * ray);
    scene()->addItem(circle);
    for (int i=0; i!=n; ++i)
    {
      const double angle = 2.0 * pi * static_cast<double>(i) / static_cast<double>(n);
      const double x = midx + (std::sin(angle) * 0.5 * ray);
      const double y = midy - (std::cos(angle) * 0.5 * ray);
      Item * const item = new Item;
      item->SetCenterPos(x,y);
      std::vector<std::string> text;
      text.push_back("* *");
      for (int j=0; j!=i; ++j)
      {
        const std::string s = std::string(j+2,'*') + " *";
        text.push_back(s);
      }

      item->SetText(text);
      //item->setRect(-16.0,-16.0,32.0,32.0);
      scene()->addItem(item);
    }
  }


}

void ribi::QtTestKeyboardFriendlyGraphicsViewWidget::DoUpdateScene()
{
  scene()->update();
}

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
void ribi::QtTestKeyboardFriendlyGraphicsViewWidget::keyPressEvent(QKeyEvent *event) noexcept
{
  switch (event->key())
  {

    case Qt::Key_Escape: m_signal_request_quit(); break;
    case Qt::Key_A     : m_signal_request_about(); break;
  }
  QtKeyboardFriendlyGraphicsView::keyPressEvent(event);
}
#pragma GCC diagnostic pop

#ifndef NDEBUG
void ribi::QtTestKeyboardFriendlyGraphicsViewWidget::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
}
#endif
