#ifndef CONCEPTMAPCOMMANDCREATENEWCONCEPTMAP_H
#define CONCEPTMAPCOMMANDCREATENEWCONCEPTMAP_H

/*

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "conceptmapcommand.h"
#pragma GCC diagnostic pop

namespace ribi {
namespace cmap {

///Start a new concept map
///-Can be used only when there is no existing concept map
struct CommandCreateNewConceptMap : public Command
{
  CommandCreateNewConceptMap() : m_widget{} {}
  CommandCreateNewConceptMap(const CommandCreateNewConceptMap&) = delete;
  CommandCreateNewConceptMap& operator=(const CommandCreateNewConceptMap&) = delete;
  ~CommandCreateNewConceptMap() noexcept {}

  bool CanDoCommandSpecific(const Widget * const widget) const noexcept;
  void DoCommandSpecific(Widget * const widget) noexcept;
  std::string ToStr() const noexcept { return "create new concept map"; }
  void Undo() noexcept;

  private:
  Widget * m_widget;
};

} //~namespace cmap
} //~namespace ribi

*/
#endif // CONCEPTMAPCOMMANDCREATENEWCONCEPTMAP_H
