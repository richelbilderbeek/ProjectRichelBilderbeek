#ifndef TOOLMULTIENCRANGERMENUDIALOG_H
#define TOOLMULTIENCRANGERMENUDIALOG_H

//#include <string>
//#include <vector>
//#include "about.h"
#include "menudialog.h"

namespace ribi {

struct ToolMultiEncrangerMenuDialog : public MenuDialog
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

#endif // TOOLMULTIENCRANGERMENUDIALOG_H
