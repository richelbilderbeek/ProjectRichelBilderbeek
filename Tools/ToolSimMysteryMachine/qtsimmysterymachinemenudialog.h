#ifndef QTSIMMYSTERYMACHINEMENUDIALOG_H
#define QTSIMMYSTERYMACHINEMENUDIALOG_H
//---------------------------------------------------------------------------
#include <QDialog>
//---------------------------------------------------------------------------
namespace Ui {
  class QtSimMysteryMachineMenuDialog;
}
//---------------------------------------------------------------------------
class QtSimMysteryMachineMenuDialog : public QDialog
{
  Q_OBJECT

public:
  explicit QtSimMysteryMachineMenuDialog(QWidget *parent = 0);
  ~QtSimMysteryMachineMenuDialog();

protected:
  void changeEvent(QEvent *e);

private:
  Ui::QtSimMysteryMachineMenuDialog *ui;

private slots:
    void on_button_start_clicked();
    void on_button_about_clicked();
    void on_button_quit_clicked();
    void on_button_instructions_clicked();
    void on_button_real_clicked();
};
//---------------------------------------------------------------------------
#endif // QTSIMMYSTERYMACHINEMENUDIALOG_H
