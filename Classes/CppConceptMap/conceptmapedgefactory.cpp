#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "conceptmapedgefactory.h"

#include <cassert>
#include <boost/lexical_cast.hpp>

#include "conceptmapconcept.h"
#include "conceptmapconceptfactory.h"
#include "conceptmapedge.h"
#include "conceptmapedgefactory.h"
#include "conceptmaphelper.h"
#include "trace.h"
#include "xml.h"
#pragma GCC diagnostic pop

const boost::shared_ptr<ribi::cmap::Edge> ribi::cmap::EdgeFactory::Create(
  const boost::shared_ptr<ribi::cmap::Concept>& concept,
  const double concept_x,
  const double concept_y,
  const boost::shared_ptr<ribi::cmap::Node> from,
  const bool tail_arrow,
  const boost::shared_ptr<ribi::cmap::Node> to,
  const bool head_arrow)
{
  assert(concept);
  assert(concept->GetExamples());
  assert(from);
  assert(to);
  assert(from != to);
  boost::shared_ptr<ribi::cmap::Edge> p(new Edge(concept,concept_x,concept_y,from,tail_arrow,to,head_arrow));
  assert(p);
  return p;
}

#ifndef NDEBUG
const boost::shared_ptr<ribi::cmap::Edge> ribi::cmap::EdgeFactory::DeepCopy(
  const boost::shared_ptr<const cmap::Edge> edge,
  const boost::shared_ptr<ribi::cmap::Node> from,
  const boost::shared_ptr<ribi::cmap::Node> to)
{
  assert(edge);
  assert(edge->GetConcept());
  assert(edge->GetConcept()->GetExamples());
  assert(from);
  assert(to);
  assert(from != to);
  const boost::shared_ptr<ribi::cmap::Concept> concept = ribi::cmap::ConceptFactory::DeepCopy(edge->GetConcept());
  assert(concept);
  const boost::shared_ptr<ribi::cmap::Edge> p = ribi::cmap::EdgeFactory::Create(
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

const boost::shared_ptr<ribi::cmap::Edge> ribi::cmap::EdgeFactory::FromXml(
  const std::string& s,
  const std::vector<boost::shared_ptr<ribi::cmap::Node> >& nodes)
{
  assert(s.size() >= 13);
  assert(s.substr(0,6) == std::string("<edge>"));
  assert(s.substr(s.size() - 7,7) == std::string("</edge>"));
  //m_concept
  boost::shared_ptr<ribi::cmap::Concept> concept;
  {
    const std::vector<std::string> v = cmap::GetRegexMatches(s,QRegExp("(<concept>.*</concept>)"));
    assert(v.size() == 1);
    concept = Concept::FromXml(v[0]);
  }
  //m_from
  int from = -1;
  {
    const std::vector<std::string> v = cmap::GetRegexMatches(s,QRegExp("(<from>.*</from>)"));
    assert(v.size() == 1);
    from = boost::lexical_cast<int>(ribi::xml::StripXmlTag(v[0]));
  }
  //m_head_arrow
  bool head_arrow = false;
  {
    const std::vector<std::string> v = cmap::GetRegexMatches(s,QRegExp("(<head_arrow>.*</head_arrow>)"));
    assert(v.size() == 1);
    head_arrow = boost::lexical_cast<bool>(ribi::xml::StripXmlTag(v[0]));
  }
  //m_tail_arrow
  bool tail_arrow = false;
  {
    const std::vector<std::string> v = cmap::GetRegexMatches(s,QRegExp("(<tail_arrow>.*</tail_arrow>)"));
    assert(v.size() == 1);
    tail_arrow = boost::lexical_cast<bool>(ribi::xml::StripXmlTag(v[0]));
  }
  //m_to
  int to = -1;
  {
    const std::vector<std::string> v = cmap::GetRegexMatches(s,QRegExp("(<to>.*</to>)"));
    assert(v.size() == 1);
    to = boost::lexical_cast<int>(ribi::xml::StripXmlTag(v[0]));
  }
  //m_x
  double x = 0.0;
  {
    const std::vector<std::string> v = cmap::GetRegexMatches(s,QRegExp("(<x>.*</x>)"));
    assert(v.size() == 1);
    x = boost::lexical_cast<double>(ribi::xml::StripXmlTag(v[0]));
  }
  //m_y
  double y = 0.0;
  {
    const std::vector<std::string> v = cmap::GetRegexMatches(s,QRegExp("(<y>.*</y>)"));
    assert(v.size() == 1);
    y = boost::lexical_cast<double>(ribi::xml::StripXmlTag(v[0]));
  }
  assert(from != to);
  assert(from < boost::numeric_cast<int>(nodes.size()));
  assert(to   < boost::numeric_cast<int>(nodes.size()));

  const boost::shared_ptr<ribi::cmap::Edge> edge(new Edge(concept,x,y,nodes[from],tail_arrow,nodes[to],head_arrow));
  assert(edge);
  return edge;
}

const std::vector<boost::shared_ptr<ribi::cmap::Edge> > ribi::cmap::EdgeFactory::GetTests(
    const boost::shared_ptr<ribi::cmap::Node> from,
    const boost::shared_ptr<ribi::cmap::Node> to)
{
  assert(from);
  assert(to);
  const auto test_concepts = ConceptFactory::GetTests();

  std::vector<boost::shared_ptr<ribi::cmap::Edge> > result;

  for(const boost::shared_ptr<ribi::cmap::Concept> concept: test_concepts)
  {
    {
      const boost::shared_ptr<ribi::cmap::Edge> edge(new Edge(concept,1.2,3.4,from,false,to,true));
      result.push_back(edge);
    }
    /*
    {
      const boost::shared_ptr<ribi::cmap::Edge> edge(new Edge(concept,0,2,true));
      result.push_back(edge);
    }
    {
      const boost::shared_ptr<ribi::cmap::Edge> edge(new Edge(concept,0,3,true));
      result.push_back(edge);
    }
    {
      const boost::shared_ptr<ribi::cmap::Edge> edge(new Edge(concept,1,2,false));
      result.push_back(edge);
    }
    {
      const boost::shared_ptr<ribi::cmap::Edge> edge(new Edge(concept,1,3,false));
      result.push_back(edge);
    }
    {
      const boost::shared_ptr<ribi::cmap::Edge> edge(new Edge(concept,2,3,false));
      result.push_back(edge);
    }
    */
  }
  return result;
}
