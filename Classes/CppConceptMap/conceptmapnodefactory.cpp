#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "conceptmapnodefactory.h"

#include "conceptmapcenternode.h"
#include "conceptmapcenternodefactory.h"
#include "conceptmaphelper.h"
#include "conceptmapnode.h"
#include "conceptmapconcept.h"
#include "conceptmapconceptfactory.h"
#include "trace.h"
#include "xml.h"
#pragma GCC diagnostic pop

const boost::shared_ptr<ribi::cmap::Node> ribi::cmap::NodeFactory::Create(
  const boost::shared_ptr<ribi::cmap::Concept>& concept,
  const double x,
  const double y)
{
  assert(concept);
  const boost::shared_ptr<Node> node(
    new Node(concept,x,y)
  );
  assert(node);
  assert(*concept == *node->GetConcept());
  assert(node->GetX() == x);
  assert(node->GetY() == y);
  return node;
}

const boost::shared_ptr<ribi::cmap::Node> ribi::cmap::NodeFactory::Create(
  const std::string& name,
  const std::vector<std::pair<std::string,Competency> >& examples,
  const double x,
  const double y)
{
  boost::shared_ptr<Node> node(
    new Node(
      ConceptFactory().Create(name,examples),
      x,
      y
    )
  );
  assert(node);
  assert(node->GetConcept());
  assert(node->GetX() == x);
  assert(node->GetY() == y);
  return node;
}

#ifndef NDEBUG
const boost::shared_ptr<ribi::cmap::Node> ribi::cmap::NodeFactory::DeepCopy(
  const boost::shared_ptr<const cmap::Node>& node)
{
  assert(node);
  assert(node->GetConcept());
  const boost::shared_ptr<Concept> new_concept
    = ConceptFactory().DeepCopy(node->GetConcept());
  assert(new_concept);
  assert(*node->GetConcept() == *new_concept);
  const boost::shared_ptr<Node> new_node
    = Create(new_concept,
      node->GetX(),
      node->GetY()
    );
  assert(new_node);
  assert(new_node->GetConcept());
  assert(*node == *new_node);
  return new_node;
}
#endif

const boost::shared_ptr<ribi::cmap::Node> ribi::cmap::NodeFactory::FromXml(const std::string& s)
{
  {
    const boost::shared_ptr<CenterNode> center_node {
      CenterNodeFactory().FromXml(s)
    };
    if (center_node) { return center_node; }
  }

  const bool verbose = false;
  if (s.size() < 13)
  {
    if (verbose) TRACE("string too short");
    return nullptr;

  }
  if (s.substr(0,6) != std::string("<node>"))
  {
    if (verbose) TRACE("incorrect starting tag");
    return nullptr;
  }
  if (s.substr(s.size() - 7,7) != std::string("</node>"))
  {
    if (verbose) TRACE("incorrect ending tag");
    return nullptr;
  }

  //m_concept
  boost::shared_ptr<Concept> concept;
  {
    const std::vector<std::string> v = GetRegexMatches(s,QRegExp("(<concept>.*</concept>)"));
    assert(v.size() == 1);
    concept = ConceptFactory().FromXml(v[0]);
  }
  //m_x
  double x = 0.0;
  {
    const std::vector<std::string> v = GetRegexMatches(s,QRegExp("(<x>.*</x>)"));
    assert(v.size() == 1);
    x = boost::lexical_cast<double>(ribi::xml::StripXmlTag(v[0]));
  }
  //m_x
  double y = 0.0;
  {
    const std::vector<std::string> v = GetRegexMatches(s,QRegExp("(<y>.*</y>)"));
    assert(v.size() == 1);
    y = boost::lexical_cast<double>(ribi::xml::StripXmlTag(v[0]));
  }
  assert(concept);
  const boost::shared_ptr<Node> node(new Node(concept,x,y));
  assert(node);
  assert(node->ToXml() == s);
  return node;
}

const std::vector<boost::shared_ptr<ribi::cmap::Node> > ribi::cmap::NodeFactory::GetTests()
{
  std::vector<boost::shared_ptr<ribi::cmap::Node> > nodes;
  const auto v = ConceptFactory().GetTests();
  std::transform(v.begin(),v.end(),std::back_inserter(nodes),
    [](const boost::shared_ptr<ribi::cmap::Concept>& c)
    {
      static int x = 0;
      static int y = 1;
      const boost::shared_ptr<Node> p(new Node(c,x,y));
      ++x;
      ++y;
      assert(p);
      return p;
    }
  );
  return nodes;
}
