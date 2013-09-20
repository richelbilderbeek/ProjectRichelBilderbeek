//---------------------------------------------------------------------------
/*
Project Richel Bilderbeek, Richel Bilderbeek's work
Copyright (C) 2010-2013 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/ProjectRichelBilderbeek.htm
//---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "qtrichelbilderbeekmenuitemwidget.h"

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
#include <QMessageBox>

#include <QBrush>

#include "rainbow.h"
#include "richelbilderbeekprogram.h"
#include "qtrichelbilderbeekprogram.h"
#include "about.h"
#include "qtaboutdialog.h"
#include "qtroundedtextrectitem.h"
#include "richelbilderbeekprogramtypes.h"
#include "testqtroundedtextrectitemmenudialog.h"

#pragma GCC diagnostic pop

ribi::QtRichelBilderbeekMenuItemWidget::QtRichelBilderbeekMenuItemWidget(QWidget *parent)
  : QtKeyboardFriendlyGraphicsView(parent),
    m_signal_show{}
{
  assert(scene());
  scene()->clear();

  const std::vector<RichelBilderbeek::ProgramType> program_types {
    RichelBilderbeek::ProgramTypes::GetAll()
  };
  const int n_program_types = boost::numeric_cast<int>(program_types.size());
  const int n_cols = 5;
  const int n_rows = n_program_types / n_cols;
  for (int i = 0; i!=n_program_types; ++i)
  {
    QtRoundedTextRectItem * const item = new QtRoundedTextRectItem;

    const int col = i % n_cols;
    const int row = i / n_cols;
    const double w = item->boundingRect().width();
    const double h = item->boundingRect().height();
    const double x = -300.0 + (static_cast<double>(col) * 200.0);
    const double y = static_cast<double>(row-(n_rows/2)) * 22.0;

    assert(i < boost::numeric_cast<int>(program_types.size()));
    const boost::shared_ptr<RichelBilderbeek::Program> p
      = RichelBilderbeek::Program::CreateProgram(
        program_types[i]);
    const std::string s = p->GetScreenName();

    item->SetText(s);
    item->setPos(x,y);
    QPen pen = item->GetFocusPen();
    pen.setWidth(3);
    pen.setColor(QColor(255,0,0));
    item->SetFocusPen(pen);

    const double left = x;
    const double top = y;
    const double right = x + w;
    const double bottom = y + h;
    QLinearGradient brush(
      QPointF(left,top),
      QPointF(bottom,right)
    );
    {
      const double f = static_cast<double>(i) / static_cast<double>(n_program_types);
      double r,g,b;
      Rainbow::GetRgb(f,r,g,b); //RGB in range [0.0,1.0]
      //Make brighter
      r = (r + 1.0) / 2.0;
      g = (g + 1.0) / 2.0;
      b = (b + 1.0) / 2.0;
      QColor color(r * 255.0, g * 255.0, b * 255.0);
      brush.setColorAt(0.0,color);
    }
    {
      const double f = static_cast<double>((i + n_cols) % n_program_types) / static_cast<double>(n_program_types);
      double r,g,b;
      Rainbow::GetRgb(f,r,g,b); //RGB in range [0.0,1.0]
      //Make brighter
      r = (r + 1.0) / 2.0;
      g = (g + 1.0) / 2.0;
      b = (b + 1.0) / 2.0;
      QColor color(r * 255.0, g * 255.0, b * 255.0);
      brush.setColorAt(1.0,color);
    }
    item->setBrush(brush);
    //Rotation
    {
      const double f = static_cast<double>(std::rand()) / static_cast<double>(RAND_MAX);
      const double angle = -3.0 + (6.0 * f);
      item->setRotation(angle);

    }
    if (row == n_rows / 2 && col == 1)
    {
      item->setFocus();
    }

    scene()->addItem(item);
  }
}

void ribi::QtRichelBilderbeekMenuItemWidget::keyPressEvent(QKeyEvent *event)
{

  switch (event->key())
  {
    case Qt::Key_F1:
    case Qt::Key_Return:
    case Qt::Key_Space:
    {
      //Find the text on the item
      QGraphicsItem * const item = this->scene()->focusItem();
      QtRoundedTextRectItem * const text_item = dynamic_cast<QtRoundedTextRectItem*>(item);
      assert(text_item);
      const std::string text = text_item->GetText();
      m_signal_show(text);
    }
    return;
  }
  QtKeyboardFriendlyGraphicsView::keyPressEvent(event);
}
