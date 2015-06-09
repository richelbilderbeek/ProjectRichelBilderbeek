#include "qttreesearchermaindialog.h"
#include "ui_qttreesearchermaindialog.h"

QtTreesearcherMainDialog::QtTreesearcherMainDialog(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::QtTreesearcherMainDialog)
{
  ui->setupUi(this);
}

QtTreesearcherMainDialog::~QtTreesearcherMainDialog()
{
  delete ui;
}
