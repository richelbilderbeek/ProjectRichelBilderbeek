#include "qtmoleculargeneticslabdialog.h"
#include "ui_qtmoleculargeneticslabdialog.h"

QtMolecularGeneticsLabDialog::QtMolecularGeneticsLabDialog(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::QtMolecularGeneticsLabDialog)
{
  ui->setupUi(this);
}

QtMolecularGeneticsLabDialog::~QtMolecularGeneticsLabDialog()
{
  delete ui;
}
