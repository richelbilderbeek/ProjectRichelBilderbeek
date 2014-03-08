#ifndef CONCEPTMAPCOMMANDCREATENEWEDGE_H
#define CONCEPTMAPCOMMANDCREATENEWEDGE_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "conceptmapcommand.h"
#pragma GCC diagnostic pop

namespace ribi {
namespace cmap {

///Start a new node
///-Can be used only when there is an existing concept map
struct CommandCreateNewEdge : public Command
{
  CommandCreateNewEdge() : m_edge{}, m_nodes{}, m_widget{} {}
  CommandCreateNewEdge(const CommandCreateNewEdge&) = delete;
  CommandCreateNewEdge& operator=(const CommandCreateNewEdge&) = delete;
  ~CommandCreateNewEdge() noexcept {}

  bool CanDoCommandSpecific(const Widget * const widget) const noexcept;
  void DoCommandSpecific(Widget * const widget) noexcept;
  std::string ToStr() const noexcept { return "create new edge"; }
  void Undo() noexcept;

  private:
  boost::shared_ptr<Edge> m_edge;
  std::vector<boost::shared_ptr<Node>> m_nodes;
  Widget * m_widget;
};

} //~namespace cmap
} //~namespace ribi

#endif // CONCEPTMAPCOMMANDCREATENEWEDGE_H
