#ifndef SEARCHANDDESTROYCHESSMENUDIALOG_H
#define SEARCHANDDESTROYCHESSMENUDIALOG_H

#include "menudialog.h"

namespace ribi {
namespace sadc {

///The logic behind the menu dialog
struct MenuDialog : public ::ribi::MenuDialog
{
  ///Creates the resources needed
  MenuDialog();

  const About GetAbout() const noexcept;
  const Help GetHelp() const noexcept;
  const boost::shared_ptr<const Program> GetProgram() const noexcept;
  const std::string GetVersion() const noexcept;
  const std::vector<std::string> GetVersionHistory() const noexcept;

  private:
  int ExecuteSpecific(const std::vector<std::string>& argv) noexcept;

  private:

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace sadc
} //~namespace ribi

#endif // SEARCHANDDESTROYCHESSMENUDIALOG_H
