#ifndef QTCONCEPTMAPTESTEXAMPLESDIALOG_H
#define QTCONCEPTMAPTESTEXAMPLESDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <boost/shared_ptr.hpp>
#include "qthideandshowdialog.h"

#include "qtconceptmapfwd.h"
#pragma GCC diagnostic pop

namespace Ui { class QtConceptMapTestExamplesDialog; }

namespace ribi {
namespace cmap {

class QtConceptMapTestExamplesDialog : public ribi::QtHideAndShowDialog
{
  Q_OBJECT

public:
  explicit QtConceptMapTestExamplesDialog(QWidget *parent = 0);
  QtConceptMapTestExamplesDialog(const QtConceptMapTestExamplesDialog&) = delete;
  QtConceptMapTestExamplesDialog& operator=(const QtConceptMapTestExamplesDialog&) = delete;
  ~QtConceptMapTestExamplesDialog();

private slots:
  void keyPressEvent(QKeyEvent *event);
  void on_button_load_examples_clicked();
private:
  Ui::QtConceptMapTestExamplesDialog *ui;
  boost::shared_ptr<QtExamplesDialog> m_examples_1;
  boost::shared_ptr<QtExamplesDialog> m_examples_2;


};

} //~namespace cmap
} //~namespace ribi

#endif // QTCONCEPTMAPTESTEXAMPLESDIALOG_H
