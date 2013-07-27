#include "qtdialog.h"

#include <cassert>

#include "mymodel.h"
#include "ui_qtdialog.h"

QtDialog::QtDialog(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::QtDialog)
{
  ui->setupUi(this);

  assert(!ui->table->model());
  ui->table->setModel(new MyModel(this));
  assert( ui->table->model());


  ui->table->setColumnWidth(0, 24);
  ui->table->setColumnWidth(1, 24);
  ui->table->setColumnWidth(2,175);
}

QtDialog::~QtDialog()
{
  delete ui;
}

void QtDialog::on_button_clicked()
{
  dynamic_cast<MyModel*>(ui->table->model())->AddRow();
  ui->table->scrollToBottom();
  const int n_rows = ui->table->model()->rowCount();
  ui->table->setCurrentIndex(ui->table->model()->index(n_rows-1,2));
}
