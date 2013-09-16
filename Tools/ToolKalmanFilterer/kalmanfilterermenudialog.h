#ifndef KALMANFILTERERMENUDIALOG_H
#define KALMANFILTERERMENUDIALOG_H

#include <string>
#include <vector>

#include "about.h"

namespace ribi {
namespace kalman {

///GUI independent KalmanFilterer menu dialog
struct KalmanFiltererMenuDialog
{
  static const About GetAbout() noexcept;
  static const std::string GetVersion() noexcept;
  static const std::vector<std::string> GetVersionHistory() noexcept;
};

} //~namespace kalman
} //~namespace ribi

#endif // KALMANFILTERERMENUDIALOG_H
