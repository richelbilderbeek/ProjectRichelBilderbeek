#ifndef QTPVDBCONCEPTMAPEDITWIDGET_H
#define QTPVDBCONCEPTMAPEDITWIDGET_H


#include "pvdbfwd.h"

#include "qtpvdbconceptmapwidget.h"

namespace ribi {

namespace pvdb {

///QtPvdbConceptMapWidget for creation and editing of a ConceptMap
struct QtPvdbConceptMapEditWidget : public QtPvdbConceptMapWidget
{
  typedef QtPvdbConceptMapEditWidget This_t;
  QtPvdbConceptMapEditWidget(
    const boost::shared_ptr<ribi::pvdb::ConceptMap> concept_map,
    QWidget* parent = 0);
  ~QtPvdbConceptMapEditWidget() noexcept;
  QtPvdbConceptMapEditWidget(const QtPvdbConceptMapEditWidget& other) = delete;
  QtPvdbConceptMapEditWidget& operator=(const QtPvdbConceptMapEditWidget& other) = delete;

  #ifndef NDEBUG
  ///Creates a new derived class
  ///A simpler alternative to Clone (see above)
  std::unique_ptr<QtPvdbConceptMapWidget> CreateNewDerived() const;
  #endif

  ///Delete an EdgeConcept
  void DeleteEdge(QtPvdbEdgeItem * const edge);

  ///Delete a Node
  void DeleteNode(QtPvdbNodeItem * const node);

  #ifndef NDEBUG
  ///Do something random
  void DoRandomStuff();
  #endif

  ///Signal emitted when a concept map item requests to be edited
  boost::signals2::signal<void(QtPvdbConceptMapItem*)> m_signal_conceptmapitem_requests_edit;

protected:

  void keyPressEvent(QKeyEvent* event);
  void mouseMoveEvent(QMouseEvent * event);
  void mouseDoubleClickEvent(QMouseEvent *event);
  void mousePressEvent(QMouseEvent *event);

private:

  ///The arrow used to create a new arrow
  ///Is nullptr when not active
  QtPvdbNewArrow * m_arrow;

  ///The item highlighter, used when creating a new relation
  QtPvdbItemHighlighter * const m_highlighter;

  ///The item showing the tools
  QtPvdbToolsItem * m_tools;

  ///Adds an Edge and connects (some of) its signals to slots present in the derived classes
  void AddEdge(const boost::shared_ptr<ribi::pvdb::Edge> edge);

  ///Add a new edge
  void AddEdge(QtPvdbNodeItem * const from, QtPvdbNodeItem* const to);

  ///Adds a node and connects (some of) its signals to slots present in the derived classes
  QtPvdbNodeItem * AddNode(const boost::shared_ptr<ribi::pvdb::Node> node);

  ///Remove all Qt and non-Qt items
  void CleanMe();

  ///After the selected arrows, EdgeConcepts and Nodes are deleted
  ///delete the unconnected leftovers that are left
  //void DeleteLeftovers();

  ///Obtain the read-and-write Qt edge items
  ///The read-only Qt edge items is already supplied by QtPvdbConceptMapWidget
  const std::vector<QtPvdbEdgeItem *> GetQtEdges();

  ///Obtain the read-and-write Qt node items
  ///The read-only Qt node items is already supplied by QtPvdbConceptMapWidget
  const std::vector<QtPvdbNodeItem *> GetQtNodes();

  ///Called when an item wants to be edited
  void OnConceptMapItemRequestsEdit(QtPvdbConceptMapItem * const item);

  ///Called whenever a concept is clicked or moved
  ///If item is nullptr, the last item might be deleted
  ///Use QGraphicsItem* due to QtKeyboardFriendlyGraphicsView working on QGraphicsItems
  ///Is implemented by OnItemUpdateRequestImpl
  void OnItemRequestUpdateImpl(const QGraphicsItem* const item);

  ///Called whenever the tools item is clicked
  void OnToolsClicked();

  ///Test this class
  static void Test();
};

} //~namespace pvdb

} //~namespace ribi

#endif // QTPVDBCONCEPTMAPEDITWIDGET_H
