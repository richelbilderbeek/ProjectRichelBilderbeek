//---------------------------------------------------------------------------
#include "nsanabrosqtheader.h"
#include "ui_qtnsanabrosmenudialog.h"
//---------------------------------------------------------------------------
QtNsanaBrosMenuDialog::QtNsanaBrosMenuDialog(QWidget *parent)
 : QDialog(parent),
   ui(new Ui::QtNsanaBrosMenuDialog)
{
  TRACE_FUNC();
  ui->setupUi(this);
}
//---------------------------------------------------------------------------
QtNsanaBrosMenuDialog::~QtNsanaBrosMenuDialog()
{
  delete ui;
}
//---------------------------------------------------------------------------
void QtNsanaBrosMenuDialog::changeEvent(QEvent *e)
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
void QtNsanaBrosMenuDialog::on_button_start_clicked()
{
  this->hide();

  QtNsanaBrosGameDialog d(m_dialog->GetOptionsDialog()->GetOptions());
  d.exec();
  this->show();
}
//---------------------------------------------------------------------------
void QtNsanaBrosMenuDialog::on_button_options_clicked()
{
  this->hide();
  //Input the present options
  QtNsanaBrosOptionsDialog d(m_dialog->GetOptionsDialog()->GetOptions());
  d.exec();
  //Retrieve and set the new options
  m_dialog->UseOptionsDialog()->SetOptions(
    *m_dialog->GetOptionsDialog()->GetOptions());
  this->show();
}
//---------------------------------------------------------------------------
void QtNsanaBrosMenuDialog::on_button_about_clicked()
{
  this->hide();
  QtAboutDialog d(NsanaBrosMenuDialog::GetAbout());
  d.exec();
  this->show();
}
//---------------------------------------------------------------------------
void QtNsanaBrosMenuDialog::on_button_quit_clicked()
{
  this->close();
}
//---------------------------------------------------------------------------
