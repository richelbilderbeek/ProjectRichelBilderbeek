#ifndef QTPVDBVIEWTESTSDIALOG_H
#define QTPVDBVIEWTESTSDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <boost/shared_ptr.hpp>
#include "qthideandshowdialog.h"

#include "qtconceptmapfwd.h"
#pragma GCC diagnostic pop

namespace Ui {
  class QtConceptMapViewTestsDialog;
}

namespace ribi {
namespace cmap {

class QtConceptMapViewTestsDialog : public ribi::QtHideAndShowDialog
{
  Q_OBJECT
  
public:
  explicit QtConceptMapViewTestsDialog(QWidget* parent = 0);
  QtConceptMapViewTestsDialog(const QtConceptMapViewTestsDialog&) = delete;
  QtConceptMapViewTestsDialog& operator=(const QtConceptMapViewTestsDialog&) = delete;
  ~QtConceptMapViewTestsDialog() noexcept;

protected:
  void keyPressEvent(QKeyEvent* event);
  
private:
  Ui::QtConceptMapViewTestsDialog *ui;

  /// ComplexHomomorphousTestConceptMaps
  const std::vector<boost::shared_ptr<ConceptMap> > m_c;

  /// HeteromorphousTestConceptMaps
  const std::vector<boost::shared_ptr<ConceptMap> > m_h;

  /// SimpleHomomorphousTestConceptMaps
  const std::vector<boost::shared_ptr<ConceptMap> > m_s;

  /// Tha widgets
  std::vector<boost::shared_ptr<cmap::QtConceptMap> > m_widgets;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif

  static boost::shared_ptr<cmap::QtConceptMap> CreateWidget(
    const boost::shared_ptr<ConceptMap> conceptmap);
};

} //~namespace cmap
} //~namespace ribi

#endif // QTPVDBVIEWTESTSDIALOG_H
