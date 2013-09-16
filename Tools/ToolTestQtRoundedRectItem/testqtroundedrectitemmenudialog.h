#ifndef TESTQTROUNDEDRECTITEMWIDGETMENUDIALOG_H
#define TESTQTROUNDEDRECTITEMWIDGETMENUDIALOG_H

#include <string>
#include <vector>

#include "about.h"

namespace ribi {

///GUI independent TestQtRoundedRectItemWidget menu dialog
struct TestQtRoundedRectItemMenuDialog
{
  static const About GetAbout() noexcept;
  static const std::string GetVersion() noexcept;
  static const std::vector<std::string> GetVersionHistory() noexcept;
};

} //~namespace ribi

#endif // TESTQTROUNDEDRECTITEMWIDGETMENUDIALOG_H
