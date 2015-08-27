#ifndef NDSGAMEDIALOG_H
#define NDSGAMEDIALOG_H

#include <nds.h>

#include "daswahreschlagerfestdisplay.h"
#include "daswahreschlagerfestwidget.h"

namespace Ui { class NdsGameDialog; }

namespace ribi {
namespace dws {

//Images are 32x32
//Screen is 256x196 (w x h), thus 8x6 blocks
struct NdsGameDialog final : public ribi::dws::Display
{
  NdsGameDialog();

  void DoDisplay(const Widget& widget) override;
  void OnChanged(const Widget& widget) override;
  ribi::dws::Key RequestKey() override;

private:

  int m_key_pressed;

  PrintConsole m_screen_bottom;

  int GetNumberOfCharsPerLine() const noexcept { return 31; }

  //Check for key presses, touches, etceter
  void ProcessEvents();

  static const bool m_verbose{false};
};

} //~namespace dws
} //~namespace ribi

#endif // NDSGAMEDIALOG_H
