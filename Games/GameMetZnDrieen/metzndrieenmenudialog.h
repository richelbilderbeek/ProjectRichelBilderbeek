#ifndef METZNDRIEENMENUDIALOG_H
#define METZNDRIEENMENUDIALOG_H

#include "menudialog.h"

namespace ribi {

struct MetZnDrieenMenuDialog : public MenuDialog
{
  const About GetAbout() const noexcept;
  const Help GetHelp() const noexcept;
  const boost::shared_ptr<const Program> GetProgram() const noexcept;
  const std::string GetVersion() const noexcept;
  const std::vector<std::string> GetVersionHistory() const noexcept;

  private:
  int ExecuteSpecific(const std::vector<std::string>& argv) noexcept;
};

} //~namespace ribi

#endif // METZNDRIEENMENUDIALOG_H
