#ifndef K3OPEENRIJMENUDIALOG_H
#define K3OPEENRIJMENUDIALOG_H

#include <string>
#include <vector>
#include "about.h"

namespace ribi {

///
struct K3OpEenRijMenuDialog
{
  static const About GetAbout() noexcept;
  static const std::string GetVersion() noexcept;
  static const std::vector<std::string> GetVersionHistory() noexcept;
};

} //~namespace ribi

#endif // K3OPEENRIJMENUDIALOG_H
