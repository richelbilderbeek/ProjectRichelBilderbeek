#ifndef QTCONCEPTMAPTESTNODEDIALOG_H
#define QTCONCEPTMAPTESTNODEDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <boost/shared_ptr.hpp>
#include "qthideandshowdialog.h"
#include "qtconceptmapfwd.h"
#pragma GCC diagnostic pop

namespace Ui { class QtTestNodeDialog; }

namespace ribi {
namespace cmap {

///Tests all QtConceptMapConceptItem items, especially the connection between the pointer and its displayal items:
///If something via the pointer is changed, this must be displayed directly
class QtTestNodeDialog : public ribi::QtHideAndShowDialog
{
  Q_OBJECT
  
public:
  explicit QtTestNodeDialog(QWidget *parent = 0);
  QtTestNodeDialog(const QtTestNodeDialog&) = delete;
  QtTestNodeDialog& operator=(const QtTestNodeDialog&) = delete;
  ~QtTestNodeDialog() noexcept;

protected:
  void keyPressEvent(QKeyEvent *event);
  
private slots:

  void on_button_load_clicked();

private:
  Ui::QtTestNodeDialog *ui;

  boost::shared_ptr<QtNodeDialog> m_qtnodedialog_1;
  boost::shared_ptr<QtNodeDialog> m_qtnodedialog_2;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace cmap
} //~namespace ribi

#endif // QTCONCEPTMAPTESTNODEDIALOG_H
