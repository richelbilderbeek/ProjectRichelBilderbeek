//---------------------------------------------------------------------------
/*
WtLedDisplayWidget, Wt widget for displaying the Led class
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
//From http://www.richelbilderbeek.nl/CppWtLedDisplayWidget.htm
//---------------------------------------------------------------------------
#ifndef WTLEDDISPLAYWIDGET_H
#define WTLEDDISPLAYWIDGET_H
//---------------------------------------------------------------------------
#include <string>
#include <vector>
//---------------------------------------------------------------------------
#include <boost/signals2.hpp>
//---------------------------------------------------------------------------
#include <Wt/WPaintDevice>
#include <Wt/WPaintedWidget>
//---------------------------------------------------------------------------
struct Led;
//---------------------------------------------------------------------------
struct WtLedDisplayWidget : public Wt::WPaintedWidget
{
  WtLedDisplayWidget(
    const double intensity    = 0.0,
    const unsigned char red   = 255,
    const unsigned char green =   0,
    const unsigned char blue  =   0);
  const Led * GetLed() const { return m_led.get(); }
  Led * GetLed() { return m_led.get(); }

  static const std::string GetVersion();
  static const std::vector<std::string> GetVersionHistory();

  protected:
  void paintEvent(Wt::WPaintDevice *paintDevice);
  private:
  boost::scoped_ptr<Led> m_led;

  void DoRepaint();
};
//---------------------------------------------------------------------------
#endif // WTLEDDISPLAYWIDGET_H
