#include "pvdbcenternodefactory.h"
#include "pvdbcenternode.h"
#include "pvdbconcept.h"
#include "pvdbconceptfactory.h"

namespace pvdb {

const boost::shared_ptr<pvdb::CenterNode> CenterNodeFactory::Create(
  const boost::shared_ptr<pvdb::Concept>& concept,
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

const boost::shared_ptr<pvdb::CenterNode> CenterNodeFactory::Create(
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
const boost::shared_ptr<pvdb::CenterNode> CenterNodeFactory::DeepCopy(
  const boost::shared_ptr<const pvdb::CenterNode>& node)
{
  assert(node);
  assert(node->GetConcept());
  const boost::shared_ptr<pvdb::Concept> new_concept
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

} //~namespace pvdb
