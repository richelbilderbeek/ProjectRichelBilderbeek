#ifndef QTPVDBABOUTDIALOG_H
#define QTPVDBABOUTDIALOG_H

#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif

#include <boost/shared_ptr.hpp>

#include "qtaboutdialog.h"

struct QtPvdbAboutDialog
{

  ///Obtain the QtAboutDialog for this project
  static const boost::shared_ptr<QtAboutDialog> Get();
};

#endif // QTPVDBABOUTDIALOG_H
