#ifndef CONCEPTMAPCOMMANDADDFOCUSRANDOM_H
#define CONCEPTMAPCOMMANDADDFOCUSRANDOM_H

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
///- AddFocus does not care if there currently is something in focus
struct CommandAddFocusRandom : public Command
{
  CommandAddFocusRandom() : m_old_focus{}, m_widget{} {}
  CommandAddFocusRandom(const CommandAddFocusRandom&) = delete;
  CommandAddFocusRandom& operator=(const CommandAddFocusRandom&) = delete;
  ~CommandAddFocusRandom() noexcept {}

  bool CanDoCommandSpecific(const Widget * const widget) const noexcept;
  void DoCommandSpecific(Widget * const widget) noexcept;
  std::string ToStr() const noexcept { return "add focus random"; }
  void Undo() noexcept;

  private:
  std::vector<boost::shared_ptr<Node>> m_old_focus;
  Widget * m_widget;
};

} //~namespace cmap
} //~namespace ribi

#endif // CONCEPTMAPCOMMANDADDFOCUSRANDOM_H
