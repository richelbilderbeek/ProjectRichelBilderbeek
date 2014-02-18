#ifndef IMAGEROTATERMENUDIALOG_H
#define IMAGEROTATERMENUDIALOG_H

#include "menudialog.h"

namespace ribi {

///GUI independent valentine card decrypter menu dialog
struct ValentineCardDecrypterMenuDialog : public MenuDialog
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

#endif // IMAGEROTATERMENUDIALOG_H
