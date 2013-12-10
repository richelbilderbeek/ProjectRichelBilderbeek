#ifndef QTCONCEPTMAPTESTCONCEPTMAPDISPLAYWIDGETDIALOG_H
#define QTCONCEPTMAPTESTCONCEPTMAPDISPLAYWIDGETDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <boost/shared_ptr.hpp>
#include "qthideandshowdialog.h"

#include "qtconceptmapfwd.h"
#pragma GCC diagnostic pop

namespace Ui { class QtTestConceptMapDisplayWidgetDialog; }

namespace ribi {

namespace cmap {

///Tests all QtConceptMaps
///especially the connection between the pointer and its displayal items:
///If something via the pointer is changed, this must be displayed directly
class QtTestConceptMapDisplayWidgetDialog : public ribi::QtHideAndShowDialog
{
  Q_OBJECT
  
public:
  explicit QtTestConceptMapDisplayWidgetDialog(QWidget *parent = 0);
  QtTestConceptMapDisplayWidgetDialog(const QtTestConceptMapDisplayWidgetDialog&) = delete;
  QtTestConceptMapDisplayWidgetDialog& operator=(const QtTestConceptMapDisplayWidgetDialog&) = delete;
  ~QtTestConceptMapDisplayWidgetDialog() noexcept;

protected:

  void keyPressEvent(QKeyEvent *);

private slots:

  void on_button_test_modify_clicked();

private:

  Ui::QtTestConceptMapDisplayWidgetDialog *ui;

  ///The to-be-tested concept map
  boost::shared_ptr<QtConceptMapDisplayWidget> m_concept_map;

  static void Test();
};

} //~namespace cmap

} //~namespace ribi

#endif // QTCONCEPTMAPTESTCONCEPTMAPDISPLAYWIDGETDIALOG_H
