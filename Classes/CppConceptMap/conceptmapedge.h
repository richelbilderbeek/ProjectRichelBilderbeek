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
///An Edge goes from one Node to another, which must a different Node
struct Edge : public Element
{
  Edge(const Edge&) = delete;
  Edge& operator=(const Edge&) = delete;
  boost::shared_ptr<const Concept> GetConcept() const noexcept { return m_concept; }
  boost::shared_ptr<      Concept> GetConcept()       noexcept { return m_concept; }

  ///Get the Node this edge originates from
  boost::shared_ptr<const Node> GetFrom() const noexcept { return m_from; }
  boost::shared_ptr<      Node> GetFrom()       noexcept { return m_from; }

  ///Get the Node index this edge goes to
  boost::shared_ptr<const Node> GetTo() const noexcept { return m_to; }
  boost::shared_ptr<      Node> GetTo()       noexcept { return m_to; }

  ///Get the x coordinat
  double GetX() const noexcept { return m_x; }

  ///Get the y coordinat
  double GetY() const noexcept { return m_y; }

  ///Does the edge have an arrow at the head?
  bool HasHeadArrow() const noexcept { return m_head_arrow; }

  //Similar to operator==, except that the coordinats are not checked
  static bool HasSameContent(const boost::shared_ptr<const Edge>& lhs, const boost::shared_ptr<const Edge>& rhs) noexcept;

  ///Does the edge have an arrow at the tail?
  bool HasTailArrow() const noexcept { return m_tail_arrow; }

  ///Set the concept
  void SetConcept(const boost::shared_ptr<Concept>& concept) noexcept;

  ///Set the Node index this edge originates from
  void SetFrom(const boost::shared_ptr<Node> from) noexcept;

  ///Set if the head has an arrow
  void SetHeadArrow(const bool has_head_arrow) noexcept;

  ///Set the coordinat of the concept at the center of the node
  void SetPos(const double x, const double y) noexcept { SetX(x); SetY(y); }

  ///Set if the tail has an arrow
  void SetTailArrow(const bool has_tail_arrow) noexcept;

  ///Set the Node index this edge goes to
  void SetTo(const boost::shared_ptr<Node> to) noexcept;

  ///Set the x coordinat of the concept at the center of the node
  void SetX(const double x) noexcept;

  ///Set the y coordinat of the concept at the center of the node
  void SetY(const double y) noexcept;

  std::string ToStr() const noexcept;

  ///Convert an Edge from an XML std::string
  ///The container of nodes is needed to convert the 'to' and 'from'
  ///field to indices
  static std::string ToXml(
    const boost::shared_ptr<const Edge>& c,
    const std::vector<boost::shared_ptr<const Node>>& nodes
    ) noexcept;

  ///Emitted when an Edge attribute has changed
  boost::signals2::signal<void (Edge*)> m_signal_concept_changed;
  boost::signals2::signal<void (Edge*)> m_signal_from_changed;
  boost::signals2::signal<void (Edge*)> m_signal_head_arrow_changed;
  boost::signals2::signal<void (Edge*)> m_signal_tail_arrow_changed;
  boost::signals2::signal<void (Edge*)> m_signal_to_changed;
  boost::signals2::signal<void (Edge*)> m_signal_x_changed;
  boost::signals2::signal<void (Edge*)> m_signal_y_changed;

  private:

  ///The Concept on the Edge
  boost::shared_ptr<Concept> m_concept;

  ///The Node this edge originates from
  boost::shared_ptr<Node> m_from;

  ///Is there an arrowhead at the 'to' node?
  bool m_head_arrow;

  ///Is there an arrowhead at the 'from' node?
  bool m_tail_arrow;

  ///The Node this edge goes to
  boost::shared_ptr<Node> m_to;

  ///The x-coordinat
  double m_x;

  ///The y-coordinat
  double m_y;

  //void EmitSignalEdgeChanged();

  #ifndef NDEBUG
  ///Test this class
  static void Test() noexcept;
  #endif

  Edge() = delete;

  ///Block destructor, except for the friend boost::checked_delete
  ~Edge() noexcept;
  friend void boost::checked_delete<>(      Edge*);
  friend void boost::checked_delete<>(const Edge*);

  ///Block constructor, except for EdgeFactory
  friend EdgeFactory;
  Edge(
    const boost::shared_ptr<Concept> & concept,
    const double concept_x,
    const double concept_y,
    const boost::shared_ptr<Node> from,
    const bool tail_arrow,
    const boost::shared_ptr<Node> to,
    const bool head_arrow);

};

bool IsConnectedToCenterNode(const boost::shared_ptr<const Edge> edge) noexcept;

bool operator==(const Edge& lhs, const Edge& rhs);
bool operator!=(const Edge& lhs, const Edge& rhs);

bool operator<(
  const boost::shared_ptr<Edge>& lhs,
  const boost::shared_ptr<Edge>& rhs) = delete;
bool operator<(
  const boost::shared_ptr<const Edge>& lhs,
  const boost::shared_ptr<      Edge>& rhs) = delete;
bool operator<(
  const boost::shared_ptr<      Edge>& lhs,
  const boost::shared_ptr<const Edge>& rhs) = delete;
bool operator<(
  const boost::shared_ptr<const Edge>& lhs,
  const boost::shared_ptr<const Edge>& rhs) = delete;

} //~namespace cmap
} //~namespace ribi

#endif // CONCEPTMAPEDGE_H
