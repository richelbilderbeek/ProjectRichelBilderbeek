#ifndef TOOLMULTIENCRANGERMAINDIALOG_H
#define TOOLMULTIENCRANGERMAINDIALOG_H

#include <string>
#include <vector>
#include "about.h"

namespace ribi {

struct ToolMultiEncrangerMenuDialog
{
  static const About GetAbout() noexcept;
  static const std::string GetVersion() noexcept;
  static const std::vector<std::string> GetVersionHistory() noexcept;
};

} //~namespace ribi

#endif // TOOLMULTIENCRANGERMAINDIALOG_H
