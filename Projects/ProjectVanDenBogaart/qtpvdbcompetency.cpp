#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif

//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#include "qtpvdbcompetency.h"

#include <cassert>
#include <QImage>
#include <QPixmap>
#include "trace.h"

namespace pvdb {

const std::map<pvdb::Competency,QColor> QtCompetency::m_color_map = QtCompetency::CreateColorMap();
//const std::map<pvdb::Competency,QIcon > QtCompetency::m_icon_map  = QtCompetency::CreateIconMap();
std::map<pvdb::Competency,QIcon > QtCompetency::m_icon_map;

pvdb::Competency QtCompetency::ColorToCompetency(const QColor& color)
{
  #ifndef NDEBUG
  Test();
  #endif
  const auto iter = std::find_if(m_color_map.begin(),m_color_map.end(),
    [color](const std::pair<pvdb::Competency,QColor>& p)
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

const QColor QtCompetency::CompetencyToColor(const pvdb::Competency competency)
{
  #ifndef NDEBUG
  Test();
  #endif
  const auto iter = m_color_map.find(competency);
  assert(iter!=m_color_map.end());
  return iter->second;
}

const QIcon QtCompetency::CompetencyToIcon(const pvdb::Competency competency)
{
  #ifndef NDEBUG
  Test();
  #endif
  if (m_icon_map.empty()) m_icon_map = CreateIconMap();
  assert(!m_icon_map.empty());
  const auto iter = m_icon_map.find(competency);
  assert(iter!=m_icon_map.end());
  QIcon icon = iter->second;
  assert(!icon.isNull());
  return icon;
}

const std::map<pvdb::Competency,QColor> QtCompetency::CreateColorMap()
{
  return
  {
    { pvdb::Competency::uninitialized      , Qt::white },
    { pvdb::Competency::profession         , Qt::red },
    { pvdb::Competency::organisations      , QColor(255,127,0) }, //Orange
    { pvdb::Competency::social_surroundings, Qt::yellow },
    { pvdb::Competency::target_audience    , Qt::green },
    { pvdb::Competency::ti_knowledge       , Qt::cyan },
    { pvdb::Competency::prof_growth        , Qt::blue },
    { pvdb::Competency::misc               , Qt::magenta }
  };
}

const std::map<pvdb::Competency,QIcon> QtCompetency::CreateIconMap()
{
  return
  {
    /*
    { pvdb::Competency::uninitialized      , QIcon(":/images/PicWhite14x14.png") },
    { pvdb::Competency::profession         , QIcon(":/images/PicPurple14x14.png") },
    { pvdb::Competency::organisations      , QIcon(":/images/PicBlue14x14.png") },
    { pvdb::Competency::social_surroundings, QIcon(":/images/PicCyan14x14.png") },
    { pvdb::Competency::target_audience    , QIcon(":/images/PicGreen14x14.png") },
    { pvdb::Competency::ti_knowledge       , QIcon(":/images/PicYelow14x14.png") },
    { pvdb::Competency::prof_growth        , QIcon(":/images/PicOrange14x14.png") },
    { pvdb::Competency::misc               , QIcon(":/images/PicRed14x14.png") }
    */
    { pvdb::Competency::uninitialized      , QIcon(":/images/PicWhite14x14.png") },
    { pvdb::Competency::profession         , QIcon(":/images/PicRed14x14.png") },
    { pvdb::Competency::organisations      , QIcon(":/images/PicOrange14x14.png") },
    { pvdb::Competency::social_surroundings, QIcon(":/images/PicYellow14x14.png") },
    { pvdb::Competency::target_audience    , QIcon(":/images/PicGreen14x14.png") },
    { pvdb::Competency::ti_knowledge       , QIcon(":/images/PicCyan14x14.png") },
    { pvdb::Competency::prof_growth        , QIcon(":/images/PicBlue14x14.png") },
    { pvdb::Competency::misc               , QIcon(":/images/PicPurple14x14.png") }
  };
}

pvdb::Competency QtCompetency::IconToCompetency(const QIcon& icon)
{
  #ifndef NDEBUG
  Test();
  #endif
  if (m_icon_map.empty()) m_icon_map = CreateIconMap();
  assert(!m_icon_map.empty());
  const auto iter = std::find_if(m_icon_map.begin(),m_icon_map.end(),
    [icon](const std::pair<pvdb::Competency,QIcon>& p)
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
void QtCompetency::Test()
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  //Conversion between QColor and pvdb::Competency
  {
    const std::vector<pvdb::Competency> v = pvdb::GetAllCompetencies();
    std::for_each(v.begin(),v.end(),
      [](const pvdb::Competency& competency)
      {
        QColor color = pvdb::QtCompetency::CompetencyToColor(competency);
        assert(pvdb::QtCompetency::ColorToCompetency(color) == competency);
      }
    );
  }
  //Conversion between QIcon and pvdb::Competency
  {
    const std::vector<pvdb::Competency> v = pvdb::GetAllCompetencies();
    std::for_each(v.begin(),v.end(),
      [](const pvdb::Competency& competency)
      {
        QIcon icon = pvdb::QtCompetency::CompetencyToIcon(competency);
        assert(pvdb::QtCompetency::IconToCompetency(icon) == competency);
      }
    );
  }
  TRACE("QtCompetency::Test finished successfully");

}
#endif

} //~namespace pvdb
