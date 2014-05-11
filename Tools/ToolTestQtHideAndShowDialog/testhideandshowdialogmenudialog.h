#ifndef  TOOLTESTHIDEANDSHOWDIALOGMENUDIALOG_H
#define  TOOLTESTHIDEANDSHOWDIALOGMENUDIALOG_H

#include <iosfwd>
#include <string>
#include <vector>

#include "menudialog.h"

namespace ribi {

///GUI independent TestPlane menu dialog
struct TestHideAndShowDialogMenuDialog : public MenuDialog
{
  TestHideAndShowDialogMenuDialog();
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

#endif //  TOOLTESTHIDEANDSHOWDIALOGMENUDIALOG_H
