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
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "conceptmapedge.h"

#include <boost/lexical_cast.hpp>
#include <QRegExp>
#include "conceptmapconcept.h"
#include "conceptmapedgefactory.h"
#include "conceptmapnode.h"
#include "conceptmapcenternode.h"
#include "conceptmapconceptfactory.h"
#include "conceptmaphelper.h"
#include "trace.h"
#pragma GCC diagnostic pop

ribi::cmap::Edge::Edge(
  const boost::shared_ptr<Node>& node,
  //const double concept_x,
  //const double concept_y,
  const boost::shared_ptr<Node> from,
  const bool tail_arrow,
  const boost::shared_ptr<Node> to,
  const bool head_arrow)
  : m_signal_from_changed{},
    m_signal_head_arrow_changed{},
    m_signal_node_changed{},
    m_signal_tail_arrow_changed{},
    m_signal_to_changed{},
//    m_signal_x_changed{},
//    m_signal_y_changed{},
    m_from(from),
    m_head_arrow(head_arrow),
    m_node(node),
    m_tail_arrow(tail_arrow),
    m_to(to)
//    m_x(concept_x),
//    m_y(concept_y)
{
  #ifndef NDEBUG
  Test();
  #endif
  assert(from);
  assert(to);
  assert(from != to);
  assert(m_node);


  //Subscribe to all Concept signals to re-emit m_signal_edge_changed
  /*
  this->m_concept->m_signal_name_changed.connect(
    boost::bind(&ribi::cmap::Edge::EmitSignalEdgeChanged,this));

  this->m_concept->m_signal_examples_changed.connect(
    boost::bind(&ribi::cmap::Edge::EmitSignalEdgeChanged,this));

  this->m_concept->m_signal_rating_complexity_changed.connect(
    boost::bind(&ribi::cmap::Edge::EmitSignalEdgeChanged,this));

  this->m_concept->m_signal_rating_concreteness_changed.connect(
    boost::bind(&ribi::cmap::Edge::EmitSignalEdgeChanged,this));

  this->m_concept->m_signal_rating_specificity_changed.connect(
    boost::bind(&ribi::cmap::Edge::EmitSignalEdgeChanged,this));
  */
}

ribi::cmap::Edge::~Edge() noexcept
{
  /*
  this->m_concept->m_signal_name_changed.disconnect(
    boost::bind(&ribi::cmap::Edge::EmitSignalEdgeChanged,this));

  this->m_concept->m_signal_examples_changed.disconnect(
    boost::bind(&ribi::cmap::Edge::EmitSignalEdgeChanged,this));

  this->m_concept->m_signal_rating_complexity_changed.disconnect(
    boost::bind(&ribi::cmap::Edge::EmitSignalEdgeChanged,this));

  this->m_concept->m_signal_rating_concreteness_changed.disconnect(
    boost::bind(&ribi::cmap::Edge::EmitSignalEdgeChanged,this));

  this->m_concept->m_signal_rating_specificity_changed.disconnect(
    boost::bind(&ribi::cmap::Edge::EmitSignalEdgeChanged,this));
  */
}

/*
void ribi::cmap::Edge::EmitSignalEdgeChanged()
{
  m_signal_edge_changed(this);
}
*/

std::string ribi::cmap::Edge::GetVersion() noexcept
{
  return "1.1";
}

std::vector<std::string> ribi::cmap::Edge::GetVersionHistory() noexcept
{
  return {
    "2013-xx-xx: Version 1.0: initial version",
    "2014-06-01: Version 1.1: replaced Concept, X and Y by a Node"
  };
}

void ribi::cmap::Edge::SetNode(const boost::shared_ptr<Node>& node) noexcept
{
  assert(node);
  if (m_node != node)
  {
    m_node = node;
    m_signal_node_changed(this);
  }
}

void ribi::cmap::Edge::SetFrom(const boost::shared_ptr<ribi::cmap::Node> from) noexcept
{
  assert(from);
  if (m_from != from)
  {
    m_from = from;
    m_signal_from_changed(this);
  }
}

void ribi::cmap::Edge::SetHeadArrow(const bool has_head_arrow) noexcept
{
  if (m_head_arrow != has_head_arrow)
  {
    m_head_arrow = has_head_arrow;
    m_signal_head_arrow_changed(this);
  }
}

void ribi::cmap::Edge::SetTailArrow(const bool has_tail_arrow) noexcept
{
  if (m_tail_arrow != has_tail_arrow)
  {
    m_tail_arrow = has_tail_arrow;
    m_signal_tail_arrow_changed(this);
  }
}

void ribi::cmap::Edge::SetTo(const boost::shared_ptr<ribi::cmap::Node> to) noexcept
{
  assert(to);
  if (m_to != to)
  {
    m_to = to;
    m_signal_to_changed(this);
  }
}

/*
void ribi::cmap::Edge::SetX(const double x) noexcept
{
  if (m_x != x)
  {
    m_x = x;
    m_signal_x_changed(this);
  }
}

void ribi::cmap::Edge::SetY(const double y) noexcept
{
  if (m_y != y)
  {
    m_y = y;
    m_signal_y_changed(this);
  }
}
*/

#ifndef NDEBUG
void ribi::cmap::Edge::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  //Test member variables
  TRACE("Started ribi::cmap::Edge::Test");
  {
    const auto nodes = Node::GetTests();
    assert(nodes.size() >= 2);
    const auto node_from = nodes[0];
    const auto node_to   = nodes[1];
    for (const boost::shared_ptr<const cmap::Edge>& edge: EdgeFactory().GetTests(node_from,node_to))
    {
      //Test copy constructor
      assert(edge);
      const boost::shared_ptr<const cmap::Edge> c = EdgeFactory().DeepCopy(edge,node_from,node_to);
      assert(c);
      assert(*edge == *c);
      assert(*c == *edge);
      assert(*c->GetFrom() == *node_from);
      assert(*c->GetFrom() == *nodes[0]);
      assert(*c->GetTo() == *node_to);
      assert(*c->GetTo() == *nodes[1]);
      const std::string s = ToXml(c,AddConst(nodes));
      const boost::shared_ptr<ribi::cmap::Edge> d = EdgeFactory().FromXml(s,nodes);
      assert(d);
      if (*c != *d)
      {
        TRACE("ERROR");
        TRACE(ToXml(c,AddConst(nodes)));
        TRACE(ToXml(d,AddConst(nodes)));
      }
      assert(*c == *d);
    }
  }
  TRACE("Edge::Test finished successfully");
}
#endif

std::string ribi::cmap::Edge::ToStr() const noexcept
{
  std::stringstream s;
  s
    //<< GetX() << " "
    //<< GetY() << " "
    << HasHeadArrow() << " "
    << GetNode()->ToStr() << " "
    << HasTailArrow() << " "
    << GetFrom()->ToStr() << " "
    << GetTo()->ToStr()
  ;
  return s.str();
}

std::string ribi::cmap::Edge::ToXml(
  const boost::shared_ptr<const cmap::Edge>& edge,
  const std::vector<boost::shared_ptr<const cmap::Node> >& nodes
) noexcept
{
  std::stringstream s;
  s << "<edge>";
  s << edge->GetNode()->GetConcept()->ToXml();

  const auto from_iter = std::find(nodes.begin(),nodes.end(),edge->GetFrom());
  const auto to_iter = std::find(nodes.begin(),nodes.end(),edge->GetTo());
  assert(from_iter != nodes.end());
  assert(to_iter != nodes.end());
  const int from_index = std::distance(nodes.begin(),from_iter);
  const int to_index = std::distance(nodes.begin(),to_iter);
  assert(from_index >= 0);
  assert(from_index < boost::numeric_cast<int>(nodes.size()));
  assert(to_index >= 0);
  assert(to_index < boost::numeric_cast<int>(nodes.size()));
  assert(from_index != to_index);

  s << "<from>" << from_index << "</from>";
  s << "<head_arrow>" << edge->HasHeadArrow() << "</head_arrow>";
  s << "<tail_arrow>" << edge->HasTailArrow() << "</tail_arrow>";
  s << "<to>" << to_index << "</to>";
  s << "<x>" << edge->GetNode()->GetX() << "</x>";
  s << "<y>" << edge->GetNode()->GetY() << "</y>";
  s << "</edge>";

  const std::string r = s.str();
  assert(r.size() >= 13);
  assert(r.substr(0,6) == "<edge>");
  assert(r.substr(r.size() - 7,7) == "</edge>");

  return r;
}

bool ribi::cmap::IsConnectedToCenterNode(const boost::shared_ptr<const Edge> edge) noexcept
{
  assert(!(IsCenterNode(edge->GetFrom()) && IsCenterNode(edge->GetTo()))
    && "An Edge cannot be connected to two CenterNodes");
  return IsCenterNode(edge->GetFrom()) || IsCenterNode(edge->GetTo());

}

bool ribi::cmap::operator==(const ribi::cmap::Edge& lhs, const ribi::cmap::Edge& rhs)
{
  assert(lhs.GetNode()); assert(rhs.GetNode());
  #ifndef NDEBUG
  if (*lhs.GetNode()   != *rhs.GetNode()) TRACE("Node differs");
  if (*lhs.GetFrom()      != *rhs.GetFrom()) TRACE("From node differs");
  if (*lhs.GetTo()        != *rhs.GetTo()) TRACE("To node differs");
  //if ( lhs.GetX()         != rhs.GetX()) TRACE("X differs");
  //if ( lhs.GetY()         != rhs.GetY()) TRACE("Y differs");
  if ( lhs.HasHeadArrow() != rhs.HasHeadArrow()) TRACE("Has head arrow differs");
  if ( lhs.HasTailArrow() != rhs.HasTailArrow()) TRACE("Has tail arrow differs");
  #endif
  return
       *lhs.GetNode()   == *rhs.GetNode()
    && *lhs.GetFrom()      == *rhs.GetFrom()
    && *lhs.GetTo()        == *rhs.GetTo()
    //&&  lhs.GetX()         == rhs.GetX()
    //&&  lhs.GetY()         == rhs.GetY()
    &&  lhs.HasHeadArrow() == rhs.HasHeadArrow()
    &&  lhs.HasTailArrow() == rhs.HasTailArrow()
  ;
}

bool ribi::cmap::operator!=(const cmap::Edge& lhs, const cmap::Edge& rhs)
{
  return !(lhs == rhs);
}
