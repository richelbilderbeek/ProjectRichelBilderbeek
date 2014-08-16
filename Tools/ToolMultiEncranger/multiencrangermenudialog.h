#ifndef TOOLMULTIENCRANGERMENUDIALOG_H
#define TOOLMULTIENCRANGERMENUDIALOG_H

//#include <string>
//#include <vector>
//#include "about.h"
#include "menudialog.h"

namespace ribi {

struct MultiEncrangerMenuDialog final : public MenuDialog
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

#endif // TOOLMULTIENCRANGERMENUDIALOG_H
