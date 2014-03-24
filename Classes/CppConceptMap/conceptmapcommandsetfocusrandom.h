#ifndef CONCEPTMAPCOMMANDSETFOCUSRANDOM_H
#define CONCEPTMAPCOMMANDSETFOCUSRANDOM_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "conceptmapcommand.h"
#pragma GCC diagnostic pop

namespace ribi {
namespace cmap {

///Set focus with a coordinat
///- opposite of LoseFocus
///- SetFocus does not care if there currently is something in focus
struct CommandSetFocusRandom : public Command
{
  CommandSetFocusRandom() : m_old_focus{}, m_widget{} {}
  CommandSetFocusRandom(const CommandSetFocusRandom&) = delete;
  CommandSetFocusRandom& operator=(const CommandSetFocusRandom&) = delete;
  ~CommandSetFocusRandom() noexcept {}

  bool CanDoCommandSpecific(const Widget * const widget) const noexcept;
  void DoCommandSpecific(Widget * const widget) noexcept;
  std::string ToStr() const noexcept { return "set focus random"; }
  void Undo() noexcept;

  private:
  boost::shared_ptr<Node> m_old_focus;
  Widget * m_widget;
};

} //~namespace cmap
} //~namespace ribi

#endif // CONCEPTMAPCOMMANDSETFOCUSRANDOM_H
