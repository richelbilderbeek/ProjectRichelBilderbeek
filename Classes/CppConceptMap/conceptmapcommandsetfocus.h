#ifndef CONCEPTMAPCOMMANDSETFOCUS_H
#define CONCEPTMAPCOMMANDSETFOCUS_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "conceptmapcommand.h"
#pragma GCC diagnostic pop

namespace ribi {
namespace cmap {

///Set focus
///- opposite of LoseFocus
///- SetFocus does not care if there currently is something in focus
struct CommandSetFocus : public Command
{
  CommandSetFocus(const int x, const int y)
    : m_widget{}, m_x(x), m_y(y) {}
  CommandSetFocus(const CommandSetFocus&) = delete;
  CommandSetFocus& operator=(const CommandSetFocus&) = delete;
  ~CommandSetFocus() noexcept {}

  bool CanDoCommandSpecific(const Widget * const widget) const noexcept;
  void DoCommandSpecific(Widget * const widget) noexcept;
  const std::string ToStr() const noexcept { return "set focus"; }
  void Undo() noexcept;

  private:
  Widget * m_widget;
  const int m_x;
  const int m_y;
};

} //~namespace cmap
} //~namespace ribi

#endif // CONCEPTMAPCOMMANDSETFOCUS_H
