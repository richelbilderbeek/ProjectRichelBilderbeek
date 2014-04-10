#include "grabmedialog.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "ui_grabmedialog.h"
#pragma GCC diagnostic pop

GrabMeDialog::GrabMeDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GrabMeDialog)
{
  ui->setupUi(this);
}

GrabMeDialog::~GrabMeDialog()
{
  delete ui;
}

void GrabMeDialog::on_button_grab_clicked()
{
  ui->label_image->setPixmap(
      QPixmap::grabWindow(this->winId()));

  //Other way:
  //QImage copy = QPixmap::grabWindow(this->winId()).toImage();
  //copy.save("temp.png");
  //ui->label_image->setPixmap(QPixmap("temp.png"));
}

