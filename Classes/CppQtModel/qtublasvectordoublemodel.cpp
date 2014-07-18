//---------------------------------------------------------------------------
/*
QtModel, my classes derived from QAbstractTableModel
Copyright (C) 2013-2014 Richel Bilderbeek

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program. If not, see <http://www.gnu.org/licenses/>.
*/
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/CppQtModel.htm
//---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "qtublasvectordoublemodel.h"

#include <cassert>
#include <boost/lexical_cast.hpp>
#include "matrix.h"
#include "trace.h"

#pragma GCC diagnostic pop

ribi::QtUblasVectorDoubleModel::QtUblasVectorDoubleModel(QObject *parent) noexcept
  : QAbstractTableModel(parent),
    m_data{},
    m_header_horizontal_text{},
    m_header_vertical_text{}
{
  #ifndef NDEBUG
  Test();
  #endif
}

int ribi::QtUblasVectorDoubleModel::columnCount(const QModelIndex &) const noexcept
{
  return rowCount() > 0 ? 1 : 0;
}

QVariant ribi::QtUblasVectorDoubleModel::data(const QModelIndex &index, int role) const
{
  //Removing this line will cause checkboxes to appear
  if (role != Qt::EditRole && role != Qt::DisplayRole) return QVariant();

  assert(index.isValid());

  const int row = index.row();

  #ifndef NDEBUG
  const int col = index.column();
  assert(row >= 0);
  assert(row < this->rowCount());
  assert(row < boost::numeric_cast<int>(m_data.size()));
  assert(col == 0);
  #endif

  #ifdef RETURN_DOUBLE_723465978463059835
  return m_data(row);
  #else
  //Convert to string, otherwise the number digits behind the comma
  //will be set to 2, e.g. 0.01
  const std::string s = boost::lexical_cast<std::string>(m_data(row));
  return QString(s.c_str());
  #endif

}

Qt::ItemFlags ribi::QtUblasVectorDoubleModel::flags(const QModelIndex &) const noexcept
{
  return
    Qt::ItemIsSelectable
  | Qt::ItemIsEditable
  | Qt::ItemIsDragEnabled
  | Qt::ItemIsDropEnabled
  | Qt::ItemIsEnabled;
}

std::string ribi::QtUblasVectorDoubleModel::GetVersion() noexcept
{
  return "1.5";
}

std::vector<std::string> ribi::QtUblasVectorDoubleModel::GetVersionHistory() noexcept
{
  return {
    "2013-05-15: version 1.0: initial version",
    "2013-05-21: version 1.1: added rows are initialized with zeroes",
    "2013-05-23: version 1.2: allow an infine amount of digits behind the comma",
    "2013-05-28: version 1.3: allow columnCount to be zero, if rowCount is zero",
    "2013-06-27: version 1.4: added self-test",
    "2013-07-05: version 1.5: signal layoutChanged emitted correctly"
  };
}

QVariant ribi::QtUblasVectorDoubleModel::headerData(int section, Qt::Orientation orientation, int role) const
{
  //Removing this line will cause checkboxes to appear
  if (role != Qt::EditRole && role != Qt::DisplayRole) return QVariant();

  if (orientation == Qt::Horizontal)
  {
    assert(section == 0);
    return QString( m_header_horizontal_text.c_str() );
  }
  else
  {
    assert(orientation == Qt::Vertical);
    //No idea why this happens
    if (!(section < boost::numeric_cast<int>(m_header_vertical_text.size())))
    {
      return QVariant();
    }

    assert(section < boost::numeric_cast<int>(m_header_vertical_text.size()));
    return QString( m_header_vertical_text[section].c_str() );
  }
}

bool ribi::QtUblasVectorDoubleModel::insertRows(int row, int count, const QModelIndex &parent)
{
  //Must be called before the real operation
  this->beginInsertRows(parent,row,row+count-1);

  //The real operation: resize the m_data
  assert(m_data.size() == m_header_vertical_text.size());

  const int new_size = m_data.size() + count;

  boost::numeric::ublas::vector<double> new_data = boost::numeric::ublas::zero_vector<double>(new_size);
  std::copy(m_data.begin(),m_data.end(),new_data.begin());
  m_data = new_data;

  m_header_vertical_text.resize(new_size);

  assert(m_data.size() == m_header_vertical_text.size());

  //Must be called in the end
  this->endInsertRows();

  //It worked!
  return true;
}

bool ribi::QtUblasVectorDoubleModel::removeRows(int row, int count, const QModelIndex &parent)
{
  //Must be called before the real operation
  this->beginRemoveRows(parent,row,row+count-1);

  //The real operation: resize the m_data
  assert(m_data.size() == m_header_vertical_text.size());

  const int new_size = m_data.size() - count;
  m_data.resize(new_size);
  m_header_vertical_text.resize(new_size);

  assert(m_data.size() == m_header_vertical_text.size());

  //Must be called in the end
  this->endRemoveRows();

  //It worked!
  return true;
}

int ribi::QtUblasVectorDoubleModel::rowCount(const QModelIndex &) const noexcept
{
  assert(m_data.size() == m_header_vertical_text.size());
  return boost::numeric_cast<int>(m_data.size());
}


bool ribi::QtUblasVectorDoubleModel::setData(const QModelIndex &index, const QVariant &value, int /* role */)
{
  const int row = index.row();

  #ifndef NDEBUG
  const int col = index.column();
  assert(row < boost::numeric_cast<int>(m_data.size()));
  assert(col == 0);
  #endif

  m_data(row) = value.toDouble();

  ///This line below is needed to let multiple views synchronize
  emit dataChanged(index,index);

  //Editing succeeded!
  return true;
}

bool ribi::QtUblasVectorDoubleModel::setHeaderData(int section, Qt::Orientation orientation, const QVariant &value, int /*role*/)
{
  if (orientation == Qt::Horizontal)
  {
    assert(section == 0);
    assert(m_header_horizontal_text != value.toString().toStdString());
    m_header_horizontal_text = value.toString().toStdString();
    ///This line below is needed to let multiple views synchronize
    emit headerDataChanged(orientation,section,section);
    //Editing succeeded!
    return true;
  }
  else
  {
    assert(orientation == Qt::Vertical);
    assert(section < boost::numeric_cast<int>(m_header_vertical_text.size()));
    assert(m_header_vertical_text[section] != value.toString().toStdString());
    m_header_vertical_text[section] = value.toString().toStdString();
    ///This line below is needed to let multiple views synchronize
    emit headerDataChanged(orientation,section,section);
    //Editing succeeded!
    return true;
  }
}

void ribi::QtUblasVectorDoubleModel::SetHeaderData(
  const std::string& horizontal_header_text, const std::vector<std::string>& vertical_header_text)
{
  if (m_header_horizontal_text != horizontal_header_text)
  {
    emit layoutAboutToBeChanged();
    assert(this->columnCount() == (this->rowCount() == 0 ? 0 : 1));
    m_header_horizontal_text = horizontal_header_text;
    emit layoutChanged();
    emit headerDataChanged(Qt::Horizontal,0,1);
  }

  if (m_header_vertical_text != vertical_header_text)
  {
    emit layoutAboutToBeChanged();
    const int new_size = boost::numeric_cast<int>(vertical_header_text.size());
    const int cur_size = this->rowCount();

    if (cur_size < new_size)
    {
      this->insertRows(cur_size,new_size - cur_size,QModelIndex());
    }
    else if (cur_size > new_size)
    {
      this->removeRows(cur_size,cur_size - new_size,QModelIndex());
    }

    //Set the data before emitting signals, as the response to that signal
    //will be dependent on that data
    m_header_vertical_text = vertical_header_text;

    assert(this->rowCount() == boost::numeric_cast<int>(vertical_header_text.size())
      && "So emit layoutChange can work on the newest layout");

    emit layoutChanged();
    emit headerDataChanged(Qt::Vertical,0,new_size);
  }

  assert(this->rowCount() == boost::numeric_cast<int>(this->m_data.size()));
  assert(this->rowCount() == boost::numeric_cast<int>(m_header_vertical_text.size()));
  assert(this->columnCount() == (this->rowCount() == 0 ? 0 : 1));
}

void ribi::QtUblasVectorDoubleModel::SetRawData(const boost::numeric::ublas::vector<double>& data)
{
  if (!Matrix::VectorsDoubleAreEqual(m_data,data))
  {
    const int new_size = boost::numeric_cast<int>(data.size());
    const int cur_size = this->rowCount();
    if (cur_size < new_size)
    {
      this->insertRows(cur_size,new_size - cur_size,QModelIndex());
    }
    else if (cur_size > new_size)
    {
      this->removeRows(cur_size,cur_size - new_size,QModelIndex());
    }
    //Set the data before emitting signals, as the response to that signal
    //will be dependent on that data
    m_data = data;

    assert(this->rowCount() == boost::numeric_cast<int>(data.size())
      && "So emit layoutChange can work on the newest layout");

    //If you forget this line, the view displays a different number of rows than m_data has
    emit layoutChanged();

    //emit dataChanged(QModelIndex(),QModelIndex());
    const QModelIndex top_left = this->index(0,0);
    const QModelIndex bottom_right = this->index(m_data.size() - 1, 0);
    emit dataChanged(top_left,bottom_right);
  }

  assert(this->rowCount() == boost::numeric_cast<int>(this->m_data.size()));
  assert(this->rowCount() == boost::numeric_cast<int>(m_header_vertical_text.size()));
  assert(this->columnCount() == (this->rowCount() == 0 ? 0 : 1));
}

#ifndef NDEBUG
void ribi::QtUblasVectorDoubleModel::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Started ribi::QtUblasVectorDoubleModel::Test");
  {
    QtUblasVectorDoubleModel model;
    assert(model.rowCount()    == 0);
    assert(model.columnCount() == 0);
    model.insertRow(1);
    assert(model.rowCount()    == 1);
    assert(model.columnCount() == 1);
    model.removeRow(1);
    assert(model.rowCount()    == 0);
    assert(model.columnCount() == 0);
  }
  TRACE("Finished ribi::QtUblasVectorDoubleModel::Test successfully");
}
#endif
