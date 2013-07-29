#ifndef MYMODEL_H
#define MYMODEL_H

#include <QAbstractTableModel>
#include <boost/shared_ptr.hpp>

struct MyData;

struct MyModel : public QAbstractTableModel
{
  MyModel(const boost::shared_ptr<MyData> data, QObject *parent = 0);

  int columnCount(const QModelIndex &parent) const;
  QVariant data(const QModelIndex &index, int role) const;
  Qt::ItemFlags flags(const QModelIndex &index) const;
  QVariant headerData(int section, Qt::Orientation orientation, int role) const;

  int rowCount(const QModelIndex &parent) const;
  bool setData(const QModelIndex &index, const QVariant &value, int role);

  private:
  const boost::shared_ptr<MyData> m_data;
};

#endif // MYMODEL_H
