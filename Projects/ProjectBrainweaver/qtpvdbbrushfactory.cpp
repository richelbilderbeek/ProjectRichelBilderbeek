#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif

//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#include "qtpvdbbrushfactory.h"

#include <QLinearGradient>

const int QtPvdbBrushFactory::sm_bottom = 10;
const int QtPvdbBrushFactory::sm_left = -100;
const int QtPvdbBrushFactory::sm_right = 100;
const int QtPvdbBrushFactory::sm_top = -10;
const int QtPvdbBrushFactory::sm_color_low_value  =  64;
const int QtPvdbBrushFactory::sm_color_mid_value  = 128;

const std::string QtPvdbBrushFactory::BrushToStr(const QBrush& brush)
{
  if (brush == CreateBlueGradientBrush()) return "blue";
  if (brush == CreateGoldGradientBrush()) return "gold";
  if (brush == CreateGrayGradientBrush()) return "gray";
  if (brush == CreateGreenGradientBrush()) return "green";
  if (brush == CreateRedGradientBrush()) return "red";
  if (brush == CreateYellowGradientBrush()) return "yellow";
  if (brush == CreateWhiteGradientBrush()) return "white";
  return "unknown";

}

const QBrush QtPvdbBrushFactory::CreateBlueGradientBrush()
{
  QLinearGradient linearGradient(sm_left,sm_top,sm_right,sm_bottom);
  linearGradient.setColorAt(0.0,QColor( sm_color_mid_value, sm_color_mid_value,255));
  linearGradient.setColorAt(1.0,QColor(255,255,255));
  return linearGradient;
}

const QBrush QtPvdbBrushFactory::CreateGoldGradientBrush()
{
  QLinearGradient linearGradient(sm_left,sm_top,sm_right,sm_bottom);
  linearGradient.setColorAt(0.0,QColor( sm_color_mid_value, sm_color_mid_value,sm_color_low_value));
  linearGradient.setColorAt(1.0,QColor(255,255,sm_color_low_value));
  return linearGradient;
}

const QBrush QtPvdbBrushFactory::CreateGrayGradientBrush()
{
  QLinearGradient linearGradient(sm_left,sm_top,sm_right,sm_bottom);
  linearGradient.setColorAt(0.0,QColor(196,196,196));
  linearGradient.setColorAt(1.0,QColor(255,255,255));
  return linearGradient;
}

const QBrush QtPvdbBrushFactory::CreateGreenGradientBrush()
{
  QLinearGradient linearGradient(sm_left,sm_top,sm_right,sm_bottom);
  linearGradient.setColorAt(0.0,QColor( sm_color_mid_value,255, sm_color_mid_value));
  linearGradient.setColorAt(1.0,QColor(255,255,255));
  return linearGradient;
}

const QBrush QtPvdbBrushFactory::CreateRedGradientBrush()
{
  QLinearGradient linearGradient(sm_left,sm_top,sm_right,sm_bottom);
  linearGradient.setColorAt(0.0,QColor(255, sm_color_mid_value, sm_color_mid_value));
  linearGradient.setColorAt(1.0,QColor(255,255,255));
  return linearGradient;
}

const QBrush QtPvdbBrushFactory::CreateYellowGradientBrush()
{
  QLinearGradient linearGradient(sm_left,sm_top,sm_right,sm_bottom);
  linearGradient.setColorAt(0.0,QColor(255,255, sm_color_mid_value));
  linearGradient.setColorAt(1.0,QColor(255,255,255));
  return linearGradient;
}

const QBrush QtPvdbBrushFactory::CreateWhiteGradientBrush()
{
  QLinearGradient linearGradient(sm_left,sm_top,sm_right,sm_bottom);
  const int low_value = 250;
  linearGradient.setColorAt(0.0,QColor(low_value,low_value,low_value));
  linearGradient.setColorAt(1.0,QColor(255,255,255));
  return linearGradient;
}
