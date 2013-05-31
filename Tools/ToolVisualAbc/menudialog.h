#ifndef VISUALABCMENUDIALOG_H
#define VISUALABCMENUDIALOG_H
//---------------------------------------------------------------------------
#include <string>
#include <vector>
//---------------------------------------------------------------------------
#include "about.h"
//---------------------------------------------------------------------------
struct VisualAbcMenuDialog
{
  static const About GetAbout();
  static const std::string GetVersion();
  static const std::vector<std::string> GetVersionHistory();
};
//---------------------------------------------------------------------------
#endif // VISUALABCMENUDIALOG_H
