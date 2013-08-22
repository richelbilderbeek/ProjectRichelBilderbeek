#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
  ui->setupUi(this);
}

Dialog::~Dialog()
{
  delete ui;
}

void Dialog::changeEvent(QEvent *e)
{
  QDialog::changeEvent(e);
  switch (e->type())
  {
  case QEvent::LanguageChange:
    ui->retranslateUi(this);
    break;
  default:
    break;
  }
}

//Added
void Dialog::resizeEvent(QResizeEvent*)
{
  static int n_times = 0;
  QString s; s = s.number(n_times);
  ui->label->setText("Resized " + s + " times");
  ++n_times;
}
