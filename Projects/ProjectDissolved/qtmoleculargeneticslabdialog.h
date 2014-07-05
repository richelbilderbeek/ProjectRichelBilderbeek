#ifndef QTMOLECULARGENETICSLABDIALOG_H
#define QTMOLECULARGENETICSLABDIALOG_H

#include <QDialog>

namespace Ui {
  class QtMolecularGeneticsLabDialog;
}

class QtMolecularGeneticsLabDialog : public QDialog
{
  Q_OBJECT

public:
  explicit QtMolecularGeneticsLabDialog(QWidget *parent = 0);
  ~QtMolecularGeneticsLabDialog();

private:
  Ui::QtMolecularGeneticsLabDialog *ui;
};

#endif // QTMOLECULARGENETICSLABDIALOG_H
