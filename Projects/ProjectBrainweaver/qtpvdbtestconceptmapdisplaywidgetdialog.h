#ifndef QTPVDBTESTCONCEPTMAPDISPLAYWIDGETDIALOG_H
#define QTPVDBTESTCONCEPTMAPDISPLAYWIDGETDIALOG_H

#include <boost/shared_ptr.hpp>
#include "qthideandshowdialog.h"

#ifdef PVDB_USE_FORWARD_DECLARATIONS_248738
#include "pvdbfwd.h"
#else
#include "pvdbnode.h"
#include "qtpvdbconceptitem.h"
#include "qtpvdbdisplayconceptitem.h"
#include "qtpvdbnodeitem.h"
#include "qtpvdbrateconceptitem.h"
#endif

namespace Ui { class QtPvdbTestConceptMapDisplayWidgetDialog; }

///Tests all QtPvdbConceptMapWidgets
///especially the connection between the pointer and its displayal items:
///If something via the pointer is changed, this must be displayed directly
class QtPvdbTestConceptMapDisplayWidgetDialog : public QtHideAndShowDialog
{
  Q_OBJECT
  
public:
  explicit QtPvdbTestConceptMapDisplayWidgetDialog(QWidget *parent = 0);
  ~QtPvdbTestConceptMapDisplayWidgetDialog();

protected:

  void keyPressEvent(QKeyEvent *);

private slots:

  void on_button_test_modify_clicked();

private:

  Ui::QtPvdbTestConceptMapDisplayWidgetDialog *ui;

  static void Test();
};

#endif // QTPVDBTESTCONCEPTMAPDISPLAYWIDGETDIALOG_H
