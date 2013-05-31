#ifndef QTPVDBCOMPETENCY_H
#define QTPVDBCOMPETENCY_H

#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif

#include <map>
#include <QColor>
#include <QIcon>
#include "pvdbcompetency.h"

#ifdef PVDB_USE_FORWARD_DECLARATIONS_248738
#include "pvdbfwd.h"
#else

#endif

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

#endif // QTPVDBCOMPETENCY_H
