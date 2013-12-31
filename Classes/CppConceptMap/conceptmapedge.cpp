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
  const boost::shared_ptr<ribi::cmap::Concept> & concept,
  const double concept_x,
  const double concept_y,
  const boost::shared_ptr<ribi::cmap::Node> from,
  const bool tail_arrow,
  const boost::shared_ptr<ribi::cmap::Node> to,
  const bool head_arrow)
  : m_signal_edge_changed{},
    m_concept(concept),
    m_from(from),
    m_head_arrow(head_arrow),
    m_tail_arrow(tail_arrow),
    m_to(to),
    m_x(concept_x),
    m_y(concept_y)
{
  #ifndef NDEBUG
  Test();
  #endif
  assert(from);
  assert(to);
  assert(from != to);
  assert(m_concept);



  //Subscribe to all Concept signals to re-emit m_signal_edge_changed
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
}

void ribi::cmap::Edge::EmitSignalEdgeChanged()
{
  m_signal_edge_changed(this);
}

void ribi::cmap::Edge::SetFrom(const boost::shared_ptr<ribi::cmap::Node> from)
{
  assert(from);
  if (m_from != from)
  {
    m_from = from;
    m_signal_edge_changed(this);
  }
}

void ribi::cmap::Edge::SetHeadArrow(const bool has_head_arrow)
{
  if (m_head_arrow != has_head_arrow)
  {
    m_head_arrow = has_head_arrow;
    m_signal_edge_changed(this);
  }
}

void ribi::cmap::Edge::SetTailArrow(const bool has_tail_arrow)
{
  if (m_tail_arrow != has_tail_arrow)
  {
    m_tail_arrow = has_tail_arrow;
    m_signal_edge_changed(this);
  }
}

void ribi::cmap::Edge::SetTo(const boost::shared_ptr<ribi::cmap::Node> to)
{
  assert(to);
  if (m_to != to)
  {
    m_to = to;

    m_signal_edge_changed(this);
  }
}

void ribi::cmap::Edge::SetX(const double x)
{
  if (m_x != x)
  {
    m_x = x;
    m_signal_edge_changed(this);
  }
}

void ribi::cmap::Edge::SetY(const double y)
{
  if (m_y != y)
  {
    m_y = y;
    m_signal_edge_changed(this);
  }
}

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
    for (const boost::shared_ptr<const cmap::Edge>& edge: EdgeFactory::GetTests(node_from,node_to))
    {
      //Test copy constructor
      assert(edge);
      const boost::shared_ptr<const cmap::Edge> c = cmap::EdgeFactory::DeepCopy(edge,node_from,node_to);
      assert(c);
      assert(*edge == *c);
      assert(*c == *edge);
      assert(*c->GetFrom() == *node_from);
      assert(*c->GetFrom() == *nodes[0]);
      assert(*c->GetTo() == *node_to);
      assert(*c->GetTo() == *nodes[1]);
      const std::string s = ToXml(c,AddConst(nodes));
      const boost::shared_ptr<ribi::cmap::Edge> d = cmap::EdgeFactory::FromXml(s,nodes);
      assert(d);
      if (*c != *d)
      {
        TRACE("BREAK");
        TRACE(ToXml(c,AddConst(nodes)));
        TRACE(ToXml(d,AddConst(nodes)));
      }
      assert(*c == *d);
    }
  }
  TRACE("Edge::Test finished successfully");
}
#endif

const std::string ribi::cmap::Edge::ToXml(
  const boost::shared_ptr<const cmap::Edge>& edge,
  const std::vector<boost::shared_ptr<const cmap::Node> >& nodes)
{
  std::stringstream s;
  s << "<edge>";
  s << Concept::ToXml(edge->GetConcept());

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
  s << "<x>" << edge->GetX() << "</x>";
  s << "<y>" << edge->GetY() << "</y>";
  s << "</edge>";

  const std::string r = s.str();
  assert(r.size() >= 13);
  assert(r.substr(0,6) == std::string("<edge>"));
  assert(r.substr(r.size() - 7,7) == std::string("</edge>"));

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
  assert(lhs.GetConcept()); assert(rhs.GetConcept());
  #ifndef NDEBUG
  if (*lhs.GetConcept()   != *rhs.GetConcept()) TRACE("Concept differs");
  if (*lhs.GetFrom()      != *rhs.GetFrom()) TRACE("From node differs");
  if (*lhs.GetTo()        != *rhs.GetTo()) TRACE("To node differs");
  if ( lhs.GetX()         != rhs.GetX()) TRACE("X differs");
  if ( lhs.GetY()         != rhs.GetY()) TRACE("Y differs");
  if ( lhs.HasHeadArrow() != rhs.HasHeadArrow()) TRACE("Has head arrow differs");
  if ( lhs.HasTailArrow() != rhs.HasTailArrow()) TRACE("Has tail arrow differs");
  #endif
  return
       *lhs.GetConcept()   == *rhs.GetConcept()
    && *lhs.GetFrom()      == *rhs.GetFrom()
    && *lhs.GetTo()        == *rhs.GetTo()
    &&  lhs.GetX()         == rhs.GetX()
    &&  lhs.GetY()         == rhs.GetY()
    &&  lhs.HasHeadArrow() == rhs.HasHeadArrow()
    &&  lhs.HasTailArrow() == rhs.HasTailArrow();
}

bool ribi::cmap::operator!=(const cmap::Edge& lhs, const cmap::Edge& rhs)
{
  return !(lhs == rhs);
}
