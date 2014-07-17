#ifndef TESTIMAGECANVASMENUDIALOG_H
#define TESTIMAGECANVASMENUDIALOG_H

#include "menudialog.h"

namespace ribi {

///GUI independent TestImageCanvas menu dialog
struct TestImageCanvasMenuDialog final : public MenuDialog
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

#endif // TESTIMAGECANVASMENUDIALOG_H
