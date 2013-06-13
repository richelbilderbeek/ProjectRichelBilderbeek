#ifndef QTPVDBCONCEPTMAPWIDGET_H
#define QTPVDBCONCEPTMAPWIDGET_H

#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif

#include <boost/noncopyable.hpp>
#include "qtkeyboardfriendlygraphicsview.h"

#ifdef PVDB_USE_FORWARD_DECLARATIONS_248738
#include "pvdbfwd.h"
#else
#include "qtpvdbexamplesitem.h"
#include "pvdbhints.h"
#include "qtpvdbnodeitem.h"
#include "qtpvdbedgeitem.h"
#include "pvdbconceptmap.h"
#endif

//An ABC View with a ConceptMap as the Model
class QtPvdbConceptMapWidget : public QtKeyboardFriendlyGraphicsView, boost::noncopyable
{
  Q_OBJECT

public:
  explicit QtPvdbConceptMapWidget(
    const boost::shared_ptr<pvdb::ConceptMap> concept_map,
    QWidget* parent = 0);
  virtual ~QtPvdbConceptMapWidget();
  //QtPvdbConceptMapWidget& operator=(const QtPvdbConceptMapWidget& other) = delete;
  //QtPvdbConceptMapWidget(const QtPvdbConceptMapWidget& other) = delete;

  ///Clone the derived class
  ///std::unique_ptr is used to:
  /// - prevent memory leaks, when the result of Clone is unused
  /// - being able to transfer ownership to shared_ptr<T>
  /// - being able to transfer ownership to shared_ptr<const T>
  ///TOO MUCH WORK, TOO LITTLE GAIN
  //virtual std::unique_ptr<QtPvdbConceptMapWidget> Clone() const = 0;

  #ifndef NDEBUG
  ///Creates a new derived class
  ///A simpler alternative to Clone (see above)
  virtual std::unique_ptr<QtPvdbConceptMapWidget> CreateNewDerived() const = 0;
  #endif

  ///Do something random
  virtual void DoRandomStuff() = 0;

  ///Obtain the concept map
  const boost::shared_ptr<const pvdb::ConceptMap> GetConceptMap() const { return m_concept_map; }
        boost::shared_ptr<      pvdb::ConceptMap> GetConceptMap()       { return m_concept_map; }

  ///Obtain the QGraphicsScene
  QGraphicsScene* GetScene() const;

  ///Shuffle the concepts (used in debugging)
  void Shuffle();

  #ifndef NDEBUG
  ///Test this class with a derived class instance
  static void Test(const boost::shared_ptr<const QtPvdbConceptMapWidget>& widget);
  #endif

  ///Write the widget its data to a cluster
  //const boost::shared_ptr<pvdb::ConceptMap> WriteToConceptMap() const;

public slots:

  virtual void keyPressEvent(QKeyEvent *event);

protected:


  ///The item showing the examples
  QtPvdbExamplesItem * m_examples;

  ///Adds an Edge and connects (some of) its signals to slots present in the derived classes
  ///Edge cannot be const, as an Edge has a Concept that the user might want to edit
  virtual void AddEdge(const boost::shared_ptr<pvdb::Edge> edge) = 0;

  ///Adds a node and connects (some of) its signals to slots present in the derived classes
  ///It returns (the derived class of) the QtPvdbNodeConcept added to the scene
  virtual QtPvdbNodeItem * AddNode(const boost::shared_ptr<pvdb::Node> node) = 0;

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
  QtPvdbNodeItem * FindQtNode(const boost::shared_ptr<pvdb::Node> node) const;

  ///Obtain the center node
  const QtPvdbNodeItem * GetCenterNode() const;

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

  #ifndef NDEBUG
  ///Test the internals of this class:
  ///Does the current content really reflect the map
  void TestMe(const boost::shared_ptr<const pvdb::ConceptMap> map) const;
  #endif

signals:

  ///Supply the client with a hint how to use this widget
  void GiveHint(const QString hint);

private:

  ///The concept map to work on, the Model
  ///m_concept_map->GetNodes()[0] contains the focal node
  const boost::shared_ptr<pvdb::ConceptMap> m_concept_map;

  ///Implemention of OnItemUpdateRequest
  virtual void OnItemRequestUpdateImpl(const QGraphicsItem* const item) = 0;

  ///Put the central node at index zero
  #ifdef BELIEF_THAT_INDEXLESS_EDGES_NEED_SORTING_672357462547263842756287
  const std::vector<QtPvdbNodeItem* > Sort(const std::vector<QtPvdbNodeItem*>& v) const;
  #endif

public slots:

  ///Called whenever a concept is clicked or moved
  ///If item is nullptr, the last item might be deleted
  ///Use QGraphicsItem* due to QtKeyboardFriendlyGraphicsView working on QGraphicsItems
  ///Is implemented by OnItemUpdateRequestImpl
  void OnItemRequestsUpdate(const QGraphicsItem* const item);

  ///Called when an item requests a scene update
  void OnRequestSceneUpdate();
};

#endif // QTPVDBCONCEPTMAPWIDGET_H
