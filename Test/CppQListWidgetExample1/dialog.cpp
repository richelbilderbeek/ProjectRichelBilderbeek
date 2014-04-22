#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::Dialog)
{
  ui->setupUi(this);
  ui->listWidget->setAlternatingRowColors(true);
}

Dialog::~Dialog()
{
  delete ui;
}

void Dialog::on_pushButton_clicked()
{
  QListWidgetItem * const item = new QListWidgetItem;
  item->setText(ui->lineEdit->text());
  ui->listWidget->addItem(item);
  ui->lineEdit->clear();
}
