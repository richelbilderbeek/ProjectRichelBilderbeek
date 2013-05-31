#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif

//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#include "pvdbedge.h"


#include <boost/lexical_cast.hpp>
#include <QRegExp>
#include "pvdbconcept.h"
#include "pvdbedgefactory.h"
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
  const int from,
  const bool tail_arrow,
  const int to,
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
  assert(from >= 0);
  assert(to >= 0);
  assert(from != to);
  assert(m_concept);
}

const boost::shared_ptr<pvdb::Edge> pvdb::Edge::FromXml(const std::string& s)
{
  assert(s.size() >= 13);
  assert(s.substr(0,6) == std::string("<edge>"));
  assert(s.substr(s.size() - 7,7) == std::string("</edge>"));
  //m_concept
  boost::shared_ptr<pvdb::Concept> concept;
  {
    const std::vector<std::string> v = pvdb::GetRegexMatches(s,QRegExp("(<concept>.*</concept>)"));
    assert(v.size() == 1);
    concept = Concept::FromXml(v[0]);
  }
  //m_from
  int from = -1;
  {
    const std::vector<std::string> v = pvdb::GetRegexMatches(s,QRegExp("(<from>.*</from>)"));
    assert(v.size() == 1);
    from = boost::lexical_cast<int>(StripXmlTag(v[0]));
  }
  //m_head_arrow
  bool head_arrow = false;
  {
    const std::vector<std::string> v = pvdb::GetRegexMatches(s,QRegExp("(<head_arrow>.*</head_arrow>)"));
    assert(v.size() == 1);
    head_arrow = boost::lexical_cast<bool>(StripXmlTag(v[0]));
  }
  //m_tail_arrow
  bool tail_arrow = false;
  {
    const std::vector<std::string> v = pvdb::GetRegexMatches(s,QRegExp("(<tail_arrow>.*</tail_arrow>)"));
    assert(v.size() == 1);
    tail_arrow = boost::lexical_cast<bool>(StripXmlTag(v[0]));
  }
  //m_to
  int to = -1;
  {
    const std::vector<std::string> v = pvdb::GetRegexMatches(s,QRegExp("(<to>.*</to>)"));
    assert(v.size() == 1);
    to = boost::lexical_cast<int>(StripXmlTag(v[0]));
  }
  //m_x
  double x = 0.0;
  {
    const std::vector<std::string> v = pvdb::GetRegexMatches(s,QRegExp("(<x>.*</x>)"));
    assert(v.size() == 1);
    x = boost::lexical_cast<double>(StripXmlTag(v[0]));
  }
  //m_y
  double y = 0.0;
  {
    const std::vector<std::string> v = pvdb::GetRegexMatches(s,QRegExp("(<y>.*</y>)"));
    assert(v.size() == 1);
    y = boost::lexical_cast<double>(StripXmlTag(v[0]));
  }

  const boost::shared_ptr<pvdb::Edge> edge(new Edge(concept,x,y,from,tail_arrow,to,head_arrow));
  assert(edge);
  return edge;
}

const std::vector<boost::shared_ptr<pvdb::Edge> > pvdb::Edge::GetTests()
{
  const auto test_concepts = ConceptFactory::GetTests();

  std::vector<boost::shared_ptr<pvdb::Edge> > result;

  std::for_each(test_concepts.begin(),test_concepts.end(),
    [&result](const boost::shared_ptr<pvdb::Concept>& concept)
    {
      {
        const boost::shared_ptr<pvdb::Edge> edge(new Edge(concept,1.2,3.4,0,false,1,true));
        result.push_back(edge);
      }
      /*
      {
        const boost::shared_ptr<pvdb::Edge> edge(new Edge(concept,0,2,true));
        result.push_back(edge);
      }
      {
        const boost::shared_ptr<pvdb::Edge> edge(new Edge(concept,0,3,true));
        result.push_back(edge);
      }
      {
        const boost::shared_ptr<pvdb::Edge> edge(new Edge(concept,1,2,false));
        result.push_back(edge);
      }
      {
        const boost::shared_ptr<pvdb::Edge> edge(new Edge(concept,1,3,false));
        result.push_back(edge);
      }
      {
        const boost::shared_ptr<pvdb::Edge> edge(new Edge(concept,2,3,false));
        result.push_back(edge);
      }
      */
    }
  );
  return result;
}

void pvdb::Edge::SetFrom(const int from)
{
  assert(from >= 0);
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
    m_signal_changed(this);
  }
}

void pvdb::Edge::SetTailArrow(const bool has_tail_arrow)
{
  if (m_tail_arrow != has_tail_arrow)
  {
    m_tail_arrow = has_tail_arrow;
    m_signal_changed(this);
  }
}

void pvdb::Edge::SetTo(const int to)
{
  assert(to >= 0);
  if (m_to != to)
  {
    m_to = to;
    m_signal_changed(this);
  }
}

void pvdb::Edge::Test()
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  //Test member variables
  TRACE("Started pvdb::Edge::Test");
  {
    const std::vector<boost::shared_ptr<const pvdb::Edge> > v = AddConst(Edge::GetTests());
    std::for_each(v.begin(),v.end(),
      [](const boost::shared_ptr<const pvdb::Edge>& edge)
      {
        //Test copy constructor
        assert(edge);
        const boost::shared_ptr<const pvdb::Edge> c = pvdb::EdgeFactory::DeepCopy(edge);
        assert(c);
        assert(edge == c); assert(c == edge);
        const std::string s = ToXml(c);
        const boost::shared_ptr<pvdb::Edge> d = FromXml(s);
        assert(c == d);
      }
    );
  }
  TRACE("Edge::Test finished successfully");
}

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
