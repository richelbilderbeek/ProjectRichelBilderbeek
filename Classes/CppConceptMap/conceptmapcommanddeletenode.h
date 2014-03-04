#ifndef CONCEPTMAPCOMMANDDELETENODE_H
#define CONCEPTMAPCOMMANDDELETENODE_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "conceptmapcommand.h"
#pragma GCC diagnostic pop

namespace ribi {
namespace cmap {

///Delete an existing node
struct CommandDeleteNode : public Command
{
  CommandDeleteNode(const boost::shared_ptr<Node> node);
  CommandDeleteNode(const CommandDeleteNode&) = delete;
  CommandDeleteNode& operator=(const CommandDeleteNode&) = delete;
  ~CommandDeleteNode() noexcept {}

  bool CanDoCommandSpecific(const Widget * const widget) const noexcept;
  void DoCommandSpecific(Widget * const widget) noexcept;
  std::string ToStr() const noexcept { return "delete node"; }
  void Undo() noexcept;

  private:
  boost::shared_ptr<Node> m_node;
  Widget * m_widget;
};

} //~namespace cmap
} //~namespace ribi

#endif // CONCEPTMAPCOMMANDDELETENODE_H
