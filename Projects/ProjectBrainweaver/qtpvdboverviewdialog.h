#ifndef QTPVDBOVERVIEWDIALOG_H
#define QTPVDBOVERVIEWDIALOG_H

#include <boost/shared_ptr.hpp>
#include "qthideandshowdialog.h"

#ifdef PVDB_USE_FORWARD_DECLARATIONS_248738
#include "pvdbfwd.h"
#else

#endif

struct QtPvdbOverviewDialog : public QtHideAndShowDialog
{
  explicit QtPvdbOverviewDialog(QWidget* parent = 0);

protected:
  void keyPressEvent(QKeyEvent *);
};

#endif // QTPVDBOVERVIEWDIALOG_H
