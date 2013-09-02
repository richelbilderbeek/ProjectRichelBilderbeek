//---------------------------------------------------------------------------
/*
QtShinyButtonWidget, Qt widget for displaying the ShinyButton class
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
//From http://www.richelbilderbeek.nl/CppQtShinyButtonWidget.htm
//---------------------------------------------------------------------------
#ifndef QTSHINYBUTTONWIDGET_H
#define QTSHINYBUTTONWIDGET_H

#include <string>
#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <boost/signals2.hpp>
#pragma GCC diagnostic pop

#include <QWidget>

#include "shinybutton.h" //For MOC
#include "shinybuttonwidget.h" //For MOC

struct QtToggleButtonWidget;

///QtShinyButtonWidget displays a ShinyButton
struct QtShinyButtonWidget : public QWidget
{
  Q_OBJECT

  public:

  explicit QtShinyButtonWidget(QWidget *parent = 0);

  ///A QtShinyButtonWidget is created by its width and height
  QtShinyButtonWidget(
    const double color,
    const double gradient,
    const std::string& text = "",
    const Rect rect = Rect(80,20),
    QWidget *parent = 0);

  static void DrawShinyButton(
    QPainter& painter,
    const int left, const int top,
    const int width, const int height,
    const ShinyButton * const button);

  ///Draw a ShinyButton
  static void DrawShinyButton(
    QPainter& painter,
    const ShinyButtonWidget * const widget);

  ///Obtain a read-only pointer to the ShinyButton
  const ShinyButtonWidget * GetWidget() const { return m_widget.get(); }

  ///Obtain a read-and-write pointer to the ShinyButton
  ShinyButtonWidget * GetWidget() { return m_widget.get(); }

  ///Signal that is emitted when a QtShinyButtonWidget is toggled
  mutable boost::signals2::signal<void ()> m_signal_changed;

  ///Obtain the QtShinyButtonWidget its version
  static const std::string GetVersion();

  ///Obtain the QtShinyButtonWidget its version history
  static const std::vector<std::string> GetVersionHistory();

  protected:
  ///Respond to mouse clicks
  void mousePressEvent(QMouseEvent *);

  ///Paint the QtShinyButtonWidget
  void paintEvent(QPaintEvent *);

  ///Resize the QtShinyButtonWidget
  void resizeEvent(QResizeEvent *);

  private:

  ///The ShinyButton
  boost::scoped_ptr<ShinyButtonWidget> m_widget;

  ///Repaint the QtShinyButtonWidget
  void DoRepaint();

  ///Respond to mouse click
  //void OnClicked(const Wt::WMouseEvent& e);
};

#endif // WTSHINYBUTTONWIDGET_H
