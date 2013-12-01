#ifndef QTPVDBVIEWTESTSDIALOG_H
#define QTPVDBVIEWTESTSDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <boost/shared_ptr.hpp>
#include "qthideandshowdialog.h"

#include "pvdbfwd.h"
#pragma GCC diagnostic pop

namespace Ui {
  class QtPvdbViewTestsDialog;
}

namespace ribi {

namespace pvdb {

class QtPvdbViewTestsDialog : public ribi::QtHideAndShowDialog
{
  Q_OBJECT
  
public:
  explicit QtPvdbViewTestsDialog(QWidget* parent = 0);
  QtPvdbViewTestsDialog(const QtPvdbViewTestsDialog&) = delete;
  QtPvdbViewTestsDialog& operator=(const QtPvdbViewTestsDialog&) = delete;
  ~QtPvdbViewTestsDialog() noexcept;

protected:
  void keyPressEvent(QKeyEvent* event);
  
private:
  Ui::QtPvdbViewTestsDialog *ui;

  /// ComplexHomomorphousTestConceptMaps
  const std::vector<boost::shared_ptr<ribi::cmap::ConceptMap> > m_c;

  /// HeteromorphousTestConceptMaps
  const std::vector<boost::shared_ptr<ribi::cmap::ConceptMap> > m_h;

  /// SimpleHomomorphousTestConceptMaps
  const std::vector<boost::shared_ptr<ribi::cmap::ConceptMap> > m_s;

  /// Tha widgets
  std::vector<boost::shared_ptr<QtPvdbConceptMapWidget> > m_widgets;

  #ifndef NDEBUG
  static void Test();
  #endif

  static boost::shared_ptr<QtPvdbConceptMapWidget> CreateWidget(
    const int type,
    const boost::shared_ptr<ribi::cmap::ConceptMap> concept_map);
};

} //~namespace pvdb

} //~namespace ribi

#endif // QTPVDBVIEWTESTSDIALOG_H
