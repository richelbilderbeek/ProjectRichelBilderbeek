#ifndef CONCEPTMAPCOMMANDLOSEFOCUS_H
#define CONCEPTMAPCOMMANDLOSEFOCUS_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "conceptmapcommand.h"
#pragma GCC diagnostic pop

namespace ribi {
namespace cmap {

///Lose focus
///- opposite of SetFocus
struct CommandLoseFocus : public Command
{
  CommandLoseFocus() : m_old_focus{}, m_widget{} {}
  CommandLoseFocus(const CommandLoseFocus&) = delete;
  CommandLoseFocus& operator=(const CommandLoseFocus&) = delete;
  ~CommandLoseFocus() noexcept {}

  bool CanDoCommandSpecific(const Widget * const widget) const noexcept;
  void DoCommandSpecific(Widget * const widget) noexcept;
  const std::string ToStr() const noexcept { return "lose focus"; }
  void Undo() noexcept;

  private:
  Node * m_old_focus;
  Widget * m_widget;
};

} //~namespace cmap
} //~namespace ribi

#endif // CONCEPTMAPCOMMANDLOSEFOCUS_H
