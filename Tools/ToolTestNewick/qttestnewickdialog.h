#ifndef QTTESTNEWICKDIALOG_H
#define QTTESTNEWICKDIALOG_H

#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <boost/shared_ptr.hpp>
#include <boost/tuple/tuple.hpp>

#include <QDialog>

#include "about.h"
#include "testnewickdialog.h"
#pragma GCC diagnostic pop

namespace Ui {
  class QtTestNewickDialog;
}

namespace ribi {

struct TestNewick;

class QtTestNewickDialog : public QDialog
{
  Q_OBJECT

public:
  explicit QtTestNewickDialog(QWidget *parent = 0);
  QtTestNewickDialog(const QtTestNewickDialog&) = delete;
  QtTestNewickDialog& operator=(const QtTestNewickDialog&) = delete;
  ~QtTestNewickDialog();

protected:
  void resizeEvent(QResizeEvent *);

private:
  Ui::QtTestNewickDialog *ui;
  TestNewickDialog m_dialog;
  void Display();



private slots:
  void on_button_about_clicked();
  void on_any_change();
  void on_button_compare_clicked();

};

} //~namespace ribi

#endif // QTTESTNEWICKDIALOG_H
