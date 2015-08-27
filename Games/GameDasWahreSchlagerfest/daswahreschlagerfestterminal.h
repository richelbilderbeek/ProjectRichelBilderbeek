#ifndef DASWAHRESCHLAGERFESTTERMINAL_H
#define DASWAHRESCHLAGERFESTTERMINAL_H

#include "daswahreschlagerfestdisplay.h"

namespace ribi {
namespace dws {

struct Terminal : public Display
{
  Terminal();
  void DoDisplay(const Widget& widget) override;
  void OnChanged(const Widget& widget) override;
  ribi::dws::Key RequestKey() override;
  void SetAutoPlay(const bool auto_play) noexcept { m_auto_play = auto_play; }
  private:

  bool m_auto_play;
};

} //~namespace dws
} //~namespace ribi

#endif // DASWAHRESCHLAGERFESTTERMINAL_H
