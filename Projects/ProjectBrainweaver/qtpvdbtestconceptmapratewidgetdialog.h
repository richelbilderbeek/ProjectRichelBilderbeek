#ifndef QTPVDBTESTCONCEPTMAPRATEWIDGETDIALOG_H
#define QTPVDBTESTCONCEPTMAPRATEWIDGETDIALOG_H

#include <boost/shared_ptr.hpp>
#include "qthideandshowdialog.h"

#include "pvdbfwd.h"

namespace Ui { class QtPvdbTestConceptMapRateWidgetDialog; }

namespace ribi {

namespace pvdb {

///Tests all QtPvdbConceptMapWidgets
///especially the connection between the pointer and its displayal items:
///If something via the pointer is changed, this must be displayed directly
class QtPvdbTestConceptMapRateWidgetDialog : public ribi::QtHideAndShowDialog
{
  Q_OBJECT
  
public:
  explicit QtPvdbTestConceptMapRateWidgetDialog(QWidget *parent = 0);
  QtPvdbTestConceptMapRateWidgetDialog(const QtPvdbTestConceptMapRateWidgetDialog&) = delete;
  QtPvdbTestConceptMapRateWidgetDialog& operator=(const QtPvdbTestConceptMapRateWidgetDialog&) = delete;
  ~QtPvdbTestConceptMapRateWidgetDialog() noexcept;

protected:

  void keyPressEvent(QKeyEvent *);

private slots:

private:

  Ui::QtPvdbTestConceptMapRateWidgetDialog *ui;

  ///The to-be-tested concept map
  boost::shared_ptr<QtPvdbConceptMapRateWidget> m_concept_map;

  void DoSomethingRandom();

  static void Test();
};

} //~namespace pvdb

} //~namespace ribi

#endif // QTPVDBTESTCONCEPTMAPRATEWIDGETDIALOG_H
