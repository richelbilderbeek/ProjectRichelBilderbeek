#ifndef QTCONCEPTMAPRATECONCEPTMAP_H
#define QTCONCEPTMAPRATECONCEPTMAP_H

#include "qtconceptmap.h"

#include "conceptmapfwd.h"

namespace ribi {

namespace cmap {

///Rateable QtConceptMap with a low-level interface
///Use QtRateConceptMapWidget for a Command driven interface
struct QtRateConceptMap : public QtConceptMap
{
  typedef QtRateConceptMap This_t;

  QtRateConceptMap(
    const boost::shared_ptr<ConceptMap> concept_map = boost::shared_ptr<ConceptMap>(),
    QWidget* parent = 0);
  ~QtRateConceptMap() noexcept {}
  QtRateConceptMap(const QtRateConceptMap& other) = delete;
  QtRateConceptMap& operator=(const QtRateConceptMap& other) = delete;

  #ifndef NDEBUG
  ///Creates a new derived class
  ///A simpler alternative to Clone (see above)
  std::unique_ptr<QtConceptMap> CreateNewDerived() const;

  ///Do something random
  void DoRandomStuff();
  #endif

  std::string GetVersion() const noexcept;
  std::vector<std::string> GetVersionHistory() const noexcept;

  ///If the user wants to rate the focal concept of the already generated sub concept map
  ///the dialog using this widget must display the tally dialog
  boost::signals2::signal<void (boost::shared_ptr<ConceptMap>)> m_signal_request_rate_concept_dialog;

private:

  ///Adds an Edge and connects (some of) its signals to slots present in the derived classes
  void AddEdge(
    const boost::shared_ptr<Edge> edge);

  ///Adds a node and connects (some of) its signals to slots present in the derived classes
  ///For rating and editing, the node must be non-cost
  ///For display, the node should best be const
  QtNode * AddNode(const boost::shared_ptr<Node> node);

  ///Remove all Qt and non-Qt items and add new ones
  void CleanMe();

  ///Create a subsection of the concept map, with item at the center
  ///Item is non-const, as all items can be edited in other contexts
  const boost::shared_ptr<ConceptMap> CreateSubConceptMap(QtNode * const item);

  ///The way a QtConceptMap displays its Nodes (both as nodes and on edges)
  const boost::shared_ptr<QtItemDisplayStrategy> GetDisplayStrategy(
    const boost::shared_ptr<Concept> concept) const noexcept;

  ///Called whenever a concept is clicked or moved
  ///If item is nullptr, the last item might be deleted
  ///Use QGraphicsItem* due to QtKeyboardFriendlyGraphicsView working on QGraphicsItems
  ///Is implemented by OnItemUpdateRequestImpl
  void OnItemRequestUpdateImpl(const QGraphicsItem* const item);

  ///Called when a QtItemDisplayStrategy requests to have its concept rated
  ///Note that this might be a ConceptItem on an Edge, but those signals are not connected
  ///item must be a Node, becaus only Nodes can be rated and because the Node is
  ///used for contruction of a sub concept map
  void OnNodeRequestsRateConcept(QtNode * const item);

  ///Called when a QtItemDisplayStrategy requests to have its concept rated
  ///Note that this might be a ConceptItem on an Edge, but those signals are not connected
  ///item must be a Node, becaus only Nodes can be rated and because the Node is
  ///used for contruction of a sub concept map
  void OnNodeRequestsRateConceptWithSuggestion(QtNode * const item);

  ///Called when a QtItemDisplayStrategy requests to have its examples rated
  ///Note that this might be a ConceptItem on an Edge, but those signals are not connected
  void OnNodeRequestsRateExamples(QtNode * const item);

  #ifndef NDEBUG
  ///Test this class
  static void Test() noexcept;
  #endif
};

} //~namespace cmap

} //~namespace ribi

#endif // QTCONCEPTMAPRATECONCEPTMAP_H
