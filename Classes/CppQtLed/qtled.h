//---------------------------------------------------------------------------
/*
QtLed, Qt widget for displaying the Led class
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
//From http://www.richelbilderbeek.nl/CppQtLed.htm
//---------------------------------------------------------------------------
#ifndef QTLED_H
#define QTLED_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <boost/shared_ptr.hpp>
#include <QWidget>
#pragma GCC diagnostic pop

namespace ribi {

struct Led;

///QtLed is the Qt display widhet of an LED
class QtLed : public QWidget
{
  Q_OBJECT
public:
  //Creates an Led
  explicit QtLed(
    const double intensity    = 0.0,
    const unsigned char red   = 255,
    const unsigned char green =   0,
    const unsigned char blue  =   0,
    QWidget *parent = 0
  );

  ///Draw a Led from a Led
  static void DrawLed(
    QPainter& painter,
    const int left, const int top,
    const int width, const int height,
    const Led& led
  ) noexcept;


  boost::shared_ptr<const Led> GetLed() const noexcept { return m_led; }
  boost::shared_ptr<      Led> GetLed()       noexcept { return m_led; }

  void SetLed(
    const boost::shared_ptr<Led>& led
  ) noexcept;

protected:
  void paintEvent(QPaintEvent *);
  //void resizeEvent(QResizeEvent *);

private:
  boost::shared_ptr<Led> m_led;

  ///OnResize is called when the geometry of the LedWidget is changed
  //void OnResize();
  void OnColorChanged(Led * const) noexcept;
  void OnIntensityChanged(Led * const) noexcept;

public:
  static std::string GetVersion() noexcept;
  static std::vector<std::string> GetVersionHistory() noexcept;

};

} //~namespace ribi

#endif // QTLED_H
