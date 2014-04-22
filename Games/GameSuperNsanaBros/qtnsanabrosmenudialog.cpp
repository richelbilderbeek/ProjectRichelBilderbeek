#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"

#include "nsanabrosqtheader.h"
#include "ui_qtnsanabrosmenudialog.h"
#pragma GCC diagnostic pop

ribi::QtNsanaBrosMenuDialog::QtNsanaBrosMenuDialog(QWidget *parent)
 : QDialog(parent),
   ui(new Ui::QtNsanaBrosMenuDialog),
   m_dialog{}
{
  TRACE_FUNC();
  ui->setupUi(this);
}

ribi::QtNsanaBrosMenuDialog::~QtNsanaBrosMenuDialog()
{
  delete ui;
}


void ribi::QtNsanaBrosMenuDialog::on_button_start_clicked()
{
  this->hide();

  QtNsanaBrosGameDialog d(m_dialog->GetOptionsDialog()->GetOptions().get());
  d.exec();
  this->show();
}

void ribi::QtNsanaBrosMenuDialog::on_button_options_clicked()
{
  this->hide();
  //Input the present options
  QtNsanaBrosOptionsDialog d(m_dialog->GetOptionsDialog()->GetOptions().get());
  d.exec();
  //Retrieve and set the new options
  //m_dialog->UseOptionsDialog()->SetOptions(
  //  *m_dialog->GetOptionsDialog()->GetOptions());
  this->show();
}

void ribi::QtNsanaBrosMenuDialog::on_button_about_clicked()
{
  this->hide();
  QtAboutDialog d(NsanaBrosMenuDialog().GetAbout());
  d.exec();
  this->show();
}

void ribi::QtNsanaBrosMenuDialog::on_button_quit_clicked()
{
  this->close();
}

