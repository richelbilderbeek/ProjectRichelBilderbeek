//---------------------------------------------------------------------------
#include "nsanabrosqtheader.h"
#include "ui_qtnsanabrosoptionsdialog.h"
//---------------------------------------------------------------------------
QtNsanaBrosOptionsDialog::QtNsanaBrosOptionsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QtNsanaBrosOptionsDialog)
{
  TRACE_FUNC();
  ui->setupUi(this);

  NsanaBrosKeys::SetKeyUp(Qt::Key_Up);
  NsanaBrosKeys::SetKeyDown(Qt::Key_Down);
  NsanaBrosKeys::SetKeyLeft(Qt::Key_Left);
  NsanaBrosKeys::SetKeyRight(Qt::Key_Right);
}
//---------------------------------------------------------------------------
QtNsanaBrosOptionsDialog::~QtNsanaBrosOptionsDialog()
{
  delete ui;
}
//---------------------------------------------------------------------------
void QtNsanaBrosOptionsDialog::changeEvent(QEvent *e)
{
  QDialog::changeEvent(e);
  switch (e->type()) {
  case QEvent::LanguageChange:
    ui->retranslateUi(this);
    break;
  default:
    break;
  }
}
//---------------------------------------------------------------------------
