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
///Command must use a Widget* because a Widget will call a Command with this:
///
///  some_command->CanDo(this);
///
struct Command
{
  virtual ~Command() noexcept {}
  bool CanDoCommand(const Widget * const widget) const noexcept;
  bool CanDoCommand(const boost::shared_ptr<const Widget> widget) const noexcept { return CanDoCommand(widget.get()); }
  void DoCommand(Widget * const widget) noexcept;
  void DoCommand(const boost::shared_ptr<Widget> widget) noexcept { DoCommand(widget.get()); }

  virtual const std::string ToStr() const noexcept = 0;
  virtual void Undo() noexcept = 0;

  private:
  ///Hook
  virtual bool CanDoCommandSpecific(const Widget * const widget) const noexcept = 0;

  ///Hook
  virtual void DoCommandSpecific(Widget * const widget) noexcept = 0;
};






} //~namespace cmap
} //~namespace ribi


#endif // CONCEPTMAPCOMMAND_H
