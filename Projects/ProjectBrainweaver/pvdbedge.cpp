#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif

//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#include "pvdbedge.h"

#ifdef COMPILER_SUPPORTS_THREADS_20130507
#include <thread>
#endif

#include <boost/lexical_cast.hpp>
#include <QRegExp>
#include "pvdbconcept.h"
#include "pvdbedgefactory.h"
#include "pvdbnode.h"
#include "pvdbconceptfactory.h"
#include "pvdbhelper.h"
#include "trace.h"

#ifdef PVDB_KEEP_NAMESPACE_IN_CPP_FILES
namespace pvdb {
#endif

pvdb::Edge::Edge(
  const boost::shared_ptr<pvdb::Concept> & concept,
  const double concept_x,
  const double concept_y,
  const boost::shared_ptr<pvdb::Node> from,
  const bool tail_arrow,
  const boost::shared_ptr<pvdb::Node> to,
  const bool head_arrow)
  : m_concept(concept),
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
}


void pvdb::Edge::SetFrom(const boost::shared_ptr<pvdb::Node> from)
{
  assert(from);
  if (m_from != from)
  {
    m_from = from;
    m_signal_changed(this);
  }
}

void pvdb::Edge::SetHeadArrow(const bool has_head_arrow)
{
  if (m_head_arrow != has_head_arrow)
  {
    m_head_arrow = has_head_arrow;
    //m_signal_changed(this); //2013-04-15 FIX?
  }
}

void pvdb::Edge::SetTailArrow(const bool has_tail_arrow)
{
  if (m_tail_arrow != has_tail_arrow)
  {
    m_tail_arrow = has_tail_arrow;
    //m_signal_changed(this); //2013-04-15 FIX?
  }
}

void pvdb::Edge::SetTo(const boost::shared_ptr<pvdb::Node> to)
{
  assert(to);
  if (m_to != to)
  {
    m_to = to;

    m_signal_changed(this);
  }
}

#ifndef NDEBUG
void pvdb::Edge::Test()
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  #ifdef COMPILER_SUPPORTS_THREADS_20130507
  std::thread t(
    []
    {
  #endif
  //Test member variables
  TRACE("Started pvdb::Edge::Test");
  {
    const auto nodes = Node::GetTests();
    assert(nodes.size() >= 2);
    const auto node_from = nodes[0];
    const auto node_to   = nodes[1];
    for (const boost::shared_ptr<const pvdb::Edge>& edge: EdgeFactory::GetTests(node_from,node_to))
    {
      //Test copy constructor
      assert(edge);
      const boost::shared_ptr<const pvdb::Edge> c = pvdb::EdgeFactory::DeepCopy(edge,node_from,node_to);
      assert(c);
      assert(edge == c); assert(c == edge);
      const std::string s = ToXml(c);
      const boost::shared_ptr<pvdb::Edge> d = pvdb::EdgeFactory::FromXml(s,nodes);
      assert(c == d);
    }
  }
  TRACE("Edge::Test finished successfully");
  #ifdef COMPILER_SUPPORTS_THREADS_20130507
    }
  );
  t.detach();
  #endif
}
#endif

const std::string pvdb::Edge::ToXml(const boost::shared_ptr<const pvdb::Edge>& edge)
{
  std::stringstream s;
  s << "<edge>";
  s << Concept::ToXml(edge->GetConcept());
  s << "<from>" << edge->GetFrom() << "</from>";
  s << "<head_arrow>" << edge->HasHeadArrow() << "</head_arrow>";
  s << "<tail_arrow>" << edge->HasTailArrow() << "</tail_arrow>";
  s << "<to>" << edge->GetTo() << "</to>";
  s << "<x>" << edge->GetX() << "</x>";
  s << "<y>" << edge->GetY() << "</y>";
  s << "</edge>";

  const std::string r = s.str();
  assert(r.size() >= 13);
  assert(r.substr(0,6) == std::string("<edge>"));
  assert(r.substr(r.size() - 7,7) == std::string("</edge>"));

  return r;
}

#ifndef PVDB_KEEP_NAMESPACE_IN_CPP_FILES
namespace pvdb {
#endif

bool IsEqual(const pvdb::Edge& lhs, const pvdb::Edge& rhs)
{
  assert(lhs.GetConcept()); assert(rhs.GetConcept());
  return
       IsEqual(*lhs.GetConcept(),*rhs.GetConcept())
    && lhs.GetFrom()      == rhs.GetFrom()
    && lhs.GetTo()        == rhs.GetTo()
    && lhs.GetX()         == rhs.GetX()
    && lhs.GetY()         == rhs.GetY()
    && lhs.HasHeadArrow() == rhs.HasHeadArrow()
    && lhs.HasTailArrow() == rhs.HasTailArrow();
}

bool operator==(const boost::shared_ptr<const pvdb::Edge>& lhs, const boost::shared_ptr<const pvdb::Edge>& rhs)
{
  assert(lhs); assert(rhs);
  return IsEqual(*lhs,*rhs);
}

bool operator==(const boost::shared_ptr<const pvdb::Edge>& lhs, const boost::shared_ptr<pvdb::Edge>& rhs)
{
  return boost::shared_ptr<const pvdb::Edge>(lhs) == boost::shared_ptr<const pvdb::Edge>(rhs);
}

bool operator==(const boost::shared_ptr<pvdb::Edge>& lhs, const boost::shared_ptr<const pvdb::Edge>& rhs)
{
  return boost::shared_ptr<const pvdb::Edge>(lhs) == boost::shared_ptr<const pvdb::Edge>(rhs);
}

bool operator==(const boost::shared_ptr<pvdb::Edge>& lhs, const boost::shared_ptr<pvdb::Edge>& rhs)
{
  return boost::shared_ptr<const pvdb::Edge>(lhs) == boost::shared_ptr<const pvdb::Edge>(rhs);
}

bool operator!=(const boost::shared_ptr<const pvdb::Edge>& lhs, const boost::shared_ptr<const pvdb::Edge>& rhs)
{
  return !(lhs == rhs);
}

bool operator!=(const boost::shared_ptr<const pvdb::Edge>& lhs, const boost::shared_ptr<pvdb::Edge>& rhs)
{
  return boost::shared_ptr<const pvdb::Edge>(lhs) != boost::shared_ptr<const pvdb::Edge>(rhs);
}

bool operator!=(const boost::shared_ptr<pvdb::Edge>& lhs, const boost::shared_ptr<const pvdb::Edge>& rhs)
{
  return boost::shared_ptr<const pvdb::Edge>(lhs) != boost::shared_ptr<const pvdb::Edge>(rhs);
}

bool operator!=(const boost::shared_ptr<pvdb::Edge>& lhs, const boost::shared_ptr<pvdb::Edge>& rhs)
{
  return boost::shared_ptr<const pvdb::Edge>(lhs) != boost::shared_ptr<const pvdb::Edge>(rhs);
}

} //~namespace pvdb
