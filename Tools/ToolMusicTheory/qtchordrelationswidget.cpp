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
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "qtchordrelationswidget.h"

#include <boost/math/constants/constants.hpp>

#include <QGraphicsScene>
#include <QPainterPath>
#include <QPen>
#include "qtchordvertex.h"
#include "qtchordedge.h"
#include "musicchord.h"
#pragma GCC diagnostic pop

ribi::QtChordRelationsWidget::QtChordRelationsWidget(QWidget *parent)
 : QGraphicsView(parent),
   m_scene(new QGraphicsScene(this))
{
  this->setScene(m_scene); //Obligatory

  //Turn off the scrollbars, as they look ugly
  this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

std::string ribi::QtChordRelationsWidget::GetVersion() noexcept
{
  return "1.1";
}

std::vector<std::string> ribi::QtChordRelationsWidget::GetVersionHistory() noexcept
{
  std::vector<std::string> v;
  v.push_back("2012-08-10: version 1.0: initial version");
  v.push_back("2013-07-25: version 1.1: transition to Qt5");
  return v;
}

void ribi::QtChordRelationsWidget::resizeEvent(QResizeEvent *)
{
  m_scene->setSceneRect(this->rect());
}

void ribi::QtChordRelationsWidget::SetChords(std::vector<boost::shared_ptr<Music::Chord> >& chords)
{
  m_scene->clear();

  std::vector<QtChordVertex * > qt_chords;

  //Create QtChords and add them to the scene
  std::transform(chords.begin(),chords.end(),
    std::back_inserter(qt_chords),
    [this](boost::shared_ptr<Music::Chord>& chord)
    {
      //m_scene will delete these QtChords
      QtChordVertex * const qt_chord = new QtChordVertex(chord,0);
      m_scene->addItem(qt_chord);
      return qt_chord;
      //m_scene->addItem(qt_chord);
    }
  );
  //Position the qt_chords
  {
    //Circumference must be 64 * SQRT(2) * sz,
    //So ray must be circumference / 2 * M_PI
    const std::size_t sz = qt_chords.size();
    //const double ray = 2.0 * 64.0 * std::sqrt(2.0) * static_cast<double>(sz) / (2.0 * M_PI);
    const double ray = 0.4 * static_cast<double>(std::min(this->width(),this->height()));
    const double pi = boost::math::constants::pi<double>();
    const double d_angle = 2.0 * pi / static_cast<double>(sz);
    for (std::size_t i = 0; i!=sz; ++i)
    {
      const double angle = static_cast<double>(i) * d_angle;
      const double x = (0.5*static_cast<double>(this->width())) + (std::sin(angle)*ray);
      const double y = (0.5*static_cast<double>(this->height())) - (std::cos(angle)*ray);
      qt_chords[i]->setPos(x,y);
    }
  }

  //Create the edges based on the number of identical notes
  const std::size_t sz = chords.size();
  for (std::size_t i = 0; i!=sz; ++i)
  {
    //The indices of the notes
    const boost::shared_ptr<Music::Chord> x = chords[i];
    for (std::size_t j = i+1; j!=sz; ++j)
    {
      assert(j < sz);
      const boost::shared_ptr<Music::Chord> y = chords[j];
      const int same = Music::Chord::CountSameNotes(x,y);
      if (same)
      {
        QtChordEdge * const edge = new QtChordEdge(0);
        m_scene->addItem(edge);
        QPen pen;
        pen.setWidth(same * same);
        edge->setPen(pen);
        edge->setZValue(-1.0);
        edge->setLine(
          qt_chords[i]->pos().x(),
          qt_chords[i]->pos().y(),
          qt_chords[j]->pos().x(),
          qt_chords[j]->pos().y()
        );
      }
    }
  }
}
