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

namespace Ui { class QtTestExampleDialog; }

namespace ribi {
namespace cmap {

///Tests QtExampleDialog
class QtTestExampleDialog : public ribi::QtHideAndShowDialog
{
  Q_OBJECT

public:
  explicit QtTestExampleDialog(QWidget *parent = 0);
  QtTestExampleDialog(const QtTestExampleDialog&) = delete;
  QtTestExampleDialog& operator=(const QtTestExampleDialog&) = delete;
  ~QtTestExampleDialog();

protected:
  void keyPressEvent(QKeyEvent *event);

private slots:

  void on_button_load_example_clicked();

private:
  Ui::QtTestExampleDialog *ui;
  boost::shared_ptr<QtExampleDialog> m_example_1;
  boost::shared_ptr<QtExampleDialog> m_example_2;
};

} //~namespace cmap
} //~namespace ribi

#endif // QTCONCEPTMAPTESTEXAMPLEDIALOG_H
