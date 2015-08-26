//---------------------------------------------------------------------------
/*
ConceptMap, concept map classes
Copyright (C) 2013-2015 Richel Bilderbeek

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program. If not, see <http://www.gnu.org/licenses/>.
*/
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/CppConceptMap.htm
//---------------------------------------------------------------------------
#ifndef CONCEPTMAPCONCEPTMAP_H
#define CONCEPTMAPCONCEPTMAP_H

#include <string>
#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <boost/shared_ptr.hpp>
#include <boost/signals2.hpp>
#include <QPointF>
#include "conceptmapfwd.h"
#pragma GCC diagnostic pop

namespace ribi {
namespace cmap {

struct ConceptMapFactory;

///A concept map
///Its interface is based on nodes and edges
///Use ConceptMapWidget to work with commands
struct ConceptMap
{
  using CenterNodePtr = boost::shared_ptr<CenterNode> ;
  using ConceptMapPtr = boost::shared_ptr<ConceptMap>;
  using ConceptMaps = std::vector<ConceptMapPtr>;
  using ConstEdges = std::vector<boost::shared_ptr<const Edge>>;
  using ConstNodes = std::vector<boost::shared_ptr<const Node>>;
  using ConstEdgesAndNodes = std::pair<ConstEdges,ConstNodes>;
  using EdgePtr = boost::shared_ptr<Edge>;
  using Edges = std::vector<boost::shared_ptr<Edge>>;
  using NodePtr = boost::shared_ptr<Node>;
  using Nodes = std::vector<boost::shared_ptr<Node>>;
  using EdgesAndNodes = std::pair<Edges,Nodes>;
  using ReadOnlyCenterNodePtr = boost::shared_ptr<const CenterNode>;
  using ReadOnlyConceptMapPtr = boost::shared_ptr<const ConceptMap>;
  using ReadOnlyEdgePtr = boost::shared_ptr<const Edge>;
  using ReadOnlyEdges = std::vector<ReadOnlyEdgePtr>;
  using ReadOnlyNodePtr = boost::shared_ptr<const Node>;
  using ReadOnlyNodes = std::vector<ReadOnlyNodePtr>;
  using SubConceptMaps = ConceptMaps; //Just to let the code speak more for itself

  ConceptMap(const ConceptMap&) = delete;
  ConceptMap& operator=(const ConceptMap&) = delete;

  //Add an Edge, assumes that the nodes it points to are in the concept map
  void AddEdge(const EdgePtr& edge) noexcept;

  //Add a node, always works
  void AddNode(const NodePtr& node) noexcept;

  ///Test if this ConceptMap can be constructed successfully
  static bool CanConstruct(
    const Nodes& nodes,
    const Edges& edges
  ) noexcept;

  bool CanDoCommand(const boost::shared_ptr<const Command> command) const noexcept;
  bool CanUndo() const noexcept { return !m_undo.empty(); }

  ///Prepend the question as a first node, before adding the supplied nodes
  static std::vector<NodePtr> CreateNodes(
    const std::string& question,
    const Nodes& nodes
  ) noexcept;

  ///Create all sub-conceptmaps
  ///Note that CreateSubs()[0] is the concept map around the focal question
  SubConceptMaps CreateSubs() const noexcept;

  ///Delete an edge
  void DeleteEdge(const EdgePtr& edge) noexcept;

  ///Delete a node and all the edges connected to it
  void DeleteNode(const ReadOnlyNodePtr& node) noexcept;
  void DeleteNode(const NodePtr& node) noexcept;

  void DoCommand(const boost::shared_ptr<Command> command) noexcept;

  ///Check if the ConceptMap is empty, that is: it has no nodes and (thus) no edges
  bool Empty() const noexcept;

  ///Find the CenterNode, if any
  ReadOnlyCenterNodePtr FindCenterNode() const noexcept;
  CenterNodePtr FindCenterNode() noexcept;

  ///There is one item in focus at most
  ///There can be multiple items selected
  ///The node in focus is never in the collection of selected nodes
  ///Use GetFocusAndSelected to get all
  boost::shared_ptr<const Node> GetFocus() const noexcept;
  boost::shared_ptr<      Node> GetFocus()       noexcept;

  ReadOnlyEdges GetEdges() const noexcept;
  Edges& GetEdges() noexcept { return m_edges; }

  ///Get the focal node (always at index zero)
  ReadOnlyNodePtr GetFocalNode() const noexcept;
  NodePtr GetFocalNode() noexcept;

  ReadOnlyNodes GetNodes() const noexcept;
  Nodes& GetNodes() noexcept { return m_nodes; }

  ///There can be multiple items selected
  ///There is one item in focus at most
  ///The node in focus is never in the collection of selected nodes
  ///Use GetFocusAndSelected to get all
  ConstEdgesAndNodes GetSelected() const noexcept;
       EdgesAndNodes GetSelected()       noexcept { return m_selected; }

  ConstEdges GetSelectedEdges() const noexcept;
       Edges GetSelectedEdges()       noexcept { return m_selected.first; }

  ConstNodes GetSelectedNodes() const noexcept;
       Nodes GetSelectedNodes()       noexcept { return m_selected.second; }

  ///Obtain the version
  static std::string GetVersion() noexcept;

  ///Obtain the version history
  static std::vector<std::string> GetVersionHistory() noexcept;

  bool HasEdge(const ReadOnlyEdgePtr& edge) const noexcept;
  bool HasNode(const ReadOnlyNodePtr& node) const noexcept;
  //const std::vector<boost::shared_ptr<      Node>>& GetNodes() { return m_nodes; }

  ///Similar to operator==, except that the GUI member variables aren't checked for equality
  static bool HasSameContent(const ConceptMap& lhs, const ConceptMap& rhs) noexcept;


  #ifndef NDEBUG
  ///Check if there are no nulls in the edges and nodes
  bool IsValid() const noexcept;
  #endif


  void MouseMoveEvent(const QPointF& mouse_pos) noexcept;

  ///Set the nodes to the only nodes selected
  void SetSelected(const ConstNodes& nodes) noexcept;
  void SetSelected(const ConstEdges& edges) noexcept;
  void SetSelected(const Nodes& nodes) noexcept;
  void SetSelected(const Edges& edges) noexcept;
  void SetSelected(const Edges& edges,const Nodes& nodes) noexcept;
  void SetSelected(const ConstEdges& edges,const ConstNodes& nodes) noexcept;
  void SetSelected(const ConstEdgesAndNodes& edges_and_nodes) noexcept;

  ///Convert a ConceptMap from an XML std::string
  static std::string ToXml(const ReadOnlyConceptMapPtr& c) noexcept;

  void Undo() noexcept;

  ///Emitted when an Edge is added
  ///This has to be handled by QtConceptMapWidget
  boost::signals2::signal<void(boost::shared_ptr<Edge>)> m_signal_add_edge;

  ///Emitted when a Node is added
  ///This has to be handled by QtConceptMapWidget
  boost::signals2::signal<void(boost::shared_ptr<Node>)> m_signal_add_node;

  ///Emitted when the ConceptMap is modified as a whole: deleted, created or overwritten
  boost::signals2::signal<void()> m_signal_concept_map_changed;

  ///Emitted when an Edge is deleted
  ///This has to be handled by QtConceptMapWidget
  boost::signals2::signal<void(boost::shared_ptr<Edge>)> m_signal_delete_edge;

  ///Emitted when a Node is deleted
  ///This has to be handled by QtConceptMapWidget
  boost::signals2::signal<void(const ReadOnlyNodePtr)> m_signal_delete_node;

  ///Emitted when a Node loses focus
  ///This has to be handled by QtConceptMapWidget
  boost::signals2::signal<void(boost::shared_ptr<Node>)> m_signal_lose_focus;

  ///Emitted when one or more Nodes lose to be selected
  ///This has to be handled by QtConceptMapWidget
  boost::signals2::signal<void(const ConstEdges&, const ConstNodes&)> m_signal_lose_selected;

  ///Emitted when a Node receives focus
  ///This has to be handled by QtConceptMapWidget
  //boost::signals2::signal<void(boost::shared_ptr<Node>)> m_signal_set_focus;

  ///Emitted when multiple Nodes are selected
  ///This has to be handled by QtConceptMapWidget
  boost::signals2::signal<void(const Edges&, const Nodes&)> m_signal_set_selected;

private:

  ///The edges
  Edges m_edges;

  ///The nodes
  Nodes m_nodes;

  ///The elements in focus, if any. These might be:
  ///- a true Node
  ///- the label in the middle of an edge
  ///- the CenterNode
  boost::shared_ptr<Node> m_focus;


  const int m_font_height;
  const int m_font_width;

  QPointF m_mouse_pos;

  ///The elements selected
  ///- a true Node
  ///- the label in the middle of an edge
  ///- the CenterNode
  EdgesAndNodes m_selected;

  ///The undo stack (use std::vector because it is a true STL container)
  ///The Commands aren't const, because Command::Undo changes their state
  std::vector<boost::shared_ptr<Command>> m_undo;

  ///Add the nodes to the current (can be zero) selected nodes
  void AddSelected(const Edges& edges) noexcept;
  void AddSelected(const Nodes& nodes) noexcept;
  void AddSelected(const Edges& edges,const Nodes& nodes) noexcept;

  static boost::shared_ptr<ConceptMap> CreateEmptyConceptMap() noexcept;

  ///Creates a new Node in the concept map. The return value is
  ///that node. This is used by CommandCreateNode::Undo
  boost::shared_ptr<Edge> CreateNewEdge() noexcept;

  ///Creates a new Node in the concept map. The return value is
  ///that node. This is used by CommandCreateNode::Undo
  boost::shared_ptr<Node> CreateNewNode() noexcept;


  ///Find a Node at a coordinat
  ///Returns nullptr if none is present
  boost::shared_ptr<      Node> FindNodeAt(const double x, const double y)       noexcept;
  boost::shared_ptr<const Node> FindNodeAt(const double x, const double y) const noexcept;

  ///Lose the current focus, assumes something has focus
  void LoseFocus() noexcept;

  ///Used by CommandAddFocusRandom and CommandSetFocusRandom
  ///Of all the concept maps its nodes, except for the uses supplied as the
  ///argument, return 1 to all the nodes, except when there is no node
  ///left (as all are excluded) or the concept map does not have any nodes
  std::vector<boost::shared_ptr<Edge>> GetRandomEdges(std::vector<boost::shared_ptr<const Edge>> edges_to_exclude = {}) noexcept;
  boost::shared_ptr<Edge> GetRandomEdge(std::vector<boost::shared_ptr<const Edge>> edges_to_exclude = {}) noexcept;


  ///Used by CommandAddFocusRandom and CommandSetFocusRandom
  ///Of all the concept maps its nodes, except for the uses supplied as the
  ///argument, return 1 to all the nodes, except when there is no node
  ///left (as all are excluded) or the concept map does not have any nodes
  std::vector<boost::shared_ptr<Node>> GetRandomNodes(std::vector<boost::shared_ptr<const Node>> nodes_to_exclude = {}) noexcept;
  boost::shared_ptr<Node> GetRandomNode(std::vector<boost::shared_ptr<const Node>> nodes_to_exclude = {}) noexcept;

  ///Called by m_undo its top command when it calles Undo itself,
  ///by which the Command indicates that it must be removed from that m_undo vector
  void OnUndo(const Command * const command_to_remove) noexcept;


  #ifndef NDEBUG
  static void Test() noexcept;
  #endif

  ///Unselect the node, assumes it is selected

  void Unselect(const ConstEdgesAndNodes& edges_and_nodes) noexcept;
  void Unselect(const ConstEdges& edges) noexcept;
  void Unselect(const ConstNodes& nodes) noexcept;

  ///Block constructor, except for the friend ConceptMapFactory
  ConceptMap(const std::string& question) noexcept;

  //Nodes[0] must be the focal question
  explicit ConceptMap(
    const Nodes& nodes = {},
    const Edges& edges = {}
  ) noexcept;
  ///Create a concept map from a cluster
  #ifdef TO_ADD_TO_PROJECTBRAINWEAVER
  ConceptMap(
    const std::string& question,
    const boost::shared_ptr<cmap::Cluster>& cluster);
  #endif

  ///To make the compiler use the const version
  ReadOnlyCenterNodePtr FindCenterNodeConst() const noexcept { return FindCenterNode(); }
  ///To make the compiler use the const version
  ReadOnlyNodePtr GetFocalNodeConst() const noexcept { return GetFocalNode(); }

  friend ConceptMapFactory;
  ///Block destructor, except for the friend boost::checked_delete
  ~ConceptMap() noexcept;
  friend void boost::checked_delete<>(ConceptMap* x);
  friend void boost::checked_delete<>(const ConceptMap* x);

  //friend class Command;
  friend class CommandAddSelectedRandom;
  friend class CommandCreateNewConceptMap;
  friend class CommandCreateNewEdge;
  friend class CommandCreateNewNode;
  friend class CommandDeleteConceptMap;
  friend class CommandDeleteFocusNode;
  friend class CommandDeleteNode;
  friend class CommandLoseFocus;
  friend class CommandSetFocusRandom;
  friend class CommandSetSelectedWithCoordinat;
  friend class CommandUnselectRandom;
  friend bool operator==(const ConceptMap& lhs, const ConceptMap& rhs) noexcept;

};

///Count the number of CenterNodes
///- regular concept map: 1, the focus
///- sub-concept map: 0 or 1, if the focus is connected to the sub's focus node
int CountCenterNodes(const boost::shared_ptr<const ConceptMap>& conceptmap) noexcept;

///Count the number of Edges connected to a CenterNodes
int CountCenterNodeEdges(const boost::shared_ptr<const ConceptMap>& conceptmap) noexcept;

bool operator==(const ConceptMap& lhs, const ConceptMap& rhs) noexcept;
bool operator!=(const ConceptMap& lhs, const ConceptMap& rhs) noexcept;

} //~namespace cmap
} //~namespace ribi

#endif // CONCEPTMAPCONCEPTMAP_H
