#include "qtdialog.h"

#include <cassert>

#include <QHeaderView>
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
  dynamic_cast<QStandardItemModel*>(ui->table->model())->setColumnCount(3);
  dynamic_cast<QStandardItemModel*>(ui->table->model())->setHeaderData(0,Qt::Horizontal,"Y");
  dynamic_cast<QStandardItemModel*>(ui->table->model())->setHeaderData(1,Qt::Horizontal,"N");
  dynamic_cast<QStandardItemModel*>(ui->table->model())->setHeaderData(2,Qt::Horizontal,"Question");

  ui->table->setColumnWidth(0, 24);
  ui->table->setColumnWidth(1, 24);
  ui->table->setColumnWidth(2,175);

  for (int i=0; i!=10; ++i) on_button_clicked();
}

QtDialog::~QtDialog()
{
  delete ui;
}

void QtDialog::on_button_clicked()
{
  QList<QStandardItem*> items;
  //Add 'yes' checkbox
  {
    QStandardItem * const item = new QStandardItem;
    item->setCheckable(true);
    item->setEditable(false);
    item->setCheckState(Qt::Unchecked);
    items.push_back(item);
  }
  //Add 'no' checkbox
  {
    QStandardItem * const item = new QStandardItem;
    item->setCheckable(true);
    item->setEditable(false);
    item->setCheckState(Qt::Unchecked);
    items.push_back(item);
  }
  //Add 'yes' checkbox
  {
    QStandardItem * const item = new QStandardItem;
    item->setEditable(true);
    item->setText("Is this a useful question?");
    items.push_back(item);
  }

  assert(dynamic_cast<QStandardItemModel*>(ui->table->model()));
  assert(dynamic_cast<QStandardItemModel*>(ui->table->model())->columnCount() == items.size());

  dynamic_cast<QStandardItemModel*>(ui->table->model())->appendRow(items);

  ui->table->scrollToBottom();
  ui->table->setCurrentIndex(items[2]->index());
  ui->table->setRowHeight(items[0]->index().row(),24);
}
