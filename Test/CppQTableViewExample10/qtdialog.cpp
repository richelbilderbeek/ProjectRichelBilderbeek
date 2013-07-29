#include "qtdialog.h"

#include <cassert>

#include "mydata.h"
#include "mymodel.h"
#include "ui_qtdialog.h"

QtDialog::QtDialog(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::QtDialog),
  m_data(new MyData)
{
  ui->setupUi(this);

  MyModel * const model = new MyModel(m_data,this);
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
