//---------------------------------------------------------------------------
/*
BeerWanter. A simple game.
Copyright (C) 2005-2015 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/GameBeerWanter.htm
//---------------------------------------------------------------------------
#ifndef QTBEERWANTERWIDGET_H
#define QTBEERWANTERWIDGET_H

#include <tuple>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include <boost/scoped_ptr.hpp>
#include <boost/shared_ptr.hpp>
#include <QWidget>
#include "beerwantermaindialog.h"
#pragma GCC diagnostic pop

struct QMouseEvent;
struct QPixmap;
struct QTimer;

namespace ribi {

struct BeerWanterMainDialog;

class QtBeerWanterWidget : public QWidget
{
  Q_OBJECT

public:
  explicit QtBeerWanterWidget(QWidget *parent = 0);
  const BeerWanterMainDialog * GetBeerWanter() const;

private:
  std::tuple<int,int,int> m_background_rgb;

  std::string m_debug_text;

  boost::scoped_ptr<BeerWanterMainDialog> m_dialog;

  boost::shared_ptr<QPixmap> m_sprite;
  boost::shared_ptr<QTimer> m_timer;

  ///Modify the color value, keep it in unsigned char range
  void Modify(int& color);

private slots:
  void mouseMoveEvent(QMouseEvent * event);
  void mousePressEvent(QMouseEvent * event);
  void onTimer();
  void paintEvent(QPaintEvent *);

signals:
  void DoShake(const int x,const int y);
  void LevelUp(const std::string&);

private:
  //From http://www.richelbilderbeek.nl/CppPaint.htm
  static void MyPaint(
    QPixmap& pixmap,
    const unsigned char r,
    const unsigned char g,
    const unsigned char b,
    const unsigned char a = 255); //Opaque
};

} //~namespace ribi

#endif // QTBEERWANTERWIDGET_H

