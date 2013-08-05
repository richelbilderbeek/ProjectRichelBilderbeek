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

} //~namespace pvdb
