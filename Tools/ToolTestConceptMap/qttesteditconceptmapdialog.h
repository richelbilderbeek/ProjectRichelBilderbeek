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

namespace Ui { class QtTestEditConceptMapDialog; }

namespace ribi {
namespace cmap {

///Tests all QtConceptMaps
///especially the connection between the pointer and its displayal items:
///If something via the pointer is changed, this must be displayed directly
class QtTestEditConceptMapDialog : public ribi::QtHideAndShowDialog
{
  Q_OBJECT
  
public:
  explicit QtTestEditConceptMapDialog(QWidget *parent = 0);
  QtTestEditConceptMapDialog(const QtTestEditConceptMapDialog&) = delete;
  QtTestEditConceptMapDialog& operator=(const QtTestEditConceptMapDialog&) = delete;
  ~QtTestEditConceptMapDialog() noexcept;

protected:

  void keyPressEvent(QKeyEvent *);

private slots:

  void OnCheck();

private:

  Ui::QtTestEditConceptMapDialog *ui;

  ///The to-be-tested concept map
  boost::shared_ptr<QtConceptMap> m_conceptmap;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif

  void DoSomethingRandom();
};

} //~namespace cmap
} //~namespace ribi

#endif // QTCONCEPTMAPTESTCONCEPTMAPEDITWIDGETDIALOG_H
