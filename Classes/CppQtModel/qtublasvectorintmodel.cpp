//---------------------------------------------------------------------------
/*
QtModel, my classes derived from QAbstractTableModel
Copyright (C) 2013 Richel Bilderbeek

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
#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif

//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#include "qtublasvectorintmodel.h"

#include <cassert>
#include <numeric>
#include <boost/lexical_cast.hpp>
#include <boost/numeric/ublas/vector.hpp>
#include "matrix.h"

QtUblasVectorIntModel::QtUblasVectorIntModel(QObject *parent)
  : QAbstractTableModel(parent)
{

}

int QtUblasVectorIntModel::columnCount(const QModelIndex &) const
{
  return rowCount() > 0 ? 1 : 0;
}

QVariant QtUblasVectorIntModel::data(const QModelIndex &index, int role) const
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

Qt::ItemFlags QtUblasVectorIntModel::flags(const QModelIndex &) const
{
  return
    Qt::ItemIsSelectable
  | Qt::ItemIsEditable
  | Qt::ItemIsDragEnabled
  | Qt::ItemIsDropEnabled
  | Qt::ItemIsEnabled;
}

const std::string QtUblasVectorIntModel::GetVersion()
{
  return "1.0";
}

const std::vector<std::string> QtUblasVectorIntModel::GetVersionHistory()
{
  std::vector<std::string> v;
  v.push_back("2013-06-27: version 1.0: initial version");
  return v;
}

QVariant QtUblasVectorIntModel::headerData(int section, Qt::Orientation orientation, int role) const
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

bool QtUblasVectorIntModel::insertRows(int row, int count, const QModelIndex &parent)
{
  //Must be called before the real operation
  this->beginInsertRows(parent,row,row+count-1);

  //The real operation: resize the m_data
  assert(m_data.size() == m_header_vertical_text.size());

  const int new_size = m_data.size() + count;

  #ifdef USE_NAIVE_APPROACH_785768676876547
  //The drawback of this naive approach is that new cells are uninitialized
  m_data.resize(new_size);
  #else
  boost::numeric::ublas::vector<int> new_data(new_size,0);
  std::copy(m_data.begin(),m_data.end(),new_data.begin());
  m_data = new_data;
  #endif

  m_header_vertical_text.resize(new_size);

  assert(m_data.size() == m_header_vertical_text.size());

  //Must be called in the end
  this->endInsertRows();

  //It worked!
  return true;
}

bool QtUblasVectorIntModel::removeRows(int row, int count, const QModelIndex &parent)
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

int QtUblasVectorIntModel::rowCount(const QModelIndex &) const
{
  assert(m_data.size() == m_header_vertical_text.size());
  return boost::numeric_cast<int>(m_data.size());
}


bool QtUblasVectorIntModel::setData(const QModelIndex &index, const QVariant &value, int /* role */)
{
  const int row = index.row();

  #ifndef NDEBUG
  const int col = index.column();
  assert(row < boost::numeric_cast<int>(m_data.size()));
  assert(col == 0);
  #endif

  bool can_convert_to_int = false;
  m_data(row) = value.toInt(&can_convert_to_int);
  if (!can_convert_to_int)
  {
    //Might be a double, round it to the closest integer
    m_data(row) = boost::numeric_cast<int>(value.toDouble() + 0.5);
  }
  ///This line below is needed to let multiple views synchronize
  emit dataChanged(index,index);

  //Editing succeeded!
  return true;
}

bool QtUblasVectorIntModel::setHeaderData(int section, Qt::Orientation orientation, const QVariant &value, int /*role*/)
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

void QtUblasVectorIntModel::SetHeaderData(
  const std::string& horizontal_header_text, const std::vector<std::string>& vertical_header_text)
{
  if (m_header_horizontal_text != horizontal_header_text)
  {
    assert(this->columnCount() == (this->rowCount() == 0 ? 0 : 1));
    m_header_horizontal_text = horizontal_header_text;
    emit headerDataChanged(Qt::Horizontal,0,1);
  }

  if (m_header_vertical_text != vertical_header_text)
  {
    const int new_size = boost::numeric_cast<int>(vertical_header_text.size());
    const int cur_size = this->rowCount();
    if (cur_size < new_size)
    {
      //Insert some rows in the raw data
      this->insertRows(cur_size,new_size - cur_size,QModelIndex());

      //If you forget this line, the view displays a different number of rows than m_data has
      emit layoutChanged();
    }
    else if (cur_size > new_size)
    {
      //Remove some rows from the raw data
      this->removeRows(cur_size,cur_size - new_size,QModelIndex());

      //If you forget this line, the view displays a different number of rows than m_data has
      emit layoutChanged();
    }

    assert(this->rowCount() == boost::numeric_cast<int>(vertical_header_text.size()));

    m_header_vertical_text = vertical_header_text;

    emit headerDataChanged(Qt::Vertical,0,new_size);
  }

  assert(this->rowCount() == boost::numeric_cast<int>(this->m_data.size()));
  assert(this->rowCount() == boost::numeric_cast<int>(m_header_vertical_text.size()));
  assert(this->columnCount() == (this->rowCount() == 0 ? 0 : 1));
}

void QtUblasVectorIntModel::SetRawData(const boost::numeric::ublas::vector<int>& data)
{
  if (!Matrix::VectorsIntAreEqual(m_data,data))
  {
    const int new_size = boost::numeric_cast<int>(data.size());
    const int cur_size = this->rowCount();
    if (cur_size < new_size)
    {
      //Insert some rows in the raw data
      this->insertRows(cur_size,new_size - cur_size,QModelIndex());

      //If you forget this line, the view displays a different number of rows than m_data has
      emit layoutChanged();
    }
    else if (cur_size > new_size)
    {
      //Remove some rows from the raw data
      this->removeRows(cur_size,cur_size - new_size,QModelIndex());

      //If you forget this line, the view displays a different number of rows than m_data has
      emit layoutChanged();
    }

    assert(this->rowCount() == static_cast<int>(data.size()));

    m_data = data;

    emit dataChanged(QModelIndex(),QModelIndex());
  }

  assert(this->rowCount() == boost::numeric_cast<int>(this->m_data.size()));
  assert(this->rowCount() == boost::numeric_cast<int>(m_header_vertical_text.size()));
  assert(this->columnCount() == (this->rowCount() == 0 ? 0 : 1));
}
