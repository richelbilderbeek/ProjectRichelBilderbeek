#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "conceptmapnodefactory.h"

#include "conceptmapnode.h"
#include "conceptmapconcept.h"
#include "conceptmapconceptfactory.h"
#include "trace.h"
#pragma GCC diagnostic pop

const boost::shared_ptr<ribi::cmap::Node> ribi::cmap::NodeFactory::Create(
  const boost::shared_ptr<ribi::cmap::Concept>& concept,
  const double x,
  const double y)
{
  assert(concept);
  boost::shared_ptr<ribi::cmap::Node> node(
    new cmap::Node(
      concept,x,y
    )
  );
  assert(node);
  assert(IsEqual(*concept,*node->GetConcept()));
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
  boost::shared_ptr<ribi::cmap::Node> node(
    new Node(
      ConceptFactory::Create(name,examples),
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
  const boost::shared_ptr<ribi::cmap::Concept> new_concept
    = ConceptFactory::DeepCopy(node->GetConcept());
  assert(new_concept);
  assert(IsEqual(*node->GetConcept(),*new_concept));
  const boost::shared_ptr<ribi::cmap::Node> new_node
    = Create(new_concept,
      node->GetX(),
      node->GetY()
    );
  assert(new_node);
  assert(new_node->GetConcept());
  assert(IsEqual(*node,*new_node));
  return new_node;
}
#endif


const std::vector<boost::shared_ptr<ribi::cmap::Node> > ribi::cmap::NodeFactory::GetTests()
{
  std::vector<boost::shared_ptr<ribi::cmap::Node> > nodes;
  const auto v = ConceptFactory::GetTests();
  std::transform(v.begin(),v.end(),std::back_inserter(nodes),
    [](const boost::shared_ptr<ribi::cmap::Concept>& c)
    {
      static int x = 0;
      static int y = 1;
      boost::shared_ptr<ribi::cmap::Node> p(new Node(c,x,y));
      ++x;
      ++y;
      assert(p);
      return p;
    }
  );
  return nodes;
}
