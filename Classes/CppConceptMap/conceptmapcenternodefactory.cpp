#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "conceptmapcenternodefactory.h"
#include "conceptmapcenternode.h"
#include "conceptmapconcept.h"
#include "conceptmapconceptfactory.h"
#pragma GCC diagnostic pop

const boost::shared_ptr<ribi::cmap::CenterNode> ribi::cmap::CenterNodeFactory::Create(
  const boost::shared_ptr<ribi::cmap::Concept>& concept,
  const double x,
  const double y)
{
  assert(concept);
  boost::shared_ptr<cmap::CenterNode> node(
    new cmap::CenterNode(
      concept,x,y
    )
  );
  assert(node);
  assert(operator==(*concept,*node->GetConcept()));
  assert(node->GetX() == x);
  assert(node->GetY() == y);
  return node;
}

const boost::shared_ptr<ribi::cmap::CenterNode> ribi::cmap::CenterNodeFactory::Create(
  const std::string& name,
  const std::vector<std::pair<std::string,Competency> >& examples,
  const double x,
  const double y)
{
  boost::shared_ptr<cmap::CenterNode> node(
    new CenterNode(
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
const boost::shared_ptr<ribi::cmap::CenterNode> ribi::cmap::CenterNodeFactory::DeepCopy(
  const boost::shared_ptr<const cmap::CenterNode>& node)
{
  assert(node);
  assert(node->GetConcept());
  const boost::shared_ptr<ribi::cmap::Concept> new_concept
    = ConceptFactory::DeepCopy(node->GetConcept());
  assert(new_concept);
  assert(operator==(*node->GetConcept(),*new_concept));
  const boost::shared_ptr<cmap::CenterNode> new_node
    = Create(new_concept,
      node->GetX(),
      node->GetY()
    );
  assert(new_node);
  assert(new_node->GetConcept());
  assert(operator==(*node,*new_node));
  return new_node;
}
#endif
