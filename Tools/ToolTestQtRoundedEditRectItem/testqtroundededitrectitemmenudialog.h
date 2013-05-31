#ifndef TESTQTROUNDEDEDITRECTITEMWIDGETMENUDIALOG_H
#define TESTQTROUNDEDEDITRECTITEMWIDGETMENUDIALOG_H

#include <string>
#include <vector>

#include "about.h"

///GUI independent TestQtRoundedEditRectItemWidget menu dialog
struct TestQtRoundedEditRectItemMenuDialog
{
  static const About GetAbout();
  static const std::string GetVersion();
  static const std::vector<std::string> GetVersionHistory();
};

#endif // TESTQTROUNDEDEDITRECTITEMWIDGETMENUDIALOG_H
