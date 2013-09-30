#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "qttooldotmatrixmaindialog.h"
#include "ui_qttooldotmatrixmaindialog.h"
#pragma GCC diagnostic pop

ribi::QtToolDotMatrixMainDialog::QtToolDotMatrixMainDialog(QWidget *parent)
  : QtHideAndShowDialog(parent),
    ui(new Ui::QtToolDotMatrixMainDialog)
{
  ui->setupUi(this);
}

ribi::QtToolDotMatrixMainDialog::~QtToolDotMatrixMainDialog() noexcept
{
  delete ui;
}
