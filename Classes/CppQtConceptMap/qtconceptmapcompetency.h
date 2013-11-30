#ifndef QTPVDBCOMPETENCY_H
#define QTPVDBCOMPETENCY_H

#include <map>
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <QColor>
#include <QIcon>
#include "conceptmapcompetency.h"

#include "qtconceptmapfwd.h"
#pragma GCC diagnostic pop

namespace ribi {
namespace cmap {

///Class to convert cmap::Competency to QColor and vice versa
struct QtCompetency
{
  ///Convert a QColor to a cmap::Competency
  static cmap::Competency ColorToCompetency(const QColor& color);

  ///Convert a cmap::Competency to a QColor
  static const QColor CompetencyToColor(const cmap::Competency competency);

  ///Convert a cmap::Competency to a QIcon
  static const QIcon CompetencyToIcon(const cmap::Competency competency);

  ///Convert a QIcon to a cmap::Competency
  static cmap::Competency IconToCompetency(const QIcon& icon);

  private:
  ///The map between cmap::Competency and QColor
  static const std::map<cmap::Competency,QColor> m_color_map;

  ///The map between cmap::Competency and QIcon
  static std::map<cmap::Competency,QIcon> m_icon_map;

  ///Create map between cmap::Competency and QColor
  static const std::map<cmap::Competency,QColor> CreateColorMap();

  ///Create map between cmap::Competency and QIcon
  static const std::map<cmap::Competency,QIcon> CreateIconMap();

  #ifndef NDEBUG
  ///Test this class
  static void Test();
  #endif
};

} //~namespace pvdb
} //~namespace ribi

#endif // QTPVDBCOMPETENCY_H
