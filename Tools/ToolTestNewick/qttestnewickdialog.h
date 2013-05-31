//---------------------------------------------------------------------------
#ifndef QTTESTNEWICKDIALOG_H
#define QTTESTNEWICKDIALOG_H
//---------------------------------------------------------------------------
#include <vector>
//---------------------------------------------------------------------------
#include <boost/shared_ptr.hpp>
#include <boost/tuple/tuple.hpp>
//---------------------------------------------------------------------------
#include <QDialog>
//---------------------------------------------------------------------------
#include "about.h"
#include "testnewickdialog.h"
//---------------------------------------------------------------------------
struct TestNewick;
//---------------------------------------------------------------------------
namespace Ui {
  class QtTestNewickDialog;
}
//---------------------------------------------------------------------------
class QtTestNewickDialog : public QDialog
{
  Q_OBJECT

public:
  explicit QtTestNewickDialog(QWidget *parent = 0);
  ~QtTestNewickDialog();

protected:
  void changeEvent(QEvent *e);
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
//---------------------------------------------------------------------------
#endif // QTTESTNEWICKDIALOG_H
