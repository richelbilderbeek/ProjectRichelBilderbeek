#ifndef QTTESTTOGGLEBUTTONMENUDIALOG_H
#define QTTESTTOGGLEBUTTONMENUDIALOG_H
//---------------------------------------------------------------------------
#include <QDialog>
//---------------------------------------------------------------------------
namespace Ui {
class QtTestToggleButtonMenuDialog;
}
//---------------------------------------------------------------------------
class QtTestToggleButtonMenuDialog : public QDialog
{
  Q_OBJECT

public:
  explicit QtTestToggleButtonMenuDialog(QWidget *parent = 0);
  ~QtTestToggleButtonMenuDialog();

private slots:
  void on_button_start_clicked();
  void on_button_about_clicked();
  void on_button_quit_clicked();

private:
  Ui::QtTestToggleButtonMenuDialog *ui;
};
//---------------------------------------------------------------------------
#endif // QTTESTTOGGLEBUTTONMENUDIALOG_H
