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
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "qtchordvertex.h"

#include <QBrush>
#include <QPainter>
#pragma GCC diagnostic pop

ribi::QtChordVertex::QtChordVertex(
  boost::shared_ptr<Music::Chord>& chord,
  QGraphicsItem *parent)
  : QGraphicsItem(parent), m_chord(chord), m_color(200,200,200)
{
  //this->setFlag(ItemIsMovable);
  {
    //Set the ToolTip
    const std::vector<Music::Note> notes = chord->GetNotes();
    std::string s;
    std::for_each(notes.begin(),notes.end(),
      [&s](const Music::Note& note) { s += note.ToStr() + "-"; } );
    s.resize(s.size() - 1);
    this->setToolTip(s.c_str());
  }
}


QRectF ribi::QtChordVertex::boundingRect() const
{
  return QRectF(-32.0,-32.0,64.0,64.0);
}


void ribi::QtChordVertex::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
  painter->setBrush(QBrush(m_color));
  painter->drawEllipse(this->boundingRect());

  painter->drawText(
    boundingRect().adjusted(16.0,22.0,0.0,-22.0),
    m_chord->ToStr().c_str());
}

std::string ribi::QtChordVertex::GetVersion() noexcept
{
  return "1.2";
}

std::vector<std::string> ribi::QtChordVertex::GetVersionHistory() noexcept
{
  std::vector<std::string> v;
  v.push_back("2012-08-10: version 1.0: initial version");
  v.push_back("2012-08-17: version 1.1: added SetColor method");
  v.push_back("2013-07-25: version 1.2: transition to Qt5");
  return v;
}
