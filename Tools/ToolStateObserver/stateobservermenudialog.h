#ifndef TESTSTATEOBSERVERMENUDIALOG_H
#define TESTSTATEOBSERVERMENUDIALOG_H

#include "about.h"

struct StateObserverMenuDialog
{

  ///Obtain this class its About information
  static const About GetAbout();

  ///Obtain this class its version
  static const std::string GetVersion();

  ///Obtain this class its version history
  static const std::vector<std::string> GetVersionHistory();
};

#endif // TESTSTATEOBSERVERMENUDIALOG_H
