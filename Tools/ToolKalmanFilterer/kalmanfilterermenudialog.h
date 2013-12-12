#ifndef KALMANFILTERERMENUDIALOG_H
#define KALMANFILTERERMENUDIALOG_H

#include <string>
#include <vector>

#include "about.h"
#include "menudialog.h"
#include "help.h"
#include "richelbilderbeekprogram.h"

namespace ribi {
namespace kalman {

///GUI independent KalmanFilterer menu dialog
struct KalmanFiltererMenuDialog : public ribi::MenuDialog
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

} //~namespace kalman
} //~namespace ribi

#endif // KALMANFILTERERMENUDIALOG_H
