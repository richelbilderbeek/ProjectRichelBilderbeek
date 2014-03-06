#ifndef PVDBMENUDIALOG_H
#define PVDBMENUDIALOG_H

#include <string>
#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "menudialog.h"
#pragma GCC diagnostic pop

namespace ribi {
namespace pvdb {

///The GUI independent version of Project Van Den Bogaart its menu dialog
struct MenuDialog : public ::ribi::MenuDialog
{
  About GetAbout() const noexcept;
  Help GetHelp() const noexcept;
  boost::shared_ptr<const Program> GetProgram() const noexcept;
  std::string GetVersion() const noexcept;
  std::vector<std::string> GetVersionHistory() const noexcept;

  private:
  int ExecuteSpecific(const std::vector<std::string>& argv) noexcept;
};

} //~namespace pvdb
} //~namespace ribi

#endif // PVDBMENUDIALOG_H

