#ifndef SECRETMESSAGEMENUDIALOG_H
#define SECRETMESSAGEMENUDIALOG_H

#include <string>
#include <vector>

#include "menudialog.h"

namespace ribi {
namespace sema {

struct MenuDialog : public ::ribi::MenuDialog
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

} //~namespace sema
} //~namespace ribi

#endif // SECRETMESSAGEMENUDIALOG_H
