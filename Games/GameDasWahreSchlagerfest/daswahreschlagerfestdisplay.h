#ifndef DASWAHRESCHLAGERFESTDISPLAY_H
#define DASWAHRESCHLAGERFESTDISPLAY_H

#include "daswahreschlagerfestkey.h"

namespace ribi {
namespace dws {

struct Widget;

struct Display
{
  virtual ~Display() {}
  virtual void DoDisplay(const Widget& widget) = 0;
  virtual void OnChanged(const Widget& widget) = 0;
  virtual ribi::dws::Key RequestKey() = 0;

};

} //~namespace dws
} //~namespace ribi

#endif // DASWAHRESCHLAGERFESTDISPLAY_H
