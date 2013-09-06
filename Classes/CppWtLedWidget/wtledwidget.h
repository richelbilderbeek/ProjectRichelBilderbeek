//---------------------------------------------------------------------------
/*
WtLedWidget, Wt widget for displaying the Led class
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
//From http://www.richelbilderbeek.nl/CppWtLedWidget.htm
//---------------------------------------------------------------------------
#ifndef WTLEDWIDGET_H
#define WTLEDWIDGET_H
//---------------------------------------------------------------------------
#include <string>
#include <vector>
//---------------------------------------------------------------------------
#include <boost/signals2.hpp>
//---------------------------------------------------------------------------
#include <Wt/WPaintDevice>
#include <Wt/WPaintedWidget>
//---------------------------------------------------------------------------

namespace ribi {

struct Led;
struct LedWidget;
//---------------------------------------------------------------------------
struct WtLedWidget : public Wt::WPaintedWidget
{
  explicit WtLedWidget(
    const double intensity    = 0.0,
    const unsigned char red   = 255,
    const unsigned char green =   0,
    const unsigned char blue  =   0);

  ///Draw a Led
  static void DrawLed(
    Wt::WPainter& painter,
    const int x, const int y,
    const int width, const int height,
    const Led * const led);

  ///Draw a Led
  static void DrawLed(
    Wt::WPainter& painter,
    const LedWidget * const widget);

  ///Get a read-only pointer to Led
  const LedWidget * GetWidget() const { return m_widget.get(); }

  ///Get a read-and-write pointer to Led
  LedWidget * GetWidget() { return m_widget.get(); }


  static const std::string GetVersion();
  static const std::vector<std::string> GetVersionHistory();

  protected:
  void paintEvent(Wt::WPaintDevice *paintDevice);
  private:
  boost::scoped_ptr<LedWidget> m_widget;

  void DoRepaint();

  ///OnResize is called when the geometry of the widget is changed
  void OnResize();

  ///Wt resize: hide it from sight
  void resize(const Wt::WLength& width, const Wt::WLength& height);
};

} //~namespace ribi

#endif // WTLEDWIDGET_H
