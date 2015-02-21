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
#ifndef QTCHORDRELATIONSWIDGET_H
#define QTCHORDRELATIONSWIDGET_H


#include <boost/shared_ptr.hpp>
#include <QGraphicsView>
struct QGraphicsScene;

namespace ribi {

namespace Music { struct ChordVertex; struct Chord; }

struct QtChordRelationsWidget : public QGraphicsView
{
  QtChordRelationsWidget(QWidget *parent = 0);

  ///Obtain this class its version number
  static std::string GetVersion() noexcept;

  ///Obtain this class its version history
  static std::vector<std::string> GetVersionHistory() noexcept;

  ///Set the collection of chords
  void SetChords(std::vector<boost::shared_ptr<Music::Chord> >& chords);

  void resizeEvent(QResizeEvent *event);

  private:
  QGraphicsScene * const m_scene;
};

} //~namespace ribi

#endif // QTCHORDRELATIONSWIDGET_H
