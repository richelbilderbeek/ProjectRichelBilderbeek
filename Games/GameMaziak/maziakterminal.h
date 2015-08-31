#ifndef MAZIAKTERMINAL_H
#define MAZIAKTERMINAL_H

#include "maziakdisplay.h"

namespace ribi {
namespace maziak {

struct MainDialog;

///Displays Maziak in command-line mode
struct Terminal : public Display
{
  Terminal();

  //Put the MainDialog on screen
  void DoDisplay(const MainDialog& main_dialog) override;

  ///Every turn, the animation must take place
  bool MustAnimateEnemiesAndPrisoners() noexcept override { return true; }

  std::set<Key> RequestKeys() override;
};

} //~namespace maziak
} //~namespace ribi

#endif // MAZIAKTERMINAL_H
