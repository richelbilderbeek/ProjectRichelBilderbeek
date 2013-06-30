#ifndef QTPVDBRATECONCEPTTALLYMODEL_H
#define QTPVDBRATECONCEPTTALLYMODEL_H

#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif

#ifdef NOT_NOW_8765434567898765456789876578909876556789876

#include <boost/shared_ptr.hpp>
#include <QAbstractTableModel>
#include <pvdbfwd.h>

class QtPvdbRateConceptTallyModel : public QAbstractTableModel
{
public:
  QtPvdbRateConceptTallyModel(
    const boost::shared_ptr</* const */ pvdb::ConceptMap> concept_map,
    QObject *parent = 0);

  private:
  ///The raw data
  const boost::shared_ptr</* const */ pvdb::ConceptMap> m_concept_map;

  ///Must be defined from ABC
  int columnCount(const QModelIndex &parent = QModelIndex()) const;

  //Must be defined from ABC
  QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

  ///These flags are needed to allow editing
  Qt::ItemFlags flags(const QModelIndex &index) const;

  ///Redefined from ABC
  QVariant headerData(int section, Qt::Orientation orientation, int role) const;

  ///Redefined from ABC
  bool insertColumns(int row, int count, const QModelIndex &parent);

  ///Redefined from ABC
  bool insertRows(int row, int count, const QModelIndex &parent);

  ///Redefined from ABC
  bool removeColumns(int row, int count, const QModelIndex &parent);

  ///Redefined from ABC
  bool removeRows(int row, int count, const QModelIndex &parent);

  ///Must be defined from ABC
  int rowCount(const QModelIndex &parent = QModelIndex()) const;

  ///Needed for editable data
  bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);

  ///Redefined from ABC
  bool setHeaderData(int section, Qt::Orientation orientation, const QVariant &value, int role);
};
#endif

#endif // QTPVDBRATECONCEPTTALLYMODEL_H
