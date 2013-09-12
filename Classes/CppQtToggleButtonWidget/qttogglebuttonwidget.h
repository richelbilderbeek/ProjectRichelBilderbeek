//---------------------------------------------------------------------------
/*
QtToggleButtonWidget, Qt widget for displaying the ToggleButtonWidget class
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
//From http://www.richelbilderbeek.nl/CppQtToggleButtonWidget.htm
//---------------------------------------------------------------------------
#ifndef QTTOGGLEBUTTONWIDGET_H
#define QTTOGGLEBUTTONWIDGET_H

#include <string>
#include <vector>


#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/signals2.hpp>
#include <QWidget>
#pragma GCC diagnostic pop

namespace ribi {

struct ToggleButton;
struct ToggleButtonWidget;

///QtToggleButtonWidget displays a ToggleButton
struct QtToggleButtonWidget : public QWidget
{
  ///A QtToggleButtonWidget is created by its toggle state and its color
  QtToggleButtonWidget(
    const bool toggled = false,
    const unsigned char red = 255,
    const unsigned char green = 255,
    const unsigned char blue = 255);

  ///Obtain a read-only pointer to the ToggleButton
  const ToggleButtonWidget * GetWidget() const { return m_widget.get(); }

  ///Obtain a read-and-write pointer to the ToggleButton
  ToggleButtonWidget * GetWidget() { return m_widget.get(); }

  ///Signal that is emitted when a QtToggleButtonWidget is toggled
  mutable boost::signals2::signal<void ()> m_signal_toggled;

  ///Obtain the QtToggleButtonWidget its version
  static const std::string GetVersion();

  ///Obtain the QtToggleButtonWidget its version history
  static const std::vector<std::string> GetVersionHistory();

  ///Draw a ToggleButton from a ToggleButton
  static void DrawToggleButton(
    QPainter& painter,
    const int left, const int top,
    const int width, const int height,
    const ToggleButton * const toggle_button);

  ///Draw a ToggleButton from a ToggleButtonWidget
  static void DrawToggleButton(
    QPainter& painter,
    const ToggleButtonWidget * const widget);

  protected:
  ///Paint the QtToggleButtonWidget
  void paintEvent(QPaintEvent * event);

  ///Resize the QtToggleButtonWidget
  void resizeEvent(QResizeEvent *);

  private:

  ///The ToggleButton
  boost::scoped_ptr<ToggleButtonWidget> m_widget;

  ///Repaint the QtToggleButtonWidget
  void DoRepaint();

  ///Respond to mouse click
  void mousePressEvent(QMouseEvent * e);
};

} //~namespace ribi

#endif // QTTOGGLEBUTTONWIDGET_H
