#ifndef CONCEPTMAPCOMMAND_H
#define CONCEPTMAPCOMMAND_H

#include <string>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <boost/shared_ptr.hpp>

#include "conceptmapfwd.h"
#pragma GCC diagnostic pop

namespace ribi {
namespace cmap {

///Command can be used to do and undo commands to a concept map Widget
struct Command
{
  virtual ~Command() noexcept {}
  bool CanDoCommand(const Widget * const widget) const noexcept;
  void DoCommand(Widget * const widget) const noexcept;
  virtual const std::string ToStr() const noexcept = 0;

  private:
  ///Hook
  virtual bool CanDoCommandSpecific(const Widget * const widget) const noexcept = 0;

  ///Hook
  virtual void DoCommandSpecific(Widget * const widget) const noexcept = 0;
};

///Delete a concept map
///-Can be used only when there is an existing concept map
///-Inverse: StartConceptMap
struct CommandDeleteConceptMap : public Command
{
  bool CanDoCommandSpecific(const Widget * const widget) const noexcept;
  void DoCommandSpecific(Widget * const widget) const noexcept;
  const std::string ToStr() const noexcept { return "delete concept map"; }
};

///Start a new concept map
///-Can be used only when there is no existing concept map
///-Inverse: DeleteConceptMap
struct CommandStartConceptMap : public Command
{
  bool CanDoCommandSpecific(const Widget * const widget) const noexcept;
  void DoCommandSpecific(Widget * const widget) const noexcept;
  const std::string ToStr() const noexcept { return "start concept map"; }
};


} //~namespace cmap
} //~namespace ribi


#endif // CONCEPTMAPCOMMAND_H
