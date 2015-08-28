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

#include <QApplication>
#include <QKeyEvent>
#include <QPainter>
#include <QPixmap>

#include "daswahreschlagerfestwidget.h"
#include "qtgraphics.h"
#include "testtimer.h"
#include "trace.h"
#pragma GCC diagnostic pop

ribi::dws::QtDwsWidget::QtDwsWidget(QWidget *parent) noexcept
  : QWidget(parent),
    m_beer(":/images/GameDasWahreSchlagerfestBeer.png"),
    m_bratwurst(":/images/GameDasWahreSchlagerfestBratwurst.png"),
    m_empty(":/images/GameDasWahreSchlagerfestSmiley.png"),
    m_image{QtGraphics().CreateImage(1000,600,0)},
    m_keys{},
    m_richel(":/images/GameDasWahreSchlagerfestRichel.png")
{
  #ifndef NDEBUG
  Test();
  #endif
  assert(m_beer.width() == 102);
  assert(m_bratwurst.width() == 102);
  assert(m_empty.width() == 102);
  assert(m_richel.width() == 102);

}

void ribi::dws::QtDwsWidget::DoDisplay(const Widget& /* widget */)
{
  qApp->processEvents();
  this->repaint();
  this->show();
}

const QPixmap& ribi::dws::QtDwsWidget::GetPixmap(const Tile& tile) const noexcept
{
  switch (tile)
  {
    case Tile::beer     : return m_beer;
    case Tile::bratwurst: return m_bratwurst;
    case Tile::empty    : return m_empty;
    case Tile::richel   : return m_richel;
  }
  assert(!"Should not get here");
  throw std::logic_error("ribi::dws::QtDwsWidget::GetPixmap");
}


void ribi::dws::QtDwsWidget::keyPressEvent(QKeyEvent * e) noexcept
{
  switch (e->key())
  {
    case Qt::Key_Right:  m_keys.push_back(Key::right); break;
    case Qt::Key_Down:   m_keys.push_back(Key::down); break;
    case Qt::Key_Left:   m_keys.push_back(Key::left); break;
    case Qt::Key_Escape: m_keys.push_back(Key::quit);
      this->close();
      return;
    default: return;
  }
}

void ribi::dws::QtDwsWidget::OnChanged(const Widget& widget)
{
  const std::vector<std::vector<Tile> > & v = widget.GetTiles();
  assert(!v.empty());
  const int rows = static_cast<int>(v.size()   );
  const int cols = static_cast<int>(v[0].size());
  if (width() != cols * m_beer.width() || height() != rows * m_beer.height())
  {
    const int width {cols * m_beer.width() };
    const int height{rows * m_beer.height()};
    this->setGeometry(0,0,width,height);
    m_image = QtGraphics().CreateImage(width,height,0);
  }
  const int block_width  = static_cast<double>(width() ) / static_cast<double>(cols);
  const int block_height = static_cast<double>(height()) / static_cast<double>(rows);
  for (int y=0; y!=rows; ++y)
  {
    assert(y < static_cast<int>(v.size()));
    const std::vector<Tile>& line = v[y];
    assert(cols == static_cast<int>(line.size()));
    const int y1 = static_cast<int>(block_height * static_cast<double>(y  ));
    //const int y2 = static_cast<int>(block_height * static_cast<double>(y+1));
    for (int x=0; x!=cols; ++x)
    {
      assert(x < static_cast<int>(line.size()));
      const QPixmap& pixmap = GetPixmap(line[x]);
      const int x1 = static_cast<int>(block_width * static_cast<double>(x  ));
      //const int x2 = static_cast<int>(block_width * static_cast<double>(x+1));
      QtGraphics().DrawImage(m_image,pixmap.toImage(),x1,y1);
      //painter.drawPixmap(x1,y1,block_width,block_height,pixmap);
    }
  }
  //Draw cursor
  {
    const Cursor cursor = widget.GetCursor();
    const int x = cursor.x * block_width;
    const int y = cursor.y * block_height;
    const QPixmap& pixmap = GetPixmap(cursor.tile);
    QtGraphics().DrawImage(m_image,pixmap.toImage(),x,y);
    //painter.drawPixmap(x,y,block_width,block_height,pixmap);

  }

  this->repaint();
}

void ribi::dws::QtDwsWidget::paintEvent(QPaintEvent *) noexcept
{
  QPainter painter(this);
  painter.drawImage(0,0,m_image);
}


ribi::dws::Key ribi::dws::QtDwsWidget::RequestKey()
{
  while (1)
  {
    qApp->processEvents();
    if (m_keys.empty()) continue;
    const auto key = m_keys.back();
    m_keys.clear();
    return key;
  }
}

#ifndef NDEBUG
void ribi::dws::QtDwsWidget::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  {
    QtGraphics();
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
}
#endif
