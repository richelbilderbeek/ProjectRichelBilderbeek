#include "qtmicrobialgeneticslabdialog.h"
#include "ui_qtmicrobialgeneticslabdialog.h"

QtMicrobialGeneticsLabDialog::QtMicrobialGeneticsLabDialog(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::QtMicrobialGeneticsLabDialog)
{
  ui->setupUi(this);
}

QtMicrobialGeneticsLabDialog::~QtMicrobialGeneticsLabDialog()
{
  delete ui;
}
