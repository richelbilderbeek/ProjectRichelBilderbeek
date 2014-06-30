//---------------------------------------------------------------------------
/*
TestQtRoundedTextRectItem, tool to test QtRoundedTextRectItem
Copyright (C) 2012-2014 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/ToolTestQtRoundedTextRectItem.htm
//---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "qttestqtroundedtextrectitemwidget.h"

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
#include "about.h"
#include "qtaboutdialog.h"
#include "qtroundedtextrectitem.h"
#include "testqtroundedtextrectitemmenudialog.h"
#pragma GCC diagnostic pop

ribi::QtTestQtRoundedTextRectItemWidget::QtTestQtRoundedTextRectItemWidget(QWidget *parent)
  : QtKeyboardFriendlyGraphicsView(parent)
{
  //Display with default font
  QtRoundedTextRectItem tmp;
  const QFont font = tmp.GetFont();
  this->Display(font);
}

void ribi::QtTestQtRoundedTextRectItemWidget::Display(const QFont& font)
{
  assert(scene());
  scene()->clear();

  //Add texts
  {
    const std::vector<std::string> v
      =
      {
        "F1: change font",
        "ESC: quit",
        "Space: set focus to random item",
        "Arrow keys: move focus",
        "Shift + arrow keys: move item",
        "F2: edit item"
      };
    const int sz = boost::numeric_cast<int>(v.size());
    for (int i=0; i!=sz; ++i)
    {
      QGraphicsSimpleTextItem * const item = new QGraphicsSimpleTextItem(v[i].c_str());
      const double w = item->boundingRect().width();
      const double h = item->boundingRect().height();
      const double y = static_cast<double>(i - (sz/2)) * 20.0;
      item->setPos(-0.5 * w,(-0.5 * h) + y);
      assert(!item->scene());
      scene()->addItem(item);
    }
  }
  const int n_cols = 2;
  const int n_rows = 26;
  for (int col=0; col!=n_cols; ++col)
  {
    const double x = -200.0 + (static_cast<double>(col) * 400.0);
    for (int row=0; row!=n_rows; ++row)
    {
      const double y = static_cast<double>(row-(n_rows/2)) * 22.0;
      QtRoundedTextRectItem * const item = new QtRoundedTextRectItem;
      item->SetFont(font);
      const char c = (col % 2  ? 'A' : 'a') + row;
      const std::string s
        = std::string(1 + (col/2),c)
        + " "
        + boost::lexical_cast<std::string>(c);
      item->SetText(s);
      item->SetPos(x,y);
      assert(!item->scene());
      scene()->addItem(item);
    }
  }

}

void ribi::QtTestQtRoundedTextRectItemWidget::keyPressEvent(QKeyEvent *event) noexcept
{

  switch (event->key())
  {
    case Qt::Key_F1:
    {
      bool ok;
      static QFont font = QtRoundedTextRectItem().GetFont();
      const QFont new_font = QFontDialog::getFont(&ok, font, this);
      if (ok) { font = new_font; Display(font); }
    }
    return;
  }
  QtKeyboardFriendlyGraphicsView::keyPressEvent(event);
}
