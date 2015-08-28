//---------------------------------------------------------------------------
/*
Das Wahre Schlagerfest, a simple game
Copyright (C) 2003-2015 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/GameDasWahreSchlagerfest.htm
//---------------------------------------------------------------------------
#ifndef QTDASWAHRESCHLAGERFESTWIDGET_H
#define QTDASWAHRESCHLAGERFESTWIDGET_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include <boost/shared_ptr.hpp>
#include <QImage>
#include <QWidget>
#include "daswahreschlagerfestdisplay.h"
#include "daswahreschlagerfestkey.h"
#include "daswahreschlagerfesttile.h"
#pragma GCC diagnostic pop

namespace Ui { class QtDwsWidget; }

namespace ribi {
namespace dws {

struct Widget;

class QtDwsWidget : public QWidget, public ribi::dws::Display
{
  Q_OBJECT
    
public:
  explicit QtDwsWidget(QWidget *parent = 0) noexcept;

  void DoDisplay(const Widget& widget) override;
  void OnChanged(const Widget& widget) override;
  ribi::dws::Key RequestKey() override;

protected:
  void keyPressEvent(QKeyEvent *) noexcept;
  void paintEvent(QPaintEvent *) noexcept;

private:
  const QPixmap m_beer;
  const QPixmap m_bratwurst;
  const QPixmap m_empty;

  //Will be painted
  QImage m_image;
  std::vector<Key> m_keys;
  const QPixmap m_richel;

  ///Obtain the pixmap for this tile
  const QPixmap& GetPixmap(const Tile& tile) const noexcept;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace dws
} //~namespace ribi


#endif // QTDASWAHRESCHLAGERFESTWIDGET_H
