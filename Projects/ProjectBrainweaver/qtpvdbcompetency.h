#ifndef QTPVDBCOMPETENCY_H
#define QTPVDBCOMPETENCY_H

#include <map>
#include <QColor>
#include <QIcon>
#include "pvdbcompetency.h"

#include "pvdbfwd.h"

namespace ribi {

namespace pvdb {

///Class to convert pvdb::Competency to QColor and vice versa
struct QtCompetency
{
  ///Convert a QColor to a pvdb::Competency
  static pvdb::Competency ColorToCompetency(const QColor& color);

  ///Convert a pvdb::Competency to a QColor
  static const QColor CompetencyToColor(const pvdb::Competency competency);

  ///Convert a pvdb::Competency to a QIcon
  static const QIcon CompetencyToIcon(const pvdb::Competency competency);

  ///Convert a QIcon to a pvdb::Competency
  static pvdb::Competency IconToCompetency(const QIcon& icon);

  private:
  ///The map between pvdb::Competency and QColor
  static const std::map<pvdb::Competency,QColor> m_color_map;

  ///The map between pvdb::Competency and QIcon
  static std::map<pvdb::Competency,QIcon> m_icon_map;

  ///Create map between pvdb::Competency and QColor
  static const std::map<pvdb::Competency,QColor> CreateColorMap();

  ///Create map between pvdb::Competency and QIcon
  static const std::map<pvdb::Competency,QIcon> CreateIconMap();

  #ifndef NDEBUG
  ///Test this class
  static void Test();
  #endif
};

} //~namespace pvdb

} //~namespace ribi

#endif // QTPVDBCOMPETENCY_H
