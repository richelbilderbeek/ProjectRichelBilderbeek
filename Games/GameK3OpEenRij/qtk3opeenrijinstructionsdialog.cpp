#include "qtk3opeenrijinstructionsdialog.h"
#include "ui_qtk3opeenrijinstructionsdialog.h"

QtK3OpEenRijInstructionsDialog::QtK3OpEenRijInstructionsDialog(QWidget *parent) :
  QtHideAndShowDialog(parent),
  ui(new Ui::QtK3OpEenRijInstructionsDialog)
{
  ui->setupUi(this);
}

QtK3OpEenRijInstructionsDialog::~QtK3OpEenRijInstructionsDialog()
{
  delete ui;
}
