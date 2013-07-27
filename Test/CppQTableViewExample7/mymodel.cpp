#include "mymodel.h"

#include <cassert>
#include <boost/lexical_cast.hpp>

MyModel::MyModel(QObject *parent)
  : QAbstractTableModel(parent)
{

}

QVariant MyModel::data(const QModelIndex &index, int role) const
{
  //Removing this line will cause checkboxes to appear
  if (role != Qt::EditRole &&  role != Qt::DisplayRole) return QVariant();

  assert(index.isValid());

  return m_data.Get(index.row(),index.column());
}

Qt::ItemFlags MyModel::flags(const QModelIndex &) const
{
  return
    Qt::ItemIsSelectable
  | Qt::ItemIsEditable
  | Qt::ItemIsDragEnabled
  | Qt::ItemIsDropEnabled
  | Qt::ItemIsEnabled;

}

int MyModel::rowCount(const QModelIndex &) const
{
  return m_data.GetRowCount();
}

int MyModel::columnCount(const QModelIndex &) const
{
  return m_data.GetColCount();
}

bool MyModel::setData(const QModelIndex &index, const QVariant &value, int /* role */)
{
  m_data.Set(index.row(),index.column(),value.toDouble());
  ///This line below is needed to let the two views synchronize
  emit dataChanged(index,index);

  //Editing succeeded!
  return true;
}
