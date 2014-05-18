#ifndef QTCONCEPTMAPTESTEXAMPLEDIALOG_H
#define QTCONCEPTMAPTESTEXAMPLEDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <boost/shared_ptr.hpp>
#include "qthideandshowdialog.h"

#include "qtconceptmapfwd.h"
#pragma GCC diagnostic pop

namespace Ui { class QtConceptMapTestExampleDialog; }

namespace ribi {
namespace cmap {

///Tests QtExampleDialog
class QtConceptMapTestExampleDialog : public ribi::QtHideAndShowDialog
{
  Q_OBJECT

public:
  explicit QtConceptMapTestExampleDialog(QWidget *parent = 0);
  QtConceptMapTestExampleDialog(const QtConceptMapTestExampleDialog&) = delete;
  QtConceptMapTestExampleDialog& operator=(const QtConceptMapTestExampleDialog&) = delete;
  ~QtConceptMapTestExampleDialog();

private slots:

  void on_button_load_example_clicked();

private:
  Ui::QtConceptMapTestExampleDialog *ui;
  boost::shared_ptr<QtExampleDialog> m_example_dialog;
};

} //~namespace cmap
} //~namespace ribi

#endif // QTCONCEPTMAPTESTEXAMPLEDIALOG_H
