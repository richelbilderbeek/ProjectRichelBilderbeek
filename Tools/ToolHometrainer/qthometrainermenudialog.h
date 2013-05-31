#ifndef QTHOMETRAINERMENUDIALOG_H
#define QTHOMETRAINERMENUDIALOG_H

#include "qthideandshowdialog.h"

namespace Ui {
  class QtHometrainerMenuDialog;
}

class QtHometrainerMenuDialog : public QtHideAndShowDialog
{
  Q_OBJECT

public:
  explicit QtHometrainerMenuDialog(QWidget *parent = 0);
  ~QtHometrainerMenuDialog();

protected:
  void changeEvent(QEvent *e);

private:
  Ui::QtHometrainerMenuDialog *ui;

private slots:
  void on_button_about_clicked();
  void on_button_quit_clicked();
  void on_button_start_clicked();
};

#endif // QTHOMETRAINERMENUDIALOG_H
