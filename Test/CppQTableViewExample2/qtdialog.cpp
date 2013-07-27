#include "qtdialog.h"

#include <cassert>

#include <QStandardItemModel>
#include "ui_qtdialog.h"

QtDialog::QtDialog(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::QtDialog)
{
  ui->setupUi(this);

  assert(!ui->table->model());
  ui->table->setModel(new QStandardItemModel(this));
  assert( ui->table->model());

  assert(dynamic_cast<QStandardItemModel*>(ui->table->model()));
  dynamic_cast<QStandardItemModel*>(ui->table->model())->setColumnCount(8);

  for (int i=0; i!=10; ++i) on_button_clicked();
}

QtDialog::~QtDialog()
{
  delete ui;
}

void QtDialog::on_button_clicked()
{
  const int n_cols = ui->table->model()->columnCount();
  QList<QStandardItem*> items;
  for (int i=0; i!=n_cols; ++i)
  {
    QStandardItem * const item = new QStandardItem;
    item->setCheckable(true);
    item->setEditable(false);
    item->setCheckState(Qt::Checked);
    items.push_back(item);

    ui->table->setColumnWidth(i,24);

  }
  assert(dynamic_cast<QStandardItemModel*>(ui->table->model()));
  dynamic_cast<QStandardItemModel*>(ui->table->model())->appendRow(items);

  ui->table->scrollToBottom();
  ui->table->setCurrentIndex(items[0]->index());
  ui->table->setRowHeight(items[0]->index().row(),24);
}
