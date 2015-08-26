#ifndef CONCEPTMAPCOMMANDDELETEEDGE_H
#define CONCEPTMAPCOMMANDDELETEEDGE_H

#include "conceptmapcommand.h"

namespace ribi {
namespace cmap {

///Delete an existing edge
struct CommandDeleteEdge : public Command
{
  CommandDeleteEdge(const boost::shared_ptr<Edge> edge);
  CommandDeleteEdge(const CommandDeleteEdge&) = delete;
  CommandDeleteEdge& operator=(const CommandDeleteEdge&) = delete;
  ~CommandDeleteEdge() noexcept {}

  std::string ToStr() const noexcept final { return "delete edge"; }

  private:
  boost::shared_ptr<Edge> m_edge;
  ConceptMap * m_concept_map;

  bool CanDoCommandSpecific(const ConceptMap * const widget) const noexcept final;
  void DoCommandSpecific(ConceptMap * const widget) noexcept final;
  void UndoSpecific() noexcept final;
};

} //~namespace cmap
} //~namespace ribi

#endif // CONCEPTMAPCOMMANDDELETEEDGE_H
