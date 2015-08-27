//---------------------------------------------------------------------------
/*
QtConceptMap, Qt classes for display and interaction with ConceptMap
Copyright (C) 2013-2015 The Brainweaver Team

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program.If not, see <http://www.gnu.org/licenses/>.
*/
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/CppQtConceptMap.htm
//---------------------------------------------------------------------------
#ifndef QTCONCEPTMAPCONCEPTMAP_H
#define QTCONCEPTMAPCONCEPTMAP_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "qtkeyboardfriendlygraphicsview.h"
#include "qtconceptmapfwd.h"
#include "qtconceptmapqtedge.h"
#pragma GCC diagnostic pop

namespace ribi {
namespace cmap {

///QtConceptMap displays a ConceptMap
///It does not offer UI interaction with the user
///QtConceptMap does offer UI interaction
class QtConceptMap final: public ribi::QtKeyboardFriendlyGraphicsView
{
  Q_OBJECT

public:

  explicit QtConceptMap(
    QWidget* parent = 0
  );
  QtConceptMap(const QtConceptMap&) = delete;
  QtConceptMap& operator=(const QtConceptMap&) = delete;
  ~QtConceptMap();

  bool CanDoCommand(const boost::shared_ptr<const Command> command) const noexcept;

  void DoCommand(const boost::shared_ptr<Command> command) noexcept;

  ///Obtain the concept map
  boost::shared_ptr<const ConceptMap> GetConceptMap() const noexcept { return m_concept_map; }
  boost::shared_ptr<      ConceptMap> GetConceptMap()       noexcept { return m_concept_map; }

  std::vector<const QtEdge *> GetQtEdges() const;
  std::vector<      QtEdge *> GetQtEdges();

  std::vector<const QtNode *> GetQtNodes() const;
  std::vector<      QtNode *> GetQtNodes();

  ///Obtain the QGraphicsScene
  QGraphicsScene* GetScene() const noexcept;

  static std::string GetVersion() noexcept;
  static std::vector<std::string> GetVersionHistory() noexcept;


  void RemoveExamplesItem() noexcept { SetExamplesItem(nullptr); }

  void SetConceptMap(const boost::shared_ptr<ConceptMap> concept_map);

  void SetVerbosity(const bool verbosity) noexcept { m_verbose = verbosity; }

  #ifndef NDEBUG
  ///Shuffle the concepts (used in debugging)
  void Shuffle() noexcept;

  ///Test this class with a derived class instance
  static void Test() noexcept;
  #endif

  ///Signal emitted when a concept map item requests to be edited
  boost::signals2::signal<void(QtRoundedEditRectItem*)> m_signal_conceptmapitem_requests_edit;

  boost::signals2::signal<void(const boost::shared_ptr<ConceptMap> sub_concept_map)> m_signal_request_rate_concept;

public slots:

  void keyPressEvent(QKeyEvent* event) noexcept;
  void mouseMoveEvent(QMouseEvent * event);
  void mouseDoubleClickEvent(QMouseEvent *event);
  void mousePressEvent(QMouseEvent *event);

protected:

  ///Delete a QtEdge
  void DeleteQtEdge(const QtEdge * const edge);

  ///Delete a Node
  //void DeleteNode(const boost::shared_ptr<QtNode>& node);
  void DeleteQtNode(const QtNode * const node);

  ///Get all the edges connected to the concept
  std::vector<QtEdge*> GetQtEdges(const QtNode * const from) const noexcept;

  //Find the Qt edge with the same from and to
  const QtEdge * GetQtEdgeConst(const boost::shared_ptr<const Edge> edge) const noexcept;
        QtEdge * GetQtEdge(const boost::shared_ptr<      Edge> edge)       noexcept;
  const QtEdge * GetQtEdge(     const QtEdge* const edge) const noexcept { return GetQtEdgeConst(edge); }
  const QtEdge * GetQtEdgeConst(const QtEdge* const edge) const noexcept;
        QtEdge * GetQtEdge(const QtEdge* const edge)       noexcept;
  const QtEdge * GetQtEdgeConst(
    const QtNode* const from,
    const QtNode* const to) const noexcept;

  ///Find the QtNode containing the Node
  //QtNode * FindQtNode(boost::shared_ptr<Node> node) const { return FindQtNode(node.get()); }
  const QtNode * GetQtNodeConst(const Node * const node) const noexcept;
  //const QtNode * FindQtNode     (const Node * const node) const noexcept { return FindQtNodeConst(node); }
        QtNode * GetQtNode(           Node * const node)       noexcept;

  ///Obtain the center node
  const QtNode * GetCenterNode() const noexcept;
        QtNode * GetCenterNode()       noexcept;

  ///Obtain the rectangle with text showing the examples
  const QtExamplesItem * GetExamplesItem() const;

  ///Obtain the rectangle with text showing the examples
  QtExamplesItem * GetExamplesItem();

  ///Obtain the first QtNode under the cursor
  ///Returns nullptr if none is present
  QtNode* GetItemBelowCursor(const QPointF& pos) const;

  ///Check if this item is the center node
  static bool IsQtCenterNode(const QGraphicsItem* const item);

  ///Have the nodes in the concept map be positioned once already, or must
  ///these be (re)positioned. '(re)', because the nodes are initially positioned at the origin
  bool MustReposition(const std::vector<boost::shared_ptr<const cmap::Node> >& nodes) const;

  ///All items from a ConceptMap are put in at the center and need to be repositioned
  void RepositionItems();

  ///Set the rectangle with text showing the examples
  void SetExamplesItem(QtExamplesItem * const item);

  #ifndef NDEBUG
  ///Test the internals of this class:
  ///Does the current content really reflect the map
  void TestMe(const boost::shared_ptr<const ConceptMap> map) const;
  #endif

private:

  ///The arrow used to create a new arrow
  ///Is nullptr when not active
  QtNewArrow * m_arrow;

  ///The concept map to work on, the Model
  boost::shared_ptr<ConceptMap> m_concept_map;

  ///The item showing the examples
  QtExamplesItem * m_examples_item;


  ///The item highlighter, used when creating a new relation
  QtItemHighlighter * const m_highlighter;

  ///The item showing the tools
  QtTool * m_tools;

  bool m_verbose;

  ///Adds an Edge, returns the freshly created QtEdge
  QtEdge * AddEdge(const boost::shared_ptr<Edge> edge);

  ///Adds a Node, returns the freshly created QtNode
  QtNode * AddNode(const boost::shared_ptr<Node> node);

  ///Remove all Qt and non-Qt items
  void CleanMe();

  ///Called when an Edge gets deleted from the ConceptMap
  void DeleteEdge(const boost::shared_ptr<const Edge> edge);

  ///Called when a Node gets deleted from the ConceptMap
  void DeleteNode(const boost::shared_ptr<const Node> node);


  ///Called when an item wants to be edited
  void OnEdgeKeyDownPressed(QtEdge * const item, const int key);

  ///Called when an item wants to be edited
  void OnNodeKeyDownPressed(QtNode* const item, const int key);

  ///Called whenever a concept is clicked or moved
  ///If item is nullptr, the last item might be deleted
  ///Use QGraphicsItem* due to QtKeyboardFriendlyGraphicsView working on QGraphicsItems
  ///Is implemented by OnItemUpdateRequestImpl
  void OnItemRequestUpdateImpl(const QGraphicsItem* const item);

  ///Called whenever the tools item is clicked
  void OnToolsClicked();

  void UpdateSelection();

public slots:

  ///Called whenever a concept is clicked or moved
  ///If item is nullptr, the last item might be deleted
  ///Use QGraphicsItem* due to QtKeyboardFriendlyGraphicsView working on QGraphicsItems
  ///Is implemented by OnItemUpdateRequestImpl
  void OnItemRequestsUpdate(const QGraphicsItem* const item);

  ///Called when an item requests a scene update
  void OnRequestSceneUpdate();
};

} //~namespace cmap
} //~namespace ribi

#endif // QTCONCEPTMAPCONCEPTMAP_H
