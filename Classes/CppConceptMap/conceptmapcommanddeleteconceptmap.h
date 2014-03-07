#ifndef CONCEPTMAPCOMMANDDELETECONCEPTMAP_H
#define CONCEPTMAPCOMMANDDELETECONCEPTMAP_H

/*

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "conceptmapcommand.h"
#pragma GCC diagnostic pop

namespace ribi {
namespace cmap {

///Delete a concept map
///-Can be used only when there is an existing concept map
struct CommandDeleteConceptMap : public Command
{
  CommandDeleteConceptMap() : m_deleted_concept_map{}, m_widget{} {}
  CommandDeleteConceptMap(const CommandDeleteConceptMap&) = delete;
  CommandDeleteConceptMap& operator=(const CommandDeleteConceptMap&) = delete;
  ~CommandDeleteConceptMap() noexcept {}
  bool CanDoCommandSpecific(const Widget * const widget) const noexcept;
  void DoCommandSpecific(Widget * const widget) noexcept;
  std::string ToStr() const noexcept { return "delete concept map"; }
  void Undo() noexcept;

  private:
  boost::shared_ptr<ConceptMap> m_deleted_concept_map;
  Widget * m_widget;
};

} //~namespace cmap
} //~namespace ribi

*/

#endif // CONCEPTMAPCOMMANDDELETECONCEPTMAP_H
