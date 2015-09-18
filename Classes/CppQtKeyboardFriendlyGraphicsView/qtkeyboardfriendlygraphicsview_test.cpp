#include "qtkeyboardfriendlygraphicsview.h"

#ifndef NDEBUG
#include <cassert>

#include <QKeyEvent>
#include <QGraphicsRectItem>

#include "testtimer.h"
#include "counter.h"
#include "trace.h"

namespace ribi {
  namespace qtkeyboardfriendlygraphicsview {
    QKeyEvent CreateDown() noexcept { return QKeyEvent(QEvent::KeyPress,Qt::Key_Down,Qt::NoModifier); }
    QKeyEvent CreateLeft() noexcept { return QKeyEvent(QEvent::KeyPress,Qt::Key_Left,Qt::NoModifier); }
    QKeyEvent CreateRight() noexcept { return QKeyEvent(QEvent::KeyPress,Qt::Key_Right,Qt::NoModifier); }
    QKeyEvent CreateSpace() noexcept { return QKeyEvent(QEvent::KeyPress,Qt::Key_Space,Qt::NoModifier); }
    QKeyEvent CreateUp() noexcept { return QKeyEvent(QEvent::KeyPress,Qt::Key_Up,Qt::NoModifier); }
  }
}

void ribi::QtKeyboardFriendlyGraphicsView::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  {
    Counter();
  }
  using namespace ribi::qtkeyboardfriendlygraphicsview;
  const TestTimer test_timer(__func__,__FILE__,1.0);
  const bool verbose{true};
  QtKeyboardFriendlyGraphicsView view;
  QGraphicsRectItem * const item1{new QGraphicsRectItem};
  QGraphicsRectItem * const item2{new QGraphicsRectItem};
  item1->setFlag(QGraphicsItem::ItemIsFocusable);
  item2->setFlag(QGraphicsItem::ItemIsFocusable);
  item1->setFlag(QGraphicsItem::ItemIsSelectable);
  item2->setFlag(QGraphicsItem::ItemIsSelectable);
  view.scene()->addItem(item1);
  view.scene()->addItem(item2);

  if (verbose) { TRACE("Space selects one random item"); }
  {
    item1->setSelected(false);
    item2->setSelected(false);
    assert(view.scene()->selectedItems().empty());
    auto space = CreateSpace();
    view.keyPressEvent(&space);
    assert(view.scene()->selectedItems().size() == 1);
  }
  if (verbose) { TRACE("Space causes m_signal_update to be emitted"); }
  {
    item1->setSelected(false);
    item2->setSelected(false);
    assert(view.scene()->selectedItems().empty());

    Counter c{0}; //For receiving the signal
    view.m_signal_update.connect(
      boost::bind(&ribi::Counter::Inc,&c) //Do not forget the &
    );

    auto space = CreateSpace();
    view.keyPressEvent(&space);

    assert(c.Get() > 0);
  }

}
#endif


