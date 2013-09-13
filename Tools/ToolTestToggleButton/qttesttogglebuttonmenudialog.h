#ifndef QTTESTTOGGLEBUTTONMENUDIALOG_H
#define QTTESTTOGGLEBUTTONMENUDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include <QDialog>
#pragma GCC diagnostic pop

namespace Ui {
  class QtTestToggleButtonMenuDialog;
}

namespace ribi {

class QtTestToggleButtonMenuDialog : public QDialog
{
  Q_OBJECT

public:
  explicit QtTestToggleButtonMenuDialog(QWidget *parent = 0);
  QtTestToggleButtonMenuDialog(const QtTestToggleButtonMenuDialog&) = delete;
  QtTestToggleButtonMenuDialog& operator=(const QtTestToggleButtonMenuDialog&) = delete;
  ~QtTestToggleButtonMenuDialog();

private slots:
  void on_button_start_clicked();
  void on_button_about_clicked();
  void on_button_quit_clicked();

private:
  Ui::QtTestToggleButtonMenuDialog *ui;
};

} //~namespace ribi

#endif // QTTESTTOGGLEBUTTONMENUDIALOG_H
