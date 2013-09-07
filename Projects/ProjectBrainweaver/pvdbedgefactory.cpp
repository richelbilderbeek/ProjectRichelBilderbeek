#include "pvdbedgefactory.h"

#include <cassert>
#include <boost/lexical_cast.hpp>

#include "pvdbconcept.h"
#include "pvdbconceptfactory.h"
#include "pvdbedge.h"
#include "pvdbedgefactory.h"
#include "pvdbhelper.h"
#include "trace.h"

const boost::shared_ptr<ribi::pvdb::Edge> ribi::pvdb::EdgeFactory::Create(
  const boost::shared_ptr<ribi::pvdb::Concept>& concept,
  const double concept_x,
  const double concept_y,
  const boost::shared_ptr<ribi::pvdb::Node> from,
  const bool tail_arrow,
  const boost::shared_ptr<ribi::pvdb::Node> to,
  const bool head_arrow)
{
  assert(concept);
  assert(concept->GetExamples());
  assert(from);
  assert(to);
  assert(from != to);
  boost::shared_ptr<ribi::pvdb::Edge> p(new Edge(concept,concept_x,concept_y,from,tail_arrow,to,head_arrow));
  assert(p);
  return p;
}

#ifndef NDEBUG
const boost::shared_ptr<ribi::pvdb::Edge> ribi::pvdb::EdgeFactory::DeepCopy(
  const boost::shared_ptr<const pvdb::Edge> edge,
  const boost::shared_ptr<ribi::pvdb::Node> from,
  const boost::shared_ptr<ribi::pvdb::Node> to)
{
  assert(edge);
  assert(edge->GetConcept());
  assert(edge->GetConcept()->GetExamples());
  assert(from);
  assert(to);
  assert(from != to);
  const boost::shared_ptr<ribi::pvdb::Concept> concept = ribi::pvdb::ConceptFactory::DeepCopy(edge->GetConcept());
  assert(concept);
  const boost::shared_ptr<ribi::pvdb::Edge> p = ribi::pvdb::EdgeFactory::Create(
    concept,
    edge->GetX(),
    edge->GetY(),
    from,
    edge->HasTailArrow(),
    to,
    edge->HasHeadArrow()
  );
  assert(p);
  assert(IsEqual(*edge,*p));
  return p;
}
#endif

const boost::shared_ptr<ribi::pvdb::Edge> ribi::pvdb::EdgeFactory::FromXml(
  const std::string& s,
  const std::vector<boost::shared_ptr<ribi::pvdb::Node> >& nodes)
{
  assert(s.size() >= 13);
  assert(s.substr(0,6) == std::string("<edge>"));
  assert(s.substr(s.size() - 7,7) == std::string("</edge>"));
  //m_concept
  boost::shared_ptr<ribi::pvdb::Concept> concept;
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
  assert(from != to);
  assert(from < boost::numeric_cast<int>(nodes.size()));
  assert(to   < boost::numeric_cast<int>(nodes.size()));

  const boost::shared_ptr<ribi::pvdb::Edge> edge(new Edge(concept,x,y,nodes[from],tail_arrow,nodes[to],head_arrow));
  assert(edge);
  return edge;
}

const std::vector<boost::shared_ptr<ribi::pvdb::Edge> > ribi::pvdb::EdgeFactory::GetTests(
    const boost::shared_ptr<ribi::pvdb::Node> from,
    const boost::shared_ptr<ribi::pvdb::Node> to)
{
  assert(from);
  assert(to);
  const auto test_concepts = ConceptFactory::GetTests();

  std::vector<boost::shared_ptr<ribi::pvdb::Edge> > result;

  for(const boost::shared_ptr<ribi::pvdb::Concept> concept: test_concepts)
  {
    {
      const boost::shared_ptr<ribi::pvdb::Edge> edge(new Edge(concept,1.2,3.4,from,false,to,true));
      result.push_back(edge);
    }
    /*
    {
      const boost::shared_ptr<ribi::pvdb::Edge> edge(new Edge(concept,0,2,true));
      result.push_back(edge);
    }
    {
      const boost::shared_ptr<ribi::pvdb::Edge> edge(new Edge(concept,0,3,true));
      result.push_back(edge);
    }
    {
      const boost::shared_ptr<ribi::pvdb::Edge> edge(new Edge(concept,1,2,false));
      result.push_back(edge);
    }
    {
      const boost::shared_ptr<ribi::pvdb::Edge> edge(new Edge(concept,1,3,false));
      result.push_back(edge);
    }
    {
      const boost::shared_ptr<ribi::pvdb::Edge> edge(new Edge(concept,2,3,false));
      result.push_back(edge);
    }
    */
  }
  return result;
}
