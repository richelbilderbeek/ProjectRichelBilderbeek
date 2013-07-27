#include "qtdialog.h"

#include <cassert>

#include "mymodel.h"
#include "ui_qtdialog.h"

QtDialog::QtDialog(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::QtDialog)
{
  ui->setupUi(this);

  MyModel * const model = new MyModel(this);
  assert(!ui->table_1->model());
  assert(!ui->table_2->model());
  ui->table_1->setModel(model);
  ui->table_2->setModel(model);
  assert(ui->table_1->model());
  assert(ui->table_2->model());


  ui->table_1->setColumnWidth(0, 24);
  ui->table_2->setColumnWidth(0, 24);
  ui->table_1->setColumnWidth(1, 24);
  ui->table_2->setColumnWidth(1, 24);
  ui->table_1->setColumnWidth(2,175);
  ui->table_2->setColumnWidth(2,175);
}

QtDialog::~QtDialog()
{
  delete ui;
}

void QtDialog::on_button_clicked()
{
  QTableView * const view = ui->table_1->hasFocus() ? ui->table_1 : ui->table_2;
  dynamic_cast<MyModel*>(view->model())->AddRow(); //Other view will synchronize
  view->scrollToBottom();
  const int n_rows = view->model()->rowCount();
  view->setCurrentIndex(view->model()->index(n_rows-1,2));
}
