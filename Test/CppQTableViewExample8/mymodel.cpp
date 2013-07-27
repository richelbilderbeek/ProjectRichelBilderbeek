#include "mymodel.h"

#include <cassert>

MyModel::MyModel(QObject *parent)
  : QStandardItemModel(parent)
{
  setColumnCount(3);
  setHeaderData(0,Qt::Horizontal,"Y");
  setHeaderData(1,Qt::Horizontal,"N");
  setHeaderData(2,Qt::Horizontal,"Question");
  for (int i=0; i!=5; ++i) AddRow();
}

void MyModel::AddRow()
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

  assert(columnCount() == items.size());
  appendRow(items);
  emit layoutChanged();
}
