#ifndef TESTQTROUNDEDEDITRECTITEMWIDGETMENUDIALOG_H
#define TESTQTROUNDEDEDITRECTITEMWIDGETMENUDIALOG_H

#include "menudialog.h"

namespace ribi {

struct TestQtRoundedEditRectItemMenuDialog : public MenuDialog
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

} //~namespace ribi

#endif // TESTQTROUNDEDEDITRECTITEMWIDGETMENUDIALOG_H
