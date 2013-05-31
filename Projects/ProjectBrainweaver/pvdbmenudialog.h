#ifndef PVDBMENUDIALOG_H
#define PVDBMENUDIALOG_H

#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif

#include <string>
#include <vector>

#include <boost/shared_ptr.hpp>

#include "about.h"

namespace pvdb {

///The GUI independent version of Project Van Den Bogaart its menu dialog
struct MenuDialog
{
  MenuDialog();

  ///Obtain the version of this class
  static const std::string GetVersion();

  ///Obtain the version history of this class
  static const std::vector<std::string> GetVersionHistory();

  ///Obtain the About information of this class
  static const About GetAbout();

  private:
  ///Block destructor, except for the friend boost::checked_delete
  ~MenuDialog() {}

  ///Correct befriending, from http://richelbilderbeek.nl/CppChecked_delete.htm
  friend void boost::checked_delete<>(MenuDialog* x);

};

} //~namespace pvdb

#endif // PVDBMENUDIALOG_H

