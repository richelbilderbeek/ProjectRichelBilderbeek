#ifndef QTFISHERWRIGHTERMAINDIALOG_H
#define QTFISHERWRIGHTERMAINDIALOG_H

#include <QDialog>
#include "parameters.h"

namespace Ui {
  class QtFisherWrighterMainDialog;
}

class QtFisherWrighterMainDialog : public QDialog
{
  Q_OBJECT

public:
  explicit QtFisherWrighterMainDialog(QWidget *parent = 0);
  ~QtFisherWrighterMainDialog();

private slots:
  void on_button_run_clicked();

private:
  Ui::QtFisherWrighterMainDialog *ui;
  int ReadNumberOfGenerations() const noexcept;
};

#endif // QTFISHERWRIGHTERMAINDIALOG_H
