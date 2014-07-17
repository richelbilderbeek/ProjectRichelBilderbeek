#ifndef TOOLTESTMULTIAPPROXIMATORMENUDIALOG_H
#define TOOLTESTMULTIAPPROXIMATORMENUDIALOG_H

#include "menudialog.h"

namespace ribi {

struct ToolTestMultiApproximatorMenuDialog final : public MenuDialog
{
  About GetAbout() const noexcept override;
  Help GetHelp() const noexcept override;
  boost::shared_ptr<const Program> GetProgram() const noexcept override;
  std::string GetVersion() const noexcept override;
  std::vector<std::string> GetVersionHistory() const noexcept override;

  private:
  int ExecuteSpecific(const std::vector<std::string>& argv) noexcept override;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace ribi

#endif // TOOLTESTMULTIAPPROXIMATORMENUDIALOG_H
