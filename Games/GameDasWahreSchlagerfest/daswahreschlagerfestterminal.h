#ifndef DASWAHRESCHLAGERFESTTERMINAL_H
#define DASWAHRESCHLAGERFESTTERMINAL_H

#include "daswahreschlagerfestdisplay.h"

namespace ribi {

struct DasWahreSchlagerfestTerminal : public DasWahreSchlagerfestDisplay
{
  void Display(const DasWahreSchlagerfestWidget& widget) override;
  void OnChanged(const DasWahreSchlagerfestWidget& widget) override;
};

} //~namespace ribi

#endif // DASWAHRESCHLAGERFESTTERMINAL_H
