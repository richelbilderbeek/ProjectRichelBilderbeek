#ifndef QTPVDBCONCEPTMAPEDITWIDGET_H
#define QTPVDBCONCEPTMAPEDITWIDGET_H

#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif

#ifdef PVDB_USE_FORWARD_DECLARATIONS_248738
#include "pvdbfwd.h"
#else
#include "qtpvdbnewarrow.h"
#include "qtpvdbitemhighlighter.h"
#include "qtpvdbrateconcept.h"
#include "qtpvdbtoolsitem.h"
#endif

#include "qtpvdbconceptmapwidget.h"

///QtPvdbConceptMapWidget for creation and editing of a ConceptMap
struct QtPvdbConceptMapEditWidget : public QtPvdbConceptMapWidget
{
  typedef QtPvdbConceptMapEditWidget This_t;
  QtPvdbConceptMapEditWidget(
    const boost::shared_ptr<pvdb::ConceptMap> concept_map,
    QWidget* parent = 0);
  ~QtPvdbConceptMapEditWidget();
  QtPvdbConceptMapEditWidget(const QtPvdbConceptMapEditWidget& other) = delete;
  QtPvdbConceptMapEditWidget& operator=(const QtPvdbConceptMapEditWidget& other) = delete;

  #ifndef NDEBUG
  ///Creates a new derived class
  ///A simpler alternative to Clone (see above)
  std::unique_ptr<QtPvdbConceptMapWidget> CreateNewDerived() const;
  #endif

  ///Do something random
  void DoRandomStuff();

  ///Initialize the widget with a concept map
  ///Note that ReadFromConceptMap changes the copy of the map entered, by changing some GUI
  ///elements (coordinats of the nodes, for example). Therefore, the following test will fail:
  ///  conceptmapwidget->ReadFromConceptMap(m);
  ///  const pvdb::ConceptMapPtr n = w->WriteToConceptMap();
  ///  assert(m == n);
  ///instead, use
  ///  assert(HasSameContent(m,n));
  //void ReadFromConceptMap(const boost::shared_ptr<const pvdb::ConceptMap> map);

  ///NEW 2013-01-13
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
  void AddEdge(const boost::shared_ptr<pvdb::Edge> edge);

  ///Add a new edge
  void AddEdge(QtPvdbNodeItem * const from, QtPvdbNodeItem* const to);

  ///Adds a node and connects (some of) its signals to slots present in the derived classes
  QtPvdbNodeItem * AddNode(const boost::shared_ptr<pvdb::Node> node);

  ///Remove all Qt and non-Qt items
  void CleanMe();

  ///Delete an EdgeConcept
  void DeleteEdge(QtPvdbEdgeItem * const edge);

  ///After the selected arrows, EdgeConcepts and Nodes are deleted
  ///delete the unconnected leftovers that are left
  void DeleteLeftovers();

  ///Delete a Node
  void DeleteNode(QtPvdbNodeItem * const node);

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

///Keep undefined
bool operator==(const boost::shared_ptr<const QtPvdbConceptMapEditWidget>& lhs, const boost::shared_ptr<const QtPvdbConceptMapEditWidget>& rhs) = delete;
bool operator==(const boost::shared_ptr<const QtPvdbConceptMapEditWidget>& lhs, boost::shared_ptr<const QtPvdbConceptMapEditWidget>& rhs) = delete;
bool operator==(const boost::shared_ptr<QtPvdbConceptMapEditWidget>& lhs, const boost::shared_ptr<const QtPvdbConceptMapEditWidget>& rhs) = delete;
bool operator==(const boost::shared_ptr<QtPvdbConceptMapEditWidget>& lhs, const boost::shared_ptr<QtPvdbConceptMapEditWidget>& rhs) = delete;
bool operator!=(const boost::shared_ptr<const QtPvdbConceptMapEditWidget>& lhs, const boost::shared_ptr<const QtPvdbConceptMapEditWidget>& rhs) = delete;
bool operator!=(const boost::shared_ptr<const QtPvdbConceptMapEditWidget>& lhs, boost::shared_ptr<const QtPvdbConceptMapEditWidget>& rhs) = delete;
bool operator!=(const boost::shared_ptr<QtPvdbConceptMapEditWidget>& lhs, const boost::shared_ptr<const QtPvdbConceptMapEditWidget>& rhs) = delete;
bool operator!=(const boost::shared_ptr<QtPvdbConceptMapEditWidget>& lhs, const boost::shared_ptr<QtPvdbConceptMapEditWidget>& rhs) = delete;

#endif // QTPVDBCONCEPTMAPEDITWIDGET_H
