#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif

//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#include "pvdbrating.h"

#include <cassert>
#include <boost/numeric/conversion/cast.hpp>

#include "pvdbconceptmap.h"
#include "pvdbnode.h"
#include "pvdbconcept.h"
#include "pvdbexamples.h"

int pvdb::Rating::SuggestComplexity(const int n_edges, const int n_examples)
{
  const int complexity
    = n_edges == 0  || (n_edges == 1 && n_examples == 0)
    ? 0
    : (n_edges == 1 && n_examples > 0) || (n_edges == 2 && n_examples == 0)
      ? 1
      : 2;
  return complexity;
}

int pvdb::Rating::SuggestComplexity(const boost::shared_ptr<const pvdb::ConceptMap> sub_concept_map)
{
  assert(sub_concept_map);
  const int n_edges = boost::numeric_cast<int>(sub_concept_map->GetEdges().size());
  assert(!sub_concept_map->GetNodes().empty());
  assert(sub_concept_map->GetNodes().at(0)->GetConcept());
  assert(sub_concept_map->GetNodes().at(0)->GetConcept()->GetExamples());
  const int n_examples
    = boost::numeric_cast<int>(
      sub_concept_map->GetNodes().at(0)->GetConcept()->GetExamples()->Get().size()
    );
  return SuggestComplexity(n_edges,n_examples);
}

int pvdb::Rating::SuggestConcreteness(const int n_examples)
{
  const int concreteness
    = n_examples < 2
    ? 0
    : n_examples > 1 && n_examples < 4
      ? 1
      : 2;
  return concreteness;
}

int pvdb::Rating::SuggestConcreteness(const boost::shared_ptr<const pvdb::ConceptMap> sub_concept_map)
{
  assert(sub_concept_map);
  assert(!sub_concept_map->GetNodes().empty());
  assert(sub_concept_map->GetNodes().at(0)->GetConcept());
  assert(sub_concept_map->GetNodes().at(0)->GetConcept()->GetExamples());
  const int n_examples
    = boost::numeric_cast<int>(
      sub_concept_map->GetNodes().at(0)->GetConcept()->GetExamples()->Get().size()
    );
  return SuggestConcreteness(n_examples);
}

int pvdb::Rating::SuggestSpecificity(const int n_examples)
{
  const int specificity = SuggestConcreteness(n_examples);
  return specificity;
}

int pvdb::Rating::SuggestSpecificity(const boost::shared_ptr<const pvdb::ConceptMap> sub_concept_map)
{
  assert(sub_concept_map);
  assert(!sub_concept_map->GetNodes().empty());
  assert(sub_concept_map->GetNodes().at(0)->GetConcept());
  assert(sub_concept_map->GetNodes().at(0)->GetConcept()->GetExamples());
  const int n_examples
    = boost::numeric_cast<int>(
      sub_concept_map->GetNodes().at(0)->GetConcept()->GetExamples()->Get().size()
    );
  return SuggestSpecificity(n_examples);
}
