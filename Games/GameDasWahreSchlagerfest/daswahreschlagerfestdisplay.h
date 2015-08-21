#ifndef DASWAHRESCHLAGERFESTDISPLAY_H
#define DASWAHRESCHLAGERFESTDISPLAY_H

#include "daswahreschlagerfestkey.h"

namespace ribi {
namespace dws {

struct DasWahreSchlagerfestWidget;

struct DasWahreSchlagerfestDisplay
{
  virtual ~DasWahreSchlagerfestDisplay() {}
  virtual void Display(const DasWahreSchlagerfestWidget& widget) = 0;
  virtual void OnChanged(const DasWahreSchlagerfestWidget& widget) = 0;
  virtual ribi::dws::Key RequestKey() = 0;

};

} //~namespace dws
} //~namespace ribi

#endif // DASWAHRESCHLAGERFESTDISPLAY_H
