#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif

//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#include "pvdbnodefactory.h"

#include "pvdbnode.h"
#include "pvdbconcept.h"
#include "pvdbconceptfactory.h"
#include "trace.h"

#ifdef PVDB_KEEP_NAMESPACE_IN_CPP_FILES
namespace pvdb {
#endif

const boost::shared_ptr<pvdb::Node> pvdb::NodeFactory::Create(
  const boost::shared_ptr<pvdb::Concept>& concept,
  const double x,
  const double y)
{
  assert(concept);
  boost::shared_ptr<pvdb::Node> node(
    new pvdb::Node(
      concept,x,y
    )
  );
  assert(node);
  assert(IsEqual(*concept,*node->GetConcept()));
  assert(node->GetX() == x);
  assert(node->GetY() == y);
  return node;
}

const boost::shared_ptr<pvdb::Node> pvdb::NodeFactory::Create(
  const std::string& name,
  const std::vector<std::pair<std::string,Competency> >& examples,
  const double x,
  const double y)
{
  boost::shared_ptr<pvdb::Node> node(
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
const boost::shared_ptr<pvdb::Node> pvdb::NodeFactory::DeepCopy(
  const boost::shared_ptr<const pvdb::Node>& node)
{
  assert(node);
  assert(node->GetConcept());
  const boost::shared_ptr<pvdb::Concept> new_concept
    = ConceptFactory::DeepCopy(node->GetConcept());
  assert(new_concept);
  assert(IsEqual(*node->GetConcept(),*new_concept));
  const boost::shared_ptr<pvdb::Node> new_node
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


const std::vector<boost::shared_ptr<pvdb::Node> > pvdb::NodeFactory::GetTests()
{
  std::vector<boost::shared_ptr<pvdb::Node> > nodes;
  const auto v = ConceptFactory::GetTests();
  std::transform(v.begin(),v.end(),std::back_inserter(nodes),
    [](const boost::shared_ptr<pvdb::Concept>& c)
    {
      static int x = 0;
      static int y = 1;
      boost::shared_ptr<pvdb::Node> p(new Node(c,x,y));
      ++x;
      ++y;
      assert(p);
      return p;
    }
  );
  return nodes;
}

#ifdef PVDB_KEEP_NAMESPACE_IN_CPP_FILES
} //~namespace pvdb
#endif
