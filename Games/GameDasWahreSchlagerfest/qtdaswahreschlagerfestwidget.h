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
#include <QWidget>
#include "daswahreschlagerfestwidget.h"
#include "daswahreschlagerfestdisplay.h"
#pragma GCC diagnostic pop

struct DasWahreSchlagerfestWidget;
namespace Ui {
  class QtDasWahreSchlagerfestWidget;
}

namespace ribi {

class QtDasWahreSchlagerfestWidget : public QWidget, public ribi::DasWahreSchlagerfestDisplay
{
  Q_OBJECT
    
public:
  explicit QtDasWahreSchlagerfestWidget(QWidget *parent = 0) noexcept;

  void Display(const DasWahreSchlagerfestWidget& widget) override;
  void OnChanged(const DasWahreSchlagerfestWidget& widget) override;

protected:
  void keyPressEvent(QKeyEvent *) noexcept;
  void paintEvent(QPaintEvent *) noexcept;

private:
  boost::shared_ptr<DasWahreSchlagerfestWidget> m_widget;
  const QPixmap m_beer;
  const QPixmap m_bratwurst;
  const QPixmap m_empty;
  const QPixmap m_richel;

  ///Obtain the pixmap for this tile
  const QPixmap& GetPixmap(const DasWahreSchlagerfestWidget::Tile& tile) const noexcept;


};

} //~namespace ribi


#endif // QTDASWAHRESCHLAGERFESTWIDGET_H
