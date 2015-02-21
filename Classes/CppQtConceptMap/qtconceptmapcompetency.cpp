//---------------------------------------------------------------------------
/*
QtConceptMap, Qt classes for display and interaction with ConceptMap
Copyright (C) 2013-2014 The Brainweaver Team

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
//From http://www.richelbilderbeek.nl/CppQtConceptMap.htm
//---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "qtconceptmapcompetency.h"

#include <cassert>

#include "conceptmapcompetencies.h"

#include <QImage>
#include <QPixmap>
#include "testtimer.h"
#include "trace.h"
#pragma GCC diagnostic pop

const std::map<ribi::cmap::Competency,QColor> ribi::cmap::QtCompetency::m_color_map = ribi::cmap::QtCompetency::CreateColorMap();
//const std::map<cmap::Competency,QIcon > ribi::cmap::QtCompetency::m_icon_map  = ribi::cmap::QtCompetency::CreateIconMap();
std::map<ribi::cmap::Competency,QIcon > ribi::cmap::QtCompetency::m_icon_map;

ribi::cmap::QtCompetency::QtCompetency()
{
  #ifndef NDEBUG
  Test();
  #endif
}

ribi::cmap::Competency ribi::cmap::QtCompetency::ColorToCompetency(const QColor& color) const
{
  const auto iter = std::find_if(m_color_map.begin(),m_color_map.end(),
    [color](const std::pair<cmap::Competency,QColor>& p)
    {
      return
           color.red() == p.second.red()
        && color.green() == p.second.green()
        && color.blue() == p.second.blue();
    }
  );
  assert(iter!=m_color_map.end());
  return iter->first;
}

QColor ribi::cmap::QtCompetency::CompetencyToColor(const cmap::Competency competency) const
{
  const auto iter = m_color_map.find(competency);
  assert(iter!=m_color_map.end());
  return iter->second;
}

QIcon ribi::cmap::QtCompetency::CompetencyToIcon(const cmap::Competency competency) const
{
  if (m_icon_map.empty()) m_icon_map = CreateIconMap();
  assert(!m_icon_map.empty());
  const auto iter = m_icon_map.find(competency);
  assert(iter!=m_icon_map.end());
  QIcon icon = iter->second;
  assert(!icon.isNull());
  return icon;
}

const std::map<ribi::cmap::Competency,QColor> ribi::cmap::QtCompetency::CreateColorMap()
{
  return
  {
    { cmap::Competency::uninitialized      , Qt::white },
    { cmap::Competency::profession         , Qt::red },
    { cmap::Competency::organisations      , QColor(255,127,0) }, //Orange
    { cmap::Competency::social_surroundings, Qt::yellow },
    { cmap::Competency::target_audience    , Qt::green },
    { cmap::Competency::ti_knowledge       , Qt::cyan },
    { cmap::Competency::prof_growth        , Qt::blue },
    { cmap::Competency::misc               , Qt::magenta }
  };
}

const std::map<ribi::cmap::Competency,QIcon> ribi::cmap::QtCompetency::CreateIconMap()
{
  return
  {
    /*
    { cmap::Competency::uninitialized      , QIcon(":/images/PicWhite14x14.png") },
    { cmap::Competency::profession         , QIcon(":/images/PicPurple14x14.png") },
    { cmap::Competency::organisations      , QIcon(":/images/PicBlue14x14.png") },
    { cmap::Competency::social_surroundings, QIcon(":/images/PicCyan14x14.png") },
    { cmap::Competency::target_audience    , QIcon(":/images/PicGreen14x14.png") },
    { cmap::Competency::ti_knowledge       , QIcon(":/images/PicYelow14x14.png") },
    { cmap::Competency::prof_growth        , QIcon(":/images/PicOrange14x14.png") },
    { cmap::Competency::misc               , QIcon(":/images/PicRed14x14.png") }
    */
    { cmap::Competency::uninitialized      , QIcon(":/images/PicWhite14x14.png") },
    { cmap::Competency::profession         , QIcon(":/images/PicRed14x14.png") },
    { cmap::Competency::organisations      , QIcon(":/images/PicOrange14x14.png") },
    { cmap::Competency::social_surroundings, QIcon(":/images/PicYellow14x14.png") },
    { cmap::Competency::target_audience    , QIcon(":/images/PicGreen14x14.png") },
    { cmap::Competency::ti_knowledge       , QIcon(":/images/PicCyan14x14.png") },
    { cmap::Competency::prof_growth        , QIcon(":/images/PicBlue14x14.png") },
    { cmap::Competency::misc               , QIcon(":/images/PicPurple14x14.png") }
  };
}

ribi::cmap::Competency ribi::cmap::QtCompetency::IconToCompetency(const QIcon& icon) const
{
  #ifndef NDEBUG
  Test();
  #endif
  if (m_icon_map.empty()) m_icon_map = CreateIconMap();
  assert(!m_icon_map.empty());
  const auto iter = std::find_if(m_icon_map.begin(),m_icon_map.end(),
    [icon](const std::pair<cmap::Competency,QIcon>& p)
    {

      return icon.pixmap(14,14).toImage() == (p.second).pixmap(14,14).toImage();
      //return icon.name() == (p.second).name();
      //assert(icon.pixmap().size() == (p.second).pixmap().size());
      //return icon.pixmap() == (p.second).pixmap();
    }
  );
  assert(iter!=m_icon_map.end());
  return iter->first;
}

#ifndef NDEBUG
void ribi::cmap::QtCompetency::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  const TestTimer test_timer{__func__,__FILE__,0.1};
  //Conversion between QColor and cmap::Competency
  {
    const std::vector<cmap::Competency> v = Competencies().GetAllCompetencies();
    std::for_each(v.begin(),v.end(),
      [](const cmap::Competency& competency)
      {
        QColor color = ribi::cmap::QtCompetency().CompetencyToColor(competency);
        assert(ribi::cmap::QtCompetency().ColorToCompetency(color) == competency);
      }
    );
  }
  //Conversion between QIcon and cmap::Competency
  {
    const std::vector<cmap::Competency> v = Competencies().GetAllCompetencies();
    std::for_each(v.begin(),v.end(),
      [](const cmap::Competency& competency)
      {
        QIcon icon = ribi::cmap::QtCompetency().CompetencyToIcon(competency);
        assert(ribi::cmap::QtCompetency().IconToCompetency(icon) == competency);
      }
    );
  }

}
#endif
