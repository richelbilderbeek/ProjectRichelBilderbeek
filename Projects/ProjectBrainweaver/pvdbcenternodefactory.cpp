#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "pvdbcenternodefactory.h"
#include "pvdbcenternode.h"
#include "pvdbconcept.h"
#include "pvdbconceptfactory.h"
#pragma GCC diagnostic pop

const boost::shared_ptr<ribi::pvdb::CenterNode> ribi::pvdb::CenterNodeFactory::Create(
  const boost::shared_ptr<ribi::pvdb::Concept>& concept,
  const double x,
  const double y)
{
  assert(concept);
  boost::shared_ptr<pvdb::CenterNode> node(
    new pvdb::CenterNode(
      concept,x,y
    )
  );
  assert(node);
  assert(IsEqual(*concept,*node->GetConcept()));
  assert(node->GetX() == x);
  assert(node->GetY() == y);
  return node;
}

const boost::shared_ptr<ribi::pvdb::CenterNode> ribi::pvdb::CenterNodeFactory::Create(
  const std::string& name,
  const std::vector<std::pair<std::string,Competency> >& examples,
  const double x,
  const double y)
{
  boost::shared_ptr<pvdb::CenterNode> node(
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
const boost::shared_ptr<ribi::pvdb::CenterNode> ribi::pvdb::CenterNodeFactory::DeepCopy(
  const boost::shared_ptr<const pvdb::CenterNode>& node)
{
  assert(node);
  assert(node->GetConcept());
  const boost::shared_ptr<ribi::pvdb::Concept> new_concept
    = ConceptFactory::DeepCopy(node->GetConcept());
  assert(new_concept);
  assert(IsEqual(*node->GetConcept(),*new_concept));
  const boost::shared_ptr<pvdb::CenterNode> new_node
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
