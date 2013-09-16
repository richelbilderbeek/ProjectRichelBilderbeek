#ifndef TESTQTROUNDEDEDITRECTITEMWIDGETMENUDIALOG_H
#define TESTQTROUNDEDEDITRECTITEMWIDGETMENUDIALOG_H

#include <string>
#include <vector>

#include "about.h"

namespace ribi {

///GUI independent TestQtRoundedEditRectItemWidget menu dialog
struct TestQtRoundedEditRectItemMenuDialog
{
  static const About GetAbout() noexcept;
  static const std::string GetVersion() noexcept;
  static const std::vector<std::string> GetVersionHistory() noexcept;
};

} //~namespace ribi

#endif // TESTQTROUNDEDEDITRECTITEMWIDGETMENUDIALOG_H
