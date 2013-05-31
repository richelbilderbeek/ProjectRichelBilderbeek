#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif

//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#include "pvdbedgefactory.h"

#include <cassert>
#include "pvdbconcept.h"
#include "pvdbconceptfactory.h"
#include "pvdbedge.h"
#include "pvdbedgefactory.h"

#ifdef PVDB_KEEP_NAMESPACE_IN_CPP_FILES
namespace pvdb {
#endif

const boost::shared_ptr<pvdb::Edge> pvdb::EdgeFactory::Create(
  const boost::shared_ptr<pvdb::Concept>& concept,
  const double concept_x,
  const double concept_y,
  const int from,
  const bool tail_arrow,
  const int to,
  const bool head_arrow)
{
  assert(concept);
  assert(concept->GetExamples());
  boost::shared_ptr<pvdb::Edge> p(new Edge(concept,concept_x,concept_y,from,tail_arrow,to,head_arrow));
  assert(p);
  return p;
}

const boost::shared_ptr<pvdb::Edge> pvdb::EdgeFactory::DeepCopy(
  const boost::shared_ptr<const pvdb::Edge> edge)
{
  assert(edge);
  assert(edge->GetConcept());
  assert(edge->GetConcept()->GetExamples());
  const boost::shared_ptr<pvdb::Concept> concept = pvdb::ConceptFactory::DeepCopy(edge->GetConcept());
  assert(concept);
  const boost::shared_ptr<pvdb::Edge> p = pvdb::EdgeFactory::Create(
    concept,
    edge->GetX(),
    edge->GetY(),
    edge->GetFrom(),
    edge->HasTailArrow(),
    edge->GetTo(),
    edge->HasHeadArrow()
  );
  assert(p);
  assert(IsEqual(*edge,*p));
  return p;
}

const std::vector<boost::shared_ptr<pvdb::Edge> > pvdb::EdgeFactory::GetTests()
{
  std::vector<boost::shared_ptr<pvdb::Edge> > edges;
  const auto v = ConceptFactory::GetTests();
  std::transform(v.begin(),v.end(),std::back_inserter(edges),
    [](const boost::shared_ptr<pvdb::Concept>& c)
    {
      static int x = 0;
      static int y = 1;
      boost::shared_ptr<pvdb::Edge> p(new Edge(c,x,y,0,false,1,true));
      ++x;
      ++y;
      assert(p);
      return p;
    }
  );
  return edges;
}


#ifdef PVDB_KEEP_NAMESPACE_IN_CPP_FILES
} //~namespace pvdb
#endif
