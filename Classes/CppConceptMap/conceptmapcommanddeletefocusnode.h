#ifndef CONCEPTMAPCOMMANDDELETEFOCUSNODE_H
#define CONCEPTMAPCOMMANDDELETEFOCUSNODE_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "conceptmapcommand.h"
#pragma GCC diagnostic pop

namespace ribi {
namespace cmap {

///Delete a node the concept map has in focus
///-Can be used only when there is an existing concept map
/// and a Node in focus
struct CommandDeleteFocusNode : public Command
{
  CommandDeleteFocusNode() : m_old_focus{}, m_widget{} {}
  CommandDeleteFocusNode(const CommandDeleteFocusNode&) = delete;
  CommandDeleteFocusNode& operator=(const CommandDeleteFocusNode&) = delete;
  ~CommandDeleteFocusNode() noexcept {}

  bool CanDoCommandSpecific(const Widget * const widget) const noexcept;
  int CountDeleted() const noexcept { return static_cast<int>(m_old_focus.size()); }
  void DoCommandSpecific(Widget * const widget) noexcept;
  std::string ToStr() const noexcept { return "delete nodes in focus"; }
  void Undo() noexcept;

  private:
  std::vector<boost::shared_ptr<Node>> m_old_focus;
  Widget * m_widget;
};

} //~namespace cmap
} //~namespace ribi

#endif // CONCEPTMAPCOMMANDDELETEFOCUSNODE_H
