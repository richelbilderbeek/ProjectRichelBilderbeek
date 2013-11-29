#ifndef QTPVDBCONCEPTMAPDISPLAYWIDGET_H
#define QTPVDBCONCEPTMAPDISPLAYWIDGET_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <boost/shared_ptr.hpp>

#include "qtconceptmapwidget.h"

#include "conceptmapfwd.h"

#include "conceptmapnode.h"
#include "conceptmapedge.h"
#pragma GCC diagnostic pop

namespace ribi {
namespace cmap {

///QtConceptMapWidget for creation and editing of a ConceptMap
struct QtConceptMapDisplayWidget : public QtConceptMapWidget
{
  typedef QtConceptMapDisplayWidget This_t;

  QtConceptMapDisplayWidget(
    const boost::shared_ptr<ribi::cmap::ConceptMap> concept_map,
    QWidget* parent = 0);
  ~QtConceptMapDisplayWidget() noexcept {}

  #ifndef NDEBUG
  ///Creates a new derived class
  ///A simpler alternative to Clone (see above)
  std::unique_ptr<QtConceptMapWidget> CreateNewDerived() const;

  ///Do something random
  void DoRandomStuff();
  #endif

private:
  ///Adds an Edge and connects (some of) its signals to slots present in the derived classes
  ///Edge cannot be const, as it has a Concept on it that the user might want to edit
  void AddEdge(const boost::shared_ptr<ribi::cmap::Edge> edge);

  ///Adds a node and connects (some of) its signals to slots present in the derived classes
  QtConceptMapNodeItem * AddNode(const boost::shared_ptr<ribi::cmap::Node> node);

  void CleanMe();

  ///Called whenever a concept is clicked or moved
  ///If item is nullptr, the last item might be deleted
  ///Use QGraphicsItem* due to QtKeyboardFriendlyGraphicsView working on QGraphicsItems
  ///Is implemented by OnItemUpdateRequestImpl
  ///QGraphicsItem cannot be const: some items request for an update via-via
  void OnItemRequestUpdateImpl(const QGraphicsItem* const);

  ///Test this class
  static void Test() {}
};

} //~namespace cmap
} //~namespace ribi

#endif // QTPVDBCONCEPTMAPDISPLAYWIDGET_H
