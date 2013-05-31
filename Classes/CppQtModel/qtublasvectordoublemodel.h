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
#ifndef QTUBLASVECTORDOUBLEMODEL_H
#define QTUBLASVECTORDOUBLEMODEL_H

#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif

#include <string>
#include <vector>
#include <boost/numeric/ublas/vector.hpp>
#include <QAbstractTableModel>

struct QtUblasVectorDoubleModel: public QAbstractTableModel
{
  QtUblasVectorDoubleModel(QObject *parent = 0);

  ///Working with the raw data
  const boost::numeric::ublas::vector<double>& GetRawData() const { return m_data; }

  ///Obtain the version of this class
  static const std::string GetVersion();

  ///Obtain the version history of this class
  static const std::vector<std::string> GetVersionHistory();

  ///Working with the raw data
  void SetRawData(const boost::numeric::ublas::vector<double>& data);

  ///Set the header text
  void SetHeaderData(const std::string& title, const std::vector<std::string>& header_text);

  private:
  ///The raw data
  boost::numeric::ublas::vector<double> m_data;

  ///The horizontal header text (for the only one column)
  std::string m_header_horizontal_text;

  ///The vertical header text
  std::vector<std::string> m_header_vertical_text;

  ///Must be defined from ABC
  int columnCount(const QModelIndex &parent = QModelIndex()) const;

  ///Must be defined from ABC
  QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

  ///These flags are needed to allow editing
  Qt::ItemFlags flags(const QModelIndex &index) const;

  ///Redefined from ABC
  QVariant headerData(int section, Qt::Orientation orientation, int role) const;

  ///Redefined from ABC
  bool insertRows(int row, int count, const QModelIndex &parent);

  ///Redefined from ABC
  bool removeRows(int row, int count, const QModelIndex &parent);

  ///Must be defined from ABC
  int rowCount(const QModelIndex &parent = QModelIndex()) const;

  ///Needed for editable data
  bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);

  ///Redefined from ABC
  bool setHeaderData(int section, Qt::Orientation orientation, const QVariant &value, int role);

};

#endif // QTUBLASVECTORDOUBLEMODEL_H
