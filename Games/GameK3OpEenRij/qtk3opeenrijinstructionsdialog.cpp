#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "qtk3opeenrijinstructionsdialog.h"
#include "ui_qtk3opeenrijinstructionsdialog.h"
#pragma GCC diagnostic pop

ribi::QtK3OpEenRijInstructionsDialog::QtK3OpEenRijInstructionsDialog(QWidget *parent) noexcept
  : QtHideAndShowDialog(parent),
    ui(new Ui::QtK3OpEenRijInstructionsDialog)
{
  ui->setupUi(this);
}

ribi::QtK3OpEenRijInstructionsDialog::~QtK3OpEenRijInstructionsDialog() noexcept
{
  delete ui;
}
