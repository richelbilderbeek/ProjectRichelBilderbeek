#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "qttestqtroundedrectitemwidget.h"

#include <cassert>
#include <cmath>
#include <iostream>

#include <boost/math/constants/constants.hpp>

#include <QGraphicsScene>
#include <QKeyEvent>
#include <QGraphicsSimpleTextItem>

#include "qtroundedrectitem.h"
#include "testtimer.h"
#pragma GCC diagnostic pop

ribi::QtTestQtRoundedRectItemWidget::QtTestQtRoundedRectItemWidget(QWidget *parent)
  : ribi::QtKeyboardFriendlyGraphicsView(parent)
{
  const double pi = boost::math::constants::pi<double>();
  const int n_items = 16;
  for (int i=0; i!=n_items; ++i)
  {
    const double angle = 2.0 * pi * (static_cast<double>(i) / static_cast<double>(n_items));
    {
      const double ray = 200.0;
      const double x =  std::sin(angle) * ray;
      const double y = -std::cos(angle) * ray;
      QtRoundedRectItem * const item = new QtRoundedRectItem;
      assert(item);
      item->SetCenterPos(x,y);
      item->SetInnerWidth(64.0);
      item->SetInnerHeight(32.0);
      assert(scene());
      scene()->addItem(item);
    }
    {
      const double ray = 120.0;
      const double x =  std::sin(angle) * ray;
      const double y = -std::cos(angle) * ray;
      QGraphicsRectItem * const item = new QGraphicsRectItem;
      assert(item);
      item->setFlags(
          QGraphicsItem::ItemIsFocusable
        | QGraphicsItem::ItemIsMovable
        | QGraphicsItem::ItemIsSelectable
      );
      item->setPos(x,y);
      item->setRect(-16.0,-16.0,32.0,32.0);
      assert(scene());
      scene()->addItem(item);
    }
  }
  //Add texts
  {
    const std::vector<std::string> v
      =
      {
        "Goal: compare my custom class to the Qt class",
        "Outer ring: my custom QtRoundedRectItem",
        "Inner ring: Qt its QGraphicsRectItem (note that these do not indicate being selected)",
        "Space: set focus to random item",
        "Arrow keys: move focus",
        "Shift + arrow keys: move item"
        //"F2: edit item"
      };
    const int sz = boost::numeric_cast<int>(v.size());
    for (int i=0; i!=sz; ++i)
    {
      QGraphicsSimpleTextItem * const item = new QGraphicsSimpleTextItem(v[i].c_str());
      const double w = item->boundingRect().width();
      const double h = item->boundingRect().height();
      const double x = -300.0;
      const double y = -300.0 + (static_cast<double>(i - (sz/2)) * 20.0);
      item->setPos((-0.5 * w) + x,(-0.5 * h) + y);
      assert(!item->scene());
      scene()->addItem(item);
    }
  }

}
