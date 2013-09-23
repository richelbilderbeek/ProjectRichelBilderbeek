#ifndef QTPVDBTESTCONCEPTMAPEDITWIDGETDIALOG_H
#define QTPVDBTESTCONCEPTMAPEDITWIDGETDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <boost/shared_ptr.hpp>
#include "qthideandshowdialog.h"

#include "pvdbfwd.h"
#pragma GCC diagnostic pop

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
  ~QtPvdbTestConceptMapEditWidgetDialog() noexcept;

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
