#ifndef QTCONCEPTMAPCONCEPTMAPRATEWIDGET_H
#define QTCONCEPTMAPCONCEPTMAPRATEWIDGET_H

#include "qtconceptmapwidget.h"

#include "conceptmapfwd.h"

namespace ribi {

namespace cmap {

///QtConceptMapWidget for creation and editing of a ConceptMap
struct QtConceptMapRateWidget : public QtConceptMapWidget
{
  typedef QtConceptMapRateWidget This_t;

  QtConceptMapRateWidget(
    const boost::shared_ptr<ribi::cmap::ConceptMap> concept_map,
    QWidget* parent = 0);
  ~QtConceptMapRateWidget() noexcept {}
  QtConceptMapRateWidget(const QtConceptMapRateWidget& other) = delete;
  QtConceptMapRateWidget& operator=(const QtConceptMapRateWidget& other) = delete;

  #ifndef NDEBUG
  ///Creates a new derived class
  ///A simpler alternative to Clone (see above)
  std::unique_ptr<QtConceptMapWidget> CreateNewDerived() const;

  ///Do something random
  void DoRandomStuff();
  #endif

  const std::string GetVersion() const noexcept;
  const std::vector<std::string> GetVersionHistory() const noexcept;

  ///If the user wants to rate the focal concept of the already generated sub concept map
  ///the dialog using this widget must display the tally dialog
  boost::signals2::signal<void (boost::shared_ptr<ribi::cmap::ConceptMap>)> m_signal_request_rate_concept_dialog;

private:

  ///Adds an Edge and connects (some of) its signals to slots present in the derived classes
  void AddEdge(
    const boost::shared_ptr<ribi::cmap::Edge> edge);

  ///Adds a node and connects (some of) its signals to slots present in the derived classes
  ///For rating and editing, the node must be non-cost
  ///For display, the node should best be const
  QtConceptMapNodeItem * AddNode(const boost::shared_ptr<ribi::cmap::Node> node);

  ///Remove all Qt and non-Qt items and add new ones
  void CleanMe();

  ///Create a subsection of the concept map, with item at the center
  ///Item is non-const, as all items can be edited in other contexts
  const boost::shared_ptr<ribi::cmap::ConceptMap> CreateSubConceptMap(QtConceptMapNodeItem * const item);

  ///Called whenever a concept is clicked or moved
  ///If item is nullptr, the last item might be deleted
  ///Use QGraphicsItem* due to QtKeyboardFriendlyGraphicsView working on QGraphicsItems
  ///Is implemented by OnItemUpdateRequestImpl
  void OnItemRequestUpdateImpl(const QGraphicsItem* const item);

  ///Called when a QtConceptItem requests to have its concept rated
  ///Note that this might be a ConceptItem on an Edge, but those signals are not connected
  ///item must be a Node, becaus only Nodes can be rated and because the Node is
  ///used for contruction of a sub concept map
  void OnNodeRequestsRateConcept(QtConceptMapNodeItem * const item);

  ///Called when a QtConceptItem requests to have its concept rated
  ///Note that this might be a ConceptItem on an Edge, but those signals are not connected
  ///item must be a Node, becaus only Nodes can be rated and because the Node is
  ///used for contruction of a sub concept map
  void OnNodeRequestsRateConceptWithSuggestion(QtConceptMapNodeItem * const item);

  ///Called when a QtConceptItem requests to have its examples rated
  ///Note that this might be a ConceptItem on an Edge, but those signals are not connected
  void OnNodeRequestsRateExamples(QtConceptMapNodeItem * const item);

  #ifndef NDEBUG
  ///Test this class
  static void Test();
  #endif
};

} //~namespace cmap

} //~namespace ribi

#endif // QTCONCEPTMAPCONCEPTMAPRATEWIDGET_H
