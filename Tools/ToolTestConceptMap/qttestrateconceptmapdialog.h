#ifndef QTCONCEPTMAPTESTCONCEPTMAPRATEWIDGETDIALOG_H
#define QTCONCEPTMAPTESTCONCEPTMAPRATEWIDGETDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <boost/shared_ptr.hpp>
#include "qthideandshowdialog.h"

#include "qtconceptmapfwd.h"
#pragma GCC diagnostic pop

namespace Ui { class QtTestRateConceptMapDialog; }

namespace ribi {
namespace cmap {

///Tests the QtConceptMaps
///especially the connection between the pointer and its displayal items:
///If something via the pointer is changed, this must be displayed directly
class QtTestRateConceptMapDialog : public ribi::QtHideAndShowDialog
{
  Q_OBJECT
  
public:
  explicit QtTestRateConceptMapDialog(QWidget *parent = 0);
  QtTestRateConceptMapDialog(const QtTestRateConceptMapDialog&) = delete;
  QtTestRateConceptMapDialog& operator=(const QtTestRateConceptMapDialog&) = delete;
  ~QtTestRateConceptMapDialog() noexcept;

protected:

  void keyPressEvent(QKeyEvent *);

private slots:

private:

  Ui::QtTestRateConceptMapDialog *ui;

  ///The to-be-tested concept map
  boost::shared_ptr<QtRateConceptMap> m_concept_map;

  void DoSomethingRandom();

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace cmap

} //~namespace ribi

#endif // QTCONCEPTMAPTESTCONCEPTMAPRATEWIDGETDIALOG_H
