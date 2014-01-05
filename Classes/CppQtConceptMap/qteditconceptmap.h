#ifndef QTCONCEPTMAPEDITCONCEPTMAP_H
#define QTCONCEPTMAPEDITCONCEPTMAP_H


#include "qtconceptmapfwd.h"

#include "qtconceptmap.h"

namespace ribi {

namespace cmap {

///Editable QtConceptMap with a low-level interface
///Use QtEditConceptMapWidget for a Command driven interface
struct QtEditConceptMap : public QtConceptMap
{
  typedef QtEditConceptMap This_t;

  ///Mode is temporary: I want to seperate QtEditConceptMap
  ///into a class that only does the display (this class)
  ///and a class that handles the user interaction (QtConceptMapWidget).
  ///To not break the current build, I switch on Mode
  enum class Mode { classic, simple };

  QtEditConceptMap(
    const boost::shared_ptr<ConceptMap> concept_map = boost::shared_ptr<ConceptMap>(),
    const Mode mode = Mode::classic,
    QWidget* parent = 0);
  ~QtEditConceptMap() noexcept;
  QtEditConceptMap(const QtEditConceptMap& other) = delete;
  QtEditConceptMap& operator=(const QtEditConceptMap& other) = delete;

  #ifndef NDEBUG
  ///Creates a new derived class
  ///A simpler alternative to Clone (see above)
  std::unique_ptr<QtConceptMap> CreateNewDerived() const;
  #endif

  ///Delete an EdgeConcept
  void DeleteEdge(QtEdge * const edge);

  ///Delete a Node
  void DeleteNode(QtNode * const node);

  #ifndef NDEBUG
  ///Do something random
  void DoRandomStuff();
  #endif

  ///Signal emitted when a concept map item requests to be edited
  boost::signals2::signal<void(QtConceptMapElement*)> m_signal_conceptmapitem_requests_edit;

protected:

  void keyPressEvent(QKeyEvent* event) noexcept;
  void mouseMoveEvent(QMouseEvent * event);
  void mouseDoubleClickEvent(QMouseEvent *event);
  void mousePressEvent(QMouseEvent *event);

private:

  ///The arrow used to create a new arrow
  ///Is nullptr when not active
  QtNewArrow * m_arrow;

  ///The item highlighter, used when creating a new relation
  QtItemHighlighter * const m_highlighter;

  ///The current mode, to be removed later (see definition of Mode)
  const Mode m_mode;

  ///The item showing the tools
  QtTool * m_tools;

  ///Adds an Edge and connects (some of) its signals to slots present in the derived classes
  void AddEdge(const boost::shared_ptr<Edge> edge);

  ///Add a new edge
  void AddEdge(QtNode * const from, QtNode* const to);

  ///Adds a node and connects (some of) its signals to slots present in the derived classes
  QtNode * AddNode(const boost::shared_ptr<Node> node);

  ///Remove all Qt and non-Qt items
  void CleanMe();

  ///The way a QtConceptMap displays its Nodes (both as nodes and on edges)
  const boost::shared_ptr<QtItemDisplayStrategy> GetDisplayStrategy(
    const boost::shared_ptr<Concept> concept) const noexcept;

  ///Obtain the read-and-write Qt edge items
  ///The read-only Qt edge items is already supplied by QtConceptMap
  const std::vector<QtEdge *> GetQtEdges();

  ///Obtain the read-and-write Qt node items
  ///The read-only Qt node items is already supplied by QtConceptMap
  const std::vector<QtNode *> GetQtNodes();

  ///Called when an item wants to be edited
  void OnConceptMapItemRequestsEdit(QtConceptMapElement * const item);

  ///Called whenever a concept is clicked or moved
  ///If item is nullptr, the last item might be deleted
  ///Use QGraphicsItem* due to QtKeyboardFriendlyGraphicsView working on QGraphicsItems
  ///Is implemented by OnItemUpdateRequestImpl
  void OnItemRequestUpdateImpl(const QGraphicsItem* const item);

  ///Called whenever the tools item is clicked
  void OnToolsClicked();

  ///Test this class
  static void Test() noexcept;
};

} //~namespace cmap

} //~namespace ribi

#endif // QTCONCEPTMAPEDITCONCEPTMAP_H
