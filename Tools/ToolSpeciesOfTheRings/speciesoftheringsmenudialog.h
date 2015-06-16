#ifndef SIMTOPPREDATORPREYMENUDIALOG_H
#define SIMTOPPREDATORPREYMENUDIALOG_H

#include <string>
#include <vector>

#include "about.h"
#include "help.h"
#include "richelbilderbeekprogram.h"
#include "menudialog.h"

namespace ribi {

struct SpeciesOfTheRingsMenuDialog final : public MenuDialog
{
  SpeciesOfTheRingsMenuDialog();
  About GetAbout() const noexcept override;
  Help GetHelp() const noexcept override;
  boost::shared_ptr<const Program> GetProgram() const noexcept override;
  std::string GetVersion() const noexcept override;
  std::vector<std::string> GetVersionHistory() const noexcept override;

  private:
  int ExecuteSpecific(const std::vector<std::string>& argv) noexcept override;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif

};

} //~namespace ribi

#endif // SIMTOPPREDATORPREYMENUDIALOG_H
