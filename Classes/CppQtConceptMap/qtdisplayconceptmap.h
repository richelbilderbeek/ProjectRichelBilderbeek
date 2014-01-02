#ifndef QTCONCEPTMAPDISPLAYCONCEPTMAP_H
#define QTCONCEPTMAPDISPLAYCONCEPTMAP_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <boost/shared_ptr.hpp>

#include "qtconceptmap.h"

#include "conceptmapfwd.h"

#include "conceptmapnode.h"
#include "conceptmapedge.h"
#pragma GCC diagnostic pop

namespace ribi {
namespace cmap {

///QtConceptMap for displayal of a ConceptMap in a read-only fashion
struct QtDisplayConceptMap : public QtConceptMap
{
  typedef QtDisplayConceptMap This_t;

  QtDisplayConceptMap(
    const boost::shared_ptr<ConceptMap> concept_map = boost::shared_ptr<ConceptMap>(),
    QWidget* parent = 0);
  ~QtDisplayConceptMap() noexcept {}

  #ifndef NDEBUG
  ///Creates a new derived class
  ///A simpler alternative to Clone (see above)
  std::unique_ptr<QtConceptMap> CreateNewDerived() const;

  ///Do something random
  void DoRandomStuff();
  #endif

private:
  ///Adds an Edge and connects (some of) its signals to slots present in the derived classes
  ///Edge cannot be const, as it has a Concept on it that the user might want to edit
  ///In this derived class, I promise not to change the Edge
  void AddEdge(const boost::shared_ptr<ribi::cmap::Edge> edge);

  ///Adds a node and connects (some of) its signals to slots present in the derived classes
  ///In this derived class, I promise not to change the Node
  QtNode * AddNode(const boost::shared_ptr<ribi::cmap::Node> node);

  void CleanMe();

  ///The way a QtConceptMap displays its Nodes (both as nodes and on edges)
  const boost::shared_ptr<QtItemDisplayStrategy> GetDisplayStrategy(
    const boost::shared_ptr<Concept> concept) const noexcept;

  ///Called whenever a concept is clicked or moved
  ///If item is nullptr, the last item might be deleted
  ///Use QGraphicsItem* due to QtKeyboardFriendlyGraphicsView working on QGraphicsItems
  ///Is implemented by OnItemUpdateRequestImpl
  ///QGraphicsItem cannot be const: some items request for an update via-via
  void OnItemRequestUpdateImpl(const QGraphicsItem* const);

  #ifndef NDEBUG
  ///Test this class
  static void Test() {}
  #endif
};

} //~namespace cmap
} //~namespace ribi

#endif // QTCONCEPTMAPDISPLAYCONCEPTMAP_H
