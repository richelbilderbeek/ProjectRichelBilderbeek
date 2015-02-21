//---------------------------------------------------------------------------
/*
MusicTheory, tool for visualizing my music theory
Copyright (C) 2012-2015 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/ToolMusicTheory.htm
//---------------------------------------------------------------------------
#ifndef QTCHORDVERTEX_H
#define QTCHORDVERTEX_H

#include <boost/shared_ptr.hpp>

#include <QGraphicsItem>

#include "musicchord.h"

namespace ribi {

///QtChord displays a Music::Chord
struct QtChordVertex : public QGraphicsItem
{
  QtChordVertex(
    boost::shared_ptr<Music::Chord>& chord,
    QGraphicsItem *parent = 0);

  //Thanks compiler, for reminding me to define this
  QRectF boundingRect() const;

  ///Obtain this class its version number
  static std::string GetVersion() noexcept;

  ///Obtain this class its version history
  static std::vector<std::string> GetVersionHistory() noexcept;

  //Thanks compiler, for reminding me to define this
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);

  ///Set the color
  void SetColor(const QColor color) { m_color = color; }

  private:
  ///The chord
  boost::shared_ptr<Music::Chord> m_chord;

  ///The color used to draw this vertex
  QColor m_color;
};

} //~namespace ribi

#endif // QTCHORDVERTEX_H
