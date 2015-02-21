//---------------------------------------------------------------------------
/*
QtRoundedRectItem, rectangular-shaped QGraphicsItem
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
//From http://www.richelbilderbeek.nl/CppQtRoundedRectItem.htm
//---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "qtroundedrectitem.h"

#include <QCoreApplication>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsScene>
#include <QImage>
#include <QPainter>

#include "counter.h"
#include "testtimer.h"
#include "trace.h"
#pragma GCC diagnostic pop

#ifndef NDEBUG
void ribi::QtRoundedRectItem::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
  const bool verbose{false};
  if (verbose) { TRACE("Construction"); }
  {
    QtRoundedRectItem();
  }
  QtRoundedRectItem i;
  if (verbose) { TRACE("SetOuterX and GetOuterX must be symmetric"); }
  {
    const auto old_x = i.GetCenterX();
    const auto new_x = old_x + 10.0;
    i.SetCenterX(new_x);
    assert(std::abs(i.GetCenterX() - new_x) < 4.0);
  }
  if (verbose) { TRACE("SetOuterY and GetOuterY must be symmetric"); }
  {
    const auto old_y = i.GetCenterY();
    const auto new_y = old_y + 10.0;
    i.SetCenterY(new_y);
    assert(std::abs(i.GetCenterY() - new_y) < 4.0);
  }
  if (verbose) { TRACE("SetOuterPos and GetOuterPos must be symmetric"); }
  {
    const auto old_pos = i.GetCenterPos();
    const auto new_pos = old_pos + QPointF(10.0,10.0);
    i.SetCenterPos(new_pos);
    assert(std::abs(i.GetCenterPos().x() - new_pos.x()) < 2.0);
    assert(std::abs(i.GetCenterPos().y() - new_pos.y()) < 2.0);
  }
  if (verbose) { TRACE("SetOuterWidth and GetOuterWidth must be symmetric"); }
  {
    const auto old_width = i.GetOuterWidth();
    const auto new_width = old_width + 10.0;
    i.SetOuterWidth(new_width);
    assert(std::abs(i.GetOuterWidth() - new_width) < 2.0);
  }
  if (verbose) { TRACE("SetOuterHeight and GetOuterHeight must be symmetric"); }
  {
    const auto old_height = i.GetOuterHeight();
    const auto new_height = old_height + 10.0;
    i.SetOuterHeight(new_height);
    assert(std::abs(i.GetOuterHeight() - new_height) < 2.0);
  }
  if (verbose) { TRACE("SetInnerX and GetInnerX must be symmetric"); }
  {
    const auto old_x = i.GetCenterX();
    const auto new_x = old_x + 10.0;
    i.SetCenterX(new_x);
    assert(std::abs(i.GetCenterX() - new_x) < 2.0);
  }
  if (verbose) { TRACE("SetInnerY and GetInnerY must be symmetric"); }
  {
    const auto old_y = i.GetCenterY();
    const auto new_y = old_y + 10.0;
    i.SetCenterY(new_y);
    assert(std::abs(i.GetCenterY() - new_y) < 2.0);
  }
  if (verbose) { TRACE("SetInnerPos and GetInnerPos must be symmetric"); }
  {
    const auto old_pos = i.GetCenterPos();
    const auto new_pos = old_pos + QPointF(10.0,10.0);
    i.SetCenterPos(new_pos);
    assert(std::abs(i.GetCenterPos().x() - new_pos.x()) < 2.0);
    assert(std::abs(i.GetCenterPos().y() - new_pos.y()) < 2.0);
  }
  if (verbose) { TRACE("SetInnerHeight and GetInnerHeight must be symmetric"); }
  {
    const auto old_height = i.GetInnerHeight();
    const auto new_height = old_height + 10.0;
    i.SetInnerHeight(new_height);
    assert(std::abs(i.GetInnerHeight() - new_height) < 2.0);
  }
  if (verbose) { TRACE("SetInnerWidth and GetInnerWidth must be symmetric"); }
  {
    const auto old_width = i.GetInnerWidth();
    const auto new_width = old_width + 10.0;
    i.SetInnerWidth(new_width);
    //Difference has been measured to be 3.0
    assert(std::abs(i.GetInnerWidth() - new_width) < 4.0);
  }
  if (verbose) { TRACE("SetRadiusX and GetRadiusX must be symmetric"); }
  {
    const auto old_radius_x = i.GetRadiusX();
    const auto new_radius_x = old_radius_x + 10.0;
    i.SetRadiusX(new_radius_x);
    assert(std::abs(i.GetRadiusX() - new_radius_x) < 2.0);
  }
  if (verbose) { TRACE("SetRadiusY and GetRadiusY must be symmetric"); }
  {
    const auto old_radius_y = i.GetRadiusY();
    const auto new_radius_y = old_radius_y + 10.0;
    i.SetRadiusY(new_radius_y);
    assert(std::abs(i.GetRadiusY() - new_radius_y) < 2.0);
  }
  if (verbose) { TRACE("Position must be in GetOuterRect"); }
  {
    assert(i.GetOuterRect().contains(i.GetCenterPos()));
  }
  if (verbose) { TRACE("Position must be in GetInnerRect"); }
  {
    assert(i.GetInnerRect().contains(i.GetCenterPos()));
  }
  if (verbose) { TRACE("After changing the outer width and position, the Position must be in GetOuterRect"); }
  {
    i.SetOuterWidth(3.0);
    i.SetOuterHeight(3.0);
    i.SetCenterX(i.GetCenterX() + 10.0);
    i.SetCenterY(i.GetCenterY() + 10.0);
    assert(i.GetOuterRect().contains(i.GetCenterPos()));
  }
  if (verbose) { TRACE("After changing the inner width and position, the Position must be in GetInnerRect"); }
  {
    i.SetInnerWidth(3.0);
    i.SetInnerHeight(3.0);
    i.SetCenterX(i.GetCenterX() + 10.0);
    i.SetCenterY(i.GetCenterY() + 10.0);
    assert(i.GetInnerRect().contains(i.GetCenterPos()));
  }
  if (verbose) { TRACE("After a drag event, m_signal_pos_changed must be emitted"); }
  {
    //Cannot be tested
    //Counter c{0}; //For receiving the signal
    //i.m_signal_pos_changed.connect(
    //  boost::bind(&ribi::Counter::Inc,&c) //Do not forget the &
    //);
    //const QGraphicsSceneMouseEvent * const event{new QGraphicsSceneMouseEvent};
    //QCoreApplication::sendEvent(&i,event);
    //assert(c.Get() > 0);
  }
  if (verbose) { TRACE("GetInnerRect should not change if width of contour pen changes"); }
  {
    QGraphicsScene scene;
    scene.addItem(&i);
    i.setSelected(false);
    i.clearFocus();
    assert(!i.hasFocus() && !i.isSelected()
      && "Assume no focus, otherwise this test has no use");
    const auto before = i.GetInnerRect();
    const QPen old_pen{i.GetContourPen()};
    QPen new_pen{old_pen};
    new_pen.setWidth((old_pen.width() * 10) + 10);
    i.SetContourPen(new_pen);
    const auto after = i.GetInnerRect();
    assert(before == after);
    scene.removeItem(&i); //Otherwise i gets deleted
  }
  if (verbose) { TRACE("GetInnerRect should not change if width of focus pen changes"); }
  {
    QGraphicsScene scene;
    scene.addItem(&i);
    i.setSelected(false);
    i.clearFocus();
    assert(!i.hasFocus() && !i.isSelected()
      && "Assume no focus, otherwise this test has no use");
    const auto before = i.GetInnerRect();
    const QPen old_pen{i.GetContourPen()};
    QPen new_pen{old_pen};
    new_pen.setWidth((old_pen.width() * 10) + 10);
    i.SetFocusPen(new_pen);
    const auto after = i.GetInnerRect();
    assert(before == after);
    scene.removeItem(&i); //Otherwise i gets deleted
  }
  //#define NOT_NOW_20150112
  #ifdef NOT_NOW_20150112
  if (verbose) { TRACE("GetInnerRect should not change if width of focus pen changes and given focus"); }
  {
    QGraphicsScene scene;
    scene.addItem(&i);
    i.setSelected(false);
    i.clearFocus();
    assert(!i.hasFocus() && !i.isSelected()
      && "Assume no focus, otherwise this test has no use");
    const auto before = i.GetInnerRect();
    const QPen old_pen{i.GetContourPen()};
    QPen new_pen{old_pen};
    new_pen.setWidth((old_pen.width() * 10) + 10);

    i.SetFocusPen(new_pen);
    i.setFocus();
    i.setSelected(true);
    // Force repaint
    {
      //Create an image of the item
      QImage image(scene.sceneRect().size().toSize(), QImage::Format_ARGB32);
      // Start all pixels transparent
      image.fill(Qt::transparent);
      QPainter painter(&image);
      scene.render(&painter);
      image.save("tmp_bug244_pre.png");
    }
    assert(i.hasFocus());
    assert(i.isSelected());
    assert(i.hasFocus() && i.isSelected()
      && "Assume focus, otherwise this test has no use");
    const auto after = i.GetInnerRect();
    assert(before == after);
    scene.removeItem(&i); //Otherwise i gets deleted
  }
  if (verbose) { TRACE("Bug #244: Changing pens does not resize the raw QRect"); }
  // The GetInnerRect should always remain the same
  // Test procedure:
  // 1) Set the contour pen to wide
  // 2) Give the item focus
  // Now, the inner rectangle has gotten bigger. This should not be.

  {

    QGraphicsScene scene;
    scene.addItem(&i);

    //Set contour pen to width 20
    {
      auto contour_pen = i.GetContourPen();
      contour_pen.setWidth(20);
      i.SetContourPen(contour_pen);
    }
    //Set focus pen to width 1
    {
      auto focus_pen = i.GetFocusPen();
      focus_pen.setWidth(1);
      i.SetFocusPen(focus_pen);
      assert(i.GetFocusPen().width() == 1);
    }
    assert(i.GetContourPen().width() == 20);
    assert(i.GetCurrentPen().width() == 20);
    assert(i.GetFocusPen().width() == 1);

    //OK: inner width + 2 * contour pen width = outer width
    {
      const auto expected_outer_width
        = i.GetInnerWidth() + (2 * i.GetContourPen().width());
      const auto real_outer_width = i.GetOuterWidth();
      assert(std::abs(expected_outer_width - real_outer_width) < 4
        && "inner_width + 2 * contour_pen_width should be about the outer width"
      );
    }
    //big_rect_width is the outer rectangle of the QItem, as it is drawn
    const auto big_rect_width = i.GetOuterRect().width();
    TRACE("PAY ATTENTION!");
    //Set focus to QtNode
    i.setSelected(true);
    assert(i.GetCurrentPen() == i.GetFocusPen()
      && "Be sure that QtNode has focus now");
    //Paint it to file, to force a redraw
    {
      //Create an image of before
      QImage image(scene.sceneRect().size().toSize(), QImage::Format_ARGB32);
      // Start all pixels transparent
      image.fill(Qt::transparent);
      QPainter painter(&image);
      scene.render(&painter);
      image.save("tmp_bug244.png");
    }

    //ERROR: inner width + 2 * focus pen width != outer width
    {
      const auto expected_outer_width
        = i.GetInnerWidth() + (2 * i.GetFocusPen().width());
      const auto real_outer_width = i.GetOuterWidth();
      assert(std::abs(expected_outer_width - real_outer_width) < 4
        && "inner_width + 2 * focus_pen_width should be about the outer width"
      );
    }
    assert(i.GetContourPen().width() == 20);
    assert(i.GetCurrentPen().width() == 1);
    assert(i.GetFocusPen().width() == 1);

    //small_rect_width is the outer rectangle of the QItem, as it is drawn
    //
    //
    //   v---v   = small_rect_width
    // v-------v = big_rect_width
    //
    // +-------+
    // |       |
    // | +---+ |
    // | | X | |
    // | +---+ |
    // |       |
    // +-------+

    const auto small_rect_width = i.GetInnerRect().width();
    assert(small_rect_width + 4 < big_rect_width);

    scene.removeItem(&i); //Otherwise i gets deleted

    assert(!"Fixed, refactor, then check in");
  }
  assert(1==2);
  #endif // NOT_NOW_20150112
}
#endif

