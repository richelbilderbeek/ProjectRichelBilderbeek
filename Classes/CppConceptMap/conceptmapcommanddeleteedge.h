#ifndef CONCEPTMAPCOMMANDDELETEEDGE_H
#define CONCEPTMAPCOMMANDDELETEEDGE_H

#include "conceptmapcommand.h"

namespace ribi {
namespace cmap {

///Delete an existing edge
struct CommandDeleteEdge final : public Command
{
  CommandDeleteEdge(
    const boost::shared_ptr<ConceptMap> conceptmap,
    const boost::shared_ptr<Edge> edge
  );
  CommandDeleteEdge(const CommandDeleteEdge&) = delete;
  CommandDeleteEdge& operator=(const CommandDeleteEdge&) = delete;
  ~CommandDeleteEdge() noexcept {}

  void undo() override;
  void redo() override;

  private:
  const boost::shared_ptr<ConceptMap> m_conceptmap;
  const boost::shared_ptr<Edge> m_edge;
};

} //~namespace cmap
} //~namespace ribi

#endif // CONCEPTMAPCOMMANDDELETEEDGE_H
