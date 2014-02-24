#ifndef CONCEPTMAPCOMMANDSETFOCUSWITHCOORDINAT_H
#define CONCEPTMAPCOMMANDSETFOCUSWITHCOORDINAT_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <vector>

#include "conceptmapcommand.h"
#pragma GCC diagnostic pop

namespace ribi {
namespace cmap {

///Set focus with a coordinat
///- opposite of LoseFocus
///- SetFocus does not care if there currently is something in focus
struct CommandSetFocusWithCoordinat : public Command
{
  CommandSetFocusWithCoordinat(const int x, const int y)
    : m_widget{}, m_x(x), m_y(y) {}
  CommandSetFocusWithCoordinat(const CommandSetFocusWithCoordinat&) = delete;
  CommandSetFocusWithCoordinat& operator=(const CommandSetFocusWithCoordinat&) = delete;
  ~CommandSetFocusWithCoordinat() noexcept {}

  bool CanDoCommandSpecific(const Widget * const widget) const noexcept;
  void DoCommandSpecific(Widget * const widget) noexcept;
  const std::string ToStr() const noexcept { return "set focus with coordinat"; }
  void Undo() noexcept;

  private:
  Widget * m_widget;
  const int m_x;
  const int m_y;
};

} //~namespace cmap
} //~namespace ribi

#endif // CONCEPTMAPCOMMANDSETFOCUSWITHCOORDINAT_H
