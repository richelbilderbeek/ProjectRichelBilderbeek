//---------------------------------------------------------------------------
/*
WtDialWidget, Wt widget for displaying the Dial class
Copyright (C) 2011-2014 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/CppWtDialWidget.htm
//---------------------------------------------------------------------------
#ifndef WTDIALWIDGET_H
#define WTDIALWIDGET_H

#include <string>
#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-variable"
#include <boost/signals2.hpp>

#include <Wt/WPaintDevice>
#include <Wt/WPaintedWidget>
#pragma GCC diagnostic pop

namespace Wt { struct WMouseEventEvent; }

namespace ribi {

struct Dial;
struct DialWidget;

///Wt display widget of a Dial
struct WtDialWidget : public Wt::WPaintedWidget
{
  explicit WtDialWidget(
    const double intensity    = 0.0,
    const unsigned char red   = 255,
    const unsigned char green = 255,
    const unsigned char blue  = 255);

  const DialWidget * GetWidget() const { return m_widget.get(); }

  DialWidget * GetWidget() { return m_widget.get(); }

  ///Draw a Dial
  static void DrawDial(
    Wt::WPainter& painter,
    const int left, const int top,
    const int width, const int height,
    const Dial * const dial);

  ///Draw a Dial
  static void DrawDial(
    Wt::WPainter& painter,
    const DialWidget * const widget);

  static std::string GetVersion();
  static std::vector<std::string> GetVersionHistory();

  protected:
  void paintEvent(Wt::WPaintDevice *paintDevice);

  private:
  boost::scoped_ptr<DialWidget> m_widget;

  void DoRepaint();
  void OnClicked(const Wt::WMouseEvent& e);

  ///OnResize is called when the geometry of the widget is changed
  void OnResize();

  ///Wt resize: hide it from sight
  void resize(const Wt::WLength& width, const Wt::WLength& height);
};

} //~namespace ribi

#endif // WTLEDWIDGET_H
