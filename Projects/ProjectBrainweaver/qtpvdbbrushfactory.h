#ifndef QTPVDBBRUSHFACTORY_H
#define QTPVDBBRUSHFACTORY_H

#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif

#include <QBrush>

///Class for holding some QBrush instances
struct QtPvdbBrushFactory
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

#endif // QTPVDBBRUSHFACTORY_H
