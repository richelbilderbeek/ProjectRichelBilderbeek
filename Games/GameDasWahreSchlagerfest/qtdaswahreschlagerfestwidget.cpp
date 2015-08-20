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
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "qtdaswahreschlagerfestwidget.h"

#include <QKeyEvent>
#include <QPainter>
#include <QPixmap>
#include "daswahreschlagerfestwidget.h"
#pragma GCC diagnostic pop

ribi::QtDasWahreSchlagerfestWidget::QtDasWahreSchlagerfestWidget(QWidget *parent) noexcept
  : QWidget(parent),
    m_widget(new DasWahreSchlagerfestWidget(this)),
    m_beer(":/images/GameDasWahreSchlagerfestBeer.png"),
    m_bratwurst(":/images/GameDasWahreSchlagerfestBratwurst.png"),
    m_empty(":/images/GameDasWahreSchlagerfestSmiley.png"),
    m_richel(":/images/GameDasWahreSchlagerfestRichel.png")
{
  assert(m_beer.width() == 102);
  assert(m_bratwurst.width() == 102);
  assert(m_empty.width() == 102);
  assert(m_richel.width() == 102);
}

void ribi::QtDasWahreSchlagerfestWidget::Display(const DasWahreSchlagerfestWidget& /* widget */)
{
  this->repaint();
}

const QPixmap& ribi::QtDasWahreSchlagerfestWidget::GetPixmap(const DasWahreSchlagerfestWidget::Tile& tile) const noexcept
{
  switch (tile)
  {
    case DasWahreSchlagerfestWidget::Tile::beer     : return m_beer;
    case DasWahreSchlagerfestWidget::Tile::bratwurst: return m_bratwurst;
    case DasWahreSchlagerfestWidget::Tile::empty    : return m_empty;
    case DasWahreSchlagerfestWidget::Tile::richel   : return m_richel;
  }
  assert(!"Should not get here");
  throw std::logic_error("ribi::QtDasWahreSchlagerfestWidget::GetPixmap");
}


void ribi::QtDasWahreSchlagerfestWidget::keyPressEvent(QKeyEvent * e) noexcept
{
  DasWahreSchlagerfestWidget::Key key;
  switch (e->key())
  {
    case Qt::Key_Up:     key = DasWahreSchlagerfestWidget::Key::up; break;
    case Qt::Key_Right:  key = DasWahreSchlagerfestWidget::Key::right; break;
    case Qt::Key_Down:   key = DasWahreSchlagerfestWidget::Key::down; break;
    case Qt::Key_Left:   key = DasWahreSchlagerfestWidget::Key::left; break;
    case Qt::Key_Escape: this->close(); return;
    default: return;
  }
  m_widget->PressKey(key);
}

void ribi::QtDasWahreSchlagerfestWidget::OnChanged(const DasWahreSchlagerfestWidget& /* widget */)
{
  this->repaint();
}

void ribi::QtDasWahreSchlagerfestWidget::paintEvent(QPaintEvent *) noexcept
{
  QPainter painter(this);
  const std::vector<std::vector<DasWahreSchlagerfestWidget::Tile> > & v = m_widget->GetTiles();
  assert(!v.empty());
  const int maxy = static_cast<int>(v.size()   );
  const int maxx = static_cast<int>(v[0].size());
  const int block_width  = static_cast<double>(width() ) / static_cast<double>(maxx);
  const int block_height = static_cast<double>(height()) / static_cast<double>(maxy);

  for (int y=0; y!=maxy; ++y)
  {
    assert(y < static_cast<int>(v.size()));
    const std::vector<DasWahreSchlagerfestWidget::Tile>& line = v[y];
    assert(maxx == static_cast<int>(line.size()));
    const int y1 = static_cast<int>(block_height * static_cast<double>(y  ));
    //const int y2 = static_cast<int>(block_height * static_cast<double>(y+1));
    for (int x=0; x!=maxx; ++x)
    {
      assert(x < static_cast<int>(line.size()));
      const QPixmap& pixmap = GetPixmap(line[x]);
      const int x1 = static_cast<int>(block_width * static_cast<double>(x  ));
      //const int x2 = static_cast<int>(block_width * static_cast<double>(x+1));
      //painter.drawPixmap(x1,y1,x2,y2,*pixmap);
      //painter.drawPixmap(x1,y1,x2,y2,*pixmap);
      painter.drawPixmap(x1,y1,block_width,block_height,pixmap);
    }
  }
  //Draw cursor
  {
    const DasWahreSchlagerfestWidget::Cursor cursor = m_widget->GetCursor();
    const int x = cursor.x * block_width;
    const int y = cursor.y * block_height;
    const QPixmap& pixmap = GetPixmap(cursor.tile);
    painter.drawPixmap(x,y,block_width,block_height,pixmap);

  }
}

