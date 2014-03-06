#ifndef FUNCTIONPLOTTERMENUDIALOG_H
#define FUNCTIONPLOTTERMENUDIALOG_H

#include <string>
#include <vector>

#include "menudialog.h"

namespace ribi {

///GUI independent SurfacePlotter menu dialog
struct FunctionPlotterMenuDialog : public MenuDialog
{
  About GetAbout() const noexcept;
  Help GetHelp() const noexcept;
  boost::shared_ptr<const Program> GetProgram() const noexcept;
  std::string GetVersion() const noexcept;
  std::vector<std::string> GetVersionHistory() const noexcept;

  private:
  int ExecuteSpecific(const std::vector<std::string>& argv) noexcept;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //namespace ribi

#endif // FUNCTIONPLOTTERMENUDIALOG_H
