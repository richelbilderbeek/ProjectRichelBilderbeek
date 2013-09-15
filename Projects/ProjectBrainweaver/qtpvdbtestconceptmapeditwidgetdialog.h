#ifndef QTPVDBTESTCONCEPTMAPEDITWIDGETDIALOG_H
#define QTPVDBTESTCONCEPTMAPEDITWIDGETDIALOG_H

#include <boost/shared_ptr.hpp>
#include "qthideandshowdialog.h"

#include "pvdbfwd.h"

namespace Ui { class QtPvdbTestConceptMapEditWidgetDialog; }

namespace ribi {
namespace pvdb {

///Tests all QtPvdbConceptMapWidgets
///especially the connection between the pointer and its displayal items:
///If something via the pointer is changed, this must be displayed directly
class QtPvdbTestConceptMapEditWidgetDialog : public ribi::QtHideAndShowDialog
{
  Q_OBJECT
  
public:
  explicit QtPvdbTestConceptMapEditWidgetDialog(QWidget *parent = 0);
  QtPvdbTestConceptMapEditWidgetDialog(const QtPvdbTestConceptMapEditWidgetDialog&) = delete;
  QtPvdbTestConceptMapEditWidgetDialog& operator=(const QtPvdbTestConceptMapEditWidgetDialog&) = delete;
  ~QtPvdbTestConceptMapEditWidgetDialog();

protected:

  void keyPressEvent(QKeyEvent *);

private slots:


private:

  Ui::QtPvdbTestConceptMapEditWidgetDialog *ui;

  ///The to-be-tested concept map
  boost::shared_ptr<QtPvdbConceptMapEditWidget> m_concept_map;

  static void Test();

  void DoSomethingRandom();
};

} //~namespace pvdb
} //~namespace ribi

#endif // QTPVDBTESTCONCEPTMAPEDITWIDGETDIALOG_H
