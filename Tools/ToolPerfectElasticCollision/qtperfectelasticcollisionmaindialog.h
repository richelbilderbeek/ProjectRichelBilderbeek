//---------------------------------------------------------------------------
/*
PerfectElasticCollision, tool to investigate a perfect elastic collision
Copyright (C) 2010-2015 Richel Bilderbeek

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program.If not, see <http://www.gnu.org/licenses/>.
*/
//---------------------------------------------------------------------------
//From hhtp://www.richelbilderbeek.nl/ToolPerfectElasticCollision.htm
//---------------------------------------------------------------------------
#ifndef QTPERFECTELASTICCOLLISIONMAINDIALOG_H
#define QTPERFECTELASTICCOLLISIONMAINDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "qthideandshowdialog.h"
#pragma GCC diagnostic pop

struct QTimer;

namespace Ui {
  class QtPerfectElasticCollisionMainDialog;
}

namespace ribi {

class QtPerfectElasticCollisionMainDialog : public QtHideAndShowDialog
{
  Q_OBJECT

public:
  explicit QtPerfectElasticCollisionMainDialog(QWidget *parent = 0);
  QtPerfectElasticCollisionMainDialog(const QtPerfectElasticCollisionMainDialog&) = delete;
  QtPerfectElasticCollisionMainDialog& operator=(const QtPerfectElasticCollisionMainDialog&) = delete;
  ~QtPerfectElasticCollisionMainDialog() noexcept;

protected:
  void paintEvent(QPaintEvent*);

private:
  Ui::QtPerfectElasticCollisionMainDialog *ui;
  QTimer * const m_timer;

private slots:
  void onAnyChange();
  void onCheck();
  void onTimer();


  //From http://www.richelbilderbeek.nl/CppDrawGlobe.htm
  static QPixmap DrawGlobe(
    const int width,
    const int height,
    const unsigned char r,
    const unsigned char g,
    const unsigned char b);

  //From http://www.richelbilderbeek.nl/CppPaint.htm
  static void Paint(
  QPixmap& pixmap,
  const unsigned char r,
  const unsigned char g,
  const unsigned char b,
  const unsigned char a = 255);

  //From http://www.richelbilderbeek.nl/CppDoPerfectElasticCollision.htm
  static void DoPerfectElasticCollision(
  const double angleCollision,
  double& angle1,
  double& speed1,
  double& angle2,
  double& speed2);

  ///Obtain the angle in radians between two deltas
  ///12 o'clock is 0.0 * pi
  /// 3 o'clock is 0.5 * pi
  /// 6 o'clock is 1.0 * pi
  /// 9 o'clock is 1.5 * pi
  //From www.richelbilderbeek.nl/CppGetAngle.htm
  static double GetAngle(const double dx, const double dy);

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace ribi

#endif // QTPERFECTELASTICCOLLISIONMAINDIALOG_H
