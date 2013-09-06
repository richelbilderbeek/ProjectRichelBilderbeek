#ifndef QTPVDBCENTERNODEITEM_H
#define QTPVDBCENTERNODEITEM_H

#include <boost/shared_ptr.hpp>
#include "qtpvdbnodeitem.h"

#include "pvdbfwd.h"

namespace ribi {

namespace pvdb {

///The center node
struct QtPvdbCenterNodeItem : public QtPvdbNodeItem
{
  ///Node cannot be const, as it contains a Concept the user might want to edit
  ///(that is, when a sub-concept map is created from a concept map and the
  ///focal node needs to be rated)
  ///concept_item is the display Strategy
  explicit QtPvdbCenterNodeItem(
    const boost::shared_ptr<ribi::pvdb::Node> node);

  private:
  static const boost::shared_ptr<QtPvdbConceptItem> CreateConceptItem(const boost::shared_ptr<ribi::pvdb::Node> node);
};

} //~namespace pvdb

} //~namespace ribi

#endif // QTPVDBCENTERNODEITEM_H
