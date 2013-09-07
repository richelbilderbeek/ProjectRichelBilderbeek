#ifndef PVDBMENUDIALOG_H
#define PVDBMENUDIALOG_H

#include <string>
#include <vector>

#include <boost/shared_ptr.hpp>

#include "about.h"

namespace ribi {
namespace pvdb {

///The GUI independent version of Project Van Den Bogaart its menu dialog
struct MenuDialog
{
  ///Obtain the version of this class
  static const std::string GetVersion();

  ///Obtain the version history of this class
  static const std::vector<std::string> GetVersionHistory();

  ///Obtain the About information of this class
  static const About GetAbout();
};

} //~namespace pvdb
} //~namespace ribi

#endif // PVDBMENUDIALOG_H

