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
#ifndef QTUBLASVECTORINTMODEL_H
#define QTUBLASVECTORINTMODEL_H

#include <string>
#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/numeric/ublas/vector.hpp>
#include <QAbstractTableModel>
#pragma GCC diagnostic pop

namespace ribi {

struct QtUblasVectorIntModel: public QAbstractTableModel
{
  ///Create a QtUblasVectorIntModel
  ///with range
  ///- from = std::numeric_limits<int>::min()
  ///- to   = std::numeric_limits<int>::max()
  explicit QtUblasVectorIntModel(QObject *parent = 0) noexcept;

  ///Working with the raw data
  const boost::numeric::ublas::vector<int>& GetRawData() const  noexcept{ return m_data; }

  ///Obtain the version of this class
  static std::string GetVersion() noexcept;

  ///Obtain the version history of this class
  static std::vector<std::string> GetVersionHistory() noexcept;

  ///Set the range the values must remain in
  ///The range includes from, excludes to
  void SetRange(const int from, const int to, const int default_value);

  ///Working with the raw data
  void SetRawData(const boost::numeric::ublas::vector<int>& data);

  ///Set the header text
  void SetHeaderData(const std::string& title, const std::vector<std::string>& header_text);

  private:
  ///The raw data
  boost::numeric::ublas::vector<int> m_data;

  ///The horizontal header text (for the only one column)
  std::string m_header_horizontal_text;

  ///The vertical header text
  std::vector<std::string> m_header_vertical_text;

  ///The value set for default
  int m_range_default;

  ///The maximum value all values must have
  int m_range_max;

  ///The minimum value all values must have
  int m_range_min;

  ///Must be defined from ABC
  int columnCount(const QModelIndex &parent = QModelIndex()) const noexcept;

  ///Must be defined from ABC
  QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

  ///These flags are needed to allow editing
  Qt::ItemFlags flags(const QModelIndex &index) const noexcept;

  ///Redefined from ABC
  QVariant headerData(int section, Qt::Orientation orientation, int role) const;

  ///Redefined from ABC
  bool insertRows(int row, int count, const QModelIndex &parent);

  ///Check if the class is in a valid state
  #ifndef NDEBUG
  bool IsValid() const noexcept;
  #endif

  ///Redefined from ABC
  bool removeRows(int row, int count, const QModelIndex &parent);

  ///Must be defined from ABC
  int rowCount(const QModelIndex &parent = QModelIndex()) const noexcept;

  ///Needed for editable data
  bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);

  ///Redefined from ABC
  bool setHeaderData(int section, Qt::Orientation orientation, const QVariant &value, int role);

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif

};

} //~namespace ribi

#endif // QTUBLASVECTORINTMODEL_H
