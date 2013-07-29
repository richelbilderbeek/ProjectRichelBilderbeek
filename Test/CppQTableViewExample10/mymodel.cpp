#include "mymodel.h"

#include <cassert>
#include <QStandardItem>
#include "mydata.h"

MyModel::MyModel(const boost::shared_ptr<MyData> data, QObject *parent)
  : QAbstractTableModel(parent),
    m_data(data)
{

}

int MyModel::columnCount(const QModelIndex &) const
{
  return 3;
}

QVariant MyModel::data(const QModelIndex &index, int role) const
{
  switch (index.column())
  {
    case 0:
      if (role == Qt::DisplayRole || role == Qt::CheckStateRole)
        return m_data->GetYes(index.row()) ? Qt::Checked : Qt::Unchecked;
    case 1:
      if (role == Qt::DisplayRole || role == Qt::CheckStateRole)
        return m_data->GetNo(index.row()) ? Qt::Checked : Qt::Unchecked;
    case 2:
      if (role == Qt::DisplayRole || role == Qt::EditRole)
        return m_data->GetQuestion(index.row()).c_str();
  }
  return QVariant();
}

Qt::ItemFlags MyModel::flags(const QModelIndex &index) const
{
  switch (index.column())
  {
    case 0:
    case 1:
      return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsUserCheckable;
    case 2:
      return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;
  }
  return Qt::NoItemFlags;
}

QVariant MyModel::headerData(int section, Qt::Orientation orientation, int /*role*/) const
{
  if (orientation == Qt::Horizontal)
  {
    switch (section)
    {
      case 0: return "Y";
      case 1: return "N";
      case 2: return "Question";
      default: assert(!"Should not get here");
    }
  }
  else
  {
    return section;
  }
}

int MyModel::rowCount(const QModelIndex &) const
{
  return m_data->GetRowCount();
}

bool MyModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
  switch (index.column())
  {
    case 0:
      if (role == Qt::CheckStateRole)
        m_data->SetYes(index.row(),value.toInt() == Qt::Checked);
    break;
    case 1:
      if (role == Qt::CheckStateRole)
        m_data->SetNo(index.row(),value.toInt() == Qt::Checked);
    break;
    case 2:
      if (role == Qt::EditRole)
        m_data->SetQuestion(index.row(),value.toString().toStdString());
    break;
  }
  emit dataChanged(index,index);
  return true;
}
