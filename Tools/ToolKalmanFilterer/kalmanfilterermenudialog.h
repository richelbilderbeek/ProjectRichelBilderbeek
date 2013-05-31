#ifndef KALMANFILTERERMENUDIALOG_H
#define KALMANFILTERERMENUDIALOG_H

#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif

#include <string>
#include <vector>

#include "about.h"

///GUI independent KalmanFilterer menu dialog
struct KalmanFiltererMenuDialog
{
  KalmanFiltererMenuDialog();
  static const About GetAbout();
  static const std::string GetVersion();
  static const std::vector<std::string> GetVersionHistory();
};

#endif // KALMANFILTERERMENUDIALOG_H
