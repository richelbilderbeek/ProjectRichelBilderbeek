#ifndef QTPVDBTESTCONCEPTMAPRATEWIDGETDIALOG_H
#define QTPVDBTESTCONCEPTMAPRATEWIDGETDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <boost/shared_ptr.hpp>
#include "qthideandshowdialog.h"

#include "conceptmapfwd.h"
#pragma GCC diagnostic pop

namespace Ui { class QtTestConceptMapRateWidgetDialog; }

namespace ribi {
namespace cmap {

///Tests all QtConceptMapWidgets
///especially the connection between the pointer and its displayal items:
///If something via the pointer is changed, this must be displayed directly
class QtTestConceptMapRateWidgetDialog : public ribi::QtHideAndShowDialog
{
  Q_OBJECT
  
public:
  explicit QtTestConceptMapRateWidgetDialog(QWidget *parent = 0);
  QtTestConceptMapRateWidgetDialog(const QtTestConceptMapRateWidgetDialog&) = delete;
  QtTestConceptMapRateWidgetDialog& operator=(const QtTestConceptMapRateWidgetDialog&) = delete;
  ~QtTestConceptMapRateWidgetDialog() noexcept;

protected:

  void keyPressEvent(QKeyEvent *);

private slots:

private:

  Ui::QtTestConceptMapRateWidgetDialog *ui;

  ///The to-be-tested concept map
  boost::shared_ptr<QtConceptMapRateWidget> m_concept_map;

  void DoSomethingRandom();

  static void Test();
};

} //~namespace cmap

} //~namespace ribi

#endif // QTPVDBTESTCONCEPTMAPRATEWIDGETDIALOG_H
