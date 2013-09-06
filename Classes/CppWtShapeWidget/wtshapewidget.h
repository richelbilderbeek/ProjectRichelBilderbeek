//---------------------------------------------------------------------------
/*
WtShapeWidget, Wt class for displaying a ShapeWidget
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
//From http://www.richelbilderbeek.nl/CppWtShapeWidget.htm
//---------------------------------------------------------------------------
#ifndef WTSHAPEWIDGET_H
#define WTSHAPEWIDGET_H
//---------------------------------------------------------------------------
#include <string>
#include <vector>
//---------------------------------------------------------------------------
#include <boost/shared_ptr.hpp>
#include <boost/signals2.hpp>
//---------------------------------------------------------------------------
#include <Wt/WPaintedWidget>
#include <Wt/WPaintDevice>
//---------------------------------------------------------------------------

namespace ribi {

struct Shape;
struct ShapeWidget;
//---------------------------------------------------------------------------
///WtShapeWidget manages and displays a Shape
struct WtShapeWidget : public Wt::WPaintedWidget
{
  explicit WtShapeWidget(boost::shared_ptr<ShapeWidget> widget);

  ///Create a deep copy of WtShapeWidget for use with Wt
  WtShapeWidget * Clone() const;

  //mutable boost::signals2::signal<void ()> m_signal_position_changed;

  ///Draw a shape from a Shape
  static void DrawShape(
    Wt::WPainter& painter,
    const int left, const int top,
    const int width, const int height,
    const Shape * const shape);

  ///Draw a shape from a ShapeWidget
  static void DrawShape(
    Wt::WPainter& painter,
    const ShapeWidget * const widget);

  ShapeWidget * GetWidget() const { return m_widget.get(); }
  const ShapeWidget * GetWidget() { return m_widget.get(); }

private:
  ///The ShapeWidget
  boost::shared_ptr<ShapeWidget> m_widget;

  friend bool operator==(const WtShapeWidget& lhs, const WtShapeWidget& rhs);

  ///OnResize is called when the geometry of the widget is changed
  void OnResize();

  ///Wt paint event
  void paintEvent(Wt::WPaintDevice *paintDevice);

  ///Wt resize: hide it from sight
  void resize(const Wt::WLength& width, const Wt::WLength& height);

public:
  static const std::string GetVersion();
  static const std::vector<std::string> GetVersionHistory();
};
//---------------------------------------------------------------------------
bool operator==(const WtShapeWidget& lhs, const WtShapeWidget& rhs);


} //~namespace ribi

#endif // QTSHAPEWIDGET_H
//---------------------------------------------------------------------------
