#ifndef STAIRCASECARDCREATORMENUDIALOG_H
#define STAIRCASECARDCREATORMENUDIALOG_H

#include <string>
#include <vector>

#include "menudialog.h"
//#include "staircasecardcreatorfwd.h"

namespace ribi {
namespace scc {

///GUI independent staircasecardcreator menu dialog
struct MenuDialog : public ::ribi::MenuDialog
{
  MenuDialog();
  ~MenuDialog() noexcept {}
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

} //~namespace scc
} //~namespace ribi

#endif // STAIRCASECARDCREATORMENUDIALOG_H
