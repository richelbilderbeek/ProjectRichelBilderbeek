#ifndef QTPVDBOVERVIEWDIALOG_H
#define QTPVDBOVERVIEWDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <boost/shared_ptr.hpp>
#include "qthideandshowdialog.h"

#include "pvdbfwd.h"
#pragma GCC diagnostic pop

namespace ribi {
namespace pvdb {

struct QtPvdbOverviewDialog : public ribi::QtHideAndShowDialog
{
  explicit QtPvdbOverviewDialog(QWidget* parent = 0);

protected:
  void keyPressEvent(QKeyEvent *);
};

} //~namespace pvdb
} //~namespace ribi

#endif // QTPVDBOVERVIEWDIALOG_H
