#ifndef QTFISHERWRIGHTERMAINDIALOG_H
#define QTFISHERWRIGHTERMAINDIALOG_H

#include <QDialog>
#include "parameters.h"

namespace Ui {
  class QtFisherWrighterMainDialog;
}

struct QtNewickDisplay;

class QtFisherWrighterMainDialog : public QDialog
{
  Q_OBJECT

public:
  explicit QtFisherWrighterMainDialog(QWidget *parent = 0);
  ~QtFisherWrighterMainDialog();

private slots:
  void on_button_run_clicked();
  void on_button_run_next_clicked();

private:
  Ui::QtFisherWrighterMainDialog *ui;


  ///Displays the resulting Newick
  QtNewickDisplay * const m_newick_display;

  int ReadNumberOfGenerations() const noexcept;
};

#endif // QTFISHERWRIGHTERMAINDIALOG_H
