//---------------------------------------------------------------------------
/*
BeerWanter. A simple game.
Copyright (C) 2005-2012 Richel Bilderbeek

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
//From hhtp://www.richelbilderbeek.nl/GameBeerWanter.htm
//---------------------------------------------------------------------------
#ifndef QTBEERWANTERWIDGET_H
#define QTBEERWANTERWIDGET_H
//---------------------------------------------------------------------------
#include <boost/scoped_ptr.hpp>
#include <boost/shared_ptr.hpp>
#include <QWidget>
#include "beerwantermaindialog.h"
//---------------------------------------------------------------------------
struct BeerWanterMainDialog;
//struct QGraphicsPixmapItem;
//struct QGraphicsScene;
//struct QGraphicsView;
struct QMouseEvent;
struct QPixmap;
//struct QVBoxLayout;
struct QTimer;
//---------------------------------------------------------------------------
class QtBeerWanterWidget : public QWidget
{
  Q_OBJECT

public:
  explicit QtBeerWanterWidget(QWidget *parent = 0);
  const BeerWanterMainDialog * GetBeerWanter() const;

private:
  boost::shared_ptr<QTimer> m_timer;
  boost::shared_ptr<QPixmap> m_sprite;
  void mousePressEvent(QMouseEvent * event);
  virtual void mouseMoveEvent(QMouseEvent * event);
  boost::scoped_ptr<BeerWanterMainDialog> m_beerwanter;
  void paintEvent(QPaintEvent *);
  std::string m_debug_text;

private slots:
  void onTimer();

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
//---------------------------------------------------------------------------
#endif // QTBEERWANTERWIDGET_H
//---------------------------------------------------------------------------
