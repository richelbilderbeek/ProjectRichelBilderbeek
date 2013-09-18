#ifndef QTPVDBTESTCONCEPTMAPDISPLAYWIDGETDIALOG_H
#define QTPVDBTESTCONCEPTMAPDISPLAYWIDGETDIALOG_H

#include <boost/shared_ptr.hpp>
#include "qthideandshowdialog.h"

#include "pvdbfwd.h"

namespace Ui { class QtPvdbTestConceptMapDisplayWidgetDialog; }

namespace ribi {

namespace pvdb {

///Tests all QtPvdbConceptMapWidgets
///especially the connection between the pointer and its displayal items:
///If something via the pointer is changed, this must be displayed directly
class QtPvdbTestConceptMapDisplayWidgetDialog : public ribi::QtHideAndShowDialog
{
  Q_OBJECT
  
public:
  explicit QtPvdbTestConceptMapDisplayWidgetDialog(QWidget *parent = 0);
  QtPvdbTestConceptMapDisplayWidgetDialog(const QtPvdbTestConceptMapDisplayWidgetDialog&) = delete;
  QtPvdbTestConceptMapDisplayWidgetDialog& operator=(const QtPvdbTestConceptMapDisplayWidgetDialog&) = delete;
  ~QtPvdbTestConceptMapDisplayWidgetDialog() noexcept;

protected:

  void keyPressEvent(QKeyEvent *);

private slots:

  void on_button_test_modify_clicked();

private:

  Ui::QtPvdbTestConceptMapDisplayWidgetDialog *ui;

  ///The to-be-tested concept map
  boost::shared_ptr<QtPvdbConceptMapDisplayWidget> m_concept_map;

  static void Test();
};

} //~namespace pvdb

} //~namespace ribi

#endif // QTPVDBTESTCONCEPTMAPDISPLAYWIDGETDIALOG_H
