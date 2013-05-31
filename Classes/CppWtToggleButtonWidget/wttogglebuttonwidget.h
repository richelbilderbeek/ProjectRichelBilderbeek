//---------------------------------------------------------------------------
/*
WtToggleButtonWidget, Wt widget for displaying the ToggleButton class
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
//From http://www.richelbilderbeek.nl/CppWtToggleButtonWidget.htm
//---------------------------------------------------------------------------
#ifndef WTTOGGLEBUTTONWIDGET_H
#define WTTOGGLEBUTTONWIDGET_H
//---------------------------------------------------------------------------
#include <string>
#include <vector>
//---------------------------------------------------------------------------
#include <boost/signals2.hpp>
//---------------------------------------------------------------------------
#include <Wt/WPaintDevice>
#include <Wt/WPaintedWidget>
//---------------------------------------------------------------------------
namespace Wt { struct WMouseEventEvent; }
struct ToggleButton;
struct ToggleButtonWidget;
//---------------------------------------------------------------------------
///WtToggleButtonWidget displays a ToggleButton
struct WtToggleButtonWidget : public Wt::WPaintedWidget
{
  ///A WtToggleButtonWidget is created by its toggle state and its color
  explicit WtToggleButtonWidget(
    const bool toggled = false,
    const unsigned char red = 255,
    const unsigned char green = 255,
    const unsigned char blue = 255);

  ///Obtain a read-only pointer to the ToggleButtonWidget
  const ToggleButtonWidget * GetWidget() const { return m_widget.get(); }

  ///Obtain a read-and-write pointer to the ToggleButtonWidget
  ToggleButtonWidget * GetWidget() { return m_widget.get(); }

  ///Set the color of the WtToggleButtonWidget
  //void SetColor(
  //  const unsigned char red,
  //  const unsigned char green,
  //  const unsigned char blue);

  ///Obtain the WtToggleButtonWidget its version
  static const std::string GetVersion();

  ///Obtain the WtToggleButtonWidget its version history
  static const std::vector<std::string> GetVersionHistory();

  ///Draw the ToggleButton
  static void DrawToggleButton(
    Wt::WPainter& painter,
    const int x, const int y,
    const int width, const int height,
    const ToggleButton * const button);

  ///Draw the ToggleButton
  static void DrawToggleButton(
    Wt::WPainter& painter,
    const ToggleButtonWidget * const widget);

  protected:
  ///Paint the WtToggleButtonWidget
  void paintEvent(Wt::WPaintDevice *paintDevice);

  private:
  ///The ToggleButtonWidget
  boost::scoped_ptr<ToggleButtonWidget> m_widget;

  ///The WtToggleButtonWidget its red color intensity
  //unsigned char m_red;

  ///The WtToggleButtonWidget its green color intensity
  //unsigned char m_green;

  ///The WtToggleButtonWidget its blue color intensity
  //unsigned char m_blue;

  ///Do not let this be called by the client
  void resize(const Wt::WLength& width, const Wt::WLength& height);

  ///Repaint the WtToggleButtonWidget
  void DoRepaint();

  ///Respond to mouse click
  void OnClicked(const Wt::WMouseEvent& e);

  ///Respond to the widget resizing
  void OnResize();
};
//---------------------------------------------------------------------------
#endif // WTTOGGLEBUTTONWIDGET_H
