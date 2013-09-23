#ifndef QTPVDBABOUTDIALOG_H
#define QTPVDBABOUTDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <boost/shared_ptr.hpp>

#include "qtaboutdialog.h"
#pragma GCC diagnostic pop

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
