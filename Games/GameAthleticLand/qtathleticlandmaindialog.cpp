#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "qtathleticlandmaindialog.h"
#include "ui_qtathleticlandmaindialog.h"
#pragma GCC diagnostic pop

ribi::QtAthleticLandMainDialog::QtAthleticLandMainDialog(QWidget *parent)
  : QtHideAndShowDialog(parent),
    ui(new Ui::QtAthleticLandMainDialog)
{
  ui->setupUi(this);
}

ribi::QtAthleticLandMainDialog::~QtAthleticLandMainDialog()
{
  delete ui;
}
