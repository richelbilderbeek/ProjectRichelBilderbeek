#ifndef KALMANFILTERERMENUDIALOG_H
#define KALMANFILTERERMENUDIALOG_H

#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorUnableToFindNumericLiteralOperatorPperatorQ.htm
#if !(__GNUC__ >= 4 && __GNUC_MINOR__ >= 8)
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif
#endif

#include <string>
#include <vector>

#include "about.h"

///GUI independent KalmanFilterer menu dialog
struct KalmanFiltererMenuDialog
{
  static const About GetAbout();
  static const std::string GetVersion();
  static const std::vector<std::string> GetVersionHistory();
};

#endif // KALMANFILTERERMENUDIALOG_H
