#ifndef QTCONCEPTMAPTESTCONCEPTMAPEDITWIDGETDIALOG_H
#define QTCONCEPTMAPTESTCONCEPTMAPEDITWIDGETDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <boost/shared_ptr.hpp>
#include "qthideandshowdialog.h"

#include "qtconceptmapfwd.h"
#pragma GCC diagnostic pop

namespace Ui { class QtTestConceptMapEditWidgetDialog; }

namespace ribi {
namespace cmap {

///Tests all QtConceptMapWidgets
///especially the connection between the pointer and its displayal items:
///If something via the pointer is changed, this must be displayed directly
class QtTestConceptMapEditWidgetDialog : public ribi::QtHideAndShowDialog
{
  Q_OBJECT
  
public:
  explicit QtTestConceptMapEditWidgetDialog(QWidget *parent = 0);
  QtTestConceptMapEditWidgetDialog(const QtTestConceptMapEditWidgetDialog&) = delete;
  QtTestConceptMapEditWidgetDialog& operator=(const QtTestConceptMapEditWidgetDialog&) = delete;
  ~QtTestConceptMapEditWidgetDialog() noexcept;

protected:

  void keyPressEvent(QKeyEvent *);

private slots:


private:

  Ui::QtTestConceptMapEditWidgetDialog *ui;

  ///The to-be-tested concept map
  boost::shared_ptr<QtConceptMapEditWidget> m_concept_map;

  static void Test();

  void DoSomethingRandom();
};

} //~namespace cmap
} //~namespace ribi

#endif // QTCONCEPTMAPTESTCONCEPTMAPEDITWIDGETDIALOG_H
