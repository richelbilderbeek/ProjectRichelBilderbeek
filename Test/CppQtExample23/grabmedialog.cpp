//---------------------------------------------------------------------------
#include "grabmedialog.h"
#include "ui_grabmedialog.h"
//---------------------------------------------------------------------------
GrabMeDialog::GrabMeDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GrabMeDialog)
{
  ui->setupUi(this);
}
//---------------------------------------------------------------------------
GrabMeDialog::~GrabMeDialog()
{
  delete ui;
}
//---------------------------------------------------------------------------
void GrabMeDialog::changeEvent(QEvent *e)
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
void GrabMeDialog::on_button_grab_clicked()
{
  ui->label_image->setPixmap(
      QPixmap::grabWindow(this->winId()));

  //Other way:
  //QImage copy = QPixmap::grabWindow(this->winId()).toImage();
  //copy.save("temp.png");
  //ui->label_image->setPixmap(QPixmap("temp.png"));
}
//---------------------------------------------------------------------------
