#ifndef MYMODEL_H
#define MYMODEL_H

#include <QAbstractTableModel>
#include "mydata.h"

//I did not use QStandardItemModel because I did not work with QStandardItem

struct MyModel : public QAbstractTableModel
{
  MyModel(QObject *parent = 0);

  //Must be defined from ABC
  QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

  ///These flags are needed to allow editing
  Qt::ItemFlags flags(const QModelIndex &index) const;

  ///Working with the raw data
  MyData& GetData() { return m_data; }
  const MyData& GetData() const { return m_data; }

  ///Needed for editable data
  bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);

  ///Must be defined from ABC
  int rowCount(const QModelIndex &parent = QModelIndex()) const;

  ///Must be defined from ABC
  int columnCount(const QModelIndex &parent = QModelIndex()) const;

  private:
  ///The raw data
  MyData m_data;
};

#endif // MYMODEL_H
