#ifndef QTCONCEPTMAPTESTDISPLAYCONCEPTMAPDIALOG_H
#define QTCONCEPTMAPTESTDISPLAYCONCEPTMAPDIALOG_H

#define ADD_LATER_20140801
#ifdef  ADD_LATER_20140801

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <boost/shared_ptr.hpp>
#include "qthideandshowdialog.h"

#include "qtconceptmapfwd.h"
#pragma GCC diagnostic pop

namespace Ui { class QtTestDisplayConceptMapDialog; }

namespace ribi {

namespace cmap {

///Tests all QtConceptMaps
///especially the connection between the pointer and its displayal items:
///If something via the pointer is changed, this must be displayed directly
class QtTestDisplayConceptMapDialog : public ribi::QtHideAndShowDialog
{
  Q_OBJECT
  
public:
  explicit QtTestDisplayConceptMapDialog(QWidget *parent = 0);
  QtTestDisplayConceptMapDialog(const QtTestDisplayConceptMapDialog&) = delete;
  QtTestDisplayConceptMapDialog& operator=(const QtTestDisplayConceptMapDialog&) = delete;
  ~QtTestDisplayConceptMapDialog() noexcept;

protected:

  void keyPressEvent(QKeyEvent *);

private slots:

  void on_button_test_modify_clicked();

private:

  Ui::QtTestDisplayConceptMapDialog *ui;

  ///The to-be-tested concept map
  boost::shared_ptr<QtDisplayConceptMap> m_concept_map;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace cmap
} //~namespace ribi

#endif // ADD_LATER_20140801

#endif // QTCONCEPTMAPTESTDISPLAYCONCEPTMAPDIALOG_H
