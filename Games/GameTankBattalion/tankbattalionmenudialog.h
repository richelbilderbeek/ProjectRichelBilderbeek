#ifndef TANKBATTALIONMENUDIALOG_H
#define TANKBATTALIONMENUDIALOG_H

#include "menudialog.h"

namespace ribi {
namespace taba {

struct MenuDialog : public ::ribi::MenuDialog
{
  MenuDialog();
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

} //~namespace taba
} //~namespace ribi

#endif // TANKBATTALIONMENUDIALOG_H
