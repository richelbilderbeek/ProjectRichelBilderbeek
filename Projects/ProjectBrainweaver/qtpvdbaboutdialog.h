#ifndef QTPVDBABOUTDIALOG_H
#define QTPVDBABOUTDIALOG_H

#include <boost/shared_ptr.hpp>

#include "qtaboutdialog.h"

namespace ribi {

namespace pvdb {

struct QtPvdbAboutDialog
{
  ///Obtain the QtAboutDialog for this project
  static const boost::shared_ptr<QtAboutDialog> Get();
};

} //~namespace pvdb

} //~namespace ribi

#endif // QTPVDBABOUTDIALOG_H
