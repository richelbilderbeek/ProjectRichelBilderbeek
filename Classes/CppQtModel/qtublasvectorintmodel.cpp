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


#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "qtublasvectorintmodel.h"

#include <cassert>
#include <numeric>
#include <boost/lexical_cast.hpp>
#include <boost/numeric/ublas/vector.hpp>
#include "matrix.h"
#include "trace.h"

#pragma GCC diagnostic pop

ribi::QtUblasVectorIntModel::QtUblasVectorIntModel(QObject *parent)
  : QAbstractTableModel(parent),
    m_range_default{0},
    m_range_max{std::numeric_limits<int>::max()},
    m_range_min{std::numeric_limits<int>::min()}
{
  #ifndef NDEBUG
  Test();
  #endif

  assert(m_range_min < m_range_max);
  assert(this->IsValid());
}

int ribi::QtUblasVectorIntModel::columnCount(const QModelIndex &) const
{
  return rowCount() > 0 ? 1 : 0;
}

QVariant ribi::QtUblasVectorIntModel::data(const QModelIndex &index, int role) const
{
  assert(this->IsValid());

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
  if (m_data(row) < m_range_min || m_data(row) >= m_range_max)
  {
    TRACE("BREAK");
  }

  assert(m_data(row) >= m_range_min && "One of the purposes of this class it to ensure this");
  assert(m_data(row)  < m_range_max && "One of the purposes of this class it to ensure this");
  #endif

  //Convert to string, otherwise the number digits behind the comma
  //will be set to 2, e.g. 0.01
  const std::string s = boost::lexical_cast<std::string>(m_data(row));
  return QString(s.c_str());
}

Qt::ItemFlags ribi::QtUblasVectorIntModel::flags(const QModelIndex &) const
{
  return
    Qt::ItemIsSelectable
  | Qt::ItemIsEditable
  | Qt::ItemIsDragEnabled
  | Qt::ItemIsDropEnabled
  | Qt::ItemIsEnabled;
}

const std::string ribi::QtUblasVectorIntModel::GetVersion()
{
  return "1.2";
}

const std::vector<std::string> ribi::QtUblasVectorIntModel::GetVersionHistory()
{
  return {
    "2013-06-27: version 1.0: initial version",
    "2013-06-27: version 1.1: added setting a range",
    "2013-07-05: version 1.2: signal layoutChanged emitted correctly"
  };
}

QVariant ribi::QtUblasVectorIntModel::headerData(int section, Qt::Orientation orientation, int role) const
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

#ifndef NDEBUG
bool ribi::QtUblasVectorIntModel::IsValid() const
{
  if (m_range_min >= m_range_max)
  {
    TRACE("m_range_min bigger or equal than m_range_max");
    return false;
  }
  const std::size_t sz = m_data.size();
  for (std::size_t i=0; i!=sz; ++i)
  {
    const int x = m_data[i];
    if (x < m_range_min)
    {
      TRACE("x below minimum value");
      return false;
    }
    if (x >= m_range_max)
    {
      TRACE("x above maximum value");
      return false;
    }
  }
  return true;
}
#endif

bool ribi::QtUblasVectorIntModel::insertRows(int row, int count, const QModelIndex &parent)
{
  assert(this->IsValid());

  //Must be called before the real operation
  this->beginInsertRows(parent,row,row+count-1);

  //The real operation: resize the m_data
  assert(m_data.size() == m_header_vertical_text.size());

  const int new_size = m_data.size() + count;

  boost::numeric::ublas::vector<int> new_data(new_size,m_range_default);
  std::copy(m_data.begin(),m_data.end(),new_data.begin());
  m_data = new_data;

  m_header_vertical_text.resize(new_size);

  assert(m_data.size() == m_header_vertical_text.size());

  //Must be called in the end
  this->endInsertRows();

  assert(this->IsValid());

  //It worked!
  return true;
}

bool ribi::QtUblasVectorIntModel::removeRows(int row, int count, const QModelIndex &parent)
{
  assert(this->IsValid());

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

  assert(this->IsValid());

  //It worked!
  return true;
}

int ribi::QtUblasVectorIntModel::rowCount(const QModelIndex &) const
{
  assert(m_data.size() == m_header_vertical_text.size());
  return boost::numeric_cast<int>(m_data.size());
}


bool ribi::QtUblasVectorIntModel::setData(const QModelIndex &index, const QVariant &value, int /* role */)
{
  assert(this->IsValid());

  const int row = index.row();

  #ifndef NDEBUG
  const int col = index.column();
  assert(row < boost::numeric_cast<int>(m_data.size()));
  assert(col == 0);
  #endif


  bool can_convert = false;
  int new_value = value.toInt(&can_convert);
  if (!can_convert)
  {
    //Might be a double, round it to the closest integer
    new_value = boost::numeric_cast<int>(value.toFloat(&can_convert) + 0.5);
  }
  assert(m_range_min < m_range_max);
  if (can_convert && new_value >= m_range_min && new_value < m_range_max)
  {
    m_data(row) = new_value;

    assert(this->IsValid());

    ///This line below is needed to let multiple views synchronize
    emit dataChanged(index,index);

    assert(this->IsValid());

    //Editing succeeded!
    return true;
  }
  else
  {
    assert(this->IsValid());

    return false;
  }
}

bool ribi::QtUblasVectorIntModel::setHeaderData(int section, Qt::Orientation orientation, const QVariant &value, int /*role*/)
{
  assert(this->IsValid());

  if (orientation == Qt::Horizontal)
  {
    assert(section == 0);
    assert(m_header_horizontal_text != value.toString().toStdString());
    m_header_horizontal_text = value.toString().toStdString();
    ///This line below is needed to let multiple views synchronize
    emit headerDataChanged(orientation,section,section);

    assert(this->IsValid());
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

    assert(this->IsValid());
    //Editing succeeded!
    return true;
  }
}

void ribi::QtUblasVectorIntModel::SetHeaderData(
  const std::string& horizontal_header_text, const std::vector<std::string>& vertical_header_text)
{
  assert(this->IsValid());

  if (m_header_horizontal_text != horizontal_header_text)
  {
    emit layoutAboutToBeChanged();
    assert(this->columnCount() == (this->rowCount() == 0 ? 0 : 1));
    m_header_horizontal_text = horizontal_header_text;

    assert(this->IsValid());

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
  assert(this->IsValid());
}

void ribi::QtUblasVectorIntModel::SetRange(const int from, const int to, const int default_value)
{
  assert(this->IsValid());
  assert(from < to);
  assert(default_value < to);
  assert(default_value >= from);
  this->m_range_min = from;
  this->m_range_max = to;
  this->m_range_default = default_value;
  #ifndef NDEBUG
  {
    const std::size_t sz = m_data.size();
    for (std::size_t i=0; i!=sz; ++i)
    {
      const int x = m_data[i];
      assert(x >= m_range_min && x < m_range_max
        && "Before changing the range, the data in QtUblasVectorIntModel must be"
           " put in both the old and new range"); //Better a clear clumsy interface over a vague one
    }
  }
  assert(this->IsValid());
  #endif
}

void ribi::QtUblasVectorIntModel::SetRawData(const boost::numeric::ublas::vector<int>& data)
{
  //Check if all data is in range
  #ifndef NDEBUG
  assert(this->IsValid());
  {
    const std::size_t sz = data.size();
    for (std::size_t i=0; i!=sz; ++i)
    {
      const int x = data[i];
      assert(x >= m_range_min && x < m_range_max
        && "Supplied data to QtUblasVectorIntModel must be in range");
    }
  }
  #endif

  if (!Matrix::VectorsIntAreEqual(m_data,data))
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

    emit layoutChanged();

    const QModelIndex top_left = this->index(0,0);
    const QModelIndex bottom_right = this->index(m_data.size() - 1, 1);
    emit dataChanged(top_left,bottom_right);


    assert(this->IsValid());
  }

  assert(this->rowCount() == boost::numeric_cast<int>(this->m_data.size()));
  assert(this->rowCount() == boost::numeric_cast<int>(m_header_vertical_text.size()));
  assert(this->columnCount() == (this->rowCount() == 0 ? 0 : 1));
  assert(this->IsValid());
}

#ifndef NDEBUG
void ribi::QtUblasVectorIntModel::Test()
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  {
    QtUblasVectorIntModel d;
    d.SetRawData( Matrix::CreateVector( { 1,2,3 } ) );
    d.SetRange(1,4,1);
    assert(d.data(d.index(0,0)).toInt() == 1);
    d.setData(d.index(0,0),"0"); //Should not change the data
    assert(d.data(d.index(0,0)).toInt() == 1);
  }
}
#endif
