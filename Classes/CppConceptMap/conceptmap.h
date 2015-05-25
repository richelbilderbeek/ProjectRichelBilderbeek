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
  typedef boost::shared_ptr<ConceptMap> ConceptMapPtr;
  typedef boost::shared_ptr<const ConceptMap> ReadOnlyConceptMapPtr;
  typedef boost::shared_ptr<Edge> EdgePtr;
  typedef boost::shared_ptr<const Edge> ReadOnlyEdgePtr;
  typedef boost::shared_ptr<Node> NodePtr;
  typedef boost::shared_ptr<const Node> ReadOnlyNodePtr;
  typedef boost::shared_ptr<CenterNode> CenterNodePtr;
  typedef boost::shared_ptr<const CenterNode> ReadOnlyCenterNodePtr;
  typedef std::vector<ConceptMapPtr> ConceptMaps;
  typedef std::vector<EdgePtr> Edges;
  typedef std::vector<ReadOnlyEdgePtr> ReadOnlyEdges;
  typedef std::vector<NodePtr> Nodes;
  typedef std::vector<ReadOnlyNodePtr> ReadOnlyNodes;
  typedef ConceptMaps SubConceptMaps; //Just to let the code speak more for itself

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
  void DeleteNode(const NodePtr& node) noexcept;

  ///Check if the ConceptMap is empty, that is: it has no nodes and (thus) no edges
  bool Empty() const noexcept;

  ///Find the CenterNode, if any
  ReadOnlyCenterNodePtr FindCenterNode() const noexcept;
  CenterNodePtr FindCenterNode() noexcept;

  ReadOnlyEdges GetEdges() const noexcept;
  Edges& GetEdges() noexcept { return m_edges; }

  ///Get the focal node (always at index zero)
  ReadOnlyNodePtr GetFocalNode() const noexcept;
  NodePtr GetFocalNode() noexcept;

  ReadOnlyNodes GetNodes() const noexcept;
  Nodes& GetNodes() noexcept { return m_nodes; }

  //Use this instead:
  //  assert(FindCenterNode());
  //  assert(FindCenterNode()->GetConcept());
  //  return FindCenterNode()->GetConcept()->GetName();
  //
  //std::string GetQuestion() const noexcept

  static std::string GetVersion() noexcept;
  static std::vector<std::string> GetVersionHistory() noexcept;

  bool HasNode(const ReadOnlyNodePtr& node) const noexcept;
  //const std::vector<boost::shared_ptr<      Node>>& GetNodes() { return m_nodes; }

  ///Similar to operator==, except that the GUI member variables aren't checked for equality
  static bool HasSameContent(const ConceptMap& lhs, const ConceptMap& rhs) noexcept;

  #ifndef NDEBUG
  ///Check if there are no nulls in the edges and nodes
  bool IsValid() const noexcept;
  #endif

  ///Convert a ConceptMap from an XML std::string
  static std::string ToXml(const ReadOnlyConceptMapPtr& c) noexcept;

private:

  ///The edges
  Edges m_edges;

  ///The nodes
  Nodes m_nodes;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif

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
