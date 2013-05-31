#ifndef TESTQTROUNDEDRECTITEMWIDGETMENUDIALOG_H
#define TESTQTROUNDEDRECTITEMWIDGETMENUDIALOG_H

#include <string>
#include <vector>

#include "about.h"

///GUI independent TestQtRoundedRectItemWidget menu dialog
struct TestQtRoundedRectItemMenuDialog
{
  static const About GetAbout();
  static const std::string GetVersion();
  static const std::vector<std::string> GetVersionHistory();
};

#endif // TESTQTROUNDEDRECTITEMWIDGETMENUDIALOG_H
