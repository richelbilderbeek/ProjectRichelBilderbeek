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
};

} //~namespace maziak
} //~namespace ribi

#endif // MAZIAKTERMINAL_H
