//---------------------------------------------------------------------------
/*
ConceptMap, concept map classes
Copyright (C) 2013-2014 Richel Bilderbeek

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
#ifndef CONCEPTMAPEDGE_H
#define CONCEPTMAPEDGE_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <boost/shared_ptr.hpp>
#include <boost/signals2.hpp>
#include "conceptmapfwd.h"
#include "conceptmapelement.h"
#pragma GCC diagnostic pop


namespace ribi {
namespace cmap {

struct EdgeFactory;

///An Edge is the GUI-independent part of the edges used in QtConceptMap.
///An Edge goes from one Node to another, which must a different Node,
/// at the center of the Edge is a Node
struct Edge : public Element
{
  typedef boost::shared_ptr<const Edge> ReadOnlyEdgePtr;
  typedef boost::shared_ptr<Edge> EdgePtr;
  typedef boost::shared_ptr<const Node> ReadOnlyNodePtr;
  typedef boost::shared_ptr<Node> NodePtr;
  typedef std::vector<ReadOnlyNodePtr> ReadOnlyNodes;
  typedef std::vector<NodePtr> Nodes;

  Edge(const Edge&) = delete;
  Edge& operator=(const Edge&) = delete;
  ReadOnlyNodePtr GetNode() const noexcept { return m_node; }
  NodePtr GetNode()       noexcept { return m_node; }

  ///Get the Node this edge originates from
  ReadOnlyNodePtr GetFrom() const noexcept { return m_from; }
  NodePtr GetFrom()       noexcept { return m_from; }

  ///Get the Node index this edge goes to
  ReadOnlyNodePtr GetTo() const noexcept { return m_to; }
  NodePtr GetTo()       noexcept { return m_to; }

  static std::string GetVersion() noexcept;
  static std::vector<std::string> GetVersionHistory() noexcept;

  ///Does the edge have an arrow at the head?
  bool HasHeadArrow() const noexcept { return m_head_arrow; }

  ///Does the edge have an arrow at the tail?
  bool HasTailArrow() const noexcept { return m_tail_arrow; }

  ///Set the Node index this edge originates from
  //void SetFrom(const NodePtr& from) noexcept;

  ///Set if the head has an arrow
  void SetHeadArrow(const bool has_head_arrow) noexcept;

  ///Set the center Node
  void SetNode(const NodePtr& node) noexcept;

  ///Set if the tail has an arrow
  void SetTailArrow(const bool has_tail_arrow) noexcept;

  ///Set the Node index this edge goes to
  //void SetTo(const NodePtr& to) noexcept;

  std::string ToStr() const noexcept;

  ///Convert an Edge from an XML std::string
  ///The container of nodes is needed to convert the 'to' and 'from'
  ///field to indices
  static std::string ToXml(
    const ReadOnlyEdgePtr& c,
    const ReadOnlyNodes& nodes
    ) noexcept;

  ///Emitted when an Edge attribute has changed
  boost::signals2::signal<void (Edge*)> m_signal_from_changed;
  boost::signals2::signal<void (Edge*)> m_signal_head_arrow_changed;
  mutable boost::signals2::signal<void (Edge*)> m_signal_node_changed;
  boost::signals2::signal<void (Edge*)> m_signal_tail_arrow_changed;
  boost::signals2::signal<void (Edge*)> m_signal_to_changed;

  private:
  ///The Node this edge originates from
  const NodePtr m_from;

  ///Is there an arrowhead at the 'to' node?
  bool m_head_arrow;

  ///The Node on the Edge
  NodePtr m_node;

  ///Is there an arrowhead at the 'from' node?
  bool m_tail_arrow;

  ///The Node this edge goes to
  const NodePtr m_to;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif

  Edge() = delete;

  ///Block destructor, except for the friend boost::checked_delete
  ~Edge() noexcept;
  friend void boost::checked_delete<>(      Edge*);
  friend void boost::checked_delete<>(const Edge*);

  ///Block constructor, except for EdgeFactory
  friend class EdgeFactory;
  explicit Edge(
    const NodePtr& node,
    const NodePtr& from,
    const bool tail_arrow,
    const NodePtr& to,
    const bool head_arrow
  );

  ///Bundles Node its signals into emitting a signal that the node has changed
  void OnConceptChanged(Node * const node) noexcept;
  void OnFromChanged(Node * const node) noexcept;
  void OnToChanged(Node * const node) noexcept;
};

bool IsConnectedToCenterNode(const boost::shared_ptr<const Edge> edge) noexcept;

std::ostream& operator<<(std::ostream& os, const Edge& edge) noexcept;

bool operator==(const Edge& lhs, const Edge& rhs);
bool operator!=(const Edge& lhs, const Edge& rhs);

bool operator<(const boost::shared_ptr<      Edge>& lhs, const boost::shared_ptr<      Edge>& rhs) = delete;
bool operator<(const boost::shared_ptr<const Edge>& lhs, const boost::shared_ptr<      Edge>& rhs) = delete;
bool operator<(const boost::shared_ptr<      Edge>& lhs, const boost::shared_ptr<const Edge>& rhs) = delete;
bool operator<(const boost::shared_ptr<const Edge>& lhs, const boost::shared_ptr<const Edge>& rhs) = delete;

} //~namespace cmap
} //~namespace ribi

#endif // CONCEPTMAPEDGE_H
