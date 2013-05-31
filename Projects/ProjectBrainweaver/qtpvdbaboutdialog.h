#ifndef QTPVDBABOUTDIALOG_H
#define QTPVDBABOUTDIALOG_H

#include "qtaboutdialog.h"

struct QtPvdbAboutDialog
{
  ///Obtain the QtAboutDialog for this project
  static const boost::shared_ptr<QtAboutDialog> Get();
};

#endif // QTPVDBABOUTDIALOG_H
