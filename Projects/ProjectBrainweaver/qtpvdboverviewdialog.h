#ifndef QTPVDBOVERVIEWDIALOG_H
#define QTPVDBOVERVIEWDIALOG_H

#include <boost/shared_ptr.hpp>
#include "qthideandshowdialog.h"

#include "pvdbfwd.h"

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
