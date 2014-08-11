#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "qttestqtroundededitrectitemwidget.h"

#include <cassert>
#include <cmath>
#include <iostream>

#include <boost/lexical_cast.hpp>

#include <QFontDialog>
#include <QGraphicsScene>
#include <QGraphicsSimpleTextItem>
#include <QIcon>
#include <QKeyEvent>
#include <QGraphicsSimpleTextItem>
#include <QPen>
#include "about.h"
#include "qtaboutdialog.h"
#include "qtroundededitrectitem.h"
#include "testqtroundededitrectitemmenudialog.h"
#include "trace.h"
#include "testtimer.h"
#pragma GCC diagnostic pop

ribi::QtTestQtRoundedEditRectItemWidget::QtTestQtRoundedEditRectItemWidget(QWidget *parent)
  : QtKeyboardFriendlyGraphicsView(parent)
{
  #ifndef NDEBUG
  Test();
  #endif
  //Display with default font
  this->Display(QtRoundedEditRectItem().GetFont());
}

void ribi::QtTestQtRoundedEditRectItemWidget::Display(const QFont& font)
{
  scene()->clear();

  //Add texts
  {
    const std::vector<std::string> v
      =
      {
        "F1: change font",
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
      const double y = -100.0 + (static_cast<double>(i - (sz/2)) * 20.0);
      item->setPos(-0.5 * w,(-0.5 * h) + y);
      assert(!item->scene());
      scene()->addItem(item);
    }
  }
  const int n_cols = 10;
  const int n_rows = 26 * 2; //Twice the number of chars in the alphabet
  double x = 0.0;
  for (int col=0; col!=n_cols; ++col)
  {
    double y = 0.0;
    double max_width = 0.0;
    for (int row=0; row!=n_rows; ++row)
    {
      QtRoundedEditRectItem * const item = new QtRoundedEditRectItem;
      item->SetFont(font);
      const char c = (row / 26 ? 'A' : 'a') + (row % 26);
      const std::string s
        = std::string(1 + col,c)
        + " "
        + boost::lexical_cast<std::string>(c);

      item->SetText( std::vector<std::string>(1 + col,s) );
      item->SetCenterPos(x,y);
      item->SetFocusPen(QPen(QColor(255,0,0),3.0));
      assert(!item->scene());
      scene()->addItem(item);

      y += item->boundingRect().height() + 2.0;
      max_width = std::max(max_width,item->boundingRect().width());
    }
    x += max_width + 6.0;
  }

}

void ribi::QtTestQtRoundedEditRectItemWidget::keyPressEvent(QKeyEvent *event) noexcept
{

  switch (event->key())
  {
    case Qt::Key_F1:
    {
      bool ok;
      static QFont font = QtRoundedEditRectItem().GetFont();
      const QFont new_font = QFontDialog::getFont(&ok, font, this);
      if (ok) { font = new_font; Display(font); }
    }
    return;
  }
  QtKeyboardFriendlyGraphicsView::keyPressEvent(event);
}

#ifndef NDEBUG
void ribi::QtTestQtRoundedEditRectItemWidget::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
}
#endif
