#ifndef QTCONCEPTMAPCENTERNODE_H
#define QTCONCEPTMAPCENTERNODE_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <boost/shared_ptr.hpp>
#include "qtconceptmapnode.h"

#include "conceptmapfwd.h"
#pragma GCC diagnostic pop

namespace ribi {
namespace cmap {

///The center node
struct QtCenterNode : public QtNode
{
  ///Node cannot be const, as it contains a Concept the user might want to edit
  ///(that is, when a sub-concept map is created from a concept map and the
  ///focal node needs to be rated)
  ///concept_item is the display Strategy
  explicit QtCenterNode(const boost::shared_ptr<CenterNode> node);

  private:
  static const boost::shared_ptr<QtItemDisplayStrategy> CreateConceptItem(const boost::shared_ptr<ribi::cmap::Node> node);
};

} //~namespace cmap
} //~namespace ribi

#endif // QTCONCEPTMAPCENTERNODE_H
