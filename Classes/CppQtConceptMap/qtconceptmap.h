//---------------------------------------------------------------------------
/*
QtConceptMap, Qt classes for display and interaction with ConceptMap
Copyright (C) 2013-2014 The Brainweaver Team

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

#ifdef NOT_NOW_20140810

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "qtkeyboardfriendlygraphicsview.h"
#include "qtconceptmapfwd.h"
#pragma GCC diagnostic pop

namespace ribi {
namespace cmap {

///QtConceptMap displays a ConceptMap
///It does not offer UI interaction with the user
///QtConceptMap does offer UI interaction
class QtConceptMap : public ribi::QtKeyboardFriendlyGraphicsView
{
  Q_OBJECT

public:
  explicit QtConceptMap(
    const boost::shared_ptr<ConceptMap> concept_map,
    QWidget* parent = 0);
  QtConceptMap(const QtConceptMap&) = delete;
  QtConceptMap& operator=(const QtConceptMap&) = delete;
  virtual ~QtConceptMap() noexcept;

  #ifndef NDEBUG
  ///Creates a new derived class
  ///A simpler alternative to Clone (see above)
  virtual std::unique_ptr<QtConceptMap> CreateNewDerived() const = 0;

  ///Do something random, used in debugging
  virtual void DoRandomStuff() = 0;
  #endif

  ///Obtain the concept map
  boost::shared_ptr<const ConceptMap> GetConceptMap() const noexcept { return m_concept_map; }
  boost::shared_ptr<      ConceptMap> GetConceptMap()       noexcept { return m_concept_map; }

  ///Obtain the read-only Qt edge items
  ///Read-and-write Qt edge items are only supported for QtEditConceptMap
  std::vector<const QtEdge *> GetQtEdges() const;

  ///Obtain the read-only Qt node items
  ///Read-and-write Qt node items are only supported for QtEditConceptMap
  std::vector<const QtNode *> GetQtNodes() const;

  ///Obtain the QGraphicsScene
  QGraphicsScene* GetScene() const noexcept;

  static std::string GetVersion() noexcept;
  static std::vector<std::string> GetVersionHistory() noexcept;

  void RemoveExamplesItem() noexcept { SetExamplesItem(nullptr); }

  #ifndef NDEBUG
  ///Shuffle the concepts (used in debugging)
  void Shuffle() noexcept;

  ///Test this class with a derived class instance
  static void Test(const boost::shared_ptr<const QtConceptMap>& concept_map) noexcept;
  #endif

public slots:

  virtual void keyPressEvent(QKeyEvent *event) noexcept;

protected:

  ///Adds an Edge and connects (some of) its signals to slots present in the derived classes
  ///Edge cannot be const, as an Edge has a Concept that the user might want to edit
  virtual QtEdge * AddEdge(const boost::shared_ptr<Edge> edge) = 0;

  ///Adds a node and connects (some of) its signals to slots present in the derived classes
  ///It returns (the derived class of) the QtConceptMapNodeConcept added to the scene
  virtual QtNode * AddNode(const boost::shared_ptr<Node> node) = 0;

  ///Initialize the widget with the loaded concept map
  ///BuildQtConceptMap changes the concept map entered, by changing some GUI
  ///elements (coordinats of the nodes, for example).
  ///Instead of using operator== use HasSameContent
  void BuildQtConceptMap();

  ///Remove all Qt and non-Qt items and add new ones
  virtual void CleanMe() = 0;

  ///Delete a QtEdge
  void DeleteEdge(QtEdge * const edge);

  ///Delete a Node
  void DeleteNode(QtNode * const node);

  ///Get all the edges connected to the concept
  std::vector<QtEdge*> FindEdges(const QtNode * const from) const noexcept;

  //Find the Qt edge with the same from and to
  const QtEdge * FindQtEdgeConst(const boost::shared_ptr<const Edge> edge) const noexcept;
        QtEdge * FindQtEdge(const boost::shared_ptr<      Edge> edge)       noexcept;
  const QtEdge * FindQtEdge(     const QtEdge* const edge) const noexcept { return FindQtEdgeConst(edge); }
  const QtEdge * FindQtEdgeConst(const QtEdge* const edge) const noexcept;
        QtEdge * FindQtEdge(const QtEdge* const edge)       noexcept;
  const QtEdge * FindQtEdgeConst(
    const QtNode* const from,
    const QtNode* const to) const noexcept;

  ///Find the QtNode containing the Node
  //QtNode * FindQtNode(boost::shared_ptr<Node> node) const { return FindQtNode(node.get()); }
  const QtNode * FindQtNodeConst(const Node * const node) const noexcept;
  //const QtNode * FindQtNode     (const Node * const node) const noexcept { return FindQtNodeConst(node); }
        QtNode * FindQtNode(           Node * const node)       noexcept;

  ///Obtain the center node
  const QtNode * GetCenterNode() const noexcept;

  ///Obtain the read-and-write Qt edge items
  ///The read-only Qt edge items is already supplied by QtConceptMap
  std::vector<QtEdge *> GetQtEdges();

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

  ///The concept map to work on, the Model
  const boost::shared_ptr<ConceptMap> m_concept_map;

  ///The item showing the examples
  QtExamplesItem * m_examples_item;

  ///Implemention of OnItemUpdateRequest
  virtual void OnItemRequestUpdateImpl(const QGraphicsItem* const item) = 0;

  ///The way a QtConceptMap displays its Nodes (both as nodes and on edges)
  ///- Display/read-only concept map: DisplayStrategy
  ///- Editable: EditStrategy
  ///- Rateable: RateStrategy
  virtual const boost::shared_ptr<QtItemDisplayStrategy> GetDisplayStrategy(
    const boost::shared_ptr<Concept> concept) const noexcept = 0;

public slots:

  ///Called whenever a concept is clicked or moved
  ///If item is nullptr, the last item might be deleted
  ///Use QGraphicsItem* due to QtKeyboardFriendlyGraphicsView working on QGraphicsItems
  ///Is implemented by OnItemUpdateRequestImpl
  void OnItemRequestsUpdate(const QGraphicsItem* const item);

  ///Called when an item requests a scene update
  void OnRequestSceneUpdate();

  friend class QtConceptMapWidget;
};

} //~namespace cmap
} //~namespace ribi

#endif // QTCONCEPTMAPCONCEPTMAP_H

#endif // NOT_NOW_20140810
