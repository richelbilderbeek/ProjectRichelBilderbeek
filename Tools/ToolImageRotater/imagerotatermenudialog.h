#ifndef IMAGEROTATERMENUDIALOG_H
#define IMAGEROTATERMENUDIALOG_H

#include "menudialog.h"

namespace ribi {

///GUI independent imagerotater menu dialog
struct ImagerotaterMenuDialog : public MenuDialog
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

#endif // IMAGEROTATERMENUDIALOG_H
