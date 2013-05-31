#ifndef QTPVDBTESTCONCEPTMAPEDITWIDGETDIALOG_H
#define QTPVDBTESTCONCEPTMAPEDITWIDGETDIALOG_H

#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif

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

namespace Ui { class QtPvdbTestConceptMapEditWidgetDialog; }

///Tests all QtPvdbConceptMapWidgets
///especially the connection between the pointer and its displayal items:
///If something via the pointer is changed, this must be displayed directly
class QtPvdbTestConceptMapEditWidgetDialog : public QtHideAndShowDialog
{
  Q_OBJECT
  
public:
  explicit QtPvdbTestConceptMapEditWidgetDialog(QWidget *parent = 0);
  ~QtPvdbTestConceptMapEditWidgetDialog();

protected:

  void keyPressEvent(QKeyEvent *);

private slots:

  void on_button_modify_clicked();

private:

  Ui::QtPvdbTestConceptMapEditWidgetDialog *ui;

  static void Test();
};

#endif // QTPVDBTESTCONCEPTMAPEDITWIDGETDIALOG_H
