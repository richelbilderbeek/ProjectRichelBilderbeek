#ifndef RICHELBILDERBEEKPLACEHOLDERMENUDIALOG_H
#define RICHELBILDERBEEKPLACEHOLDERMENUDIALOG_H

#include "about.h"
#include "menudialog.h"

namespace ribi {

struct PlaceholderMenuDialog : public MenuDialog
{
  PlaceholderMenuDialog(
    const About& about,
    const boost::shared_ptr<const Program> program,
    const std::string& version,
    const std::vector<std::string> version_history);
  ~PlaceholderMenuDialog() noexcept {}
  About GetAbout() const noexcept { return m_about; }
  Help GetHelp() const noexcept;
  boost::shared_ptr<const Program> GetProgram() const noexcept { return m_program; }
  std::string GetVersion() const noexcept { return m_version; }
  std::vector<std::string> GetVersionHistory() const noexcept { return m_version_history; }

  private:
  const About m_about;
  const boost::shared_ptr<const Program> m_program;
  const std::string m_version;
  const std::vector<std::string> m_version_history;

  int ExecuteSpecific(const std::vector<std::string>& argv) noexcept;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif

};

} //~namespace ribi

#endif // RICHELBILDERBEEKPLACEHOLDERMENUDIALOG_H
