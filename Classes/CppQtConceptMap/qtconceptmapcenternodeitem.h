#ifndef QTCONCEPTMAPCENTERNODEITEM_H
#define QTCONCEPTMAPCENTERNODEITEM_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <boost/shared_ptr.hpp>
#include "qtconceptmapnodeitem.h"

#include "conceptmapfwd.h"
#pragma GCC diagnostic pop

namespace ribi {
namespace cmap {

///The center node
struct QtConceptMapCenterNodeItem : public QtConceptMapNodeItem
{
  ///Node cannot be const, as it contains a Concept the user might want to edit
  ///(that is, when a sub-concept map is created from a concept map and the
  ///focal node needs to be rated)
  ///concept_item is the display Strategy
  explicit QtConceptMapCenterNodeItem(
    const boost::shared_ptr<ribi::cmap::Node> node);

  private:
  static const boost::shared_ptr<QtConceptItem> CreateConceptItem(const boost::shared_ptr<ribi::cmap::Node> node);
};

} //~namespace cmap
} //~namespace ribi

#endif // QTCONCEPTMAPCENTERNODEITEM_H
