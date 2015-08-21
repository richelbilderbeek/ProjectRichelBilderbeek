#ifndef DASWAHRESCHLAGERFESTTERMINAL_H
#define DASWAHRESCHLAGERFESTTERMINAL_H

#include "daswahreschlagerfestdisplay.h"

namespace ribi {
namespace dws {

struct DasWahreSchlagerfestTerminal : public DasWahreSchlagerfestDisplay
{
  DasWahreSchlagerfestTerminal();
  void Display(const DasWahreSchlagerfestWidget& widget) override;
  void OnChanged(const DasWahreSchlagerfestWidget& widget) override;
  ribi::dws::Key RequestKey() override;
  void SetAutoPlay(const bool auto_play) noexcept { m_auto_play = auto_play; }
  private:

  bool m_auto_play;
};

} //~namespace dws
} //~namespace ribi

#endif // DASWAHRESCHLAGERFESTTERMINAL_H
