//---------------------------------------------------------------------------
/*
WtShinyButtonWidget, Wt widget for displaying the ShinyButton class
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
//From http://www.richelbilderbeek.nl/CppWtShinyButtonWidget.htm
//---------------------------------------------------------------------------
#ifndef WTSHINYBUTTONWIDGET_H
#define WTSHINYBUTTONWIDGET_H
//---------------------------------------------------------------------------
#include <string>
#include <vector>
//---------------------------------------------------------------------------
//#include <boost/signals2.hpp>
//---------------------------------------------------------------------------
#include <Wt/WPaintDevice>
#include <Wt/WPaintedWidget>
//---------------------------------------------------------------------------
namespace Wt { struct WMouseEventEvent; }
struct ShinyButton;
struct ShinyButtonWidget;
//---------------------------------------------------------------------------
///WtShinyButtonWidget displays a ShinyButton
struct WtShinyButtonWidget : public Wt::WPaintedWidget
{
  ///A WtShinyButtonWidget is created by its toggle state and its color
  explicit WtShinyButtonWidget(
    const double color,
    const double gradient,
    const std::string& text = "");

  ///Obtain a read-only pointer to the ShinyButtonWidget
  const ShinyButtonWidget * GetWidget() const { return m_widget.get(); }

  ///Obtain a read-and-write pointer to the ShinyButtonWidget
  ShinyButtonWidget * GetWidget() { return m_widget.get(); }

  ///Obtain the WtShinyButtonWidget its version
  static const std::string GetVersion();

  ///Obtain the WtShinyButtonWidget its version history
  static const std::vector<std::string> GetVersionHistory();

  ///Draw the ShinyButton
  static void DrawShinyButton(
    Wt::WPainter& painter,
    const int x, const int y,
    const int width, const int height,
    const ShinyButton * const button);

  ///Draw the ShinyButton
  static void DrawShinyButton(
    Wt::WPainter& painter,
    const ShinyButtonWidget * const widget);

  protected:
  ///Paint the WtShinyButtonWidget
  void paintEvent(Wt::WPaintDevice *paintDevice);

  private:
  ///The ShinyButtonWidget
  boost::scoped_ptr<ShinyButtonWidget> m_widget;

  ///Do not let this be called by the client
  void resize(const Wt::WLength& width, const Wt::WLength& height);

  ///Repaint the WtShinyButtonWidget
  void DoRepaint();

  ///Respond to mouse click
  void OnClicked(const Wt::WMouseEvent&);

  ///Respond to the widget resizing
  void OnResize();
};
//---------------------------------------------------------------------------
#endif // WTSHINYBUTTONWIDGET_H
