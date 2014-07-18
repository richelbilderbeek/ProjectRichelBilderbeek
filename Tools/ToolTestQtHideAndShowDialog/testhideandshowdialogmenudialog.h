#ifndef  TOOLTESTHIDEANDSHOWDIALOGMENUDIALOG_H
#define  TOOLTESTHIDEANDSHOWDIALOGMENUDIALOG_H

#include <iosfwd>
#include <string>
#include <vector>

#include "menudialog.h"

namespace ribi {

///GUI independent TestPlane menu dialog
struct TestHideAndShowDialogMenuDialog final : public MenuDialog
{
  TestHideAndShowDialogMenuDialog();
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

} //namespace ribi

#endif //  TOOLTESTHIDEANDSHOWDIALOGMENUDIALOG_H
