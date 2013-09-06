//---------------------------------------------------------------------------
/*
QtShapeWidget, Qt class for displaying a ShapeWidget
Copyright (C) 2011 Richel Bilderbeek

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program. If not, see <http://www.gnu.org/licenses/>.
*/
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/CppQtShapeWidget.htm
//---------------------------------------------------------------------------
#ifndef QTSHAPEWIDGET_H
#define QTSHAPEWIDGET_H

#include <string>
#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/scoped_ptr.hpp>
#include <boost/signals2.hpp>
#pragma GCC diagnostic pop

#include <QWidget>

#include "shape.h" //For MOC
#include "shapewidget.h" //For MOC

namespace ribi {

///QtShapeWidget manages and displays a Shape
class QtShapeWidget : public QWidget
{
  Q_OBJECT
public:
  explicit QtShapeWidget(QWidget *parent = 0);

  QtShapeWidget(boost::shared_ptr<ShapeWidget> widget,
    QWidget *parent = 0);

  void paintEvent(QPaintEvent *);

  mutable boost::signals2::signal<void ()> m_signal_position_changed;

  ///Draw a shape from a Shape
  static void DrawShape(
    QPainter& painter,
    const int left, const int top,
    const int width, const int height,
    const Shape * const shape);

  ///Draw a shape from a ShapeWidget
  static void DrawShape(
    QPainter& painter,
    const ShapeWidget * const widget);

  ShapeWidget * GetWidget() const { return m_widget.get(); }
  const ShapeWidget * GetWidget() { return m_widget.get(); }

private:
  boost::shared_ptr<ShapeWidget> m_widget;

public:
  static const std::string GetVersion();
  static const std::vector<std::string> GetVersionHistory();
};

} //~namespace ribi

#endif // QTSHAPEWIDGET_H

