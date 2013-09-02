//---------------------------------------------------------------------------
/*
QtLedWidget, Qt widget for displaying the Led class
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
//From http://www.richelbilderbeek.nl/CppQtLedWidget.htm
//---------------------------------------------------------------------------
#ifndef QTLEDWIDGET_H
#define QTLEDWIDGET_H

#include <boost/scoped_ptr.hpp>

#include <QWidget>

#include "led.h"       //Needed by MOC
#include "ledwidget.h" //Needed by MOC

class QtLedWidget : public QWidget
{
  Q_OBJECT
public:
  explicit QtLedWidget(
    QWidget *parent = 0,
    const double intensity    = 0.0,
    const unsigned char red   = 255,
    const unsigned char green =   0,
    const unsigned char blue  =   0);
  const LedWidget * GetWidget() const { return m_widget.get(); }
  LedWidget * GetWidget() { return m_widget.get(); }

  ///Draw a Led from a Led
  static void DrawLed(
    QPainter& painter,
    const int left, const int top,
    const int width, const int height,
    const Led * const led);

  ///Draw a Led from a LedWidget
  static void DrawLed(
    QPainter& painter,
    const LedWidget * const widget);


protected:
  void paintEvent(QPaintEvent *);
  void resizeEvent(QResizeEvent *);

private:
  boost::scoped_ptr<LedWidget> m_widget;

  ///OnResize is called when the geometry of the LedWidget is changed
  void OnResize();

public:
  static const std::string GetVersion();
  static const std::vector<std::string> GetVersionHistory();

};

#endif // QTLEDWIDGET_H
