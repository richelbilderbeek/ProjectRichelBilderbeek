#ifndef TOOLDOTMATRIXMENUDIALOG_H
#define TOOLDOTMATRIXMENUDIALOG_H

#include <string>
#include <vector>

#include "menudialog.h"

namespace ribi {

///GUI independent ToolDotMatrix menu dialog
struct ToolDotMatrixMenuDialog : public MenuDialog
{

  const About GetAbout() const noexcept;
  const Help GetHelp() const noexcept;
  const boost::shared_ptr<const Program> GetProgram() const noexcept;
  const std::string GetVersion() const noexcept;
  const std::vector<std::string> GetVersionHistory() const noexcept;

  private:
  int ExecuteSpecific(const std::vector<std::string>& argv) noexcept;

};

} //~namespace ribi

#endif // TOOLDOTMATRIXMENUDIALOG_H
