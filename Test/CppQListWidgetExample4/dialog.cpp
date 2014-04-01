#include "dialog.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <QScrollBar>
#include <QTimer>

#include "ui_dialog.h"
#pragma GCC diagnostic pop

Dialog::Dialog(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::Dialog)
{
  ui->setupUi(this);
  ui->listWidget->setAlternatingRowColors(true);
  ui->listWidget->setWordWrap(true);
}

Dialog::~Dialog()
{
  delete ui;
}

void Dialog::on_pushButton_clicked()
{
  QListWidgetItem * const item = new QListWidgetItem;
  item->setText("0123456789 0123456789 0123456789 0123456789 0123456789 0123456789 0123456789 0123456789 0123456789 0123456789 0123456789 0123456789");
  ui->listWidget->addItem(item);
}

