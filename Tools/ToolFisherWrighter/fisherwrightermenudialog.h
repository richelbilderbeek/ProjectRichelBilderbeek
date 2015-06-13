#ifndef FISHERWRIGHTERMENUDIALOG_H
#define FISHERWRIGHTERMENUDIALOG_H

#include "menudialog.h"

namespace ribi {
namespace fw {

///GUI independent FisherWrighter menu dialog
struct MenuDialog final : public ::ribi::MenuDialog
{
  MenuDialog();
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

} //~namespace fw
} //~namespace ribi

#endif // FISHERWRIGHTERMENUDIALOG_H
