#ifndef QTCONCEPTMAPBRUSHFACTORY_H
#define QTCONCEPTMAPBRUSHFACTORY_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <QBrush>
#pragma GCC diagnostic pop

namespace ribi {
namespace cmap {

///Class for holding some QBrush instances
struct QtBrushFactory
{
  ///Obtain a brush its name
  static const std::string BrushToStr(const QBrush& brush);

  ///Blue brush, to be used in all derived classes for uniform coloring
  static const QBrush CreateBlueGradientBrush();

  ///Gold brush, to be used in all derived classes for uniform coloring
  static const QBrush CreateGoldGradientBrush();

  ///Gray brush, to be used in all derived classes for uniform coloring
  static const QBrush CreateGrayGradientBrush();

  ///Green brush, to be used in all derived classes for uniform coloring
  static const QBrush CreateGreenGradientBrush();

  ///Red brush, to be used in all derived classes for uniform coloring
  static const QBrush CreateRedGradientBrush();

  ///Yellow brush, to be used in all derived classes for uniform coloring
  static const QBrush CreateYellowGradientBrush();

  ///Near-white brush, to be used in all derived classes for uniform coloring
  static const QBrush CreateWhiteGradientBrush();

  private:
  ///The bottom coordinat of a gradient
  static const int sm_bottom;
  ///The left coordinat of a gradient
  static const int sm_left;
  ///The right coordinat of a gradient
  static const int sm_right;
  ///The top coordinat of a gradient
  static const int sm_top;
  ///The low color value: low values return in darker brushes
  static const int sm_color_low_value;
  ///The middle color value: higher values return in lighter brushes
  static const int sm_color_mid_value;
};

} //~namespace pvdb
} //~namespace ribi

#endif // QTCONCEPTMAPBRUSHFACTORY_H
