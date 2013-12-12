#ifndef TOOLTESTMULTIAPPROXIMATORMENUDIALOG_H
#define TOOLTESTMULTIAPPROXIMATORMENUDIALOG_H

#include "menudialog.h"

namespace ribi {

struct ToolTestMultiApproximatorMenuDialog : public MenuDialog
{
  const About GetAbout() const noexcept;
  const Help GetHelp() const noexcept;
  const boost::shared_ptr<const Program> GetProgram() const noexcept;
  const std::string GetVersion() const noexcept;
  const std::vector<std::string> GetVersionHistory() const noexcept;

  private:
  int ExecuteSpecific(const std::vector<std::string>& argv) noexcept;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace ribi

#endif // TOOLTESTMULTIAPPROXIMATORMENUDIALOG_H
