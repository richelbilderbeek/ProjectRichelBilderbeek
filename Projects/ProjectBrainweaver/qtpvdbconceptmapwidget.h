#ifndef QTPVDBCONCEPTMAPWIDGET_H
#define QTPVDBCONCEPTMAPWIDGET_H


#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "qtkeyboardfriendlygraphicsview.h"

#include "pvdbfwd.h"
#pragma GCC diagnostic pop

namespace ribi {

namespace pvdb {

//An ABC View with a ConceptMap as the Model
class QtPvdbConceptMapWidget : public ribi::QtKeyboardFriendlyGraphicsView
{
  Q_OBJECT

public:
  explicit QtPvdbConceptMapWidget(
    const boost::shared_ptr<ribi::pvdb::ConceptMap> concept_map,
    QWidget* parent = 0);
  QtPvdbConceptMapWidget(const QtPvdbConceptMapWidget&) = delete;
  QtPvdbConceptMapWidget& operator=(const QtPvdbConceptMapWidget&) = delete;
  virtual ~QtPvdbConceptMapWidget() noexcept;

  #ifndef NDEBUG
  ///Creates a new derived class
  ///A simpler alternative to Clone (see above)
  virtual std::unique_ptr<QtPvdbConceptMapWidget> CreateNewDerived() const = 0;

  ///Do something random, used in debugging
  virtual void DoRandomStuff() = 0;
  #endif

  ///Obtain the concept map
  const boost::shared_ptr<const ribi::pvdb::ConceptMap> GetConceptMap() const { return m_concept_map; }
        boost::shared_ptr<      ribi::pvdb::ConceptMap> GetConceptMap()       { return m_concept_map; }

  ///Obtain the read-only Qt edge items
  ///Read-and-write Qt edge items are only supported for QtPvdbConceptMapEditWidget
  const std::vector<const QtPvdbEdgeItem *> GetQtEdges() const;

  ///Obtain the read-only Qt node items
  ///Read-and-write Qt node items are only supported for QtPvdbConceptMapEditWidget
  const std::vector<const QtPvdbNodeItem *> GetQtNodes() const;

  ///Obtain the QGraphicsScene
  QGraphicsScene* GetScene() const;

  #ifndef NDEBUG
  ///Shuffle the concepts (used in debugging)
  void Shuffle();

  ///Test this class with a derived class instance
  static void Test(const boost::shared_ptr<const QtPvdbConceptMapWidget>& widget);
  #endif

public slots:

  virtual void keyPressEvent(QKeyEvent *event);

protected:

  ///Adds an Edge and connects (some of) its signals to slots present in the derived classes
  ///Edge cannot be const, as an Edge has a Concept that the user might want to edit
  virtual void AddEdge(const boost::shared_ptr<ribi::pvdb::Edge> edge) = 0;

  ///Adds a node and connects (some of) its signals to slots present in the derived classes
  ///It returns (the derived class of) the QtPvdbNodeConcept added to the scene
  virtual QtPvdbNodeItem * AddNode(const boost::shared_ptr<ribi::pvdb::Node> node) = 0;

  ///Initialize the widget with the loaded concept map
  ///BuildQtConceptMap changes the concept map entered, by changing some GUI
  ///elements (coordinats of the nodes, for example).
  ///Instead of using IsEqual use HasSameContent
  void BuildQtConceptMap();

  ///Remove all Qt and non-Qt items and add new ones
  virtual void CleanMe() = 0;

  ///Get all the edges connected to the concept
  const std::vector<QtPvdbEdgeItem*> FindEdges(const QtPvdbNodeItem * const from) const;

  //Find the edge with the same from and to
  const QtPvdbEdgeItem * FindQtEdge(
    const QtPvdbNodeItem* const from,
    const QtPvdbNodeItem* const to) const;

  ///Find the QtNode containing the Node
  QtPvdbNodeItem * FindQtNode(const boost::shared_ptr<ribi::pvdb::Node> node) const;

  ///Obtain the center node
  const QtPvdbNodeItem * GetCenterNode() const;

  ///Obtain the rectangle with text showing the examples
  const QtPvdbExamplesItem * GetExamplesItem() const;

  ///Obtain the rectangle with text showing the examples
  QtPvdbExamplesItem * GetExamplesItem();

  ///Obtain the first QtPvdbNodeItem under the cursor
  ///Returns nullptr if none is present
  QtPvdbNodeItem* GetItemBelowCursor(const QPointF& pos) const;

  ///Check if this item is the center node
  static bool IsCenterNode(const QGraphicsItem* const item);

  ///Have the nodes in the concept map be positioned once already, or must
  ///these be (re)positioned. '(re)', because the nodes are initially positioned at the origin
  bool MustReposition(const std::vector<boost::shared_ptr<const pvdb::Node> >& nodes) const;

  ///All items from a ConceptMap are put in at the center and need to be repositioned
  void RepositionItems();

  ///Set the rectangle with text showing the examples
  void SetExamplesItem(QtPvdbExamplesItem * const item);

  #ifndef NDEBUG
  ///Test the internals of this class:
  ///Does the current content really reflect the map
  void TestMe(const boost::shared_ptr<const ribi::pvdb::ConceptMap> map) const;
  #endif

private:

  ///The concept map to work on, the Model
  ///m_concept_map->GetNodes()[0] contains the focal node
  const boost::shared_ptr<ribi::pvdb::ConceptMap> m_concept_map;

  ///The item showing the examples
  QtPvdbExamplesItem * m_examples_item;

  ///Implemention of OnItemUpdateRequest
  virtual void OnItemRequestUpdateImpl(const QGraphicsItem* const item) = 0;

public slots:

  ///Called whenever a concept is clicked or moved
  ///If item is nullptr, the last item might be deleted
  ///Use QGraphicsItem* due to QtKeyboardFriendlyGraphicsView working on QGraphicsItems
  ///Is implemented by OnItemUpdateRequestImpl
  void OnItemRequestsUpdate(const QGraphicsItem* const item);

  ///Called when an item requests a scene update
  void OnRequestSceneUpdate();
};

} //~namespace pvdb

} //~namespace ribi

#endif // QTPVDBCONCEPTMAPWIDGET_H
