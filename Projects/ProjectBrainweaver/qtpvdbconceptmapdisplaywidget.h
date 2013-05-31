#ifndef QTPVDBCONCEPTMAPDISPLAYWIDGET_H
#define QTPVDBCONCEPTMAPDISPLAYWIDGET_H

#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif

#include <boost/shared_ptr.hpp>
#include "qtpvdbconceptmapwidget.h"

#ifdef PVDB_USE_FORWARD_DECLARATIONS_248738
#include "pvdbfwd.h"
#else

#endif

#include "pvdbnode.h"
#include "pvdbedge.h"

///QtPvdbConceptMapWidget for creation and editing of a ConceptMap
struct QtPvdbConceptMapDisplayWidget : public QtPvdbConceptMapWidget
{
  typedef QtPvdbConceptMapDisplayWidget This_t;

  QtPvdbConceptMapDisplayWidget(QWidget* parent = 0);
  ~QtPvdbConceptMapDisplayWidget() {}
  QtPvdbConceptMapDisplayWidget(const QtPvdbConceptMapDisplayWidget& other) = delete;
  QtPvdbConceptMapDisplayWidget& operator=(const QtPvdbConceptMapDisplayWidget& other) = delete;

  ///Creates a new derived class
  ///A simpler alternative to Clone (see above)
  std::unique_ptr<QtPvdbConceptMapWidget> CreateNewDerived() const;

  ///Do something random
  void DoRandomStuff() {}

  ///Initialize the widget with a concept map
  ///Note that ReadFromConceptMap changes the copy of the map entered, by changing some GUI
  ///elements (coordinats of the nodes, for example). Therefore, the following test will fail:
  ///  conceptmapwidget->ReadFromConceptMap(m);
  ///  const pvdb::ConceptMapPtr n = w->WriteToConceptMap();
  ///  assert(m == n);
  ///instead, use
  ///  assert(HasSameContent(m,n));
  //void ReadFromConceptMap(const boost::shared_ptr<const pvdb::ConceptMap>& map);

private:
  ///Adds an Edge and connects (some of) its signals to slots present in the derived classes
  ///Edge cannot be const, as it has a Concept on it that the user might want to edit
  void AddEdge(
    const boost::shared_ptr<pvdb::Edge>& edge,
    const std::vector<QtPvdbNodeItem*>& qtnodes);

  ///Adds a node and connects (some of) its signals to slots present in the derived classes
  QtPvdbNodeItem * AddNode(const boost::shared_ptr<pvdb::Node>& node);

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

bool operator==(const boost::shared_ptr<const QtPvdbConceptMapDisplayWidget>& lhs, const boost::shared_ptr<const QtPvdbConceptMapDisplayWidget>& rhs) = delete;
bool operator==(const boost::shared_ptr<const QtPvdbConceptMapDisplayWidget>& lhs, boost::shared_ptr<const QtPvdbConceptMapDisplayWidget>& rhs) = delete;
bool operator==(const boost::shared_ptr<QtPvdbConceptMapDisplayWidget>& lhs, const boost::shared_ptr<const QtPvdbConceptMapDisplayWidget>& rhs) = delete;
bool operator==(const boost::shared_ptr<QtPvdbConceptMapDisplayWidget>& lhs, boost::shared_ptr<const QtPvdbConceptMapDisplayWidget>& rhs) = delete;
bool operator!=(const boost::shared_ptr<const QtPvdbConceptMapDisplayWidget>& lhs, const boost::shared_ptr<const QtPvdbConceptMapDisplayWidget>& rhs) = delete;
bool operator!=(const boost::shared_ptr<const QtPvdbConceptMapDisplayWidget>& lhs, boost::shared_ptr<const QtPvdbConceptMapDisplayWidget>& rhs) = delete;
bool operator!=(const boost::shared_ptr<QtPvdbConceptMapDisplayWidget>& lhs, const boost::shared_ptr<const QtPvdbConceptMapDisplayWidget>& rhs) = delete;
bool operator!=(const boost::shared_ptr<QtPvdbConceptMapDisplayWidget>& lhs, boost::shared_ptr<const QtPvdbConceptMapDisplayWidget>& rhs) = delete;

#endif // QTPVDBCONCEPTMAPDISPLAYWIDGET_H
